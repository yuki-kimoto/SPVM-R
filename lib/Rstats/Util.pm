package Rstats::Util;
use strict;
use warnings;

require Rstats;
use Scalar::Util ();
use B ();
use Carp 'croak';
use Rstats::Func;
use Rstats::Func::Vector;

my $type_level = {
  character => 6,
  complex => 5,
  double => 4,
  integer => 3,
  logical => 2,
  na => 1
};

sub higher_type {
  my ($type1, $type2) = @_;
  
  if ($type_level->{$type1} > $type_level->{$type2}) {
    return $type1;
  }
  else {
    return $type2;
  }
}

sub parse_index {
  my ($x1, $drop, @_indexs) = @_;
  
  my $x1_dim = $x1->dim_as_array->values;
  my @indexs;
  my @x2_dim;
  
  if (ref $_indexs[0] && Rstats::Func::is_array(undef(), $_indexs[0])
    && Rstats::Func::is_logical(undef(), $_indexs[0]) && Rstats::Func::dim(undef(), $_indexs[0])->length_value > 1) {
    my $x2 = $_indexs[0];
    my $x2_dim_values = Rstats::Func::dim(undef(), $x2)->values;
    my $x2_values = $x2->values;
    my $poss = [];
    for (my $i = 0; $i < @$x2_values; $i++) {
      next unless $x2_values->[$i];
      push @$poss, $i;
    }
    
    return ($poss, []);
  }
  else {
    for (my $i = 0; $i < @$x1_dim; $i++) {
      my $_index = $_indexs[$i];

      my $index = defined $_index ? Rstats::Func::to_c(undef(), $_index) : Rstats::Func::NULL();
      my $index_values = $index->values;
      if (@$index_values && !Rstats::Func::is_character(undef(), $index) && !Rstats::Func::is_logical(undef(), $index)) {
        my $minus_count = 0;
        for my $index_value (@$index_values) {
          if ($index_value == 0) {
            croak "0 is invalid index";
          }
          else {
            $minus_count++ if $index_value < 0;
          }
        }
        croak "Can't min minus sign and plus sign"
          if $minus_count > 0 && $minus_count != @$index_values;
        $index->{_minus} = 1 if $minus_count > 0;
      }
      
      if (!@{$index->values}) {
        my $index_values_new = [1 .. $x1_dim->[$i]];
        $index = Rstats::Func::new_integer(undef(), @$index_values_new);
      }
      elsif (Rstats::Func::is_character(undef(), $index)) {
        if (Rstats::Func::is_vector(undef(), $x1)) {
          my $index_new_values = [];
          for my $name (@{$index->values}) {
            my $i = 0;
            my $value;
            for my $x1_name (@{Rstats::Func::names(undef(), $x1)->values}) {
              if ($name eq $x1_name) {
                $value = $x1->values->[$i];
                last;
              }
              $i++;
            }
            croak "Can't find name" unless defined $value;
            push @$index_new_values, $value;
          }
          $indexs[$i] = Rstats::Func::new_integer(undef(), @$index_new_values);
        }
        elsif (Rstats::Func::is_matrix(undef(), $x1)) {
          
        }
        else {
          croak "Can't support name except vector and matrix";
        }
      }
      elsif (Rstats::Func::is_logical(undef(), $index)) {
        my $index_values_new = [];
        for (my $i = 0; $i < @{$index->values}; $i++) {
          push @$index_values_new, $i + 1 if $index_values->[$i];
        }
        $index = Rstats::Func::new_integer(undef(), @$index_values_new);
      }
      elsif ($index->{_minus}) {
        my $index_value_new = [];
        
        for my $k (1 .. $x1_dim->[$i]) {
          push @$index_value_new, $k unless grep { $_ == -$k } @{$index->values};
        }
        $index = Rstats::Func::new_integer(undef(), @$index_value_new);
      }

      push @indexs, $index;

      my $count = $index->vector->length_value;
      push @x2_dim, $count unless $count == 1 && $drop;
    }
    @x2_dim = (1) unless @x2_dim;
    
    my $index_values = [map { $_->values } @indexs];
    my $ords = cross_product($index_values);
    my @poss = map { Rstats::Util::index_to_pos($_, $x1_dim) } @$ords;
  
    return (\@poss, \@x2_dim, \@indexs);
  }
}

=head1 NAME

Rstats::Util - Utility class

=head1 FUNCTION

=head2 looks_like_na (xs)

=head2 looks_like_logical (xs)

=head2 looks_like_double (xs)

=head2 looks_like_integer (xs)

=head2 looks_like_complex (xs)

=head2 index_to_pos (xs)

=head2 pos_to_index (xs)

=head2 cross_product (xs)

1;

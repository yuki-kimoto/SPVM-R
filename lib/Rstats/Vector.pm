package Rstats::Vector;
use Object::Simple -base;

use Carp 'croak', 'carp';
use Rstats::VectorFunc;
use Rstats::Util;

use overload
  '""' => \&to_string;

sub to_string {
  my $self = shift;
  
  my @strs;
  my $values = $self->values;
  for my $value (@$values) {
    my $str;
    if (defined $value) {
      if ($self->is_character) {
        $str = $value . "";
      }
      elsif ($self->is_complex) {
        my $re = $value->{re};
        my $im = $value->{im};
        
        $str = "$re";
        $str .= '+' if $im >= 0;
        $str .= $im . 'i';
      }
      elsif ($self->is_double) {
        $str = $value . "";
      }
      elsif ($self->is_integer) {
        $str = $value . "";
      }
      elsif ($self->is_logical) {
        $str = $value ? 'TRUE' : 'FALSE'
      }
      else {
        croak "Invalid type";
      }
    }
    else {
      $str = 'NA';
    }
    push @strs, $str;
  }
  
  my $str_all = join ' ', @strs;
  
  return $str_all;
}

sub value { shift->values->[0] }

sub typeof { shift->type }

sub is_positive_infinite {
  my $self = shift;
  
  return Rstats::VectorFunc::new_logical($self->is_infinite->value && $self->value > 0);
}

sub is_negative_infinite {
  my $self = shift;
  
  return Rstats::VectorFunc::new_logical($self->is_infinite->value && $self->value < 0);
}

1;

=head1 NAME

Rstats::Vector - Vector

=heaa1 METHODS

=head2 values (xs)

=head2 is_character (xs)

=head2 is_complex (xs)

=head2 is_double (xs)

=head2 is_integer (xs)

=head2 is_numeric (xs)

=head2 is_logical (xs)

=head2 as_double (xs)

=head2 as_integer (xs)

=head2 as_numeric (xs)

=head2 as_complex (xs)

=head2 as_logical (xs)

=head2 type

=head2 re

=head2 im

=head2 flag

=head2  is_nan

=head2  is_infinite

=head2  is_finite


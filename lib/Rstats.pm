package Rstats;

our $VERSION = '0.01';

use Object::Simple -base;

use List::Util;
use Math::Trig ();
use Carp 'croak';
use Rstats;
use Rstats::Array;
use Rstats::Vector;
use Rstats::Complex;

my $r = Rstats->new;

sub names {
  my ($self, $vector, $names) = @_;
  
  $vector->names($names);
  
  return $self;
}

sub numeric {
  my ($self, $num) = @_;
  
  my $v = Rstats::Vector->new(values => [(0) x $num]);
  
  return $v;
}

sub matrix {
  my ($self, $data, $row_num, $col_num) = @_;
  
  croak "matrix method need data as frist argument"
    unless defined $data;
  
  my $length = $row_num * $col_num;
  
  my $values;
  unless (ref $data) {
    $values = [($data) x $length];
  }
  
  my $matrix = Rstats::Matrix->new(
    values => $values,
    type => 'matrix',
  );
  $matrix->dim([$row_num, $col_num]);
  
  return $matrix;
}

sub array {
  my ($self, $data) = @_;
  
  my $opt = ref $_[-1] eq 'HASH' ? pop @_ : {};
  my $array_class = $opt->{class} || 'Rstats::Array';
  
  my $array;
  if (ref $data eq 'ARRAY') {
    my $values = [];
    for my $a (@$data) {
      if (ref $a eq 'ARRAY') {
        push @$values, @$a;
      }
      elsif (ref $a && $a->isa('Rstats::Array')) {
        push @$values, @{$a->values};
      }
      else {
        push @$values, $a;
      }
    }
    $array = $array_class->new(values => $values);
  }
  elsif (ref $data) {
    $array = $data;
  }
  else {
    my $str = $data;
    my $by;
    if ($str =~ s/^(.+)\*//) {
      $by = $1;
    }
    
    my $from;
    my $to;
    if ($str =~ /(.+?):(.+)/) {
      $from = $1;
      $to = $2;
    }
    
    $array = $self->seq({from => $from, to => $to, by => $by});
  }
  
  my $dim = $opt->{dim};
  if ($dim) {
    if (ref $dim eq 'ARRAY') {
      $array->dim($self->c($dim));
    }
    elsif (ref $dim eq 'Rstats::Vector') {
      $array->dim($dim);
    }
    else {
      croak "dim option must be array reference or Rstats::Vector object";
    }
  }
  
  return $array;
}

sub paste {
  my $self = shift;

  # Option
  my $opt;
  if (ref $_[-1] eq 'HASH') {
    $opt = pop @_;
  }
  $opt ||= {};
  
  my $sep = $opt->{sep};
  $sep = ' ' unless defined $sep;
  
  my $str = shift;
  my $v1 = shift;
  
  my $v1_values = $v1->values;
  my $v2 = Rstats::Array->new;
  my $v2_values = $v2->values;
  push @$v2_values, "$str$sep$_" for @$v1_values;
  
  return $v2;
}

sub c {
  my ($self, $data) = @_;
  
  my $vector = $self->array($data, {class => 'Rstats::Vector'});
  
  return $vector;
}

sub seq {
  my $self = shift;
  
  # Option
  my $opt;
  if (ref $_[-1] eq 'HASH') {
    $opt = pop @_;
  }
  $opt ||= {};
  
  # From
  my $from = shift;
  $from = $opt->{from} unless defined $from;
  croak "seq function need from option" unless defined $from;
  
  # To
  my $to = shift;
  $to = $opt->{to} unless defined $to;
  
  # By
  my $by = $opt->{by};
  unless (defined $by) {
    if ($to >= $from) {
      $by = 1;
    }
    else {
      $by = -1;
    }
  }
  croak "by option should be except for 0" if $by == 0;
  
  # Length
  my $length = $opt->{length};
  
  if (defined $length) {
    my $values = [];
    push @$values, $from + $_ * $by for (0 .. $length - 1);
    return Rstats::Array->new(values => $values);
  }
  elsif (defined $to) {
    my $values = [];
    if ($to == $from) {
      return Rstats::Array->new(values => [$to]);
    }
    elsif ($to > $from) {
      if ($by < 0) {
        croak "by option is invalid number(seq function)";
      }
      
      my $value = $from;
      while ($value <= $to) {
        push @$values, $value;
        $value += $by;
      }
      return Rstats::Array->new(values => $values);
    }
    else {
      if ($by > 0) {
        croak "by option is invalid number(seq function)";
      }
      
      my $value = $from;
      while ($value >= $to) {
        push @$values, $value;
        $value += $by;
      }
      return Rstats::Array->new(values => $values);
    }
  }
  else {
    croak "seq function need to option or length option";
  }
}

sub rep {
  my $self = shift;

  # Option
  my $opt;
  if (ref $_[-1] eq 'HASH') {
    $opt = pop @_;
  }
  $opt ||= {};
  
  my $v1 = shift;
  my $times = $opt->{times} || 1;
  
  my $values = [];
  push @$values, @{$v1->values} for 1 .. $times;
  my $v2 = Rstats::Array->new(values => $values);
  
  return $v2;
}

sub max {
  my ($self, @vs) = @_;
  
  my @all_values = map { @{$_->values} } @vs;
  my $max = List::Util::max(@all_values);
  return $max;
}

sub min {
  my ($self, @vs) = @_;
  
  my @all_values = map { @{$_->values} } @vs;
  my $min = List::Util::min(@all_values);
  return $min;
}

sub pmax {
  my ($self, @vs) = @_;
  
  my @maxs;
  for my $v (@vs) {
    my $values = $v->values;
    for (my $i = 0; $i <@$values; $i++) {
      $maxs[$i] = $values->[$i]
        if !defined $maxs[$i] || $values->[$i] > $maxs[$i]
    }
  }
  
  my $v_max = Rstats::Array->new(values => \@maxs);
  
  return $v_max;
}

sub pmin {
  my ($self, @vs) = @_;
  
  my @mins;
  for my $v (@vs) {
    my $values = $v->values;
    for (my $i = 0; $i <@$values; $i++) {
      $mins[$i] = $values->[$i]
        if !defined $mins[$i] || $values->[$i] < $mins[$i]
    }
  }
  
  my $v_min = Rstats::Array->new(values => \@mins);
  
  return $v_min;
}

sub abs {
  my ($self, $data) = @_;
  
  if ($data->isa('Rstats::Array')) {
    my $tmp_v = $data * $data;
    my $abs = sqrt $self->sum($tmp_v);

    return $abs;
  }
  else {
    croak 'Not implemented';
  }
}

sub sum {
  my ($self, $data) = @_;
  
  if ($data->isa('Rstats::Array')) {
    my $sum;
    my $v = $data;
    my $v_values = $v->values;
    $sum = List::Util::sum(@$v_values);
    return $sum;
  }
  else {
    croak 'Not implemented';
  }
}

sub prod {
  my ($self, $data) = @_;
  
  if ($data->isa('Rstats::Array')) {
    my $prod;
    my $v = $data;
    my $v_values = $v->values;
    $prod = List::Util::product(@$v_values);
    return $prod;
  }
  else {
    croak 'Not implemented';
  }
}

sub mean {
  my ($self, $data) = @_;
  
  if ($data->isa('Rstats::Array')) {
    my $v = $data;
    my $mean = $self->sum($v) / $self->length($v);
    return $mean;
  }
  else {
    croak 'Not implemented';
  }
}

sub var {
  my ($self, $data) = @_;

  if ($data->isa('Rstats::Array')) {
    my $v = $data;
    
    my $var = $self->sum(($v - $self->mean($v)) ** 2) / ($self->length($v) - 1);
    return $var;
  }
  else {
    croak 'Not implemented';
  }
}

sub head {
  my $self = shift;

  my $opt = ref $_[-1] eq 'HASH' ? pop @_ : {};
  my $v1 = shift;
  
  my $n = $opt->{n};
  $n = 6 unless defined $n;
  
  my $values1 = $v1->{values};
  my $max = $v1->length < $n ? $v1->length : $n;
  my @values2;
  for (my $i = 0; $i < $max; $i++) {
    push @values2, $values1->[$i];
  }
  
  return $v1->new(values => \@values2);
}

sub tail {
  my $self = shift;
  my $array = shift;
  
  return $array->tail(@_);
}

sub length {
  my ($self, $array) = @_;
  
  return $array->length;
}

sub sort {
  my ($self, $data) = @_;
  
  if ($data->isa('Rstats::Array')) {
    my $v2 = Rstats::Array->new;
    my $sort;
    my $v1 = $data;
    my $v1_values = $v1->values;
    my $v1_values_sorted = [sort(@$v1_values)];
    $v2->values($v1_values_sorted);
    return $v2;
  }
  else {
    croak 'Not implemented';
  }
}

sub log {
  my ($self, $array) = @_;
  
  croak 'sqrt method must receive Rstats::Array based object'
    unless defined $array && $array->isa('Rstats::Array');
  
  return $self->_apply($array, sub { log $_[0] });
}

sub exp {
  my ($self, $array) = @_;
  
  croak 'sqrt method must receive Rstats::Array based object'
    unless defined $array && $array->isa('Rstats::Array');
  
  return $self->_apply($array, sub { exp $_[0] });
}

sub sin {
  my ($self, $array) = @_;
  
  croak 'sqrt method must receive Rstats::Array based object'
    unless defined $array && $array->isa('Rstats::Array');
  
  return $self->_apply($array, sub { sin $_[0] });
}

sub cos {
  my ($self, $array) = @_;
  
  croak 'sqrt method must receive Rstats::Array based object'
    unless defined $array && $array->isa('Rstats::Array');
  
  return $self->_apply($array, sub { cos $_[0] });
}

sub tan {
  my ($self, $array) = @_;
  
  croak 'sqrt method must receive Rstats::Array based object'
    unless defined $array && $array->isa('Rstats::Array');
  
  return $self->_apply($array, sub { Math::Trig::tan $_[0] });
}

sub sqrt {
  my ($self, $array) = @_;

  croak 'sqrt method must receive Rstats::Array based object'
    unless defined $array && $array->isa('Rstats::Array');
  
  return $self->_apply($array, sub { sqrt $_[0] });
}

sub _apply {
  my ($self, $array1, $cb) = @_;
  
  my $array2 = $array1->new;
  my $array1_values = $array1->values;
  my $array2_values = $array2->values;
  $array2_values->[$_] = $cb->($array1_values->[$_])
    for (0 .. @$array1_values - 1);
  return $array2;
}

sub range {
  my ($self, $array) = @_;
  
  croak 'range method must receive Rstats::Array based object'
    unless defined $array && $array->isa('Rstats::Array');
  
  my $min = $self->min($array);
  my $max = $self->max($array);
  
  return Rstats::Vector->new(values => [$min, $max]);
}

sub i {
  my $self = shift;
  
  my $i = Rstats::Complex->new(re => 0, im => 1);
  
  return $i;
}

1;

=head1 NAME

Rstats - R language build on Perl

=head1 SYNOPSYS

  my $r = Rstats->new;
  
  # Array
  my $v1 = $r->c([1, 2, 3]);
  my $v2 = $r->c([2, 3, 4]);
  my $v3 = $v1 + v2;

use Test::More 'no_plan';
use strict;
use warnings;

use Rstats::Class;
use Rstats::Func::Vector;

my $r = Rstats::Class->new;

# comparison operator
{
  # comparison operator - ==, true
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $ret = Rstats::Func::Vector::equal($z1, $z2);
    is($ret->value, 1);
  }
  # comparison operator - ==, false
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 1, im => 1});
    my $ret = Rstats::Func::Vector::equal($z1, $z2);
    is($ret->value, 0);
  }

  # comparison operator - !=, true
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    is(Rstats::Func::Vector::not_equal($z1, $z2)->value, 0);
  }
  
  # comparison operator - !=, false
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 1, im => 1});
    is(Rstats::Func::Vector::not_equal($z1, $z2)->value, 1);
  }

  # comparison operator - <, error
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    eval { my $result = Rstats::Func::Vector::less_than($z1, $z2) };
    like($@, qr/invalid/);
  }

  # comparison operator - <=, error
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    eval { my $result = Rstats::Func::Vector::less_than_or_equal($z1, $z2) };
    like($@, qr/invalid/);
  }

  # comparison operator - >, error
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    eval { my $result = Rstats::Func::Vector::more_than($z1, $z2) };
    like($@, qr/invalid/);
  }

  # comparison operator - >=, error
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    eval { my $result = Rstats::Func::Vector::more_than_or_equal($z1, $z2) };
    like($@, qr/invalid/);
  }
}

# to_string
{
  # to_string - basic
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    is("$z1", "1+2i");
  }
  
  # to_string - image number is 0
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 0});
    is("$z1", "1+0i");
  }
  
  # to_string - image number is minus
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => -1});
    is("$z1", "1-1i");
  }
}

# new
{
  # new
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    is($z1->value->{re}, 1);
    is($z1->value->{im}, 2);
  }
}

# operation
{
  # operation - negation
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::negation($z1);
    is($z2->value->{re}, -1);
    is($z2->value->{im}, -2);
  }
  
  # operation - add
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 3, im => 4});
    my $z3 = Rstats::Func::Vector::add($z1, $z2);
    is($z3->value->{re}, 4);
    is($z3->value->{im}, 6);
  }
  
  # operation - subtract
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 3, im => 4});
    my $z3 = Rstats::Func::Vector::subtract($z1, $z2);
    is($z3->value->{re}, -2);
    is($z3->value->{im}, -2);
  }
  
  # operation - multiply
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 3, im => 4});
    my $z3 = Rstats::Func::Vector::multiply($z1, $z2);
    is($z3->value->{re}, -5);
    is($z3->value->{im}, 10);
  }

  # operation - abs
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 3, im => 4});
    my $abs = Rstats::Func::Vector::abs($z1);
    is($abs->value, 5);
  }
  
  # operation - Conj
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $conj = Rstats::Func::Vector::Conj($z1);
    is($conj->value->{re}, 1);
    is($conj->value->{im}, -2);
  }
  
  # operation - divide
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 5, im => -6});
    my $z2 = Rstats::Func::Vector::new_complex({re => 3, im => 2});
    my $z3 = Rstats::Func::Vector::divide($z1, $z2);
    is($z3->value->{re}, 3/13);
    is($z3->value->{im}, -28/13);
  }

  # operation - pow
  {
    my $z1 = Rstats::Func::Vector::new_complex({re => 1, im => 2});
    my $z2 = Rstats::Func::Vector::new_complex({re => 3, im => 0});
    my $z3 = Rstats::Func::Vector::pow($z1, $z2);
    is($z3->value->{re}, -11);
    is($z3->value->{im}, -2);
  }
}

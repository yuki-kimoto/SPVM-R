use Test::More 'no_plan';
use strict;
use warnings;

use Rstats;
use Rstats;

my $r = Rstats->new;

# get
{
  # get - drop
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a3", "a1", "a2", "a3"));
    my $x2 = $x1->get($r->c(4, 6), {drop => $r->TRUE});
    ok($r->is->factor($x2));
    is_deeply($x2->values, [1, 2]);
    is_deeply($r->levels($x2)->values, ["a1", "a3"]);
  }
  
  # get - $r->factor
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a3", "a1", "a2", "a3"));
    my $x2 = $x1->get($r->c(4, 6));
    ok($r->is->factor($x2));
    is_deeply($x2->values, [1, 3]);
    is_deeply($r->levels($x2)->values, ["a1", "a2", "a3"]);
  }
  
  # get - ordered
  {
    my $x1 = $r->ordered($r->c("a1", "a2", "a3", "a1", "a2", "a3"));
    my $x2 = $x1->get($r->c(4, 6));
    ok($r->is->factor($x2));
    ok($r->is->ordered($x2));
    is_deeply($x2->values, [1, 3]);
    is_deeply($r->levels($x2)->values, ["a1", "a2", "a3"]);
  }
}

# set
{
  # set - basic
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a3", "a1", "a2", "a3"));
    $x1->at($r->c(3, 6))->set($r->c("a2", "a1"));
    is_deeply($x1->values, [1, 2, 2, 1, 2, 1]);
    is_deeply($r->levels($x1)->values, ["a1", "a2", "a3"]);
  }
}

# nlevels
{
  # nlevels - set values
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a1", "a2"));
    is_deeply($r->nlevels($x1)->values, [2]);
  }
  
  # nlevels - function
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a1", "a2"));
    is_deeply($r->nlevels($x1)->values, [2]);
  }
}

# levels
{
  # levels - set values
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a1", "a2"));
    $r->levels($x1, $r->c("A1", "A2"));
    is_deeply($r->levels($x1)->values, ["A1", "A2"]);
  }
  
  # levels - function
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a1", "a2"));
    $r->levels($x1, ($r->c("A1", "A2")));
    is_deeply($r->levels($x1)->values, ["A1", "A2"]);
  }
}

# interaction
{
  # interaction - drop
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a1", "a2"));
    my $x2 = $r->factor($r->c("b1", "b2"));
    my $x3 = $r->interaction($x1, $x2, {drop => $r->TRUE});
    ok($r->is->factor($x3));
    is_deeply($x3->values, [1, 2, 1, 2]);
    is_deeply($r->levels($x3)->values, ["a1.b1", "a2.b2"]);
  }
  
  # interaction - sep
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a1", "a2"));
    my $x2 = $r->factor($r->c("b1", "b2"));
    my $x3 = $r->interaction($x1, $x2, {sep => ":"});
    ok($r->is->factor($x3));
    is_deeply($x3->values, [1, 4, 1, 4]);
    is_deeply($r->levels($x3)->values, ["a1:b1", "a1:b2", "a2:b1", "a2:b2"]);
  }
  
  # interaction - tree elements
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a3"));
    my $x2 = $r->factor($r->c("b1", "b2"));
    my $x3 = $r->factor($r->c("c1"));
    my $x4 = $r->interaction($x1, $x2, $x3);
    ok($r->is->factor($x4));
    is_deeply($x4->values, [1, 4, 5]);
    is_deeply($r->levels($x4)->values, [
      "a1.b1.c1",
      "a1.b2.c1",
      "a2.b1.c1",
      "a2.b2.c1",
      "a3.b1.c1",
      "a3.b2.c1"
    ]);
  }

  # interaction - basic 2
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a3"));
    my $x2 = $r->factor($r->c("b1", "b2"));
    my $x3 = $r->interaction($x1, $x2);
    ok($r->is->factor($x3));
    is_deeply($x3->values, [1, 4, 5]);
    is_deeply($r->levels($x3)->values, ["a1.b1", "a1.b2", "a2.b1", "a2.b2", "a3.b1", "a3.b2"]);
  }
  
  # interaction - basic
  {
    my $x1 = $r->factor($r->c("a1", "a2", "a1", "a2"));
    my $x2 = $r->factor($r->c("b1", "b2"));
    my $x3 = $r->interaction($x1, $x2);
    ok($r->is->factor($x3));
    is_deeply($x3->values, [1, 4, 1, 4]);
    is_deeply($r->levels($x3)->values, ["a1.b1", "a1.b2", "a2.b1", "a2.b2"]);
  }
}

# gl
{
  # gl - n, k, length
  {
    my $x1 = $r->gl(2, 2, 10);
    ok($r->is->factor($x1));
    is_deeply($x1->values, [1, 1, 2, 2, 1, 1, 2, 2, 1, 1]);
  }
  
  # gl - n, k ,length, no fit length
  {
    my $x1 = $r->gl(3, 3, 10);
    ok($r->is->factor($x1));
    is_deeply($x1->values, [1, 1, 1, 2, 2, 2, 3, 3, 3, 1]);
  }

  # gl - n, k
  {
    my $x1 = $r->gl(3, 3);
    ok($r->is->factor($x1));
    is_deeply($x1->values, [1, 1, 1, 2, 2, 2, 3, 3, 3]);
    is_deeply($r->levels($x1)->values, ["1", "2", "3"]);
  }
  
  # gl - labels
  {
    my $x1 = $r->gl(3, 3, {labels => $r->c("a", "b", "c")});
    ok($r->is->factor($x1));
    is_deeply($x1->values, [1, 1, 1, 2, 2, 2, 3, 3, 3]);
    is_deeply($r->levels($x1)->values, ["a", "b", "c"]);
  }

  # gl - ordered
  {
    my $x1 = $r->gl(3, 3, {ordered => $r->TRUE});
    ok($r->is->factor($x1));
    ok($r->is->ordered($x1));
    is_deeply($x1->values, [1, 1, 1, 2, 2, 2, 3, 3, 3]);
    is_deeply($r->levels($x1)->values, ["1", "2", "3"]);
  }
}

# ordered
{
  # ordered - basic
  {
    my $x1 = $r->ordered($r->c("a", "b", "c", "a", "b", "c"));
    ok($r->is->ordered($x1));
    # ok($r->is->double($x1));
    ok($r->is->factor($x1));
    is_deeply($x1->values, [1, 2, 3, 1, 2 ,3]);
    is_deeply($r->levels($x1)->values, ["a", "b", "c"]);
  }
  # ordered - option
  {
    my $x1 = $r->ordered($r->c("a", "b", "c", "a", "b", "c"), {levels => $r->c("a", "b", "c")});
    ok($r->is->ordered($x1));
    # ok($r->is->double($x1));
    ok($r->is->factor($x1));
    is_deeply($x1->values, [1, 2, 3, 1, 2 ,3]);
    is_deeply($r->levels($x1)->values, ["a", "b", "c"]);
  }
}

# factor
{
  # factor - one element
  {
    my $x1 = $r->factor($r->c("a"));
    is_deeply($x1->values, [1]);
    is_deeply($r->levels($x1)->values, ["a"]);
  }
  
  # factor - as.numeri$r->c(levels(f))[f] 
  {
    my $x1 = $r->factor($r->c(2, 3, 4, 2, 3, 4));
    my $x1_levels = $r->levels($x1);
    my $x2_levels = $r->as->numeric($x1_levels);
    my $x3 = $x2_levels->get($x1);
    ok($r->is->numeric($x3));
    is_deeply($x3->values, [2, 3, 4, 2, 3, 4]);
  }
  
  # factor - labels
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"));
    my $x2 = $r->labels($x1);
    ok($r->is->string($x2));
    is_deeply($x2->values, ["a", "b", "c", "a", "b", "c"]);
  }
  
  # factor - as_string
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"));
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is_deeply($x2->values, ["a", "b", "c", "a", "b", "c"]);
  }
  
  # factor - as_complex
  {
    my $x1 = $r->factor($r->c("a", "b", "c"));
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is_deeply($x2->values, [{re => 1, im =>  0}, {re => 2, im => 0}, {re => 3, im => 0}]);
  }
  
  # factor - as_double
  {
    my $x1 = $r->factor($r->c("a", "b", "c"));
    my $x2 = $r->as->double($x1);
    ok($r->is->double($x2));
    is_deeply($x2->values, [1, 2, 3]);
  }
  
  # factor - as_factor, double
  {
    my $x1 = $r->c(2, 3, 4);
    my $x2 = $r->factor($x1);
    ok($r->is->factor($x2));
    is_deeply($x2->values, [1, 2, 3]);
    is_deeply($r->levels($x2)->values, ["2", "3", "4"]);
  }
  
  # factor - as_factor, string
  {
    my $x1 = $r->c("a", "b", "c");
    my $x2 = $r->factor($x1);
    ok($r->is->factor($x2));
    is_deeply($x2->values, [1, 2, 3]);
    is_deeply($r->levels($x2)->values, ["a", "b", "c"]);
  }

  # factor - ordered
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"), {ordered => $r->TRUE});
    ok($r->is->ordered($x1));
  }

  # factor - ordered, default, FALSE
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"));
    ok(!$r->is->ordered($x1));
  }

  # factor - exclude
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"), {exclude => "c"});
    is_deeply($x1->values, [1, 2, undef, 1, 2, undef]);
  }
  
  # factor - labels
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"), {levels => $r->c("a", "b", "c"), labels => $r->c(1, 2, 3)});
    my $expected = <<'EOS';
[1] 1 2 3 1 2 3
Levels: 1 2 3
EOS
    is("$x1", $expected);
  }

  # factor - labels, one element
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"), {levels => $r->c("a", "b", "c"), labels => "a"});
    my $expected = <<'EOS';
[1] a1 a2 a3 a1 a2 a3
Levels: a1 a2 a3
EOS
    is("$x1", $expected);
  }
  
  # factor - to_string
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"), {levels => $r->c("a", "b")});
    my $expected = <<'EOS';
[1] a b <NA> a b <NA>
Levels: a b
EOS
    is("$x1", $expected);
  }

  # factor - to_string, ordered
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"), {ordered => $r->TRUE});
    my $expected = <<'EOS';
[1] a b c a b c
Levels: a < b < c
EOS
    is("$x1", $expected);
  }
  
  # factor - levels
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"), {levels => $r->c("a", "b")});
    is_deeply($x1->values, [1, 2, undef, 1, 2 ,undef]);
    is_deeply($r->levels($x1)->values, ["a", "b"]);
  }
  
  # factor - basic
  {
    my $x1 = $r->factor($r->c("a", "b", "c", "a", "b", "c"));
    # ok($r->is->double($x1));
    ok($r->is->factor($x1));
    is_deeply($x1->values, [1, 2, 3, 1, 2 ,3]);
    is_deeply($r->levels($x1)->values, ["a", "b", "c"]);
  }
}

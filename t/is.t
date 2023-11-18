use Test::More 'no_plan';
use strict;
use warnings;

use Rstats;
use Rstats;

my $r = Rstats->new;

# is->nan
{
  # is->nan - NA
  {
    my $x1 = $r->NA;
    my $x2 = $r->is->nan($x1);
    is_deeply($x2->values, [0]);
  }

  # is->nan - string
  {
    my $x1 = $r->c("a");
    my $x2 = $r->is->nan($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0]);
  }

  # is->nan - double
  {
    my $x1 = $r->c(1, 2);
    my $x2 = $r->is->nan($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0, 0]);
  }

  # is->nan - double,Inf
  {
    my $x1 = $r->Inf;
    my $x2 = $r->is->nan($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0]);
  }
  
  # is->nan - double,-Inf
  {
    my $x1 = -$r->Inf;
    my $x2 = $r->is->nan($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0]);
  }

  # is->nan - double,NaN
  {
    my $x1 = $r->NaN;
    my $x2 = $r->is->nan($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [1]);
  }

  # is->nan - dimention
  {
    my $x1 = $r->array($r->c(1, 2));
    my $x2 = $r->is->nan($x1);
    is_deeply($x2->dim->values, [2]);
  }
  
  # is->nan - complex
  {
    my $x1 = $r->c(1+2*$r->i, $r->complex($r->NaN, 1), $r->complex(1, $r->NaN));
    my $x2 = $r->is->nan($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0, 1, 1]);
  }
}

# is->infinite
{
  # is->infinite - NA
  {
    my $x1 = $r->NA;
    my $x2 = $r->is->infinite($x1);
    is_deeply($x2->values, [0]);
  }

  # is->infinite - string
  {
    my $x1 = $r->c("a");
    my $x2 = $r->is->infinite($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0]);
  }

  # is->infinite - complex
  {
    my $x1 = $r->c(1+2*$r->i, $r->complex($r->NaN, 1), $r->Inf + 1*$r->i, $r->complex(1, $r->Inf));
    my $x2 = $r->is->infinite($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0, 0, 1, 1]);
  }
    
  # is->infinite - double
  {
    my $x1 = $r->c(1, 2);
    my $x2 = $r->is->infinite($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0, 0]);
  }

  # is->infinite - double,Inf
  {
    my $x1 = $r->Inf;
    my $x2 = $r->is->infinite($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [1]);
  }
  
  # is->infinite - double,-Inf
  {
    my $x1 = -$r->Inf;
    my $x2 = $r->is->infinite($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [1]);
  }

  # is->infinite - double,NaN
  {
    my $x1 = $r->NaN;
    my $x2 = $r->is->infinite($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0]);
  }

  # is->infinite - dimention
  {
    my $x1 = $r->array($r->c(1, 2));
    my $x2 = $r->is->infinite($x1);
    is_deeply($x2->dim->values, [2]);
  }
}

# is->na
{
  # is->na - dim
  {
    my $x1 = $r->array($r->c(1.1, 1.2));
    my $x2 = $r->is->na($x1);
    is_deeply($x2->dim->values, [2]);
  }
  
  # is->na - NULL
  {
    my $x1 = $r->NULL;
    my $x2 = $r->is->na($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, []);
  }
  
  # is->na - string
  {
    my $x1 = $r->c("aaa", $r->NA);
    my $x2 = $r->is->na($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0, 1]);
  }
  
  # is->na - complex
  {
    my $x1 = $r->c(1 + 2*$r->i, $r->NA);
    my $x2 = $r->is->na($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0, 1]);
  }
  
  # is->na - double
  {
    my $x1 = $r->c(1.1, $r->NA);
    my $x2 = $r->is->na($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0, 1]);
  }
  
  # is->na - $r->list
  {
    my $x1 = $r->list(1, 2);
    my $x2 = $r->is->na($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [0]);
  }
}

# is->string
{
  # is->string, as_string, typeof - string
  {
    my $c = $r->c(0, 1, 2);
    ok($r->is->string($r->as->string($c)));
    is($r->mode($r->as->string($c))->value, 'string');
    is($r->typeof($r->as->string($c))->value, 'string');
  }
}

# is->complex
{
  # is->complex, as_complex, typeof - complex
  {
    my $c = $r->c(0, 1, 2);
    ok($r->is->complex($r->as->complex($c)));
    is($r->mode($r->as->complex($c))->value, 'complex');
    is($r->typeof($r->as->complex($c))->value, 'complex');
  }
}

# is->vector
{
  # is->vector
  {
    my $x = $r->array($r->C('1:24'));
    ok(!$r->is->vector($x));
  }
}

# is->matrix
{
  # is->matrix
  {
    my $x = $r->matrix($r->C('1:24'), 4, 3);
    ok($r->is->matrix($x));
  }
}

# is->array
{
  # is->array
  {
    
    my $x = $r->array($r->C('1:12'), $r->c(4, 3, 2));
    ok($r->is->array($x));
  }
}

# is->finite
{
  # is->infinite - NA
  {
    my $x1 = $r->NA;
    my $x2 = $r->is->finite($x1);
    is_deeply($x2->values, [0]);
  }
  
  # is->finite - Inf, false
  {
    my $x_inf = $r->Inf;
    ok(!$r->is->finite($x_inf)->value);
  }
  
  # is->finite - -Inf, false
  {
    my $x1 = -$r->Inf;
    ok(!$r->is->finite($x1)->value);
  }
  
  # is->finite - Double
  {
    my $x_num = $r->c(1);
    ok($r->is->finite($x_num)->value);
  }
}

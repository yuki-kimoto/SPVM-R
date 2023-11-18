use Test::More 'no_plan';
use strict;
use warnings;

use Rstats;
use Rstats;

my $r = Rstats->new;


# array upgrade mode
{
  # array decide mode - complex
  {
    my $x0 = $r->complex(3, 4);
    my $x0_1 = $r->c(1, $x0);
    my $x1 = $r->array($x0_1);
    is($x1->values->[0]->{re}, 1);
    is($x1->values->[0]->{im}, 0);
    is($x1->values->[1]->{re}, 3);
    is($x1->values->[1]->{im}, 4);
    ok($r->is->complex($x1));
  }
}

# as->double
{
  # as->double - error
  {
    my $x1 = $r->array("a");
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is($x2->values->[0], undef);
  }
  
  # as->double - NULL
  {
    my $x1 = $r->NULL;
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, []);
  }

  # as->double - dim
  {
    my $x1 = $r->array($r->c(1.1, 1.2));
    my $x2 = $r->as->double($x1);
    is_deeply($x2->dim->values, [2]);
  }
  
  # as->double - $r->Inf
  {
    my $x1 = $r->Inf;
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, ['Inf']);
  }

  # as->double - NA
  {
    my $x1 = $r->array($r->NA);
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, [undef]);
  }

  # as->double - NaN
  {
    my $x1 = $r->NaN;
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is_deeply($x2->values, ['NaN']);
  }

  # as->double - string, only real number, no sign
  {
    my $x1 = $r->array("1.23");
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is($x2->values->[0], 1.23);
  }

  # as->double - string, only real number, plus
  {
    my $x1 = $r->array("+1.23");
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is($x2->values->[0], 1.23);
  }
  
  # as->double - string, only real number, minus
  {
    my $x1 = $r->array("-1.23");
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is($x2->values->[0], -1.23);
  }

  # as->double - string, pre and trailing space
  {
    my $x1 = $r->array("  1  ");
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is($x2->values->[0], 1);
  }

  # as->double - complex
  {
    my $x1 = $r->array($r->complex(1, 2));
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is($x2->values->[0], 1);
  }
  
  # as->double - double
  {
    my $x1 = $r->array(1.1);
    my $x2 = $r->as->double($x1);
    # ok($r->is->double($x2));
    is($x2->values->[0], 1.1);
  }
}

# as->numeric
{
  # as->numeric - from complex
  {
    my $x1 = $r->c($r->complex(1, 1), $r->complex(2, 2));
    $r->mode($x1 => 'complex');
    my $x2 = $r->as->numeric($x1);
    is($r->mode($x2)->value, 'numeric');
    is_deeply($x2->values, [1, 2]);
  }

  # as->numeric - from numeric
  {
    my $x1 = $r->c(0.1, 1.1, 2.2);
    $r->mode($x1 => 'numeric');
    my $x2 = $r->as->numeric($x1);
    is($r->mode($x2)->value, 'numeric');
    is_deeply($x2->values, [0.1, 1.1, 2.2]);
  }
}

# is_*
{
  # is_* - is_array
  {
    my $x = $r->array($r->C('1:24'), $r->c(4, 3, 2));
    ok($r->is->array($x));
    ok(!$r->is->vector($x));
    ok(!$r->is->matrix($x));
  }

  # is_* - is_matrix
  {
    my $x = $r->matrix($r->C('1:12'), 4, 3);
    ok($r->is->matrix($x));
    ok($r->is->array($x));
  }

  # is_* - is_vector
  {
    my $x = $r->C('1:24');
    ok($r->is->vector($x));
    ok(!$r->is->array($x));
  }

  # is_* - is_vector
  {
    my $x = $r->array($r->C('1:24'));
    ok(!$r->is->vector($x));
    ok($r->is->array($x));
  }
}

# as->string
{
  # as->double - NULL
  {
    my $x1 = $r->NULL;
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is_deeply($x2->values, []);
  }
  
  # as->string - complex
  {
    my $x0 = $r->complex(1, 2);
    my $x1 = $r->array($r->complex(1, 2));
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is($x2->values->[0], "1+2i");
  }

  # as->string - NA
  {
    my $x1 = $r->array($r->NA);
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is_deeply($x2->values, [undef]);
  }

  # as->string - $r->Inf
  {
    my $x1 = $r->Inf;
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is_deeply($x2->values, ["Inf"]);
  }

  # as->string - NaN
  {
    my $x1 = $r->NaN;
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is_deeply($x2->values, ["NaN"]);
  }
  
  # as->string - string
  {
    my $x1 = $r->array($r->c("a"));
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is($x2->values->[0], "a");
  }
  
  # as->string - complex, 0 + 0i
  {
    my $x1 = $r->array($r->complex(0, 0));
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is($x2->values->[0], "0+0i");
  }
  
  # as->string - numeric
  {
    my $x1 = $r->array($r->c(1.1, 0));
    my $x2 = $r->as->string($x1);
    ok($r->is->string($x2));
    is($x2->values->[0], 1.1);
    is($x2->values->[1], "0");
  }
}

# as->numeric
{
  # as->numeric - string, pre and trailing space
  {
    my $x1 = $r->array("  1  ");
    my $x2 = $r->as->numeric($x1);
    ok($r->is->numeric($x2));
    is($x2->values->[0], 1);
  }
}

# as->complex
{
  # as->complex - NULL
  {
    my $x1 = $r->NULL;
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is_deeply($x2->values, []);
  }

  # as->complex - $r->Inf
  {
    my $x1 = $r->Inf;
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 'Inf');
    is($x2->values->[0]->{im}, 0);
  }

  # as->complex - NA
  {
    my $x1 = $r->array($r->NA);
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is_deeply($x2->values, [undef]);
  }

  # as->complex - NaN
  {
    my $x1 = $r->NaN;
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is_deeply($x2->values, [{re => 'NaN', im => 0}]);
  }

  # as->complex - string, only real number, no sign
  {
    my $x1 = $r->array("1.23");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 1.23);
    is($x2->values->[0]->{im}, 0);
  }

  # as->complex - string, only real number, pre and trailing space
  {
    my $x1 = $r->array("  1.23  ");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 1.23);
    is($x2->values->[0]->{im}, 0);
  }
  
  # as->complex - string, only real number, plus
  {
    my $x1 = $r->array("+1.23");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 1.23);
    is($x2->values->[0]->{im}, 0);
  }
  
  # as->complex - string, only real number, minus
  {
    my $x1 = $r->array("-1.23");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, -1.23);
    is($x2->values->[0]->{im}, 0);
  }

  # as->complex - string, only image number, no sign
  {
    my $x1 = $r->array("1.23i");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 0);
    is($x2->values->[0]->{im}, 1.23);
  }

  # as->complex - string, only image number, plus
  {
    my $x1 = $r->array("+1.23i");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 0);
    is($x2->values->[0]->{im}, 1.23);
  }

  # as->complex - string, only image number, minus
  {
    my $x1 = $r->array("-1.23i");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 0);
    is($x2->values->[0]->{im}, -1.23);
  }

  # as->complex - string, real number and image number, no sign
  {
    my $x1 = $r->array("2.5+1.23i");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 2.5);
    is($x2->values->[0]->{im}, 1.23);
  }

  # as->complex - string, real number and image number, plus
  {
    my $x1 = $r->array("+2.5+1.23i");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 2.5);
    is($x2->values->[0]->{im}, 1.23);
  }
  
  # as->complex - string, real number and image number, minus
  {
    my $x1 = $r->array("-2.5-1.23i");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, -2.5);
    is($x2->values->[0]->{im}, -1.23);
  }

  # as->complex - string, pre and trailing space
  {
    my $x1 = $r->array("  2.5+1.23i  ");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 2.5);
    is($x2->values->[0]->{im}, 1.23);
  }

  # as->complex - error
  {
    my $x1 = $r->array("a");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0], undef);
  }

  # as->complex - error
  {
    my $x1 = $r->array("i");
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0], undef);
  }
        
  # as->complex - complex
  {
    my $x1 = $r->array($r->complex(1, 2));
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 1);
    is($x2->values->[0]->{im}, 2);
  }
  
  # as->complex - numeric
  {
    my $x1 = $r->array(1.1);
    my $x2 = $r->as->complex($x1);
    ok($r->is->complex($x2));
    is($x2->values->[0]->{re}, 1.1);
    is($x2->values->[0]->{im}, 0);
  }
}

# array decide type
{
  # array decide type - complex
  {
    my $x1 = $r->array($r->c($r->complex(1, 2), $r->complex(3, 4)));
    is($x1->values->[0]->{re}, 1);
    is($x1->values->[0]->{im}, 2);
    is($x1->values->[1]->{re}, 3);
    is($x1->values->[1]->{im}, 4);
    ok($r->is->complex($x1));
  }

  # array decide type - numerci
  {
    my $x1 = $r->array($r->c(1, 2));
    is_deeply($x1->values, [1, 2]);
    ok($r->is->numeric($x1));
  }
  
  # array decide type - string
  {
    my $x1 = $r->array($r->c("c1", "c2"));
    is_deeply($x1->values, ["c1", "c2"]);
    ok($r->is->string($x1));
  }

  # array decide type - string, look like number
  {
    my $x1 = $r->array($r->c("1", "2"));
    is_deeply($x1->values, ["1", "2"]);
    ok($r->is->string($x1));
  }

  # array decide type - $r->Inf
  {
    my $x1 = $r->Inf;
    is_deeply($x1->values, ['Inf']);
    ok($r->is->numeric($x1));
  }

  # array decide type - NaN
  {
    my $x1 = $r->NaN;
    is_deeply($x1->values, ['NaN']);
    ok($r->is->numeric($x1));
  }

  # array decide type - NA
  {
    my $x1 = $r->array($r->NA);
    is_deeply($x1->values, [undef]);
    # ok($r->is->double($x1));
  }
}

# as->vector
{
  my $x = $r->array($r->C('1:24'), $r->c(4, 3, 2));
  is_deeply($r->as->vector($x)->values, [1 .. 24]);
  is_deeply($r->dim($r->as->vector($x))->values, []);
}

# as->matrix
{
  # as->matrix - from vector
  {
    my $x = $r->c($r->C('1:24'));
    is_deeply($r->as->matrix($x)->values, [1 .. 24]);
    is_deeply($r->dim($r->as->matrix($x))->values, [24, 1]);
  }

  # as->matrix - from $r->matrix
  {
    my $x = $r->matrix($r->C('1:12'), 4, 3);
    is_deeply($r->as->matrix($x)->values, [1 .. 12]);
    is_deeply($r->dim($r->as->matrix($x))->values, [4, 3]);
  }

  # as->matrix - from $r->array
  {
    my $x = $r->array($r->C('1:24'), $r->c(4, 3, 2));
    is_deeply($r->as->matrix($x)->values, [1 .. 24]);
    is_deeply($r->dim($r->as->matrix($x))->values, [24, 1]);
  }
}

# as->array
{
  # as->array - from vector
  {
    my $x1 = $r->C('1:24');
    my $x2 = $r->as->array($x1);
    is_deeply($x2->values, [1 .. 24]);
    is_deeply($r->dim($x2)->values, [24]);
  }

  # as->array - from $r->array
  {
    my $x1 = $r->array($r->C('1:24'), $r->c(4, 3, 2));
    my $x2 = $r->as->array($x1);
    is_deeply($x2->values, [1 .. 24]);
    is_deeply($r->dim($x2)->values, [4, 3, 2]);
  }
}


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
    ok($r->is_complex($x1));
  }
}

# as_double
{
  # as_double - error
  {
    my $x1 = $r->array("a");
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is($x2->values->[0], undef);
  }
  
  # as_double - dim
  {
    my $x1 = $r->array($r->c(1.1, 1.2));
    my $x2 = $r->as_double($x1);
    is_deeply($x2->dim->values, [2]);
  }
  
  # as_double - $r->Inf
  {
    my $x1 = $r->Inf;
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is_deeply($x2->values, ['Inf']);
  }

  # as_double - NA
  {
    my $x1 = $r->array($r->NA);
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is_deeply($x2->values, [undef]);
  }

  # as_double - NaN
  {
    my $x1 = $r->NaN;
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is_deeply($x2->values, ['NaN']);
  }

  # as_double - string, only real number, no sign
  {
    my $x1 = $r->array("1.23");
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is($x2->values->[0], 1.23);
  }

  # as_double - string, only real number, plus
  {
    my $x1 = $r->array("+1.23");
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is($x2->values->[0], 1.23);
  }
  
  # as_double - string, only real number, minus
  {
    my $x1 = $r->array("-1.23");
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is($x2->values->[0], -1.23);
  }

  # as_double - string, pre and trailing space
  {
    my $x1 = $r->array("  1  ");
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is($x2->values->[0], 1);
  }

  # as_double - complex
  {
    my $x1 = $r->array($r->complex(1, 2));
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is($x2->values->[0], 1);
  }
  
  # as_double - double
  {
    my $x1 = $r->array(1.1);
    my $x2 = $r->as_double($x1);
    # ok($r->is_double($x2));
    is($x2->values->[0], 1.1);
  }
}

# as_numeric
{
  # as_numeric - from complex
  {
    my $x1 = $r->c($r->complex(1, 1), $r->complex(2, 2));
    $r->mode($x1 => 'complex');
    my $x2 = $r->as_numeric($x1);
    is($r->mode($x2)->value, 'numeric');
    is_deeply($x2->values, [1, 2]);
  }

  # as_numeric - from numeric
  {
    my $x1 = $r->c(0.1, 1.1, 2.2);
    $r->mode($x1 => 'numeric');
    my $x2 = $r->as_numeric($x1);
    is($r->mode($x2)->value, 'numeric');
    is_deeply($x2->values, [0.1, 1.1, 2.2]);
  }
}

# is_*
{
  # is_* - is_array
  {
    my $x = $r->array($r->C('1:24'), $r->c(4, 3, 2));
    ok($r->is_array($x));
    ok(!$r->is_vector($x));
    ok(!$r->is_matrix($x));
  }

  # is_* - is_matrix
  {
    my $x = $r->matrix($r->C('1:12'), 4, 3);
    ok($r->is_matrix($x));
    ok($r->is_array($x));
  }

  # is_* - is_vector
  {
    my $x = $r->C('1:24');
    ok($r->is_vector($x));
    ok(!$r->is_array($x));
  }

  # is_* - is_vector
  {
    my $x = $r->array($r->C('1:24'));
    ok(!$r->is_vector($x));
    ok($r->is_array($x));
  }
}

# as_string
{
  # as_string - complex
  {
    my $x0 = $r->complex(1, 2);
    my $x1 = $r->array($r->complex(1, 2));
    my $x2 = $r->as_string($x1);
    ok($r->is_string($x2));
    is($x2->values->[0], "1+2i");
  }

  # as_string - NA
  {
    my $x1 = $r->array($r->NA);
    my $x2 = $r->as_string($x1);
    ok($r->is_string($x2));
    is_deeply($x2->values, [undef]);
  }

  # as_string - $r->Inf
  {
    my $x1 = $r->Inf;
    my $x2 = $r->as_string($x1);
    ok($r->is_string($x2));
    is_deeply($x2->values, ["Inf"]);
  }

  # as_string - NaN
  {
    my $x1 = $r->NaN;
    my $x2 = $r->as_string($x1);
    ok($r->is_string($x2));
    is_deeply($x2->values, ["NaN"]);
  }
  
  # as_string - string
  {
    my $x1 = $r->array($r->c("a"));
    my $x2 = $r->as_string($x1);
    ok($r->is_string($x2));
    is($x2->values->[0], "a");
  }
  
  # as_string - complex, 0 + 0i
  {
    my $x1 = $r->array($r->complex(0, 0));
    my $x2 = $r->as_string($x1);
    ok($r->is_string($x2));
    is($x2->values->[0], "0+0i");
  }
  
  # as_string - numeric
  {
    my $x1 = $r->array($r->c(1.1, 0));
    my $x2 = $r->as_string($x1);
    ok($r->is_string($x2));
    is($x2->values->[0], 1.1);
    is($x2->values->[1], "0");
  }
}

# as_numeric
{
  # as_numeric - string, pre and trailing space
  {
    my $x1 = $r->array("  1  ");
    my $x2 = $r->as_numeric($x1);
    ok($r->is_numeric($x2));
    is($x2->values->[0], 1);
  }
}

# as_complex
{
  # as_complex - $r->Inf
  {
    my $x1 = $r->Inf;
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 'Inf');
    is($x2->values->[0]->{im}, 0);
  }

  # as_complex - NA
  {
    my $x1 = $r->array($r->NA);
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is_deeply($x2->values, [undef]);
  }

  # as_complex - NaN
  {
    my $x1 = $r->NaN;
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is_deeply($x2->values, [{re => 'NaN', im => 0}]);
  }

  # as_complex - string, only real number, no sign
  {
    my $x1 = $r->array("1.23");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 1.23);
    is($x2->values->[0]->{im}, 0);
  }

  # as_complex - string, only real number, pre and trailing space
  {
    my $x1 = $r->array("  1.23  ");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 1.23);
    is($x2->values->[0]->{im}, 0);
  }
  
  # as_complex - string, only real number, plus
  {
    my $x1 = $r->array("+1.23");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 1.23);
    is($x2->values->[0]->{im}, 0);
  }
  
  # as_complex - string, only real number, minus
  {
    my $x1 = $r->array("-1.23");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, -1.23);
    is($x2->values->[0]->{im}, 0);
  }

  # as_complex - string, only image number, no sign
  {
    my $x1 = $r->array("1.23i");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 0);
    is($x2->values->[0]->{im}, 1.23);
  }

  # as_complex - string, only image number, plus
  {
    my $x1 = $r->array("+1.23i");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 0);
    is($x2->values->[0]->{im}, 1.23);
  }

  # as_complex - string, only image number, minus
  {
    my $x1 = $r->array("-1.23i");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 0);
    is($x2->values->[0]->{im}, -1.23);
  }

  # as_complex - string, real number and image number, no sign
  {
    my $x1 = $r->array("2.5+1.23i");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 2.5);
    is($x2->values->[0]->{im}, 1.23);
  }

  # as_complex - string, real number and image number, plus
  {
    my $x1 = $r->array("+2.5+1.23i");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 2.5);
    is($x2->values->[0]->{im}, 1.23);
  }
  
  # as_complex - string, real number and image number, minus
  {
    my $x1 = $r->array("-2.5-1.23i");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, -2.5);
    is($x2->values->[0]->{im}, -1.23);
  }

  # as_complex - string, pre and trailing space
  {
    my $x1 = $r->array("  2.5+1.23i  ");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 2.5);
    is($x2->values->[0]->{im}, 1.23);
  }

  # as_complex - error
  {
    my $x1 = $r->array("a");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0], undef);
  }

  # as_complex - error
  {
    my $x1 = $r->array("i");
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0], undef);
  }
        
  # as_complex - complex
  {
    my $x1 = $r->array($r->complex(1, 2));
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
    is($x2->values->[0]->{re}, 1);
    is($x2->values->[0]->{im}, 2);
  }
  
  # as_complex - numeric
  {
    my $x1 = $r->array(1.1);
    my $x2 = $r->as_complex($x1);
    ok($r->is_complex($x2));
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
    ok($r->is_complex($x1));
  }

  # array decide type - numerci
  {
    my $x1 = $r->array($r->c(1, 2));
    is_deeply($x1->values, [1, 2]);
    ok($r->is_numeric($x1));
  }
  
  # array decide type - string
  {
    my $x1 = $r->array($r->c("c1", "c2"));
    is_deeply($x1->values, ["c1", "c2"]);
    ok($r->is_string($x1));
  }

  # array decide type - string, look like number
  {
    my $x1 = $r->array($r->c("1", "2"));
    is_deeply($x1->values, ["1", "2"]);
    ok($r->is_string($x1));
  }

  # array decide type - $r->Inf
  {
    my $x1 = $r->Inf;
    is_deeply($x1->values, ['Inf']);
    ok($r->is_numeric($x1));
  }

  # array decide type - NaN
  {
    my $x1 = $r->NaN;
    is_deeply($x1->values, ['NaN']);
    ok($r->is_numeric($x1));
  }

  # array decide type - NA
  {
    my $x1 = $r->array($r->NA);
    is_deeply($x1->values, [undef]);
    # ok($r->is_double($x1));
  }
}

# as_vector
{
  my $x = $r->array($r->C('1:24'), $r->c(4, 3, 2));
  is_deeply($r->as_vector($x)->values, [1 .. 24]);
  is_deeply($r->dim($r->as_vector($x))->values, []);
}

# as_matrix
{
  # as_matrix - from vector
  {
    my $x = $r->c($r->C('1:24'));
    is_deeply($r->as_matrix($x)->values, [1 .. 24]);
    is_deeply($r->dim($r->as_matrix($x))->values, [24, 1]);
  }

  # as_matrix - from $r->matrix
  {
    my $x = $r->matrix($r->C('1:12'), 4, 3);
    is_deeply($r->as_matrix($x)->values, [1 .. 12]);
    is_deeply($r->dim($r->as_matrix($x))->values, [4, 3]);
  }

  # as_matrix - from $r->array
  {
    my $x = $r->array($r->C('1:24'), $r->c(4, 3, 2));
    is_deeply($r->as_matrix($x)->values, [1 .. 24]);
    is_deeply($r->dim($r->as_matrix($x))->values, [24, 1]);
  }
}

# as_array
{
  # as_array - from vector
  {
    my $x1 = $r->C('1:24');
    my $x2 = $r->as_array($x1);
    is_deeply($x2->values, [1 .. 24]);
    is_deeply($r->dim($x2)->values, [24]);
  }

  # as_array - from $r->array
  {
    my $x1 = $r->array($r->C('1:24'), $r->c(4, 3, 2));
    my $x2 = $r->as_array($x1);
    is_deeply($x2->values, [1 .. 24]);
    is_deeply($r->dim($x2)->values, [4, 3, 2]);
  }
}


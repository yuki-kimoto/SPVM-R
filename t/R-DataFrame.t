use Test::More;

use strict;
use warnings;
use lib "t/lib";

use SPVM 'TestCase::R::DataFrame';

use SPVM 'R';
use SPVM::R;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::R::DataFrame->new);
ok(SPVM::TestCase::R::DataFrame->colnames);
ok(SPVM::TestCase::R::DataFrame->exists_col);
ok(SPVM::TestCase::R::DataFrame->colname);
ok(SPVM::TestCase::R::DataFrame->colindex);
ok(SPVM::TestCase::R::DataFrame->col_by_index);
ok(SPVM::TestCase::R::DataFrame->first_col);
ok(SPVM::TestCase::R::DataFrame->col);
ok(SPVM::TestCase::R::DataFrame->set_col);
ok(SPVM::TestCase::R::DataFrame->insert_col);
ok(SPVM::TestCase::R::DataFrame->remove_col);
ok(SPVM::TestCase::R::DataFrame->ncol);
ok(SPVM::TestCase::R::DataFrame->nrow);
ok(SPVM::TestCase::R::DataFrame->clone);
ok(SPVM::TestCase::R::DataFrame->to_string);
ok(SPVM::TestCase::R::DataFrame->slice);
ok(SPVM::TestCase::R::DataFrame->set_order);
ok(SPVM::TestCase::R::DataFrame->sort);
ok(SPVM::TestCase::R::DataFrame->order);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

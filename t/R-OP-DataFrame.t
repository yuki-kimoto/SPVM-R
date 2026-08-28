use Test::More;

use strict;
use warnings;
use lib "t/lib";

use SPVM 'TestCase::R::OP::DataFrame';

use SPVM 'R';
use SPVM::R;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::R::OP::DataFrame->cbind);
ok(SPVM::TestCase::R::OP::DataFrame->rbind);
ok(SPVM::TestCase::R::OP::DataFrame->subset);
ok(SPVM::TestCase::R::OP::DataFrame->na_omit);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

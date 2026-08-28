use Test::More;

use strict;
use warnings;
use lib "t/lib";

use SPVM 'TestCase::R::NDArray::Byte';

use SPVM 'R';
use SPVM::R;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::R::NDArray::Byte->data);
ok(SPVM::TestCase::R::NDArray::Byte->new);
ok(SPVM::TestCase::R::NDArray::Byte->create_default_data);
ok(SPVM::TestCase::R::NDArray::Byte->elem_to_string);
ok(SPVM::TestCase::R::NDArray::Byte->elem_assign);
ok(SPVM::TestCase::R::NDArray::Byte->elem_assign);
ok(SPVM::TestCase::R::NDArray::Byte->elem_clone);
ok(SPVM::TestCase::R::NDArray::Byte->elem_cmp);
ok(SPVM::TestCase::R::NDArray::Byte->clone);
ok(SPVM::TestCase::R::NDArray::Byte->slice);
ok(SPVM::TestCase::R::NDArray::Byte->to_int_ndarray);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

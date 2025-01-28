use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'TestCase::R::NDArray::StringBuffer';

use SPVM 'R';
use SPVM::R;
use SPVM 'Fn';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::R::NDArray::StringBuffer->data);
ok(SPVM::TestCase::R::NDArray::StringBuffer->new);
ok(SPVM::TestCase::R::NDArray::StringBuffer->create_default_data);
ok(SPVM::TestCase::R::NDArray::StringBuffer->elem_to_string);
ok(SPVM::TestCase::R::NDArray::StringBuffer->elem_assign);
ok(SPVM::TestCase::R::NDArray::StringBuffer->elem_assign);
ok(SPVM::TestCase::R::NDArray::StringBuffer->elem_clone);
ok(SPVM::TestCase::R::NDArray::StringBuffer->elem_cmp);
ok(SPVM::TestCase::R::NDArray::StringBuffer->clone);
ok(SPVM::TestCase::R::NDArray::StringBuffer->slice);
ok(SPVM::TestCase::R::NDArray::StringBuffer->to_string_ndarray);

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

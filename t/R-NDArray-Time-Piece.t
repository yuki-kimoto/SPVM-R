use Test::More;

use strict;
use warnings;
use lib "t/lib";

use SPVM 'TestCase::R::NDArray::Time::Piece';

use SPVM 'R';
use SPVM::R;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::R::NDArray::Time::Piece->data);
ok(SPVM::TestCase::R::NDArray::Time::Piece->new);
ok(SPVM::TestCase::R::NDArray::Time::Piece->create_default_data);
ok(SPVM::TestCase::R::NDArray::Time::Piece->elem_to_string);
ok(SPVM::TestCase::R::NDArray::Time::Piece->elem_assign);
ok(SPVM::TestCase::R::NDArray::Time::Piece->elem_assign);
ok(SPVM::TestCase::R::NDArray::Time::Piece->elem_clone);
ok(SPVM::TestCase::R::NDArray::Time::Piece->elem_cmp);
ok(SPVM::TestCase::R::NDArray::Time::Piece->clone);
ok(SPVM::TestCase::R::NDArray::Time::Piece->slice);
ok(SPVM::TestCase::R::NDArray::Time::Piece->to_string_ndarray);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

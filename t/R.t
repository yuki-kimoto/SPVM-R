use Test::More;

use strict;
use warnings;
use lib "t/lib";

use SPVM 'TestCase::R';

use SPVM 'R';
use SPVM::R;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Version check
{
  my $version_string = $api->get_version_string("R");
  is($SPVM::R::VERSION, $version_string);
}

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

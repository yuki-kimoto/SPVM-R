use 5.008_007;
use ExtUtils::MakeMaker;
use strict;
use warnings;
use Config;
use Getopt::Long 'GetOptions';

GetOptions(
  'meta' => \my $meta,
  'no-build-spvm-modules' => \my $no_build_spvm_modules,
);

if ($meta) {
  $no_build_spvm_modules = 1;
}

unless ($meta) {
  # Do something such as environment check.
}

my %configure_and_runtime_requires = (
  'SPVM' => '0.990154',
  'SPVM::Resource::Eigen' => '0.003'
);
WriteMakefile(
  NAME => 'SPVM::R',
  VERSION_FROM => 'lib/SPVM/R.pm',
  LICENSE => 'mit',
  ($] >= 5.005 ?
    (ABSTRACT_FROM => 'lib/SPVM/R.pm',
     AUTHOR => 'Yuki Kimoto<kimoto.yuki@gmail.com>') : ()),
  test => {TESTS => 't/*.t t/*/*.t t/*/*/*.t'},
  clean => {FILES => ['.spvm_build', 't/.spvm_build']},
  META_MERGE => {
    'meta-spec' => { version => 2 },
    resources => {
      repository => {
        type => 'git',
        url  => 'https://github.com/yuki-kimoto/SPVM-R.git',
        web  => 'https://github.com/yuki-kimoto/SPVM-R',
      },
    },
    no_index => {
      directory => [],
    }
  },
  NORECURS => 1,
  CONFIGURE_REQUIRES => {
    %configure_and_runtime_requires,
  },
  PREREQ_PM         => {
    %configure_and_runtime_requires,
    'SPVM::Math' => '1.002',
    'SPVM::Time::Piece' => '0.004',
    'SPVM::Sys' => '0.525',
  },
  TEST_REQUIRES => {
    
  },
);

sub MY::postamble {

  my $make_rule = '';
  
  unless ($no_build_spvm_modules) {
    require SPVM::Builder::Util::API;
    
    local @INC = ('lib', @INC);
    
    # Native classes for R (Eigen-based)
    my $native_classes = [
      'R::OP::Matrix::Float',
      'R::OP::Matrix::FloatComplex',
      'R::OP::Matrix::Double',
      'R::OP::Matrix::DoubleComplex',
    ];

    # Precompile classes for R
    my $precompile_classes = [
      'R::OP::Int',
      'R::OP::Long',
      'R::OP::Float',
      'R::OP::Double',
      'R::OP::FloatComplex',
      'R::OP::DoubleComplex',
      'R::OP',
      'R::OP::StringBuffer',
      'R::OP::String',
      'R::OP::Time::Piece',
      'R::NDArray',
      'R::NDArray::Byte',
      'R::NDArray::Double',
      'R::NDArray::DoubleComplex',
      'R::NDArray::Float',
      'R::NDArray::FloatComplex',
      'R::NDArray::Int',
      'R::NDArray::Long',
      'R::NDArray::Short',
      'R::NDArray::String',
    ];

    # Generate a single parallel make rule for R
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_parallel({
      native_classes => $native_classes,
      precompile_classes => $precompile_classes,
    });
    
  }
  
  return $make_rule;
}

1;

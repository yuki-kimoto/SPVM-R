// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "Eigen/Core"
#include "Eigen/Dense"

using namespace Eigen;
using Eigen::MatrixXd;
using namespace std;

extern "C" {

static const char* FILE_NAME = "R/Op/Matrix/Double.cpp";

int32_t SPVM__R__Op__Matrix__Double__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_nums1 = stack[0].oval;
  double* nums1 = env->get_elems_double(env, stack, obj_nums1);
  
  void* obj_nums2 = stack[1].oval;
  double* nums2 = env->get_elems_double(env, stack, obj_nums2);
  
  MatrixXd X1 = Map<MatrixXd>(nums1, 3, 3);
  
  MatrixXd X2 = Map<MatrixXd>(nums2, 3, 3);
  
  MatrixXd X3 = X1 + X2;
  
  void* obj_nums3 = env->new_double_array(env, stack, 9);
  double* nums3 = env->get_elems_double(env, stack, obj_nums3);
  memcpy(nums3, X3.data(), sizeof(double) * 9);
  
  stack[0].oval = obj_nums3;
  
  return 0;
}

}

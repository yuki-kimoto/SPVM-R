// Copyright (c) 2024 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include "Eigen/Core"
#include "Eigen/Dense"

extern "C" {

static const char* FILE_NAME = "R/OP/Matrix/Double.cpp";

int32_t SPVM__R__OP__Matrix__Double___mul(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_ret_data_ref = stack[0].oval;
  
  int32_t* ret_row_ref = stack[1].iref;
  
  int32_t* ret_column_ref = stack[2].iref;
  
  void* obj_x_data = stack[3].oval;
  double* x_data = env->get_elems_double(env, stack, obj_x_data);
  
  int32_t x_row = stack[4].ival;
  
  int32_t x_column = stack[5].ival;
  
  void* obj_y_data = stack[6].oval;
  double* y_data = env->get_elems_double(env, stack, obj_y_data);
  
  int32_t y_row = stack[7].ival;
  
  int32_t y_column = stack[8].ival;
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x_matrix = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>(x_data, x_row, x_column);
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> y_matrix = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>(y_data, y_row, y_column);
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> ret_matrix = x_matrix * y_matrix;
  
  int32_t ret_length = ret_matrix.rows() * ret_matrix.cols();
  void* obj_ret_data = env->new_double_array(env, stack, ret_length);
  
  double* ret_data = env->get_elems_double(env, stack, obj_ret_data);
  
  memcpy(ret_data, ret_matrix.data(), sizeof(double) * ret_length);
  
  env->set_elem_object(env, stack, obj_ret_data_ref, 0, obj_ret_data);
  
  *ret_row_ref = ret_matrix.rows();
  
  *ret_column_ref = ret_matrix.cols();
  
  return 0;
}

int32_t SPVM__R__OP__Matrix__Double___solve(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* ret_ndarray_ref = stack[0].oval;
  
  int32_t* ret_row_ref = stack[1].iref;
  
  int32_t* ret_column_ref = stack[2].iref;
  
  void* obj_x_data = stack[3].oval;
  double* x_data = env->get_elems_double(env, stack, obj_x_data);
  
  int32_t x_row = stack[4].ival;
  
  int32_t x_column = stack[5].ival;
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x_matrix = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>(x_data, x_row, x_column);
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> ret_matrix = x_matrix;
  
  ret_matrix.inverse();
  
  int32_t ret_length = ret_matrix.rows() * ret_matrix.cols();
  void* obj_ret_data = env->new_double_array(env, stack, ret_length);
  
  double* ret_data = env->get_elems_double(env, stack, obj_ret_data);
  
  memcpy(ret_data, ret_matrix.data(), sizeof(double) * ret_length);
  
  env->set_elem_object(env, stack, ret_ndarray_ref, 0, ret_data);
  
  *ret_row_ref = ret_matrix.rows();
  
  *ret_column_ref = ret_matrix.cols();
  
  return 0;
}

int32_t SPVM__R__OP__Matrix__Double___t(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* ret_ndarray_ref = stack[0].oval;
  
  int32_t* ret_row_ref = stack[1].iref;
  
  int32_t* ret_column_ref = stack[2].iref;
  
  void* obj_x_data = stack[3].oval;
  double* x_data = env->get_elems_double(env, stack, obj_x_data);
  
  int32_t x_row = stack[4].ival;
  
  int32_t x_column = stack[5].ival;
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x_matrix = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>(x_data, x_row, x_column);
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> ret_matrix = x_matrix;
  
  ret_matrix.transposeInPlace();
  
  int32_t ret_length = ret_matrix.rows() * ret_matrix.cols();
  void* obj_ret_data = env->new_double_array(env, stack, ret_length);
  
  double* ret_data = env->get_elems_double(env, stack, obj_ret_data);
  
  memcpy(ret_data, ret_matrix.data(), sizeof(double) * ret_length);
  
  env->set_elem_object(env, stack, ret_ndarray_ref, 0, ret_data);
  
  *ret_row_ref = ret_matrix.rows();
  
  *ret_column_ref = ret_matrix.cols();
  
  return 0;
}

int32_t SPVM__R__OP__Matrix__Double___det(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* ret_ndarray_ref = stack[0].oval;
  
  int32_t* ret_row_ref = stack[1].iref;
  
  int32_t* ret_column_ref = stack[2].iref;
  
  void* obj_x_data = stack[3].oval;
  double* x_data = env->get_elems_double(env, stack, obj_x_data);
  
  int32_t x_row = stack[4].ival;
  
  int32_t x_column = stack[5].ival;
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x_matrix = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>(x_data, x_row, x_column);
  
  double ret = x_matrix.determinant();
  
  int32_t ret_length = 1;
  void* obj_ret_data = env->new_double_array(env, stack, ret_length);
  
  double* ret_data = env->get_elems_double(env, stack, obj_ret_data);
  
  memcpy(ret_data, &ret, sizeof(double) * ret_length);
  
  env->set_elem_object(env, stack, ret_ndarray_ref, 0, ret_data);
  
  *ret_row_ref = 1;
  
  *ret_column_ref = 1;
  
  return 0;
}

int32_t SPVM__R__OP__Matrix__Double___eigen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* ret_ndarray_ref = stack[0].oval;
  
  int32_t* ret_row_ref = stack[1].iref;
  
  int32_t* ret_column_ref = stack[2].iref;
  
  void* obj_x_data = stack[3].oval;
  double* x_data = env->get_elems_double(env, stack, obj_x_data);
  
  int32_t x_row = stack[4].ival;
  
  int32_t x_column = stack[5].ival;
  
  void* obj_eigen_values_data_ref = stack[6].oval;
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> x_matrix = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>(x_data, x_row, x_column);
  
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> eigen_solver(x_matrix);
  
  Eigen::VectorXd eigen_values = eigen_solver.eigenvalues();
  
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> eigen_vectors = eigen_solver.eigenvectors();
  
  int32_t ret_length = eigen_vectors.rows() * eigen_vectors.cols();
  void* obj_ret_data = env->new_double_array(env, stack, ret_length);
  
  double* ret_data = env->get_elems_double(env, stack, obj_ret_data);
  
  memcpy(ret_data, eigen_vectors.data(), sizeof(double) * ret_length);
  
  env->set_elem_object(env, stack, ret_ndarray_ref, 0, ret_data);
  
  *ret_row_ref = eigen_vectors.rows();
  
  *ret_column_ref = eigen_vectors.cols();
  
  void* eigen_values_data = env->new_double_array(env, stack, eigen_values.size());
  
  memcpy(eigen_values_data, eigen_values.data(), sizeof(double) * eigen_values.size());
  
  env->set_elem_object(env, stack, obj_eigen_values_data_ref, 0, eigen_values_data);
  
  return 0;
}

}

package SPVM::R::NDArray;



1;

=head1 Name

SPVM::R::NDArray - N-Dimensional Array Base Class

=head1 Description

The R::NDArray class in L<SPVM> represetns n-dimensional array and it is the base class of classes that represents typed n-dimensional arrays.

=head1 Usage

  use R::NDArray;

=head1 Details

R::NDArray is column major.

=head1 Fields

=head2 data

C<has data : protected ro object;>

An array of numeric type, multi-numeric type, or object type.

=head2 dim

C<has dim : int[];>

Dimensions.

C<method dim : int[] ();>

Creates a new array, copies the elements of this field, and returns the array.

C<method set_dim : void ($dim : int[]);>

The dimensions $dim is normalized by L<R::Util#normalize_dim|SPVM::R::Util/"normalize_dim"> method, checks the normalized dim by L<R::Util#check_length|SPVM::R::Util/"check_length"> method, and sets this field to the normalized dim.

Exceptions:

C<set_dim> Method:

If L</"is_dim_read_only"> is a true value, an exception is thrown.

Exceptions thrown by L<R::Util#normalize_dim|SPVM::R::Util/"normalize_dim"> method could be thrown.

Exceptions thrown by L<R::Util#check_length|SPVM::R::Util/"check_length"> method could be thrown.

=head2 is_dim_read_only

C<has is_dim_read_only : ro byte;>

If this field is a true value, it indicates L</"dim"> field is read only, otherwise writable.

=head1 Class Methods

  static method new : R::NDArray ($options : object[] = undef) {

=head1 Instance Methods

  protected method init : void ($options : object[] = undef) {

  method make_dim_read_only : void () {
  
  method nrow : int () {
  
  method ncol : int () {
  
  method length : int () {
  
  method is_empty : int () {
  
  method is_scalar : int () {
  
  method is_vector : int () {
  
  method is_matrix : int () {
  
  method is_square_matrix : int () {
  
  method drop_dim : void ($index : int = -1) {
  
  method expand_dim : void ($index : int = -1) {
  
  protected method create_default_data : object ($length : int = 0) { die "Not implemented."; }
  
  method clone : R::NDArray ($elem_shallow_clone : int = 0) {
  
  method slice : R::NDArray ($vector_indexes : R::NDArray::Int[]) {
  
  method slice_set : void ($vector_indexes : R::NDArray::Int[], $ndarray : R::NDArray) {
  
  protected method slice_data : object ($data_indexes : int[]) { die "Not implemented."; }
  
  protected method slice_set_data : void ($data_indexes : int[], $data : object) { die "Not implemented."; }
  
  private precompile method create_data_indexes : int[] ($vector_indexes : R::NDArray::Int[], $dim : int[]) {
  
  method to_string : string () {
  
  private static method recursive_to_string : void ($self : R::NDArray, $dim_list : IntList, $string_buffer : StringBuffer, $dim_num_ref : int*, $coordinate_list : IntList) {
  
  method set_order : void ($indexes_ndarray : R::NDArray::Int) { die "Not impelmeneted."; }
  
  method check_set_order_args : void ($indexes_ndarray : R::NDArray::Int) {
  
  method to_string_ndarray : R::NDArray::String () {
  
  method is_numeric_ndarray : int () {
  
  method is_mulnum_ndarray : int () {
  
  method is_any_numeric_ndarray : int () {
  
  method is_object_ndarray : int () {
  
  method elem_size : int () {
  
  method elem_type_name : string () {
  
  method sort_asc : void () {
  
  method sort_desc : void () {
  
  method order : R::NDArray::Int () {
  
  method elem_cmp : int ($a_data_index : int, $b_data_index : int) { die "Not implemented."; }
  
  method elem_to_string : string ($data_index : int) { die "Not impelmented."; }
  
  method elem_clone : object ($data : object, $data_index : int) { die "Not impelmented."; }
  
=head1 Well Known Child Classes

=over 2

=item * L<R::NDArray::Byte|SPVM::R::NDArray::Byte>

=item * L<R::NDArray::Short|SPVM::R::NDArray::Short>

=item * L<R::NDArray::Int|SPVM::R::NDArray::Int>

=item * L<R::NDArray::Float|SPVM::R::NDArray::Float>

=item * L<R::NDArray::Double|SPVM::R::NDArray::Double>

=item * L<R::NDArray::FloatComplex|SPVM::R::NDArray::FloatComplex>

=item * L<R::NDArray::DoubleComplex|SPVM::R::NDArray::DoubleComplex>

=item * L<R::NDArray::Long|SPVM::R::NDArray::Long>

=item * L<R::NDArray::Object|SPVM::R::NDArray::Object>

=item * L<R::NDArray::String|SPVM::R::NDArray::String>

=item * L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>

=item * L<R::NDArray::Time::Piece|SPVM::R::NDArray::Time::Piece>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


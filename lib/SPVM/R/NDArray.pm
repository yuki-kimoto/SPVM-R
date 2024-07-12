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

If L</"is_dim_read_only"> is a true value, an exception is thrown.

Exceptions thrown by L<R::Util#normalize_dim|SPVM::R::Util/"normalize_dim"> method could be thrown.

Exceptions thrown by L<R::Util#check_length|SPVM::R::Util/"check_length"> method could be thrown.

=head2 is_dim_read_only

C<has is_dim_read_only : ro byte;>

If this field is a true value, it indicates L</"dim"> field is read only, otherwise writable.

=head1 Class Methods

=head2 new

C<static method new : R::NDArray ($options : object[] = undef);>

Creates a new L<R::NDArray|SPVM::R::NDArray> object given the options $options and returns the created object.

This method calls L</"init"> method for initialization for the object.

Options:

=over 2

=item C<data> : object = undef

An array set to L</"data"> field.

=item C<dim> : int[] = undef

Dimensions set to L</"dim"> field.

=back

=head1 Instance Methods

=head2 init

C<protected method init : void ($options : object[] = undef);>

Initialize this instance given the options $options that is the same as L</"new"> method.

C<dim> option is assinged to $dim variable.

C<data> option is assinged to $data variable.

If $data is defined, the data type is checked. The type must be same as the type of an object created by L</"create_default_data"> method.

If $dim is not defined, $dim is created by the length of $data. $dim is set to C<[length of $data]>. If $data is not defined, $dim is set to C<[]>.

$dim is normalized by L<R::Util#normalize_dim|SPVM::R::Util/"normalize_dim"> method.

If $data is not defined, $data is created by $dim. The data length is calcurated by L<R::Util#calc_data_length|SPVM::R::Util/"calc_data_length"> method 
and L</"create_default_data"> method is called given the data length.

L<R::Util#check_length|SPVM::R::Util/"check_length"> method is called to check integrity for $dim and $data.

L</"data"> field is set to $data.

L</"dim"> field is set to $dim.

Exceptions:

If checking data type failed, an exception is thrown.

Exceptions thrown by L<R::Util#normalize_dim|SPVM::R::Util/"normalize_dim"> method could be thrown.

Exceptions thrown by L<R::Util#check_length|SPVM::R::Util/"check_length"> method could be thrown.

=head2 make_dim_read_only

C<method make_dim_read_only : void ();>

Sets L</"dim_read_only"> field to 1.

=head2 nrow

C<method nrow : int ();>

=head2 ncol

C<method ncol : int ();>

=head2 length

C<method length : int ();>

=head2 is_empty

C<method is_empty : int ();>

=head2 is_scalar

C<method is_scalar : int ();>

=head2 is_vector

C<method is_vector : int ();>

=head2 is_matrix

C<method is_matrix : int ();>

=head2 is_square_matrix

C<method is_square_matrix : int ();>

=head2 drop_dim

C<method drop_dim : void ($index : int = -1);>

=head2 expand_dim

C<method expand_dim : void ($index : int = -1);>

=head2 create_default_data

C<method create_default_data : object ($length : int = 0);>

=head2 elem_to_string

C<method elem_to_string : string ($data : object, $data_index : int);>

=head2 elem_assign

C<method elem_assign : void ($dist_data : object, $dist_data_index : int, $src_data : object, $src_data_index : int);>

=head2 elem_clone

C<method elem_clone : void ($dist_data : object, $dist_data_index : int, $src_data : object, $src_data_index : int);>

=head2 elem_cmp

C<method elem_cmp : int ($data : object, $a_data_index : int, $b_data_index : int);>

=head2 to_string_ndarray

C<method to_string_ndarray : L<R::NDArray::String|SPVM::R::NDArray::String> ();>

Converts this n-dimensional array to a n-dimensional array of L<R::NDArray::String|SPVM::R::NDArray::String> and returns it.

=head2 elem_size

C<method elem_size : int ();>

=head2 elem_type_name

C<method elem_type_name : string ();>

=head2 is_numeric_ndarray

C<method is_numeric_ndarray : int ();>

=head2 is_mulnum_ndarray

C<method is_mulnum_ndarray : int ();>

=head2 is_any_numeric_ndarray

C<method is_any_numeric_ndarray : int ();>

=head2 is_object_ndarray

C<method is_object_ndarray : int ();>

=head2 clone

C<method clone : R::NDArray ($shallow : int = 0);>

Clones this n-dimensional array and returns it.

=head2 slice

C<method slice : R::NDArray ($asix_indexes_product : L<R::NDArray::Int|SPVM::R::NDArray::Int>[]);>

Slices this n-dimensional array using the cartesian product of asix indexes $asix_indexes_product and returns it.

=head2 slice_set

C<method slice_set : void ($asix_indexes_product : L<R::NDArray::Int|SPVM::R::NDArray::Int>[], $ndarray : R::NDArray);>

=head2 to_string

C<method to_string : string ();>

=head2 order

C<method order : R::NDArray::Int ();>

=head2 set_order

C<method set_order : void ($indexes_ndarray : L<R::NDArray::Int|SPVM::R::NDArray::Int>);>

=head2 sort_asc

C<method sort_asc : void ();>

=head2 sort_desc

C<method sort_desc : void ();>

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

=item * L<R::NDArray::AnyObject|SPVM::R::NDArray::AnyObject>

=item * L<R::NDArray::String|SPVM::R::NDArray::String>

=item * L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>

=item * L<R::NDArray::Time::Piece|SPVM::R::NDArray::Time::Piece>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


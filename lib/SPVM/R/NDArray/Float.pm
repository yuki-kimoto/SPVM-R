package SPVM::R::NDArray::Float;



1;

=head1 Name

SPVM::R::NDArray::Float - N-Dimensional Array of float Type.

=head1 Description

R::NDArray::Float class in L<SPVM> represents n-dimensional array of C<float> type.

=head1 Usage

  use R::NDArray::Float;
  
  my $ndarray = R::NDArray::Float->new({data => [(float)1, 2, 3, 4, 5, 6], dim => [3, 2]});

=head1 Super Class

L<R::NDArray|SPVM::R::NDArray>

=head1 Field

=head2 data

C<method data : float[] ();>

Same as L<R::NDArray#data|SPVM::R::NDArray/"data"> method, but the return type is different.

=head1 Class Methods

C<static method new : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($options : object[] = undef);>

Creates a new L<R::NDArray::Float|SPVM::R::NDArray::Float> and returns it.

This method calls L<R::NDArray#init|SPVM::R::NDArray/"init"> method given the options $options.

=head1 Instance Methods

=head2 create_default_data

C<method create_default_data : float[] ($length : int = 0);>

Creates a default data given the length $length and returns it.

=head2 elem_to_string

C<method elem_to_string : string ($data : float[], $data_index : int);>

Converts an element $data at index $data_index to a string and returns it.

=head2 elem_assign

C<method elem_assign : void ($dist_data : float[], $dist_data_index : int, $src_data : float[], $src_data_index : int);>

Assigns the element $src_data at index $src_data_index to the element $dist_data at index $dist_data_index.

=head2 elem_clone

C<method elem_clone : void ($dist_data : float[], $dist_data_index : int, $src_data : float[], $src_data_index : int);>

Copies the element $src_data at index $src_data_indext to the element $dist_data at index $dist_data_index.

=head2 elem_cmp

C<method elem_cmp : int ($data : float[], $a_data_index : int, $b_data_index : int);>

Compares the element $data at index $a_data_index and the element $data at index $b_data_index and returns the result.

=head2 clone

C<method clone : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($shallow : int = 0);>

Same as L<R::NDArray#clone|SPVM::R::NDArray/"clone"> method, but the return type is different.

=head2 slice

C<method slice : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($asix_indexes_product : L<R::NDArray::Int|SPVM::R::NDArray::Int>[]);>

Same as L<R::NDArray#slice|SPVM::R::NDArray/"slice"> method, but the return type is different.

=head2 to_int_ndarray

C<method to_int_ndarray : L<R::NDArray::Int|SPVM::R::NDArray::Int> ();>

Converts this n-dimensional array to a n-dimensional array of L<R::NDArray::Int|SPVM::R::NDArray::Int> and returns it.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


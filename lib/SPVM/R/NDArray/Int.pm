package SPVM::R::NDArray::Int;



1;

=head1 Name

SPVM::R::NDArray::Int - N-Dimensional Array of int Type.

=head1 Description

R::NDArray::Int class in L<SPVM> represents n-dimensional array of C<int> type.

=head1 Usage

  use R::NDArray::Int;
  
  my $ndarray = R::NDArray::Int->new({data => [(int)1, 2, 3, 4, 5, 6], dim => [3, 2]});

=head1 Super Class

L<R::NDArray|SPVM::R::NDArray>

=head1 Field

=head2 data

C<method data : int[] ();>

Same as L<R::NDArray#data|SPVM::R::NDArray/"data"> method, but the return type is different.

=head1 Class Methods

C<static method new : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($options : object[] = undef);>

Creates a new L<R::NDArray::Int|SPVM::R::NDArray::Int> and returns it.

This method calls L<R::NDArray#init|SPVM::R::NDArray/"init"> method given the options $options.

=head1 Instance Methods

=head2 create_default_data

C<method create_default_data : int[] ($length : int = 0);>

Creates a default data given the length $length and returns it.

=head2 elem_to_string

C<method elem_to_string : string ($data : int[], $data_index : int);>

Converts an element $data at index $data_index to a string and returns it.

=head2 elem_assign

C<method elem_assign : void ($dist_data : int[], $dist_data_index : int, $src_data : int[], $src_data_index : int);>

Assigns the element $src_data at index $src_data_index to the element $dist_data at index $dist_data_index.

=head2 elem_clone

C<method elem_clone : void ($dist_data : int[], $dist_data_index : int, $src_data : int[], $src_data_index : int);>

Copies the element $src_data at index $src_data_indext to the element $dist_data at index $dist_data_index.

=head2 elem_cmp

C<method elem_cmp : int ($data : int[], $a_data_index : int, $b_data_index : int);>

Compares the element $data at index $a_data_index and the element $data at index $b_data_index and returns the result.

=head2 clone

C<method clone : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($shallow : int = 0);>

Same as L<R::NDArray#clone|SPVM::R::NDArray/"clone"> method, but the return type is different.

=head2 slice

C<method slice : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($asix_indexes_product : L<R::NDArray::Int|SPVM::R::NDArray::Int>[]);>

Same as L<R::NDArray#slice|SPVM::R::NDArray/"slice"> method, but the return type is different.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


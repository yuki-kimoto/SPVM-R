package SPVM::R::NDArray::StringBuffer;



1;

=head1 Name

SPVM::R::NDArray::StringBuffer - N-Dimensional Array of StringBuffer Type.

=head1 Description

R::NDArray::StringBuffer class in L<SPVM> represents n-dimensional array of C<StringBuffer> type.

=head1 Usage

  use R::NDArray::StringBuffer;
  
  my $data = [
    StringBuffer->new("a"),
    StringBuffer->new("b"),
    StringBuffer->new("c"),
    StringBuffer->new("d"),
    StringBuffer->new("e"),
    StringBuffer->new("f")
  ];
  
  my $ndarray = R::NDArray::String->new({data => $data, dim => [3, 2]});

=head1 Super Class

L<R::NDArray|SPVM::R::NDArray>

=head1 Field

=head2 data

C<method data : StringBuffer[] ();>

Same as L<R::NDArray#data|SPVM::R::NDArray/"data"> method, but the return type is different.

=head1 Class Methods

=head2 new

C<static method new : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer> ($options : object[] = undef);>

Creates a new L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer> given the options $options and returns it.

This method calls L<R::NDArray#init|SPVM::R::NDArray/"init"> method given the options $options.

=head1 Instance Methods

=head2 create_default_data

C<method create_default_data : L<StringBuffer|SPVM::StringBuffer>[] ($length : int = 0);>

Creates a default data given the length $length and returns it.

The default data is created by the following code.

  my $default_data = new StringBuffer[$length];

Exceptions:

The length $length must be more than or equal to 0. Otherwise an exception is thrown.

=head2 elem_to_string

C<method elem_to_string : string ($data : L<StringBuffer|SPVM::StringBuffer>[], $data_index : int);>

The string is created by the following code.

Converts an element $data at index $data_index to a string and returns it.

  my $string = (string)undef;
  if ($data->[$data_index]) {
    $string = $data->[$data_index]->to_string;
  }

=head2 elem_assign

C<method elem_assign : void ($dist_data : L<StringBuffer|SPVM::StringBuffer>[], $dist_data_index : int, $src_data : L<StringBuffer|SPVM::StringBuffer>[], $src_data_index : int);>

Assigns the element $src_data at index $src_data_index to the element $dist_data at index $dist_data_index.

=head2 elem_clone

C<method elem_clone : void ($dist_data : L<StringBuffer|SPVM::StringBuffer>[], $dist_data_index : int, $src_data : L<StringBuffer|SPVM::StringBuffer>[], $src_data_index : int);>

Clones the element $src_data at index $src_data_indext to the element $dist_data at index $dist_data_index.

The clone is created by the following code.
  
  $dist_data->[$dist_data_index] = (StringBuffer)undef;
  if ($src_data->[$src_data_index]) {
    $dist_data->[$dist_data_index] = StringBuffer->new($src_data->[$src_data_index]->to_string);
  }

=head2 elem_cmp

C<method elem_cmp : int ($a_data : L<StringBuffer|SPVM::StringBuffer>[], $a_data_index : int, $b_data : L<StringBuffer|SPVM::StringBuffer>[], $b_data_index : int);>

Compares the element $a_data at index $a_data_index and the element $b_data at index $b_data_index using L<StringBuffer#cmp|SPVM::StringBuffer/"cmp"> method, and returns its return value.

=head2 elem_is_na

C<method elem_is_na : int ($data : object, $data_index : int);>

Checks if an element represets NA.

If the element $data at index $data_index is not defined, returns 1, otherwise returns 0.

=head2 clone

C<method clone : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer> ($shallow : int = 0);>

Same as L<R::NDArray#clone|SPVM::R::NDArray/"clone"> method, but the return type is different.

=head2 slice

C<method slice : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer> ($indexes_product : L<R::NDArray::Int|SPVM::R::NDArray::Int>[]);>

Same as L<R::NDArray#slice|SPVM::R::NDArray/"slice"> method, but the return type is different.

=head1 See Also

=over 2

=item * L<R::OP::StringBuffer|SPVM::R::OP::StringBuffer>

=item * L<R::NDArray|SPVM::R::NDArray>

=item * L<R|SPVM::R>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


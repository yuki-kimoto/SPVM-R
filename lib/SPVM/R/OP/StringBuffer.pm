package SPVM::R::OP::StringBuffer;



1;

=head1 Name

SPVM::R::OP::StringBuffer - N-Dimensional Array Operations for R::NDArray::StringBuffer

=head1 Description

R::OP::StringBuffer class in L<SPVM> has methods for n-dimensional array operations for L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>.

=head1 Usage

  use R::OP::StringBuffer as BUFOP;
  
  my $ndarray_scalar = BUFOP->c(StringBuffer->new("a"));
  
  my $ndarray_scalar = BUFOP->c("a");
  
  my $data = [
    StringBuffer->new("a"),
    StringBuffer->new("b"),
    StringBuffer->new("c"),
    StringBuffer->new("d"),
    StringBuffer->new("e"),
    StringBuffer->new("f")
  ];
  
  my $ndarray_vector = BUFOP->c($data);
  
  my $ndarray_vector = BUFOP->c([(string)"a", "b", "c", "d", "e", "f"]);
  
  my $ndarray = BUFOP->c($data, [3, 2]);
  
  my $ndarray2 = BUFOP->c($ndarray);

=head1 Class Methods

=head2 c

C<static method c : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer> ($data : object of StringBuffer|StringBuffer[]|L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>|string|string[]|L<R::NDArray::String|SPVM::R::NDArray::String>, $dim : int[] = undef);>

Creates a new L<R::NDArray::Double|SPVM::R::NDArray::Double> object given the data $data and the dimensions $dim.

Implemetation:

If $data is defined and the type of $data is L<StringBuffer|SPVM::StringBuffer>, $data is set to C<[(StringBuffer)$data->(StringBuffer)]>.

If $data is defined and the type of $data is L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $dim is set to C<$data-E<gt>(R::NDArray::StringBuffer)-E<gt>dim> unless $dim is defined and $data is set to C<$data-E<gt>(R::NDArray::StringBuffer)-E<gt>data>.

If $data is defined and the type of $data is C<string>, $data is set to C<[StringBuffer-E<gt>new((string)$data)]>.

If $data is defined and the type of $data is C<string[]>, $data is set to the return value of C<R::OP::String->c((string[])$data)->to_string_buffer_ndarray->data>.

If $data is defined and the type of $data is L<R::NDArray::String|SPVM::R::NDArray::String>, $dim is set to C<$data-E<gt>(R::NDArray::String)-E<gt>dim> unless $dim is defined and $data is set to C<$data-E<gt>(R::NDArray::String)-E<gt>to_string_buffer_ndarray-E<gt>data>.

And this method calls L<R::NDArray::StringBuffer#new|SPVM::R::NDArray::StringBuffer/"new"> method given $dim and $data.

Exceptions:

The type of the data $data must be StringBuffer, StringBuffer[], R::NDArray::StringBuffer, string, string[], R::NDArray::String if defined. Othrewise, an exception is thrown.

=head2 push

C<static method push : void ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $y_ndarray : L<R::NDArray::String|SPVM::R::NDArray::String>);>

Creates a new L<R::NDArray::String|SPVM::R::NDArray::String> object of the same dimensions as the n-dimensional array $x_ndarray for a return value, performs L<$x_elem->(StringBuffer)->push($y_elem)|StringBuffer/"push" method on each element(named $x_elem, $y_elem) of the n-dimensional array $x_ndarray and $y_ndarray, and sets each element of the new n-dimensional array to the each operation result, and returns the new n-dimensional array.

If C<push> method throw an exceptions, $x_elem is unchanged.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise, an exception is thrown.

The dimensions of $x_ndarray must be equal to the dimensions of $y_ndarray. Otherwise, an exception is thrown.

=head2 eq

C<static method eq : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $y_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>);>

Creates a new L<R::NDArray::Int|SPVM::R::NDArray::Int> object of the same dimensions as the n-dimensional array $x_ndarray for a return value, performs string comparison C<eq> operation on the each stringified element of the n-dimensional array $x_ndarray and $y_ndarray, and sets each element of the new n-dimensional array to the each operation result, and returns the new n-dimensional array.

A stringified element means if an element is undef, it is undef, otherwise it is the return value of L<R::NDArray::StringBuffer#to_string|SPVM::StringBuffer/"to_string"> method.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise, an exception is thrown.

The dimensions of $x_ndarray must be equal to the dimensions of $y_ndarray. Otherwise, an exception is thrown.

=head2 ne

C<static method ne : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $y_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>);>

Creates a new L<R::NDArray::Int|SPVM::R::NDArray::Int> object of the same dimensions as the n-dimensional array $x_ndarray for a return value, performs string comparison C<ne> operation on the each stringified element of the n-dimensional array $x_ndarray and $y_ndarray, and sets each element of the new n-dimensional array to the each operation result, and returns the new n-dimensional array.

A stringified element means if an element is undef, it is undef, otherwise it is the return value of L<R::NDArray::StringBuffer#to_string|SPVM::StringBuffer/"to_string"> method.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise, an exception is thrown.

The dimensions of $x_ndarray must be equal to the dimensions of $y_ndarray. Otherwise, an exception is thrown.

=head2 gt

C<static method gt : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $y_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>);>

Creates a new L<R::NDArray::Int|SPVM::R::NDArray::Int> object of the same dimensions as the n-dimensional array $x_ndarray for a return value, performs string comparison C<gt> operation on the each stringified element of the n-dimensional array $x_ndarray and $y_ndarray, and sets each element of the new n-dimensional array to the each operation result, and returns the new n-dimensional array.

A stringified element means if an element is undef, it is undef, otherwise it is the return value of L<R::NDArray::StringBuffer#to_string|SPVM::StringBuffer/"to_string"> method.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise, an exception is thrown.

The dimensions of $x_ndarray must be equal to the dimensions of $y_ndarray. Otherwise, an exception is thrown.

=head2 ge

C<static method ge : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $y_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>);>

Creates a new L<R::NDArray::Int|SPVM::R::NDArray::Int> object of the same dimensions as the n-dimensional array $x_ndarray for a return value, performs string comparison C<ge> operation on the each stringified element of the n-dimensional array $x_ndarray and $y_ndarray, and sets each element of the new n-dimensional array to the each operation result, and returns the new n-dimensional array.

A stringified element means if an element is undef, it is undef, otherwise it is the return value of L<R::NDArray::StringBuffer#to_string|SPVM::StringBuffer/"to_string"> method.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise, an exception is thrown.

The dimensions of $x_ndarray must be equal to the dimensions of $y_ndarray. Otherwise, an exception is thrown.

=head2 lt

C<static method lt : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $y_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>);>

Creates a new L<R::NDArray::Int|SPVM::R::NDArray::Int> object of the same dimensions as the n-dimensional array $x_ndarray for a return value, performs string comparison C<lt> operation on the each stringified element of the n-dimensional array $x_ndarray and $y_ndarray, and sets each element of the new n-dimensional array to the each operation result, and returns the new n-dimensional array.

A stringified element means if an element is undef, it is undef, otherwise it is the return value of L<R::NDArray::StringBuffer#to_string|SPVM::StringBuffer/"to_string"> method.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise, an exception is thrown.

The dimensions of $x_ndarray must be equal to the dimensions of $y_ndarray. Otherwise, an exception is thrown.

=head2 le

C<static method le : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $y_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>);>

Creates a new L<R::NDArray::Int|SPVM::R::NDArray::Int> object of the same dimensions as the n-dimensional array $x_ndarray for a return value, performs string comparison C<le> operation on the each stringified element of the n-dimensional array $x_ndarray and $y_ndarray, and sets each element of the new n-dimensional array to the each operation result, and returns the new n-dimensional array.

A stringified element means if an element is undef, it is undef, otherwise it is the return value of L<R::NDArray::StringBuffer#to_string|SPVM::StringBuffer/"to_string"> method.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise, an exception is thrown.

The dimensions of $x_ndarray must be equal to the dimensions of $y_ndarray. Otherwise, an exception is thrown.

=head2 rep

C<static method rep : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer> ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $times : int);>

Same as L<R::OP#rep|SPVM::R::OP/"rep"> method, but the return type is different.

=head2 rep_length

C<static method rep_length : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer> ($x_ndarray : L<R::NDArray::StringBuffer|SPVM::R::NDArray::StringBuffer>, $length : int);>

Same as L<R::OP#rep_length|SPVM::R::OP/"rep_length"> method, but the return type is different.

=head1 See Also

=over 2

=item * L<R::OP|SPVM::R::OP>

=item * L<R::NDArray::StringBufferBuffer|SPVM::R::NDArray::StringBufferBuffer>

=item * L<R::NDArray|SPVM::R::NDArray>

=item * L<R|SPVM::R>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


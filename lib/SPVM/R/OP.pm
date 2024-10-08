package SPVM::R::OP;



1;

=head1 Name

SPVM::R::OP - N-Dimensional Array Operations

=head1 Description

R::OP class in L<SPVM> has methods for operations for L<R::NDArray|SPVM::R::NDArray>.

=head1 Usage

  use R::OP;
  use R::IO::Int as IOP;
  
  my $ndarray1 = IOP->c([1, 2, 3]);
  
  my $ndarray2 = IOP->c([3, 4, 5]);
  
  my $equals_dim = R::OP->equals_dim($ndarray1, $ndarray2);

=head1 Related Modules

=over 2

=item * L<R::OP|SPVM::R::OP>

=item * L<R::OP::Byte|SPVM::R::OP::Byte>

=item * L<R::OP::Short|SPVM::R::OP::Short>

=item * L<R::OP::Int|SPVM::R::OP::Int>

=item * L<R::OP::Long|SPVM::R::OP::Long>

=item * L<R::OP::Float|SPVM::R::OP::Float>

=item * L<R::OP::Double|SPVM::R::OP::Double>

=item * L<R::OP::FloatComplex|SPVM::R::OP::FloatComplex>

=item * L<R::OP::DoubleComplex|SPVM::R::OP::DoubleComplex>

=item * L<R::OP::AnyObject|SPVM::R::OP::AnyObject>

=item * L<R::OP::String|SPVM::R::OP::String>

=item * L<R::OP::StringBuffer|SPVM::R::OP::StringBuffer>

=item * L<R::OP::Time::Piece|SPVM::R::OP::Time::Piece>

=item * L<R::OP::Matrix::Float|SPVM::R::OP::Matrix::Float>

=item * L<R::OP::Matrix::Double|SPVM::R::OP::Matrix::Double>

=item * L<R::OP::Matrix::FloatComplex|SPVM::R::OP::Matrix::FloatComplex>

=item * L<R::OP::Matrix::DoubleComplex|SPVM::R::OP::Matrix::DoubleComplex>

=back

=head1 Class Methods

=head2 equals_dim

C<static method equals_dim : int ($x_ndarray : L<R::NDArray|SPVM::R::NDArray>, $y_ndarray : L<R::NDArray|SPVM::R::NDArray>);>

If the dimensions of $x_ndarray is equal to the dimensions of $x_ndarray, returns 1, otherwise returns 0.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise an exception is thrown.

=head2 equals_dropped_dim

C<static method equals_dropped_dim : int ($x_ndarray : L<R::NDArray|SPVM::R::NDArray>, $y_ndarray : L<R::NDArray|SPVM::R::NDArray>);>

If the dimensions of $x_ndarray on which L<R::Util#drop_dim|SPVM::R::Util/"drop_dim"> method is performed is equal to the dimensions of $x_ndarray on which L<R::Util#drop_dim|SPVM::R::Util/"drop_dim"> method is performed, returns 1, otherwise returns 0.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise an exception is thrown.

=head2 rep

C<static method rep : L<R::NDArray|SPVM::R::NDArray> ($x_ndarray : L<R::NDArray|SPVM::R::NDArray>, $times : int);>

Creates a new L<R::NDArray|SPVM::R::NDArray> object by repeating the data of $x_ndarray $times times.

The type of new object is the same as the type of $x_ndarray, and the dimensions is C<[$length * $times]>. ($leghth is the length of $x_ndarray).

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise an exception is thrown.

The repeat count $times must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 rep_length

C<static method rep_length : L<R::NDArray|SPVM::R::NDArray> ($x_ndarray : L<R::NDArray|SPVM::R::NDArray>, $length : int);>

Creates a new L<R::NDArray|SPVM::R::NDArray> object by repeating the data of $x_ndarray up to length $length.

The type of new object is the same as the type of $x_ndarray, and the dimensions is C<[$length]>.

Exceptions:

The length $length must be greater than or equal to 0. Otherwise an exception is thrown.

The length $length must be devided by the length of the n-dimensional array $x_ndarray. Otherwise an exception is thrown.

=head2 is_na

C<static method is_na : L<R::NDArray::Int|SPVM::R::NDArray::Int> ($x_ndarray : L<R::NDArray|SPVM::R::NDArray>);>

Creates a new L<R::NDArray::Int|SPVM::R::NDArray::Int> object by performing L<R::NDArray#elem_is_na|SPVM::R::NDArray/"elem_is_na"> on all elements of the n-dimensional array $x_ndarray.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise an exception is thrown.

=head1 See Also

=over 2

=item * L<R::NDArray|SPVM::R::NDArray>

=item * L<R|SPVM::R>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


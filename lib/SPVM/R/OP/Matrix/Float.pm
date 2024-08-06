package SPVM::R::OP::Matrix::Float;



1;

=head1 Name

SPVM::R::OP::Matrix::Float - Matrix Operations for R::NDArray::Float

=head1 Description

R::OP::Matrix::Float class in L<SPVM> has methods for matrix operations for L<R::NDArray::Float|SPVM::R::NDArray::Float>.

=head1 Usage

  use R::OP::Matrix::Float as MFOP;
  
  my $nrow = 3;
  my $ncol = 2;
  my $ndarray = MFOP->matrix([(float)1, 2, 3, 4, 5, 6], $nrow, $ncol);

See also L<Matrix Examples|https://github.com/yuki-kimoto/SPVM-R/wiki/SPVM%3A%3AR-Matrix-Examples>.

=head1 Class Methods

=head2 matrix

C<static method matrix : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($data : object of L<Float|SPVM::Float>|float[]|L<R::NDArray::Float|SPVM::R::NDArray::Float>, $nrow : int, $ncol : int);>

Creates a new L<R::NDArray::Float|SPVM::R::NDArray::Float> object that represents a matrix given the data $data, the row numers $nrow, and the column numbers $ncol, and returns the new object.

This method calls L<R::OP::Float#c|SPVM::R::OP::Float/"c"> method.

  my $ret_ndarray = R::OP::Float->c($data, [$nrow, $ncol]);

Exceptions:

Exceptions thrown by L<R::OP::Float#c|SPVM::R::OP::Float/"c"> method could be thrown.

=head2 matrix_byrow

C<static method matrix_byrow : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($data : object of L<Float|SPVM::Float>|float[]|L<R::NDArray::Float|SPVM::R::NDArray::Float>, $nrow : int, $ncol : int);>

Same as L</"matrix"> method, but the input data $data is interpreted as column major order.

Exceptions:

Exceptions thrown by L</"matrix"> method could be thrown.

=head2 cbind

C<static method cbind : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

Same as L<R::OP::Matrix#cbind|SPVM::R::OP::Matrix/"cbind"> method, but the return type is different.

=head2 rbind

C<static method rbind : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

Same as L<R::OP::Matrix#rbind|SPVM::R::OP::Matrix/"rbind"> method, but the return type is different.

=head2 diag

C<static method diag : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

Creates a L<R::NDArray::Float|SPVM::R::NDArray::Float> object that represents a diagonal matrix given a n-dimensional array $x_ndarray that is a vector with diagonal values, and returns the new object.

The row numbers and column numbers of the new object is equal to the value of C<length> field of $x_ndarray.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $x_ndarray must be a vector. Otherwise, an exception is thrown.

=head2 slice_diag

C<static method slice_diag : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : R::NDArray::Float);>

Creates a new L<R::NDArray::Float|SPVM::R::NDArray::Float>, sets its data to the diagonal values of the n-dimension array $x_ndarray that is a matrix, and returns the new object.

The value of C<length> field of the new object is equal to the row numbers of $x_ndarray.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $x_ndarray must be a matrix. Otherwise, an exception is thrown.

=head2 identity

C<static method identity : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($nrow : int);>

Creates a new L<R::NDArray::Float|SPVM::R::NDArray::Float> object that represets an identity matrix given the row numbers $nrow, and returns the new object.

Exceptions:

The row numbers $nrow must be greater than 0. Otherwise, an exception is thrown.

=head2 mul

C<static method mul : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

Performs a matrix multiplication on the n-dimension array $x_ndarray that is a matrix and the n-dimension array $y_ndarray that is a matrix.

And creates a new L<R::NDArray::Float|SPVM::R::NDArray::Float> object with the result, and returns the new object.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $x_ndarray must be a matrix. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $y_ndarray must be a matrix. Otherwise, an exception is thrown.

The column numbers of the matrix $x_ndarray must be equal to the row numbers of the matrix $y_ndarray. Otherwise, an exception is thrown.

=head2 t

C<static method t : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

Performs a matrix transpose on the n-dimension array $x_ndarray that is a matrix, creates a new L<R::NDArray::Float|SPVM::R::NDArray::Float> object with the result, and returns the new object.

Excetpions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $x_ndarray must be a matrix. Otherwise, an exception is thrown.

=head2 det

C<static method det : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

Calculates the determinant of the n-dimension array $x_ndarray that is a matrix, creates a new L<R::NDArray::Float|SPVM::R::NDArray::Float> object with the result, and returns the new object.

The new object is a scalar.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $x_ndarray must be a square matrix. Otherwise, an exception is thrown.

=head2 solve

C<static method solve : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

Calculates the inverse of the n-dimension array $x_ndarray that is a matrix, creates a new L<R::NDArray::Float|SPVM::R::NDArray::Float> object with the result, and returns the new object.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $x_ndarray must be a square matrix. Otherwise, an exception is thrown.

The determinant of the n-dimensional array $x_ndarray that is a matrix must not be equal to 0. Otherwise, an exception is thrown.

=head2 eigen

C<static method eigen : L<R::NDArray::Hash|SPVM::R::NDArray::Hash> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

Finds the eigenvectors and eigenvalues of the n-dimension array $x_ndarray that is a matrix, and creates a new two L<R::NDArray::FloatComplex|SPVM::R::NDArray::FloatComplex> object for each results.

And creates a new L<R::NDArray::Hash|SPVM::R::NDArray::Hash> object, sets the value of key C<"vectors"> to the new object that has the eigenvectors, sets the value of key C<"values"> to the new object that has the eigenvalues. Note that these vectores and values are complex numbers even if the result is able to be represented by real numbers.

And returns the new L<R::NDArray::Hash|SPVM::R::NDArray::Hash>.

Exceptions:

The n-dimensional array $x_ndarray must be defined. Otherwise, an exception is thrown.

The n-dimensional array $x_ndarray must be a square matrix. Otherwise, an exception is thrown.

=head1 See Also

=over 2

=item * L<Matrix Examples|https://github.com/yuki-kimoto/SPVM-R/wiki/SPVM%3A%3AR-Matrix-Examples>

=item * L<R::OP::Float|SPVM::R::OP::Float>

=item * L<R::NDArray::Float|SPVM::R::NDArray::Float>

=item * L<R::NDArray|SPVM::R::NDArray>

=item * L<R|SPVM::R>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


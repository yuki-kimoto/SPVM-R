package SPVM::R::OP::Float;



1;

=head1 Name

SPVM::R::OP::Float - N-Dimensional Array Operations for R::NDArray::Float

=head1 Description

The R::OP::Float class in L<SPVM> has methods for n-dimensional array operations for L<R::NDArray::Float|SPVM::R::NDArray::Float>.

=head1 Usage

  use R::OP::Float as FOP;
  
  my $ndarray_scalar = FOP->c((float)1);
  
  my $ndarray_vector = FOP->c([(float)1, 2, 3]);
  
  my $ndarray = FOP->c([(float)1, 2, 3, 4, 5, 6], [3, 2]);
  
  my $ndarray2 = FOP->c($ndarray);

=head1 Class Methods

=head2 c

C<method c : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($data : object of L<Float|SPVM::Float>|float[]|L<R::NDArray::Float|SPVM::R::NDArray::Float>, $dim : int[] = undef);>

=head2 add

C<method add : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 sub

C<method sub : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 mul

C<method mul : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 scamul

C<static method scamul : R::NDArray::Int ($scalar_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 div

C<method div : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 scadiv

C<static method scadiv : R::NDArray::Int ($scalar_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 neg

C<method neg : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 abs

C<method abs : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 eq

C<method eq : R::NDArray::Int ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 ne

C<method ne : R::NDArray::Int ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 gt

C<method gt : R::NDArray::Int ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 ge

C<method ge : R::NDArray::Int ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 lt

C<method lt : R::NDArray::Int ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 le

C<method le : R::NDArray::Int ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 rep

C<method rep : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : R::NDArray, $times : int);>

=head2 rep_length

C<method rep_length : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : R::NDArray, $length : int);>

=head2 seq

C<method seq : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($begin : float, $end : float, $by : float = 1);>

=head2 seq_length

C<method seq_length : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($begin : float, $end : float, $length : int);>

=head2 sin

C<method sin : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 cos

C<method cos : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 tan

C<method tan : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 sinh

C<method sinh : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 cosh

C<method cosh : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 tanh

C<method tanh : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 acos

C<method acos : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 asin

C<method asin : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 atan

C<method atan : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 asinh

C<method asinh : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 acosh

C<method acosh : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 atanh

C<method atanh : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 exp

C<method exp : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 expm1

C<method expm1 : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 log

C<method log : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 logb

C<method logb : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 log2

C<method log2 : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 log10

C<method log10 : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 sqrt

C<method sqrt : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 isinf

C<method isinf : R::NDArray::Int ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 isnan

C<method isnan : R::NDArray::Int ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 pow

C<method pow : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 atan2

C<method atan2 : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 modf

C<method modf : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $intpart_ndarray_ref : L<R::NDArray::Float|SPVM::R::NDArray::Float>[]);>

=head2 ceil

C<method ceil : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 floor

C<method floor : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 round

C<method round : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 lround

C<method lround : R::NDArray::Long ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 remainder

C<method remainder : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 fmod

C<method fmod : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>, $y_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 sum

C<method sum : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 cumsum

C<method cumsum : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 prod

C<method prod : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head2 cumprod

C<method cumprod : L<R::NDArray::Float|SPVM::R::NDArray::Float> ($x_ndarray : L<R::NDArray::Float|SPVM::R::NDArray::Float>);>

=head1 See Also

=over 2

=item * L<R::NDArray::Float|SPVM::R::NDArray::Float>

=item * L<R::NDArray|SPVM::R::NDArray>

=item * L<R|SPVM::R>

=back

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


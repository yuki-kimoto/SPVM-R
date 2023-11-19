#ifndef PERL_RSTATS_ELEMENTFUNC_H
#define PERL_RSTATS_ELEMENTFUNC_H

#include <complex>
#include <cmath>

#include "Rstats_Util.h"

namespace Rstats {
  namespace ElementFunc {

    Rstats::Complex add(Rstats::Complex, Rstats::Complex);
    Rstats::Double add(Rstats::Double, Rstats::Double);
    Rstats::Integer add(Rstats::Integer, Rstats::Integer);

    Rstats::Complex subtract(Rstats::Complex, Rstats::Complex);
    Rstats::Double subtract(Rstats::Double, Rstats::Double);
    Rstats::Integer subtract(Rstats::Integer, Rstats::Integer);

    Rstats::Complex multiply(Rstats::Complex, Rstats::Complex);
    Rstats::Double multiply(Rstats::Double, Rstats::Double);
    Rstats::Integer multiply(Rstats::Integer, Rstats::Integer);

    Rstats::Complex divide(Rstats::Complex, Rstats::Complex);
    Rstats::Double divide(Rstats::Double, Rstats::Double);
    Rstats::Double divide(Rstats::Integer, Rstats::Integer);

    Rstats::Complex pow(Rstats::Complex, Rstats::Complex);
    Rstats::Double pow(Rstats::Double, Rstats::Double);
    Rstats::Double pow(Rstats::Integer, Rstats::Integer);

    Rstats::Complex remainder(Rstats::Complex, Rstats::Complex);
    Rstats::Double remainder(Rstats::Double, Rstats::Double);
    Rstats::Double remainder(Rstats::Integer, Rstats::Integer);

    Rstats::Double Re(Rstats::Complex);
    Rstats::Double Re(Rstats::Double);
    Rstats::Double Re(Rstats::Integer);

    Rstats::Double Im(Rstats::Complex);
    Rstats::Double Im(Rstats::Double);
    Rstats::Double Im(Rstats::Integer);

    Rstats::Complex Conj(Rstats::Complex);
    Rstats::Double Conj(Rstats::Double);
    Rstats::Double Conj(Rstats::Integer);

    Rstats::Complex sin(Rstats::Complex);
    Rstats::Double sin(Rstats::Double);
    Rstats::Double sin(Rstats::Integer);
    
    Rstats::Complex cos(Rstats::Complex);
    Rstats::Double cos(Rstats::Double);
    Rstats::Double cos(Rstats::Integer);

    Rstats::Complex tan(Rstats::Complex);
    Rstats::Double tan(Rstats::Double);
    Rstats::Double tan(Rstats::Integer);

    Rstats::Complex sinh(Rstats::Complex);
    Rstats::Double sinh(Rstats::Double);
    Rstats::Double sinh(Rstats::Integer);

    Rstats::Complex cosh(Rstats::Complex);
    Rstats::Double cosh(Rstats::Double);
    Rstats::Double cosh(Rstats::Integer);

    Rstats::Complex tanh (Rstats::Complex z);
    Rstats::Double tanh(Rstats::Double);
    Rstats::Double tanh(Rstats::Integer);

    Rstats::Double abs(Rstats::Complex);
    Rstats::Double abs(Rstats::Double);
    Rstats::Double abs(Rstats::Integer);

    Rstats::Double Mod(Rstats::Complex);
    Rstats::Double Mod(Rstats::Double);
    Rstats::Double Mod(Rstats::Integer);

    Rstats::Complex log(Rstats::Complex);
    Rstats::Double log(Rstats::Double);
    Rstats::Double log(Rstats::Integer);

    Rstats::Complex logb(Rstats::Complex);
    Rstats::Double logb(Rstats::Double);
    Rstats::Double logb(Rstats::Integer);

    Rstats::Complex log10(Rstats::Complex);
    Rstats::Double log10(Rstats::Double);
    Rstats::Double log10(Rstats::Integer);

    Rstats::Complex log2(Rstats::Complex);
    Rstats::Double log2(Rstats::Double);
    Rstats::Double log2(Rstats::Integer);
    
    Rstats::Complex expm1(Rstats::Complex);
    Rstats::Double expm1(Rstats::Double);
    Rstats::Double expm1(Rstats::Integer);

    Rstats::Double Arg(Rstats::Complex);
    Rstats::Double Arg(Rstats::Double);
    Rstats::Double Arg(Rstats::Integer);

    Rstats::Complex exp(Rstats::Complex);
    Rstats::Double exp(Rstats::Double);
    Rstats::Double exp(Rstats::Integer);

    Rstats::Complex sqrt(Rstats::Complex);
    Rstats::Double sqrt(Rstats::Double);
    Rstats::Double sqrt(Rstats::Integer);

    Rstats::Complex atan(Rstats::Complex);
    Rstats::Double atan(Rstats::Double);
    Rstats::Double atan(Rstats::Integer);

    Rstats::Complex asin(Rstats::Complex);
    Rstats::Double asin(Rstats::Double);
    Rstats::Double asin(Rstats::Integer);

    Rstats::Complex acos(Rstats::Complex);
    Rstats::Double acos(Rstats::Double);
    Rstats::Double acos(Rstats::Integer);

    Rstats::Complex asinh(Rstats::Complex);
    Rstats::Double asinh(Rstats::Double);
    Rstats::Double asinh(Rstats::Integer);

    Rstats::Complex acosh(Rstats::Complex);
    Rstats::Double acosh(Rstats::Double);
    Rstats::Double acosh(Rstats::Integer);

    Rstats::Complex atanh(Rstats::Complex);
    Rstats::Double atanh(Rstats::Double);
    Rstats::Double atanh(Rstats::Integer);
    
    Rstats::Complex negate(Rstats::Complex);
    Rstats::Double negate(Rstats::Double);
    Rstats::Integer negate(Rstats::Integer);

    Rstats::Complex atan2(Rstats::Complex, Rstats::Complex);
    Rstats::Double atan2(Rstats::Double, Rstats::Double);
    Rstats::Double atan2(Rstats::Integer, Rstats::Integer);

    Rstats::Double And(Rstats::Character, Rstats::Character);
    Rstats::Double And(Rstats::Complex, Rstats::Complex);
    Rstats::Double And(Rstats::Double, Rstats::Double);
    Rstats::Double And(Rstats::Integer, Rstats::Integer);

    Rstats::Double Or(Rstats::Character, Rstats::Character);
    Rstats::Double Or(Rstats::Complex, Rstats::Complex);
    Rstats::Double Or(Rstats::Double, Rstats::Double);
    Rstats::Double Or(Rstats::Integer, Rstats::Integer);
    
    Rstats::Double equal(Rstats::Character, Rstats::Character);
    Rstats::Double equal(Rstats::Complex, Rstats::Complex);
    Rstats::Double equal(Rstats::Double, Rstats::Double);
    Rstats::Double equal(Rstats::Integer, Rstats::Integer);

    Rstats::Double not_equal(Rstats::Character, Rstats::Character);
    Rstats::Double not_equal(Rstats::Complex, Rstats::Complex);
    Rstats::Double not_equal(Rstats::Double, Rstats::Double);
    Rstats::Double not_equal(Rstats::Integer, Rstats::Integer);

    Rstats::Double more_than(Rstats::Character, Rstats::Character);
    Rstats::Double more_than(Rstats::Complex, Rstats::Complex);
    Rstats::Double more_than(Rstats::Double, Rstats::Double);
    Rstats::Double more_than(Rstats::Integer, Rstats::Integer);

    Rstats::Double less_than(Rstats::Character, Rstats::Character);
    Rstats::Double less_than(Rstats::Complex, Rstats::Complex);
    Rstats::Double less_than(Rstats::Double, Rstats::Double);
    Rstats::Double less_than(Rstats::Integer, Rstats::Integer);

    Rstats::Double more_than_or_equal(Rstats::Character, Rstats::Character);
    Rstats::Double more_than_or_equal(Rstats::Complex, Rstats::Complex);
    Rstats::Double more_than_or_equal(Rstats::Double, Rstats::Double);
    Rstats::Double more_than_or_equal(Rstats::Integer, Rstats::Integer);

    Rstats::Double less_than_or_equal(Rstats::Character, Rstats::Character);
    Rstats::Double less_than_or_equal(Rstats::Complex, Rstats::Complex);
    Rstats::Double less_than_or_equal(Rstats::Double, Rstats::Double);
    Rstats::Double less_than_or_equal(Rstats::Integer, Rstats::Integer);

    Rstats::Double is_infinite(Rstats::Character);
    Rstats::Double is_infinite(Rstats::Complex);
    Rstats::Double is_infinite(Rstats::Double);
    Rstats::Double is_infinite(Rstats::Integer);
    Rstats::Double is_infinite(Rstats::Double);

    Rstats::Double is_finite(Rstats::Character);
    Rstats::Double is_finite(Rstats::Complex);
    Rstats::Double is_finite(Rstats::Double);
    Rstats::Double is_finite(Rstats::Integer);
    Rstats::Double is_finite(Rstats::Double);

    Rstats::Double is_nan(Rstats::Character);
    Rstats::Double is_nan(Rstats::Complex);
    Rstats::Double is_nan(Rstats::Double);
    Rstats::Double is_nan(Rstats::Integer);
    Rstats::Double is_nan(Rstats::Double);

    Rstats::Character as_string(Rstats::Character);
    Rstats::Character as_string(Rstats::Complex);
    Rstats::Character as_string(Rstats::Double);
    Rstats::Character as_string(Rstats::Integer);
    Rstats::Character as_string(Rstats::Double);

    Rstats::Double as_double(Rstats::Character);
    Rstats::Double as_double(Rstats::Complex);
    Rstats::Double as_double(Rstats::Double);
    Rstats::Double as_double(Rstats::Integer);
    Rstats::Double as_double(Rstats::Double);

    Rstats::Complex as_complex(Rstats::Character);
    Rstats::Complex as_complex(Rstats::Complex);
    Rstats::Complex as_complex(Rstats::Double);
    Rstats::Complex as_complex(Rstats::Integer);
    Rstats::Complex as_complex(Rstats::Double);
  }
}

#endif

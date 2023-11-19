#ifndef PERL_RSTATS_ELEMENTFUNC_H
#define PERL_RSTATS_ELEMENTFUNC_H

#include <complex>
#include <cmath>

#include "Rstats_Util.h"

namespace Rstats {
  namespace ElementFunc {

    Rstats::Complex add(Rstats::Complex, Rstats::Complex);
    Rstats::Double add(Rstats::Double, Rstats::Double);
    int32_t add(int32_t, int32_t);

    Rstats::Complex subtract(Rstats::Complex, Rstats::Complex);
    Rstats::Double subtract(Rstats::Double, Rstats::Double);
    int32_t subtract(int32_t, int32_t);

    Rstats::Complex multiply(Rstats::Complex, Rstats::Complex);
    Rstats::Double multiply(Rstats::Double, Rstats::Double);
    int32_t multiply(int32_t, int32_t);

    Rstats::Complex divide(Rstats::Complex, Rstats::Complex);
    Rstats::Double divide(Rstats::Double, Rstats::Double);
    Rstats::Double divide(int32_t, int32_t);

    Rstats::Complex pow(Rstats::Complex, Rstats::Complex);
    Rstats::Double pow(Rstats::Double, Rstats::Double);
    Rstats::Double pow(int32_t, int32_t);

    Rstats::Complex remainder(Rstats::Complex, Rstats::Complex);
    Rstats::Double remainder(Rstats::Double, Rstats::Double);
    Rstats::Double remainder(int32_t, int32_t);

    Rstats::Double Re(Rstats::Complex);
    Rstats::Double Re(Rstats::Double);
    Rstats::Double Re(int32_t);

    Rstats::Double Im(Rstats::Complex);
    Rstats::Double Im(Rstats::Double);
    Rstats::Double Im(int32_t);

    Rstats::Complex Conj(Rstats::Complex);
    Rstats::Double Conj(Rstats::Double);
    Rstats::Double Conj(int32_t);

    Rstats::Complex sin(Rstats::Complex);
    Rstats::Double sin(Rstats::Double);
    Rstats::Double sin(int32_t);
    
    Rstats::Complex cos(Rstats::Complex);
    Rstats::Double cos(Rstats::Double);
    Rstats::Double cos(int32_t);

    Rstats::Complex tan(Rstats::Complex);
    Rstats::Double tan(Rstats::Double);
    Rstats::Double tan(int32_t);

    Rstats::Complex sinh(Rstats::Complex);
    Rstats::Double sinh(Rstats::Double);
    Rstats::Double sinh(int32_t);

    Rstats::Complex cosh(Rstats::Complex);
    Rstats::Double cosh(Rstats::Double);
    Rstats::Double cosh(int32_t);

    Rstats::Complex tanh (Rstats::Complex z);
    Rstats::Double tanh(Rstats::Double);
    Rstats::Double tanh(int32_t);

    Rstats::Double abs(Rstats::Complex);
    Rstats::Double abs(Rstats::Double);
    Rstats::Double abs(int32_t);

    Rstats::Double Mod(Rstats::Complex);
    Rstats::Double Mod(Rstats::Double);
    Rstats::Double Mod(int32_t);

    Rstats::Complex log(Rstats::Complex);
    Rstats::Double log(Rstats::Double);
    Rstats::Double log(int32_t);

    Rstats::Complex logb(Rstats::Complex);
    Rstats::Double logb(Rstats::Double);
    Rstats::Double logb(int32_t);

    Rstats::Complex log10(Rstats::Complex);
    Rstats::Double log10(Rstats::Double);
    Rstats::Double log10(int32_t);

    Rstats::Complex log2(Rstats::Complex);
    Rstats::Double log2(Rstats::Double);
    Rstats::Double log2(int32_t);
    
    Rstats::Complex expm1(Rstats::Complex);
    Rstats::Double expm1(Rstats::Double);
    Rstats::Double expm1(int32_t);

    Rstats::Double Arg(Rstats::Complex);
    Rstats::Double Arg(Rstats::Double);
    Rstats::Double Arg(int32_t);

    Rstats::Complex exp(Rstats::Complex);
    Rstats::Double exp(Rstats::Double);
    Rstats::Double exp(int32_t);

    Rstats::Complex sqrt(Rstats::Complex);
    Rstats::Double sqrt(Rstats::Double);
    Rstats::Double sqrt(int32_t);

    Rstats::Complex atan(Rstats::Complex);
    Rstats::Double atan(Rstats::Double);
    Rstats::Double atan(int32_t);

    Rstats::Complex asin(Rstats::Complex);
    Rstats::Double asin(Rstats::Double);
    Rstats::Double asin(int32_t);

    Rstats::Complex acos(Rstats::Complex);
    Rstats::Double acos(Rstats::Double);
    Rstats::Double acos(int32_t);

    Rstats::Complex asinh(Rstats::Complex);
    Rstats::Double asinh(Rstats::Double);
    Rstats::Double asinh(int32_t);

    Rstats::Complex acosh(Rstats::Complex);
    Rstats::Double acosh(Rstats::Double);
    Rstats::Double acosh(int32_t);

    Rstats::Complex atanh(Rstats::Complex);
    Rstats::Double atanh(Rstats::Double);
    Rstats::Double atanh(int32_t);
    
    Rstats::Complex negate(Rstats::Complex);
    Rstats::Double negate(Rstats::Double);
    int32_t negate(int32_t);

    Rstats::Complex atan2(Rstats::Complex, Rstats::Complex);
    Rstats::Double atan2(Rstats::Double, Rstats::Double);
    Rstats::Double atan2(int32_t, int32_t);

    Rstats::Double And(Rstats::Character, Rstats::Character);
    Rstats::Double And(Rstats::Complex, Rstats::Complex);
    Rstats::Double And(Rstats::Double, Rstats::Double);
    Rstats::Double And(int32_t, int32_t);

    Rstats::Double Or(Rstats::Character, Rstats::Character);
    Rstats::Double Or(Rstats::Complex, Rstats::Complex);
    Rstats::Double Or(Rstats::Double, Rstats::Double);
    Rstats::Double Or(int32_t, int32_t);
    
    Rstats::Double equal(Rstats::Character, Rstats::Character);
    Rstats::Double equal(Rstats::Complex, Rstats::Complex);
    Rstats::Double equal(Rstats::Double, Rstats::Double);
    Rstats::Double equal(int32_t, int32_t);

    Rstats::Double not_equal(Rstats::Character, Rstats::Character);
    Rstats::Double not_equal(Rstats::Complex, Rstats::Complex);
    Rstats::Double not_equal(Rstats::Double, Rstats::Double);
    Rstats::Double not_equal(int32_t, int32_t);

    Rstats::Double more_than(Rstats::Character, Rstats::Character);
    Rstats::Double more_than(Rstats::Complex, Rstats::Complex);
    Rstats::Double more_than(Rstats::Double, Rstats::Double);
    Rstats::Double more_than(int32_t, int32_t);

    Rstats::Double less_than(Rstats::Character, Rstats::Character);
    Rstats::Double less_than(Rstats::Complex, Rstats::Complex);
    Rstats::Double less_than(Rstats::Double, Rstats::Double);
    Rstats::Double less_than(int32_t, int32_t);

    Rstats::Double more_than_or_equal(Rstats::Character, Rstats::Character);
    Rstats::Double more_than_or_equal(Rstats::Complex, Rstats::Complex);
    Rstats::Double more_than_or_equal(Rstats::Double, Rstats::Double);
    Rstats::Double more_than_or_equal(int32_t, int32_t);

    Rstats::Double less_than_or_equal(Rstats::Character, Rstats::Character);
    Rstats::Double less_than_or_equal(Rstats::Complex, Rstats::Complex);
    Rstats::Double less_than_or_equal(Rstats::Double, Rstats::Double);
    Rstats::Double less_than_or_equal(int32_t, int32_t);

    Rstats::Double is_infinite(Rstats::Character);
    Rstats::Double is_infinite(Rstats::Complex);
    Rstats::Double is_infinite(Rstats::Double);
    Rstats::Double is_infinite(int32_t);
    Rstats::Double is_infinite(Rstats::Double);

    Rstats::Double is_finite(Rstats::Character);
    Rstats::Double is_finite(Rstats::Complex);
    Rstats::Double is_finite(Rstats::Double);
    Rstats::Double is_finite(int32_t);
    Rstats::Double is_finite(Rstats::Double);

    Rstats::Double is_nan(Rstats::Character);
    Rstats::Double is_nan(Rstats::Complex);
    Rstats::Double is_nan(Rstats::Double);
    Rstats::Double is_nan(int32_t);
    Rstats::Double is_nan(Rstats::Double);

    Rstats::Character as_string(Rstats::Character);
    Rstats::Character as_string(Rstats::Complex);
    Rstats::Character as_string(Rstats::Double);
    Rstats::Character as_string(int32_t);
    Rstats::Character as_string(Rstats::Double);

    Rstats::Double as_double(Rstats::Character);
    Rstats::Double as_double(Rstats::Complex);
    Rstats::Double as_double(Rstats::Double);
    Rstats::Double as_double(int32_t);
    Rstats::Double as_double(Rstats::Double);

    Rstats::Complex as_complex(Rstats::Character);
    Rstats::Complex as_complex(Rstats::Complex);
    Rstats::Complex as_complex(Rstats::Double);
    Rstats::Complex as_complex(int32_t);
    Rstats::Complex as_complex(Rstats::Double);
  }
}

#endif

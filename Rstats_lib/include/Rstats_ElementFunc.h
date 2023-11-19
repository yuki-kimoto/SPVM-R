#ifndef PERL_RSTATS_ELEMENTFUNC_H
#define PERL_RSTATS_ELEMENTFUNC_H

#include <complex>
#include <cmath>

#include "Rstats_Util.h"

namespace Rstats {
  namespace ElementFunc {

    Rstats::Complex add(Rstats::Complex, Rstats::Complex);
    double add(double, double);
    int32_t add(int32_t, int32_t);

    Rstats::Complex subtract(Rstats::Complex, Rstats::Complex);
    double subtract(double, double);
    int32_t subtract(int32_t, int32_t);

    Rstats::Complex multiply(Rstats::Complex, Rstats::Complex);
    double multiply(double, double);
    int32_t multiply(int32_t, int32_t);

    Rstats::Complex divide(Rstats::Complex, Rstats::Complex);
    double divide(double, double);
    double divide(int32_t, int32_t);

    Rstats::Complex pow(Rstats::Complex, Rstats::Complex);
    double pow(double, double);
    double pow(int32_t, int32_t);

    Rstats::Complex remainder(Rstats::Complex, Rstats::Complex);
    double remainder(double, double);
    double remainder(int32_t, int32_t);

    double Re(Rstats::Complex);
    double Re(double);
    double Re(int32_t);

    double Im(Rstats::Complex);
    double Im(double);
    double Im(int32_t);

    Rstats::Complex Conj(Rstats::Complex);
    double Conj(double);
    double Conj(int32_t);

    Rstats::Complex sin(Rstats::Complex);
    double sin(double);
    double sin(int32_t);
    
    Rstats::Complex cos(Rstats::Complex);
    double cos(double);
    double cos(int32_t);

    Rstats::Complex tan(Rstats::Complex);
    double tan(double);
    double tan(int32_t);

    Rstats::Complex sinh(Rstats::Complex);
    double sinh(double);
    double sinh(int32_t);

    Rstats::Complex cosh(Rstats::Complex);
    double cosh(double);
    double cosh(int32_t);

    Rstats::Complex tanh (Rstats::Complex z);
    double tanh(double);
    double tanh(int32_t);

    double abs(Rstats::Complex);
    double abs(double);
    double abs(int32_t);

    double Mod(Rstats::Complex);
    double Mod(double);
    double Mod(int32_t);

    Rstats::Complex log(Rstats::Complex);
    double log(double);
    double log(int32_t);

    Rstats::Complex logb(Rstats::Complex);
    double logb(double);
    double logb(int32_t);

    Rstats::Complex log10(Rstats::Complex);
    double log10(double);
    double log10(int32_t);

    Rstats::Complex log2(Rstats::Complex);
    double log2(double);
    double log2(int32_t);
    
    Rstats::Complex expm1(Rstats::Complex);
    double expm1(double);
    double expm1(int32_t);

    double Arg(Rstats::Complex);
    double Arg(double);
    double Arg(int32_t);

    Rstats::Complex exp(Rstats::Complex);
    double exp(double);
    double exp(int32_t);

    Rstats::Complex sqrt(Rstats::Complex);
    double sqrt(double);
    double sqrt(int32_t);

    Rstats::Complex atan(Rstats::Complex);
    double atan(double);
    double atan(int32_t);

    Rstats::Complex asin(Rstats::Complex);
    double asin(double);
    double asin(int32_t);

    Rstats::Complex acos(Rstats::Complex);
    double acos(double);
    double acos(int32_t);

    Rstats::Complex asinh(Rstats::Complex);
    double asinh(double);
    double asinh(int32_t);

    Rstats::Complex acosh(Rstats::Complex);
    double acosh(double);
    double acosh(int32_t);

    Rstats::Complex atanh(Rstats::Complex);
    double atanh(double);
    double atanh(int32_t);
    
    Rstats::Complex negate(Rstats::Complex);
    double negate(double);
    int32_t negate(int32_t);

    Rstats::Complex atan2(Rstats::Complex, Rstats::Complex);
    double atan2(double, double);
    double atan2(int32_t, int32_t);

    double And(Rstats::Character, Rstats::Character);
    double And(Rstats::Complex, Rstats::Complex);
    double And(double, double);
    double And(int32_t, int32_t);

    double Or(Rstats::Character, Rstats::Character);
    double Or(Rstats::Complex, Rstats::Complex);
    double Or(double, double);
    double Or(int32_t, int32_t);
    
    double equal(Rstats::Character, Rstats::Character);
    double equal(Rstats::Complex, Rstats::Complex);
    double equal(double, double);
    double equal(int32_t, int32_t);

    double not_equal(Rstats::Character, Rstats::Character);
    double not_equal(Rstats::Complex, Rstats::Complex);
    double not_equal(double, double);
    double not_equal(int32_t, int32_t);

    double more_than(Rstats::Character, Rstats::Character);
    double more_than(Rstats::Complex, Rstats::Complex);
    double more_than(double, double);
    double more_than(int32_t, int32_t);

    double less_than(Rstats::Character, Rstats::Character);
    double less_than(Rstats::Complex, Rstats::Complex);
    double less_than(double, double);
    double less_than(int32_t, int32_t);

    double more_than_or_equal(Rstats::Character, Rstats::Character);
    double more_than_or_equal(Rstats::Complex, Rstats::Complex);
    double more_than_or_equal(double, double);
    double more_than_or_equal(int32_t, int32_t);

    double less_than_or_equal(Rstats::Character, Rstats::Character);
    double less_than_or_equal(Rstats::Complex, Rstats::Complex);
    double less_than_or_equal(double, double);
    double less_than_or_equal(int32_t, int32_t);

    double is_infinite(Rstats::Character);
    double is_infinite(Rstats::Complex);
    double is_infinite(double);
    double is_infinite(int32_t);
    double is_infinite(double);

    double is_finite(Rstats::Character);
    double is_finite(Rstats::Complex);
    double is_finite(double);
    double is_finite(int32_t);
    double is_finite(double);

    double is_nan(Rstats::Character);
    double is_nan(Rstats::Complex);
    double is_nan(double);
    double is_nan(int32_t);
    double is_nan(double);

    Rstats::Character as_string(Rstats::Character);
    Rstats::Character as_string(Rstats::Complex);
    Rstats::Character as_string(double);
    Rstats::Character as_string(int32_t);
    Rstats::Character as_string(double);

    double as_double(Rstats::Character);
    double as_double(Rstats::Complex);
    double as_double(double);
    double as_double(int32_t);
    double as_double(double);

    Rstats::Complex as_complex(Rstats::Character);
    Rstats::Complex as_complex(Rstats::Complex);
    Rstats::Complex as_complex(double);
    Rstats::Complex as_complex(int32_t);
    Rstats::Complex as_complex(double);
  }
}

#endif

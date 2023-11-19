#ifndef PERL_RSTATS_ELEMENTFUNC_H
#define PERL_RSTATS_ELEMENTFUNC_H

#include <complex>
#include <cmath>

#include "Rstats_Util.h"

namespace Rstats {
  namespace ElementFunc {

    std::complex<double> add(std::complex<double>, std::complex<double>);
    double add(double, double);
    int32_t add(int32_t, int32_t);

    std::complex<double> subtract(std::complex<double>, std::complex<double>);
    double subtract(double, double);
    int32_t subtract(int32_t, int32_t);

    std::complex<double> multiply(std::complex<double>, std::complex<double>);
    double multiply(double, double);
    int32_t multiply(int32_t, int32_t);

    std::complex<double> divide(std::complex<double>, std::complex<double>);
    double divide(double, double);
    double divide(int32_t, int32_t);

    std::complex<double> pow(std::complex<double>, std::complex<double>);
    double pow(double, double);
    double pow(int32_t, int32_t);

    std::complex<double> remainder(std::complex<double>, std::complex<double>);
    double remainder(double, double);
    double remainder(int32_t, int32_t);

    double Re(std::complex<double>);
    double Re(double);
    double Re(int32_t);

    double Im(std::complex<double>);
    double Im(double);
    double Im(int32_t);

    std::complex<double> Conj(std::complex<double>);
    double Conj(double);
    double Conj(int32_t);

    std::complex<double> sin(std::complex<double>);
    double sin(double);
    double sin(int32_t);
    
    std::complex<double> cos(std::complex<double>);
    double cos(double);
    double cos(int32_t);

    std::complex<double> tan(std::complex<double>);
    double tan(double);
    double tan(int32_t);

    std::complex<double> sinh(std::complex<double>);
    double sinh(double);
    double sinh(int32_t);

    std::complex<double> cosh(std::complex<double>);
    double cosh(double);
    double cosh(int32_t);

    std::complex<double> tanh (std::complex<double> z);
    double tanh(double);
    double tanh(int32_t);

    double abs(std::complex<double>);
    double abs(double);
    double abs(int32_t);

    double Mod(std::complex<double>);
    double Mod(double);
    double Mod(int32_t);

    std::complex<double> log(std::complex<double>);
    double log(double);
    double log(int32_t);

    std::complex<double> logb(std::complex<double>);
    double logb(double);
    double logb(int32_t);

    std::complex<double> log10(std::complex<double>);
    double log10(double);
    double log10(int32_t);

    std::complex<double> log2(std::complex<double>);
    double log2(double);
    double log2(int32_t);
    
    std::complex<double> expm1(std::complex<double>);
    double expm1(double);
    double expm1(int32_t);

    double Arg(std::complex<double>);
    double Arg(double);
    double Arg(int32_t);

    std::complex<double> exp(std::complex<double>);
    double exp(double);
    double exp(int32_t);

    std::complex<double> sqrt(std::complex<double>);
    double sqrt(double);
    double sqrt(int32_t);

    std::complex<double> atan(std::complex<double>);
    double atan(double);
    double atan(int32_t);

    std::complex<double> asin(std::complex<double>);
    double asin(double);
    double asin(int32_t);

    std::complex<double> acos(std::complex<double>);
    double acos(double);
    double acos(int32_t);

    std::complex<double> asinh(std::complex<double>);
    double asinh(double);
    double asinh(int32_t);

    std::complex<double> acosh(std::complex<double>);
    double acosh(double);
    double acosh(int32_t);

    std::complex<double> atanh(std::complex<double>);
    double atanh(double);
    double atanh(int32_t);
    
    std::complex<double> negate(std::complex<double>);
    double negate(double);
    int32_t negate(int32_t);

    std::complex<double> atan2(std::complex<double>, std::complex<double>);
    double atan2(double, double);
    double atan2(int32_t, int32_t);

    double And(Rstats::Character, Rstats::Character);
    double And(std::complex<double>, std::complex<double>);
    double And(double, double);
    double And(int32_t, int32_t);

    double Or(Rstats::Character, Rstats::Character);
    double Or(std::complex<double>, std::complex<double>);
    double Or(double, double);
    double Or(int32_t, int32_t);
    
    double equal(Rstats::Character, Rstats::Character);
    double equal(std::complex<double>, std::complex<double>);
    double equal(double, double);
    double equal(int32_t, int32_t);

    double not_equal(Rstats::Character, Rstats::Character);
    double not_equal(std::complex<double>, std::complex<double>);
    double not_equal(double, double);
    double not_equal(int32_t, int32_t);

    double more_than(Rstats::Character, Rstats::Character);
    double more_than(std::complex<double>, std::complex<double>);
    double more_than(double, double);
    double more_than(int32_t, int32_t);

    double less_than(Rstats::Character, Rstats::Character);
    double less_than(std::complex<double>, std::complex<double>);
    double less_than(double, double);
    double less_than(int32_t, int32_t);

    double more_than_or_equal(Rstats::Character, Rstats::Character);
    double more_than_or_equal(std::complex<double>, std::complex<double>);
    double more_than_or_equal(double, double);
    double more_than_or_equal(int32_t, int32_t);

    double less_than_or_equal(Rstats::Character, Rstats::Character);
    double less_than_or_equal(std::complex<double>, std::complex<double>);
    double less_than_or_equal(double, double);
    double less_than_or_equal(int32_t, int32_t);

    double is_infinite(Rstats::Character);
    double is_infinite(std::complex<double>);
    double is_infinite(double);
    double is_infinite(int32_t);
    double is_infinite(double);

    double is_finite(Rstats::Character);
    double is_finite(std::complex<double>);
    double is_finite(double);
    double is_finite(int32_t);
    double is_finite(double);

    double is_nan(Rstats::Character);
    double is_nan(std::complex<double>);
    double is_nan(double);
    double is_nan(int32_t);
    double is_nan(double);

    Rstats::Character as_string(Rstats::Character);
    Rstats::Character as_string(std::complex<double>);
    Rstats::Character as_string(double);
    Rstats::Character as_string(int32_t);
    Rstats::Character as_string(double);

    double as_double(Rstats::Character);
    double as_double(std::complex<double>);
    double as_double(double);
    double as_double(int32_t);
    double as_double(double);

    std::complex<double> as_complex(Rstats::Character);
    std::complex<double> as_complex(std::complex<double>);
    std::complex<double> as_complex(double);
    std::complex<double> as_complex(int32_t);
    std::complex<double> as_complex(double);
  }
}

#endif

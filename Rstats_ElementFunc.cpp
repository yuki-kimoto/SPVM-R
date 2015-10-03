#include "Rstats.h"

// Rstats::ElementFunc
namespace Rstats {
  namespace ElementFunc {

    // add
    std::complex<NV> add(std::complex<NV> e1, std::complex<NV> e2) { return e1 + e2; }
    NV add(NV e1, NV e2) { return e1 + e2; }
    IV add(IV e1, IV e2) { return e1 + e2; }

    // subtract
    std::complex<NV> subtract(std::complex<NV> e1, std::complex<NV> e2) { return e1 - e2; }
    NV subtract(NV e1, NV e2) { return e1 - e2; }
    IV subtract(IV e1, IV e2) { return e1 - e2; }

    // multiply
    std::complex<NV> multiply(std::complex<NV> e1, std::complex<NV> e2) { return e1 * e2; }
    NV multiply(NV e1, NV e2) { return e1 * e2; }
    IV multiply(IV e1, IV e2) { return e1 * e2; }

    // divide
    std::complex<NV> divide(std::complex<NV> e1, std::complex<NV> e2) { return e1 / e2; }
    NV divide(NV e1, NV e2) { return e1 / e2; }
    NV divide(IV e1, IV e2) { return e1 / e2; }

    // pow
    std::complex<NV> pow(std::complex<NV> e1, std::complex<NV> e2) { return std::pow(e1, e2); }
    NV pow(NV e1, NV e2) { return ::pow(e1, e2); }
    NV pow(IV e1, IV e2) { return pow((NV)e1, (NV)e2); }

    // remainder
    std::complex<NV> remainder(std::complex<NV> e1, std::complex<NV> e2) {
      croak("unimplemented complex operation(Rstats::VectorFunc::remainder())");
    }
    NV remainder(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2) || e2 == 0) {
        return std::numeric_limits<NV>::signaling_NaN();
      }
      else {
        return e1 - std::floor(e1 / e2) * e2;
      }
    }
    IV remainder(IV e1, IV e2) {
      if (e2 == 0) {
        throw "0 divide exception\n";
      }
      return e1 % e2;
    }

    // Re
    NV Re(std::complex<NV> e1) { return e1.real(); }
    NV Re(NV e1) { return e1; }
    NV Re(IV e1) { return e1; }

    // Im
    NV Im(std::complex<NV> e1) { return e1.imag(); }
    NV Im(NV e1) { return 0; }
    NV Im(IV e1) { return 0; }

    // Conj
    std::complex<NV> Conj(std::complex<NV> e1) { return std::complex<NV>(e1.real(), -e1.imag()); }
    NV Conj(NV e1) { return e1; }
    NV Conj(IV e1) { return e1; }

    // sin
    std::complex<NV> sin(std::complex<NV> e1) { return std::sin(e1); }
    NV sin(NV e1) { return std::sin(e1); }
    NV sin(IV e1) { return sin((NV)e1); }

    // cos
    std::complex<NV> cos(std::complex<NV> e1) { return std::cos(e1); }
    NV cos(NV e1) { return std::cos(e1); }
    NV cos(IV e1) { return cos((NV)e1); }

    // tan
    std::complex<NV> tan(std::complex<NV> e1) { return std::tan(e1); }
    NV tan(NV e1) { return std::tan(e1); }
    NV tan(IV e1) { return tan((NV)e1); }

    // sinh
    std::complex<NV> sinh(std::complex<NV> e1) { return std::sinh(e1); }
    NV sinh(NV e1) { return std::sinh(e1); }
    NV sinh(IV e1) { return sinh((NV)e1); }

    // cosh
    std::complex<NV> cosh(std::complex<NV> e1) { return std::cosh(e1); }
    NV cosh(NV e1) { return std::cosh(e1); }
    NV cosh(IV e1) { return cosh((NV)e1); }

    // tanh
    std::complex<NV> tanh (std::complex<NV> z) {
      NV re = z.real();
      
      // For fix FreeBSD bug
      // FreeBAD return (NaN + NaNi) when real value is negative infinite
      if (std::isinf(re) && re < 0) {
        return std::complex<NV>(-1, 0);
      }
      else {
        return std::tanh(z);
      }
    }
    NV tanh(NV e1) { return std::tanh(e1); }
    NV tanh(IV e1) { return tanh((NV)e1); }

    // abs
    NV abs(std::complex<NV> e1) { return std::abs(e1); }
    NV abs(NV e1) { return std::abs(e1); }
    NV abs(IV e1) { return abs((NV)e1); }

    // abs
    NV Mod(std::complex<NV> e1) { return abs(e1); }
    NV Mod(NV e1) { return abs(e1); }
    NV Mod(IV e1) { return abs((NV)e1); }

    // log
    std::complex<NV> log(std::complex<NV> e1) { return std::log(e1); }
    NV log(NV e1) { return std::log(e1); }
    NV log(IV e1) { return log((NV)e1); }

    // logb
    std::complex<NV> logb(std::complex<NV> e1) { return log(e1); }
    NV logb(NV e1) { return log(e1); }
    NV logb(IV e1) { return log((NV)e1); }

    // log10
    std::complex<NV> log10(std::complex<NV> e1) { return std::log10(e1); }
    NV log10(NV e1) { return std::log10(e1); }
    NV log10(IV e1) { return std::log10((NV)e1); }

    // log2
    std::complex<NV> log2(std::complex<NV> e1) {
      return std::log(e1) / std::log(std::complex<NV>(2, 0));
    }
    NV log2(NV e1) {
      return std::log(e1) / std::log((NV)2);
    }
    NV log2(IV e1) { return log2((NV)e1); }

    std::complex<NV> expm1(std::complex<NV> e1) { croak("Error in expm1 : unimplemented complex function"); }
    NV expm1(NV e1) { return ::expm1(e1); }
    NV expm1(IV e1) { return expm1((NV)e1); }

    // Arg
    NV Arg(std::complex<NV> e1) {
      NV re = e1.real();
      NV im = e1.imag();
      
      if (re == 0 && im == 0) {
        return 0;
      }
      else {
        return Rstats::ElementFunc::atan2(im, re);
      }
    }
    NV Arg(NV e1) { croak("Error in Arg : unimplemented double function"); }
    NV Arg(IV e1) { return Arg((NV)e1); }

    // exp
    std::complex<NV> exp(std::complex<NV> e1) { return std::exp(e1); }
    NV exp(NV e1) { return std::exp(e1); }
    NV exp(IV e1) { return exp((NV)e1); }

    // sqrt
    std::complex<NV> sqrt(std::complex<NV> e1) {
      // Fix bug that clang sqrt can't right value of perfect squeres
      if (e1.imag() == 0 && e1.real() < 0) {
        return std::complex<NV>(0, std::sqrt(-e1.real()));
      }
      else {
        return std::sqrt(e1);
      }
    }
    NV sqrt(NV e1) { return std::sqrt(e1); }
    NV sqrt(IV e1) { return sqrt((NV)e1); }

    // atan
    std::complex<NV> atan(std::complex<NV> e1) {
      if (e1 == std::complex<NV>(0, 0)) {
        return std::complex<NV>(0, 0);
      }
      else if (e1 == std::complex<NV>(0, 1)) {
        return std::complex<NV>(0, INFINITY);
      }
      else if (e1 == std::complex<NV>(0, -1)) {
        return std::complex<NV>(0, -INFINITY);
      }
      else {  
        std::complex<NV> e2_i = std::complex<NV>(0, 1);
        std::complex<NV> e2_log = std::log((e2_i + e1) / (e2_i - e1));
        return (e2_i / std::complex<NV>(2, 0)) * e2_log;
      }
    }
    NV atan(NV e1) { return ::atan2(e1, 1); }
    NV atan(IV e1) { return atan2((NV)e1, (NV)1); }

    // asin
    std::complex<NV> asin(std::complex<NV> e1) {
      NV e1_re = e1.real();
      NV e1_im = e1.imag();
      
      if (e1_re == 0 && e1_im == 0) {
        return std::complex<NV>(0, 0);
      }
      else {
        NV e2_t1 = std::sqrt(
          ((e1_re + 1) * (e1_re + 1))
          +
          (e1_im * e1_im)
        );
        NV e2_t2 = std::sqrt(
          ((e1_re - 1) * (e1_re - 1))
          +
          (e1_im * e1_im)
        );
        
        NV e2_alpha = (e2_t1 + e2_t2) / 2;
        NV e2_beta  = (e2_t1 - e2_t2) / 2;
        
        if (e2_alpha < 1) {
          e2_alpha = 1;
        }
        
        if (e2_beta > 1) {
          e2_beta = 1;
        }
        else if (e2_beta < -1) {
          e2_beta = -1;
        }
        
        NV e2_u = Rstats::ElementFunc::atan2(
          e2_beta,
          std::sqrt(1 - (e2_beta * e2_beta))
        );
        
        NV e2_v = -std::log(
          e2_alpha
          +
          std::sqrt((e2_alpha * e2_alpha) - 1)
        );
        
        if (e1_im > 0 || ((e1_im == 0) && (e1_re < -1))) {
          e2_v = -e2_v;
        }
        
        return std::complex<NV>(e2_u, e2_v);
      }
    }
    NV asin(NV e1) { return std::asin(e1); }
    NV asin(IV e1) { return asin((NV)e1); }

    // acos
    std::complex<NV> acos(std::complex<NV> e1) {
      NV e1_re = e1.real();
      NV e1_im = e1.imag();
      
      if (e1_re == 1 && e1_im == 0) {
        return std::complex<NV>(0, 0);
      }
      else {
        NV e2_t1 = std::sqrt(
          ((e1_re + 1) * (e1_re + 1))
          +
          (e1_im * e1_im)
        );
        NV e2_t2 = std::sqrt(
          ((e1_re - 1) * (e1_re - 1))
          +
          (e1_im * e1_im)
        );
        
        NV e2_alpha = (e2_t1 + e2_t2) / 2;
        NV e2_beta  = (e2_t1 - e2_t2) / 2;
        
        if (e2_alpha < 1) {
          e2_alpha = 1;
        }
        
        if (e2_beta > 1) {
          e2_beta = 1;
        }
        else if (e2_beta < -1) {
          e2_beta = -1;
        }
        
        NV e2_u = Rstats::ElementFunc::atan2(
          std::sqrt(1 - (e2_beta * e2_beta)),
          e2_beta
        );
        
        NV e2_v = std::log(
          e2_alpha
          +
          std::sqrt((e2_alpha * e2_alpha) - 1)
        );
        
        if (e1_im > 0 || (e1_im == 0 && e1_re < -1)) {
          e2_v = -e2_v;
        }
        
        return std::complex<NV>(e2_u, e2_v);
      }
    }
    NV acos(NV e1) { return std::acos(e1); }
    NV acos(IV e1) { return acos((NV)e1); }

    // asinh
    std::complex<NV> asinh(std::complex<NV> e1) {
      std::complex<NV> e2_t = (
        std::sqrt((e1 * e1) + std::complex<NV>(1, 0))
        +
        e1
      );
      
      return std::log(e2_t);
    }
    NV asinh(NV e1) {
      NV e2_t = (
        e1
        +
        std::sqrt((e1 * e1) + 1)
      );
      
      return std::log(e2_t);
    }
    NV asinh(IV e1) { return asinh((NV)e1); }

    // acosh
    std::complex<NV> acosh(std::complex<NV> e1) {
      NV e1_re = e1.real();
      NV e1_im = e1.imag();

      std::complex<NV> e2_t = (
        std::sqrt(
          (e1 * e1)
          -
          std::complex<NV>(1, 0)
        )
        +
        e1
      );
      std::complex<NV> e2_u = std::log(e2_t);
      NV e2_re = e2_u.real();
      NV e2_im = e2_u.imag();
      
      std::complex<NV> e2;
      if (e1_re < 0 && e1_im == 0) {
        e2 = std::complex<NV>(e2_re, -e2_im);
      }
      else {
        e2 = std::complex<NV>(e2_re, e2_im);
      }
      
      if (e1_re < 0) {
        return -e2;
      }
      else {
        return e2;
      }
    }
    NV acosh(NV e1) {
      if (e1 >= 1) {
        if (std::isinf(e1)) {
          warn("In acosh() : NaNs produced");
          return std::numeric_limits<NV>::signaling_NaN();
        }
        else {
          return std::log(
            e1
            +
            std::sqrt((e1 * e1) - 1)
          );
        }
      }
      else {
        warn("In acosh() : NaNs produced");
        return std::numeric_limits<NV>::signaling_NaN();
      }
    }
    NV acosh(IV e1) { return acosh((NV)e1); }

    // atanh
    std::complex<NV> atanh(std::complex<NV> e1) {
      if (e1 == std::complex<NV>(1, 0)) {
        warn("In atanh() : NaNs produced");
        return std::complex<NV>(INFINITY, std::numeric_limits<NV>::signaling_NaN());
      }
      else if (e1 == std::complex<NV>(-1, 0)) {
        warn("In atanh() : NaNs produced");
        return std::complex<NV>(-INFINITY, std::numeric_limits<NV>::signaling_NaN());
      }
      else {
        return std::complex<NV>(0.5, 0)
          *
          std::log(
            (std::complex<NV>(1, 0) + e1)
            /
            (std::complex<NV>(1, 0) - e1)
          );
      }
    }
    NV atanh(NV e1) {
      if (std::isinf(e1)) {
        warn("In acosh() : NaNs produced");
        return std::numeric_limits<NV>::signaling_NaN();
      }
      else {
        if (e1 == 1) {
          return INFINITY;
        }
        else if (e1 == -1) {
          return -INFINITY;
        }
        else if (std::abs(e1) < 1) {
          return std::log((1 + e1) / (1 - e1)) / 2;
        }
        else {
          warn("In acosh() : NaNs produced");
          return std::numeric_limits<NV>::signaling_NaN();
        }
      }
    }
    NV atanh(IV e1) { return atanh((NV)e1); }

    // negation
    std::complex<NV> negation(std::complex<NV> e1) { return -e1; }
    NV negation(NV e1) { return -e1; }
    IV negation(IV e1) { return -e1; }

    // atan2
    std::complex<NV> atan2(std::complex<NV> e1, std::complex<NV> e2) {
      std::complex<NV> e3_s = (e1 * e1) + (e2 * e2);
      if (e3_s == std::complex<NV>(0, 0)) {
        return std::complex<NV>(0, 0);
      }
      else {
        std::complex<NV> e3_i = std::complex<NV>(0, 1);
        std::complex<NV> e3_r = e2 + (e1 * e3_i);
        return -e3_i * std::log(e3_r / std::sqrt(e3_s));
      }
    }
    NV atan2(NV e1, NV e2) {
      if (std::isinf(e1) && std::isinf(e2)) {
        if (e1 > 0 && e2 > 0) {
          return (Rstats::Util::pi() / 4);
        }
        else if (e1 > 0 && e2 < 0) {
          return ((3 * Rstats::Util::pi()) / 4);
        }
        else if (e1 < 0 && e2 > 0) {
          return -(Rstats::Util::pi() / 4);
        }
        else {
          return -((3 * Rstats::Util::pi()) / 4);
        }
      }
      else {
        return ::atan2(e1, e2);
      }
    }
    NV atan2(IV e1, IV e2) { return atan2((NV)e1, (NV)e2); }

    // And
    IV And(SV* e1, SV* e2) { croak("operations are possible only for numeric, logical or complex types"); }
    IV And(std::complex<NV> e1, std::complex<NV> e2) {
      if (e1 != std::complex<NV>(0, 0) && e2 != std::complex<NV>(0, 0)) { return 1; }
      else { return 0; }
    }
    IV And(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2)) { throw "Na exception"; }
      else { return e1 && e2 ? 1 : 0; }
    }
    IV And(IV e1, IV e2) { return e1 && e2 ? 1 : 0; }

    // Or
    IV Or(SV* e1, SV* e2) { croak("operations are possible only for numeric, logical or complex types"); }
    IV Or(std::complex<NV> e1, std::complex<NV> e2) {
      if (e1 != std::complex<NV>(0, 0) || e2 != std::complex<NV>(0, 0)) { return 1; }
      else { return 0; }
    }
    IV Or(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2)) { throw "Na exception"; }
      else { return e1 || e2 ? 1 : 0; }
    }
    IV Or(IV e1, IV e2) { return e1 || e2 ? 1 : 0; }

    // equal
    IV equal(SV* e1, SV* e2) { return sv_cmp(e1, e2) == 0 ? 1 : 0; }
    IV equal(std::complex<NV> e1, std::complex<NV> e2) { return e1 == e2 ? 1 : 0; }
    IV equal(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
      else { return e1 == e2 ? 1 : 0; }
    }
    IV equal(IV e1, IV e2) { return e1 == e2 ? 1 : 0; }

    // not equal
    IV not_equal(SV* e1, SV* e2) { return sv_cmp(e1, e2) != 0 ? 1 : 0; }
    IV not_equal(std::complex<NV> e1, std::complex<NV> e2) { return e1 != e2 ? 1 : 0; }
    IV not_equal(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
      else { return e1 != e2 ? 1 : 0; }
    }
    IV not_equal(IV e1, IV e2) { return e1 != e2 ? 1 : 0; }

    // more_than
    IV more_than(SV* e1, SV* e2) { return sv_cmp(e1, e2) > 0 ? 1 : 0; }
    IV more_than(std::complex<NV> e1, std::complex<NV> e2) {
      croak("invalid comparison with complex values(more_than())");
    }
    IV more_than(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
      else { return e1 > e2 ? 1 : 0; }
    }
    IV more_than(IV e1, IV e2) { return e1 > e2 ? 1 : 0; }

    // less_than
    IV less_than(SV* e1, SV* e2) { return sv_cmp(e1, e2) < 0 ? 1 : 0; }
    IV less_than(std::complex<NV> e1, std::complex<NV> e2) {
      croak("invalid comparison with complex values(less_than())");
    }
    IV less_than(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
      else { return e1 < e2 ? 1 : 0; }
    }
    IV less_than(IV e1, IV e2) { return e1 < e2 ? 1 : 0; }

    // more_than_or_equal
    IV more_than_or_equal(SV* e1, SV* e2) { return sv_cmp(e1, e2) >= 0 ? 1 : 0; }
    IV more_than_or_equal(std::complex<NV> e1, std::complex<NV> e2) {
      croak("invalid comparison with complex values(more_than_or_equal())");
    }
    IV more_than_or_equal(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
      else { return e1 >= e2 ? 1 : 0; }
    }
    IV more_than_or_equal(IV e1, IV e2) { return e1 >= e2 ? 1 : 0; }

    // less_than_or_equal
    IV less_than_or_equal(SV* e1, SV* e2) { return sv_cmp(e1, e2) <= 0 ? 1 : 0; }
    IV less_than_or_equal(std::complex<NV> e1, std::complex<NV> e2) {
      croak("invalid comparison with complex values(less_than_or_equal())");
    }
    IV less_than_or_equal(NV e1, NV e2) {
      if (std::isnan(e1) || std::isnan(e2)) { throw "Can't compare NaN"; }
      else { return e1 <= e2 ? 1 : 0; }
    }
    IV less_than_or_equal(IV e1, IV e2) { return e1 <= e2 ? 1 : 0; }

    // is_infinite
    IV is_infinite(SV* e1) { return 0; }
    IV is_infinite(std::complex<NV> e1) {
      if (std::isnan(e1.real()) || std::isnan(e1.imag())) {
        return 0;
      }
      else if (std::isinf(e1.real()) || std::isinf(e1.imag())) {
        return 1;
      }
      else {
        return 0;
      }
    }
    IV is_infinite(NV e1) { return std::isinf(e1); }
    IV is_infinite(IV e1) { return 0; }

    // is_finite
    IV is_finite(SV* e1) { return 0; }
    IV is_finite(std::complex<NV> e1) {
      if (std::isfinite(e1.real()) && std::isfinite(e1.imag())) {
        return 1;
      }
      else {
        return 0;
      }
    }
    IV is_finite(NV e1) { return std::isfinite(e1) ? 1 : 0; }
    IV is_finite(IV e1) { return 1; }

    // is_nan
    IV is_nan(SV* e1) { return 0; }
    IV is_nan(std::complex<NV> e1) {
      if (std::isnan(e1.real()) && std::isnan(e1.imag())) {
        return 1;
      }
      else {
        return 0;
      }
    }
    IV is_nan(NV e1) { return std::isnan(e1) ? 1 : 0; }
    IV is_nan(IV e1) { return 1; }
  }
}

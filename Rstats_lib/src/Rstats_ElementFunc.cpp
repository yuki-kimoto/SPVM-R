#include "Rstats_ElementFunc.h"

// Rstats::ElementFunc
namespace Rstats {
  namespace ElementFunc {
    
    /* Note:
      In ElementFunction, croak method should't be called.
      If you want to tell warnings, use Rstats::add_warn function.
      Rstats::clear_warn function should't be called.
      If you want to tell NA introduced, throw Rstats::NaException.
    */
    
    // add
    std::complex<double> add(std::complex<double> e1, std::complex<double> e2) { return e1 + e2; }
    double add(double e1, double e2) { return e1 + e2; }
    int32_t add(int32_t e1, int32_t e2) { return e1 + e2; }
    
    // subtract
    std::complex<double> subtract(std::complex<double> e1, std::complex<double> e2) { return e1 - e2; }
    double subtract(double e1, double e2) { return e1 - e2; }
    int32_t subtract(int32_t e1, int32_t e2) { return e1 - e2; }
    
    // multiply
    std::complex<double> multiply(std::complex<double> e1, std::complex<double> e2) { return e1 * e2; }
    double multiply(double e1, double e2) { return e1 * e2; }
    int32_t multiply(int32_t e1, int32_t e2) { return e1 * e2; }

    // divide
    std::complex<double> divide(std::complex<double> e1, std::complex<double> e2) { return e1 / e2; }
    double divide(double e1, double e2) { return e1 / e2; }
    double divide(int32_t e1, int32_t e2) {
      return Rstats::ElementFunc::divide((double)e1, (double)e2);
    }
    
    // pow
    std::complex<double> pow(std::complex<double> e1, std::complex<double> e2) { return std::pow(e1, e2); }
    double pow(double e1, double e2) { return ::pow(e1, e2); }
    double pow(int32_t e1, int32_t e2) {
      return Rstats::ElementFunc::pow((double)e1, (double)e2);
    }

    // remainder
    double remainder(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2) || e2 == 0) {
        return Rstats::Util::NaN();
      }
      else {
        return fmod(e1, e2);;
      }
    }
    double remainder(int32_t e1, int32_t e2) {
      return Rstats::ElementFunc::remainder((double) e1, (double) e2);
    }

    // Re
    double Re(std::complex<double> e1) { return e1.real(); }
    double Re(double e1) { return e1; }
    double Re(int32_t e1) { return Rstats::ElementFunc::Re((double)e1); }

    // Im
    double Im(std::complex<double> e1) { return e1.imag(); }
    double Im(double e1) { return 0; }
    double Im(int32_t e1) { return Rstats::ElementFunc::Im((double)e1); }

    // Conj
    std::complex<double> Conj(std::complex<double> e1) { return std::complex<double>(e1.real(), -e1.imag()); }
    double Conj(double e1) { return e1; }
    double Conj(int32_t e1) { return Rstats::ElementFunc::Conj((double)e1); }

    // sin
    std::complex<double> sin(std::complex<double> e1) { return std::sin(e1); }
    double sin(double e1) { return std::sin(e1); }
    double sin(int32_t e1) { return Rstats::ElementFunc::sin((double)e1); }

    // cos
    std::complex<double> cos(std::complex<double> e1) { return std::cos(e1); }
    double cos(double e1) { return std::cos(e1); }
    double cos(int32_t e1) { return Rstats::ElementFunc::cos((double)e1); }

    // tan
    std::complex<double> tan(std::complex<double> e1) { return std::tan(e1); }
    double tan(double e1) { return std::tan(e1); }
    double tan(int32_t e1) { return Rstats::ElementFunc::tan((double)e1); }

    // sinh
    std::complex<double> sinh(std::complex<double> e1) { return std::sinh(e1); }
    double sinh(double e1) { return std::sinh(e1); }
    double sinh(int32_t e1) { return Rstats::ElementFunc::sinh((double)e1); }

    // cosh
    std::complex<double> cosh(std::complex<double> e1) { return std::cosh(e1); }
    double cosh(double e1) { return std::cosh(e1); }
    double cosh(int32_t e1) { return Rstats::ElementFunc::cosh((double)e1); }

    // tanh
    std::complex<double> tanh (std::complex<double> z) {
      double re = z.real();
      
      // For fix FreeBSD bug
      // FreeBAD return (NaN + NaNi) when real value is negative infinite
      if (Rstats::Util::is_Inf(re) && re < 0) {
        return std::complex<double>(-1, 0);
      }
      else {
        return std::tanh(z);
      }
    }
    double tanh(double e1) { return std::tanh(e1); }
    double tanh(int32_t e1) { return Rstats::ElementFunc::tanh((double)e1); }

    // abs
    double abs(std::complex<double> e1) { return std::abs(e1); }
    double abs(double e1) { return std::abs(e1); }
    double abs(int32_t e1) { return Rstats::ElementFunc::abs((double)e1); }

    // abs
    double Mod(std::complex<double> e1) { return abs(e1); }
    double Mod(double e1) { return abs(e1); }
    double Mod(int32_t e1) { return Rstats::ElementFunc::abs((double)e1); }

    // log
    std::complex<double> log(std::complex<double> e1) { return std::log(e1); }
    double log(double e1) { return std::log(e1); }
    double log(int32_t e1) { return Rstats::ElementFunc::log((double)e1); }

    // logb
    std::complex<double> logb(std::complex<double> e1) { return log(e1); }
    double logb(double e1) { return log(e1); }
    double logb(int32_t e1) { return Rstats::ElementFunc::log((double)e1); }

    // log10
    std::complex<double> log10(std::complex<double> e1) { return std::log10(e1); }
    double log10(double e1) { return std::log10(e1); }
    double log10(int32_t e1) { return Rstats::ElementFunc::log10((double)e1); }

    // log2
    std::complex<double> log2(std::complex<double> e1) {
      return std::log(e1) / std::log(std::complex<double>(2, 0));
    }
    double log2(double e1) {
      return std::log(e1) / std::log((double)2);
    }
    double log2(int32_t e1) { return Rstats::ElementFunc::log2((double)e1); }
    
    // expm1
    double expm1(double e1) { return ::expm1(e1); }
    double expm1(int32_t e1) { return Rstats::ElementFunc::expm1((double)e1); }

    // Arg
    double Arg(std::complex<double> e1) {
      double re = e1.real();
      double im = e1.imag();
      
      if (re == 0 && im == 0) {
        return 0;
      }
      else {
        return Rstats::ElementFunc::atan2(im, re);
      }
    }
    double Arg(double e1) {
      if (Rstats::Util::is_NaN(e1)) {
        return Rstats::Util::NaN();
      }
      else if (e1 >= 0) {
        return 0;
      }
      else {
        return Rstats::Util::pi();
      }
    }
    
    double Arg(int32_t e1) {
      if (Rstats::Util::is_NaN(e1)) {
        return Rstats::Util::NaN();
      }
      else if (e1 >= 0) {
        return 0;
      }
      else {
        return Rstats::Util::pi();
      }
    }
    // exp
    std::complex<double> exp(std::complex<double> e1) { return std::exp(e1); }
    double exp(double e1) { return std::exp(e1); }
    double exp(int32_t e1) { return Rstats::ElementFunc::exp((double)e1); }

    // sqrt
    std::complex<double> sqrt(std::complex<double> e1) {
      // Fix bug that clang sqrt can't right value of perfect squeres
      if (e1.imag() == 0 && e1.real() < 0) {
        return std::complex<double>(0, std::sqrt(-e1.real()));
      }
      else {
        return std::sqrt(e1);
      }
    }
    double sqrt(double e1) { return std::sqrt(e1); }
    double sqrt(int32_t e1) { return Rstats::ElementFunc::sqrt((double)e1); }

    // atan
    std::complex<double> atan(std::complex<double> e1) {
      if (e1 == std::complex<double>(0, 0)) {
        return std::complex<double>(0, 0);
      }
      else if (e1 == std::complex<double>(0, 1)) {
        return std::complex<double>(0, Rstats::Util::Inf());
      }
      else if (e1 == std::complex<double>(0, -1)) {
        return std::complex<double>(0, -Rstats::Util::Inf());
      }
      else {  
        std::complex<double> e2_i = std::complex<double>(0, 1);
        std::complex<double> e2_log = std::log((e2_i + e1) / (e2_i - e1));
        return (e2_i / std::complex<double>(2, 0)) * e2_log;
      }
    }
    double atan(double e1) { return ::atan2(e1, 1); }
    double atan(int32_t e1) { return Rstats::ElementFunc::atan2((double)e1, (double)1); }

    // asin
    std::complex<double> asin(std::complex<double> e1) {
      double e1_re = e1.real();
      double e1_im = e1.imag();
      
      if (e1_re == 0 && e1_im == 0) {
        return std::complex<double>(0, 0);
      }
      else {
        double e2_t1 = std::sqrt(
          ((e1_re + 1) * (e1_re + 1))
          +
          (e1_im * e1_im)
        );
        double e2_t2 = std::sqrt(
          ((e1_re - 1) * (e1_re - 1))
          +
          (e1_im * e1_im)
        );
        
        double e2_alpha = (e2_t1 + e2_t2) / 2;
        double e2_beta  = (e2_t1 - e2_t2) / 2;
        
        if (e2_alpha < 1) {
          e2_alpha = 1;
        }
        
        if (e2_beta > 1) {
          e2_beta = 1;
        }
        else if (e2_beta < -1) {
          e2_beta = -1;
        }
        
        double e2_u = Rstats::ElementFunc::atan2(
          e2_beta,
          std::sqrt(1 - (e2_beta * e2_beta))
        );
        
        double e2_v = -std::log(
          e2_alpha
          +
          std::sqrt((e2_alpha * e2_alpha) - 1)
        );
        
        if (e1_im > 0 || ((e1_im == 0) && (e1_re < -1))) {
          e2_v = -e2_v;
        }
        
        return std::complex<double>(e2_u, e2_v);
      }
    }
    double asin(double e1) { return std::asin(e1); }
    double asin(int32_t e1) { return Rstats::ElementFunc::asin((double)e1); }

    // acos
    std::complex<double> acos(std::complex<double> e1) {
      double e1_re = e1.real();
      double e1_im = e1.imag();
      
      if (e1_re == 1 && e1_im == 0) {
        return std::complex<double>(0, 0);
      }
      else {
        double e2_t1 = std::sqrt(
          ((e1_re + 1) * (e1_re + 1))
          +
          (e1_im * e1_im)
        );
        double e2_t2 = std::sqrt(
          ((e1_re - 1) * (e1_re - 1))
          +
          (e1_im * e1_im)
        );
        
        double e2_alpha = (e2_t1 + e2_t2) / 2;
        double e2_beta  = (e2_t1 - e2_t2) / 2;
        
        if (e2_alpha < 1) {
          e2_alpha = 1;
        }
        
        if (e2_beta > 1) {
          e2_beta = 1;
        }
        else if (e2_beta < -1) {
          e2_beta = -1;
        }
        
        double e2_u = Rstats::ElementFunc::atan2(
          std::sqrt(1 - (e2_beta * e2_beta)),
          e2_beta
        );
        
        double e2_v = std::log(
          e2_alpha
          +
          std::sqrt((e2_alpha * e2_alpha) - 1)
        );
        
        if (e1_im > 0 || (e1_im == 0 && e1_re < -1)) {
          e2_v = -e2_v;
        }
        
        return std::complex<double>(e2_u, e2_v);
      }
    }
    double acos(double e1) { return std::acos(e1); }
    double acos(int32_t e1) { return Rstats::ElementFunc::acos((double)e1); }

    // asinh
    std::complex<double> asinh(std::complex<double> e1) {
      std::complex<double> e2_t = (
        std::sqrt((e1 * e1) + std::complex<double>(1, 0))
        +
        e1
      );
      
      return std::log(e2_t);
    }
    double asinh(double e1) {
      double e2_t = (
        e1
        +
        std::sqrt((e1 * e1) + 1)
      );
      
      return std::log(e2_t);
    }
    double asinh(int32_t e1) { return Rstats::ElementFunc::asinh((double)e1); }

    // acosh
    std::complex<double> acosh(std::complex<double> e1) {
      double e1_re = e1.real();
      double e1_im = e1.imag();

      std::complex<double> e2_t = (
        std::sqrt(
          (e1 * e1)
          -
          std::complex<double>(1, 0)
        )
        +
        e1
      );
      std::complex<double> e2_u = std::log(e2_t);
      double e2_re = e2_u.real();
      double e2_im = e2_u.imag();
      
      std::complex<double> e2;
      if (e1_re < 0 && e1_im == 0) {
        e2 = std::complex<double>(e2_re, -e2_im);
      }
      else {
        e2 = std::complex<double>(e2_re, e2_im);
      }
      
      if (e1_re < 0) {
        return -e2;
      }
      else {
        return e2;
      }
    }
    double acosh(double e1) {
      if (e1 >= 1) {
        if (Rstats::Util::is_Inf(e1)) {
          Rstats::add_warn(Rstats::WARN_NAN_PRODUCED);
          return Rstats::Util::NaN();
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
        Rstats::add_warn(Rstats::WARN_NAN_PRODUCED);
        return Rstats::Util::NaN();
      }
    }
    double acosh(int32_t e1) { return Rstats::ElementFunc::acosh((double)e1); }

    // atanh
    std::complex<double> atanh(std::complex<double> e1) {
      if (e1 == std::complex<double>(1, 0)) {
        Rstats::add_warn(Rstats::WARN_NAN_PRODUCED);
        return std::complex<double>(Rstats::Util::Inf(), Rstats::Util::NaN());
      }
      else if (e1 == std::complex<double>(-1, 0)) {
        Rstats::add_warn(Rstats::WARN_NAN_PRODUCED);
        return std::complex<double>(-Rstats::Util::Inf(), Rstats::Util::NaN());
      }
      else {
        return std::complex<double>(0.5, 0)
          *
          std::log(
            (std::complex<double>(1, 0) + e1)
            /
            (std::complex<double>(1, 0) - e1)
          );
      }
    }
    double atanh(double e1) {
      if (Rstats::Util::is_Inf(e1)) {
        Rstats::add_warn(Rstats::WARN_NAN_PRODUCED);
        return Rstats::Util::NaN();
      }
      else {
        if (e1 == 1) {
          return Rstats::Util::Inf();
        }
        else if (e1 == -1) {
          return -Rstats::Util::Inf();
        }
        else if (std::abs(e1) < 1) {
          return std::log((1 + e1) / (1 - e1)) / 2;
        }
        else {
          Rstats::add_warn(Rstats::WARN_NAN_PRODUCED);
          return Rstats::Util::NaN();
        }
      }
    }
    double atanh(int32_t e1) { return Rstats::ElementFunc::atanh((double)e1); }

    // negate
    std::complex<double> negate(std::complex<double> e1) { return -e1; }
    double negate(double e1) { return -e1; }
    int32_t negate(int32_t e1) { return -e1; }

    // atan2
    std::complex<double> atan2(std::complex<double> e1, std::complex<double> e2) {
      std::complex<double> e3_s = (e1 * e1) + (e2 * e2);
      if (e3_s == std::complex<double>(0, 0)) {
        return std::complex<double>(0, 0);
      }
      else {
        std::complex<double> e3_i = std::complex<double>(0, 1);
        std::complex<double> e3_r = e2 + (e1 * e3_i);
        return -e3_i * std::log(e3_r / std::sqrt(e3_s));
      }
    }
    double atan2(double e1, double e2) {
      if (Rstats::Util::is_Inf(e1) && Rstats::Util::is_Inf(e2)) {
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
    double atan2(int32_t e1, int32_t e2) {
      return Rstats::ElementFunc::atan2((double)e1, (double)e2);
    }

    // And
    double And(std::complex<double> e1, std::complex<double> e2) {
      if (e1 != std::complex<double>(0, 0) && e2 != std::complex<double>(0, 0)) { return 1; }
      else { return 0; }
    }
    double And(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 && e2 ? 1 : 0; }
    }
    double And(int32_t e1, int32_t e2) { return e1 && e2 ? 1 : 0; }

    // Or
    double Or(std::complex<double> e1, std::complex<double> e2) {
      if (e1 != std::complex<double>(0, 0) || e2 != std::complex<double>(0, 0)) { return 1; }
      else { return 0; }
    }
    double Or(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 || e2 ? 1 : 0; }
    }
    double Or(int32_t e1, int32_t e2) { return e1 || e2 ? 1 : 0; }
    
    // equal
    double equal(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) == 0 ? 1 : 0; }
    double equal(std::complex<double> e1, std::complex<double> e2) { return e1 == e2 ? 1 : 0; }
    double equal(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 == e2 ? 1 : 0; }
    }
    double equal(int32_t e1, int32_t e2) { return e1 == e2 ? 1 : 0; }

    // not equal
    double not_equal(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) != 0 ? 1 : 0; }
    double not_equal(std::complex<double> e1, std::complex<double> e2) { return e1 != e2 ? 1 : 0; }
    double not_equal(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 != e2 ? 1 : 0; }
    }
    double not_equal(int32_t e1, int32_t e2) { return e1 != e2 ? 1 : 0; }

    // more_than
    double more_than(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) > 0 ? 1 : 0; }
    double more_than(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 > e2 ? 1 : 0; }
    }
    double more_than(int32_t e1, int32_t e2) { return e1 > e2 ? 1 : 0; }

    // less_than
    double less_than(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) < 0 ? 1 : 0; }
    double less_than(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 < e2 ? 1 : 0; }
    }
    double less_than(int32_t e1, int32_t e2) { return e1 < e2 ? 1 : 0; }

    // more_than_or_equal
    double more_than_or_equal(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) >= 0 ? 1 : 0; }
    double more_than_or_equal(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 >= e2 ? 1 : 0; }
    }
    double more_than_or_equal(int32_t e1, int32_t e2) { return e1 >= e2 ? 1 : 0; }
    // less_than_or_equal
    double less_than_or_equal(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) <= 0 ? 1 : 0; }
    double less_than_or_equal(double e1, double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 <= e2 ? 1 : 0; }
    }
    double less_than_or_equal(int32_t e1, int32_t e2) { return e1 <= e2 ? 1 : 0; }

    // is_infinite
    double is_infinite(Rstats::Character e1) { return 0; }
    double is_infinite(std::complex<double> e1) {
      if (Rstats::Util::is_NaN(e1.real()) || Rstats::Util::is_NaN(e1.imag())) {
        return 0;
      }
      else if (Rstats::Util::is_Inf(e1.real()) || Rstats::Util::is_Inf(e1.imag())) {
        return 1;
      }
      else {
        return 0;
      }
    }
    double is_infinite(double e1) { return Rstats::Util::is_Inf(e1) ? 1 : 0; }
    double is_infinite(int32_t e1) { return 0; }

    // is_finite
    double is_finite(Rstats::Character e1) { return 0; }
    double is_finite(std::complex<double> e1) {
      if (std::isfinite(e1.real()) && std::isfinite(e1.imag())) {
        return 1;
      }
      else {
        return 0;
      }
    }
    double is_finite(double e1) { return std::isfinite(e1) ? 1 : 0; }
    double is_finite(int32_t e1) { return 1; }

    // is_nan
    double is_nan(Rstats::Character e1) { return 0; }
    double is_nan(std::complex<double> e1) {
      if (Rstats::Util::is_NaN(e1.real()) || Rstats::Util::is_NaN(e1.imag())) {
        return 1;
      }
      else {
        return 0;
      }
    }
    double is_nan(double e1) { return Rstats::Util::is_NaN(e1) ? 1 : 0; }
    double is_nan(int32_t e1) { return 0; }

    // as_string
    Rstats::Character as_string(Rstats::Character e1) {
      return Rstats::pl_new_sv_sv(e1);
    }
    Rstats::Character as_string(std::complex<double> e1) {
      double re = e1.real();
      double im = e1.imag();
      
      SV* sv_re = Rstats::pl_new_sv_nv(re);
      SV* sv_im = Rstats::pl_new_sv_nv(im);
      SV* sv_str = Rstats::pl_new_sv_pv("");
      
      sv_catpv(sv_str, SvPV_nolen(sv_re));
      if (im >= 0) {
        sv_catpv(sv_str, "+");
      }
      sv_catpv(sv_str, SvPV_nolen(sv_im));
      sv_catpv(sv_str, "i");
      
      return sv_str;
    }
    Rstats::Character as_string(double e1) {
      SV* sv_str = Rstats::pl_new_sv_pv("");
      if (Rstats::Util::is_Inf(e1) && e1 > 0) {
        sv_catpv(sv_str, "Inf");
      }
      else if (Rstats::Util::is_Inf(e1) && e1 < 0) {
        sv_catpv(sv_str, "-Inf");
      }
      else if (Rstats::Util::is_NaN(e1)) {
        sv_catpv(sv_str, "NaN");
      }
      else {
        sv_catpv(sv_str, SvPV_nolen(Rstats::pl_new_sv_nv(e1)));
      }
      
      return sv_str;
    }
    Rstats::Character as_string(int32_t e1) {
      return Rstats::pl_new_sv_iv(e1);
    }

    // as_complex
    std::complex<double> as_complex(std::complex<double> e1) { return e1; }
    std::complex<double> as_complex(double e1) { return std::complex<double>(e1, 0); }
    std::complex<double> as_complex(int32_t e1) { return Rstats::ElementFunc::as_complex((double)e1); }

    // as_double
    double as_double(std::complex<double> e1) {
      if (e1.imag() != 0) {
        Rstats::add_warn(Rstats::WARN_IMAGINARY_PART_DISCARDED);
      }
      return e1.real();
    }
    double as_double(double e1) { return e1; }
    double as_double(int32_t e1) { return (double)e1; }

  }
}

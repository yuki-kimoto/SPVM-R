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
    Rstats::Complex add(Rstats::Complex e1, Rstats::Complex e2) { return e1 + e2; }
    Rstats::Double add(Rstats::Double e1, Rstats::Double e2) { return e1 + e2; }
    int32_t add(int32_t e1, int32_t e2) { return e1 + e2; }
    
    // subtract
    Rstats::Complex subtract(Rstats::Complex e1, Rstats::Complex e2) { return e1 - e2; }
    Rstats::Double subtract(Rstats::Double e1, Rstats::Double e2) { return e1 - e2; }
    int32_t subtract(int32_t e1, int32_t e2) { return e1 - e2; }
    
    // multiply
    Rstats::Complex multiply(Rstats::Complex e1, Rstats::Complex e2) { return e1 * e2; }
    Rstats::Double multiply(Rstats::Double e1, Rstats::Double e2) { return e1 * e2; }
    int32_t multiply(int32_t e1, int32_t e2) { return e1 * e2; }

    // divide
    Rstats::Complex divide(Rstats::Complex e1, Rstats::Complex e2) { return e1 / e2; }
    Rstats::Double divide(Rstats::Double e1, Rstats::Double e2) { return e1 / e2; }
    Rstats::Double divide(int32_t e1, int32_t e2) {
      return Rstats::ElementFunc::divide((Rstats::Double)e1, (Rstats::Double)e2);
    }
    
    // pow
    Rstats::Complex pow(Rstats::Complex e1, Rstats::Complex e2) { return std::pow(e1, e2); }
    Rstats::Double pow(Rstats::Double e1, Rstats::Double e2) { return ::pow(e1, e2); }
    Rstats::Double pow(int32_t e1, int32_t e2) {
      return Rstats::ElementFunc::pow((Rstats::Double)e1, (Rstats::Double)e2);
    }

    // remainder
    Rstats::Double remainder(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2) || e2 == 0) {
        return Rstats::Util::NaN();
      }
      else {
        return fmod(e1, e2);;
      }
    }
    Rstats::Double remainder(int32_t e1, int32_t e2) {
      return Rstats::ElementFunc::remainder((Rstats::Double) e1, (Rstats::Double) e2);
    }

    // Re
    Rstats::Double Re(Rstats::Complex e1) { return e1.real(); }
    Rstats::Double Re(Rstats::Double e1) { return e1; }
    Rstats::Double Re(int32_t e1) { return Rstats::ElementFunc::Re((Rstats::Double)e1); }

    // Im
    Rstats::Double Im(Rstats::Complex e1) { return e1.imag(); }
    Rstats::Double Im(Rstats::Double e1) { return 0; }
    Rstats::Double Im(int32_t e1) { return Rstats::ElementFunc::Im((Rstats::Double)e1); }

    // Conj
    Rstats::Complex Conj(Rstats::Complex e1) { return Rstats::Complex(e1.real(), -e1.imag()); }
    Rstats::Double Conj(Rstats::Double e1) { return e1; }
    Rstats::Double Conj(int32_t e1) { return Rstats::ElementFunc::Conj((Rstats::Double)e1); }

    // sin
    Rstats::Complex sin(Rstats::Complex e1) { return std::sin(e1); }
    Rstats::Double sin(Rstats::Double e1) { return std::sin(e1); }
    Rstats::Double sin(int32_t e1) { return Rstats::ElementFunc::sin((Rstats::Double)e1); }

    // cos
    Rstats::Complex cos(Rstats::Complex e1) { return std::cos(e1); }
    Rstats::Double cos(Rstats::Double e1) { return std::cos(e1); }
    Rstats::Double cos(int32_t e1) { return Rstats::ElementFunc::cos((Rstats::Double)e1); }

    // tan
    Rstats::Complex tan(Rstats::Complex e1) { return std::tan(e1); }
    Rstats::Double tan(Rstats::Double e1) { return std::tan(e1); }
    Rstats::Double tan(int32_t e1) { return Rstats::ElementFunc::tan((Rstats::Double)e1); }

    // sinh
    Rstats::Complex sinh(Rstats::Complex e1) { return std::sinh(e1); }
    Rstats::Double sinh(Rstats::Double e1) { return std::sinh(e1); }
    Rstats::Double sinh(int32_t e1) { return Rstats::ElementFunc::sinh((Rstats::Double)e1); }

    // cosh
    Rstats::Complex cosh(Rstats::Complex e1) { return std::cosh(e1); }
    Rstats::Double cosh(Rstats::Double e1) { return std::cosh(e1); }
    Rstats::Double cosh(int32_t e1) { return Rstats::ElementFunc::cosh((Rstats::Double)e1); }

    // tanh
    Rstats::Complex tanh (Rstats::Complex z) {
      Rstats::Double re = z.real();
      
      // For fix FreeBSD bug
      // FreeBAD return (NaN + NaNi) when real value is negative infinite
      if (Rstats::Util::is_Inf(re) && re < 0) {
        return Rstats::Complex(-1, 0);
      }
      else {
        return std::tanh(z);
      }
    }
    Rstats::Double tanh(Rstats::Double e1) { return std::tanh(e1); }
    Rstats::Double tanh(int32_t e1) { return Rstats::ElementFunc::tanh((Rstats::Double)e1); }

    // abs
    Rstats::Double abs(Rstats::Complex e1) { return std::abs(e1); }
    Rstats::Double abs(Rstats::Double e1) { return std::abs(e1); }
    Rstats::Double abs(int32_t e1) { return Rstats::ElementFunc::abs((Rstats::Double)e1); }

    // abs
    Rstats::Double Mod(Rstats::Complex e1) { return abs(e1); }
    Rstats::Double Mod(Rstats::Double e1) { return abs(e1); }
    Rstats::Double Mod(int32_t e1) { return Rstats::ElementFunc::abs((Rstats::Double)e1); }

    // log
    Rstats::Complex log(Rstats::Complex e1) { return std::log(e1); }
    Rstats::Double log(Rstats::Double e1) { return std::log(e1); }
    Rstats::Double log(int32_t e1) { return Rstats::ElementFunc::log((Rstats::Double)e1); }

    // logb
    Rstats::Complex logb(Rstats::Complex e1) { return log(e1); }
    Rstats::Double logb(Rstats::Double e1) { return log(e1); }
    Rstats::Double logb(int32_t e1) { return Rstats::ElementFunc::log((Rstats::Double)e1); }

    // log10
    Rstats::Complex log10(Rstats::Complex e1) { return std::log10(e1); }
    Rstats::Double log10(Rstats::Double e1) { return std::log10(e1); }
    Rstats::Double log10(int32_t e1) { return Rstats::ElementFunc::log10((Rstats::Double)e1); }

    // log2
    Rstats::Complex log2(Rstats::Complex e1) {
      return std::log(e1) / std::log(Rstats::Complex(2, 0));
    }
    Rstats::Double log2(Rstats::Double e1) {
      return std::log(e1) / std::log((Rstats::Double)2);
    }
    Rstats::Double log2(int32_t e1) { return Rstats::ElementFunc::log2((Rstats::Double)e1); }
    
    // expm1
    Rstats::Double expm1(Rstats::Double e1) { return ::expm1(e1); }
    Rstats::Double expm1(int32_t e1) { return Rstats::ElementFunc::expm1((Rstats::Double)e1); }

    // Arg
    Rstats::Double Arg(Rstats::Complex e1) {
      Rstats::Double re = e1.real();
      Rstats::Double im = e1.imag();
      
      if (re == 0 && im == 0) {
        return 0;
      }
      else {
        return Rstats::ElementFunc::atan2(im, re);
      }
    }
    Rstats::Double Arg(Rstats::Double e1) {
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
    
    Rstats::Double Arg(int32_t e1) {
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
    Rstats::Complex exp(Rstats::Complex e1) { return std::exp(e1); }
    Rstats::Double exp(Rstats::Double e1) { return std::exp(e1); }
    Rstats::Double exp(int32_t e1) { return Rstats::ElementFunc::exp((Rstats::Double)e1); }

    // sqrt
    Rstats::Complex sqrt(Rstats::Complex e1) {
      // Fix bug that clang sqrt can't right value of perfect squeres
      if (e1.imag() == 0 && e1.real() < 0) {
        return Rstats::Complex(0, std::sqrt(-e1.real()));
      }
      else {
        return std::sqrt(e1);
      }
    }
    Rstats::Double sqrt(Rstats::Double e1) { return std::sqrt(e1); }
    Rstats::Double sqrt(int32_t e1) { return Rstats::ElementFunc::sqrt((Rstats::Double)e1); }

    // atan
    Rstats::Complex atan(Rstats::Complex e1) {
      if (e1 == Rstats::Complex(0, 0)) {
        return Rstats::Complex(0, 0);
      }
      else if (e1 == Rstats::Complex(0, 1)) {
        return Rstats::Complex(0, Rstats::Util::Inf());
      }
      else if (e1 == Rstats::Complex(0, -1)) {
        return Rstats::Complex(0, -Rstats::Util::Inf());
      }
      else {  
        Rstats::Complex e2_i = Rstats::Complex(0, 1);
        Rstats::Complex e2_log = std::log((e2_i + e1) / (e2_i - e1));
        return (e2_i / Rstats::Complex(2, 0)) * e2_log;
      }
    }
    Rstats::Double atan(Rstats::Double e1) { return ::atan2(e1, 1); }
    Rstats::Double atan(int32_t e1) { return Rstats::ElementFunc::atan2((Rstats::Double)e1, (Rstats::Double)1); }

    // asin
    Rstats::Complex asin(Rstats::Complex e1) {
      Rstats::Double e1_re = e1.real();
      Rstats::Double e1_im = e1.imag();
      
      if (e1_re == 0 && e1_im == 0) {
        return Rstats::Complex(0, 0);
      }
      else {
        Rstats::Double e2_t1 = std::sqrt(
          ((e1_re + 1) * (e1_re + 1))
          +
          (e1_im * e1_im)
        );
        Rstats::Double e2_t2 = std::sqrt(
          ((e1_re - 1) * (e1_re - 1))
          +
          (e1_im * e1_im)
        );
        
        Rstats::Double e2_alpha = (e2_t1 + e2_t2) / 2;
        Rstats::Double e2_beta  = (e2_t1 - e2_t2) / 2;
        
        if (e2_alpha < 1) {
          e2_alpha = 1;
        }
        
        if (e2_beta > 1) {
          e2_beta = 1;
        }
        else if (e2_beta < -1) {
          e2_beta = -1;
        }
        
        Rstats::Double e2_u = Rstats::ElementFunc::atan2(
          e2_beta,
          std::sqrt(1 - (e2_beta * e2_beta))
        );
        
        Rstats::Double e2_v = -std::log(
          e2_alpha
          +
          std::sqrt((e2_alpha * e2_alpha) - 1)
        );
        
        if (e1_im > 0 || ((e1_im == 0) && (e1_re < -1))) {
          e2_v = -e2_v;
        }
        
        return Rstats::Complex(e2_u, e2_v);
      }
    }
    Rstats::Double asin(Rstats::Double e1) { return std::asin(e1); }
    Rstats::Double asin(int32_t e1) { return Rstats::ElementFunc::asin((Rstats::Double)e1); }

    // acos
    Rstats::Complex acos(Rstats::Complex e1) {
      Rstats::Double e1_re = e1.real();
      Rstats::Double e1_im = e1.imag();
      
      if (e1_re == 1 && e1_im == 0) {
        return Rstats::Complex(0, 0);
      }
      else {
        Rstats::Double e2_t1 = std::sqrt(
          ((e1_re + 1) * (e1_re + 1))
          +
          (e1_im * e1_im)
        );
        Rstats::Double e2_t2 = std::sqrt(
          ((e1_re - 1) * (e1_re - 1))
          +
          (e1_im * e1_im)
        );
        
        Rstats::Double e2_alpha = (e2_t1 + e2_t2) / 2;
        Rstats::Double e2_beta  = (e2_t1 - e2_t2) / 2;
        
        if (e2_alpha < 1) {
          e2_alpha = 1;
        }
        
        if (e2_beta > 1) {
          e2_beta = 1;
        }
        else if (e2_beta < -1) {
          e2_beta = -1;
        }
        
        Rstats::Double e2_u = Rstats::ElementFunc::atan2(
          std::sqrt(1 - (e2_beta * e2_beta)),
          e2_beta
        );
        
        Rstats::Double e2_v = std::log(
          e2_alpha
          +
          std::sqrt((e2_alpha * e2_alpha) - 1)
        );
        
        if (e1_im > 0 || (e1_im == 0 && e1_re < -1)) {
          e2_v = -e2_v;
        }
        
        return Rstats::Complex(e2_u, e2_v);
      }
    }
    Rstats::Double acos(Rstats::Double e1) { return std::acos(e1); }
    Rstats::Double acos(int32_t e1) { return Rstats::ElementFunc::acos((Rstats::Double)e1); }

    // asinh
    Rstats::Complex asinh(Rstats::Complex e1) {
      Rstats::Complex e2_t = (
        std::sqrt((e1 * e1) + Rstats::Complex(1, 0))
        +
        e1
      );
      
      return std::log(e2_t);
    }
    Rstats::Double asinh(Rstats::Double e1) {
      Rstats::Double e2_t = (
        e1
        +
        std::sqrt((e1 * e1) + 1)
      );
      
      return std::log(e2_t);
    }
    Rstats::Double asinh(int32_t e1) { return Rstats::ElementFunc::asinh((Rstats::Double)e1); }

    // acosh
    Rstats::Complex acosh(Rstats::Complex e1) {
      Rstats::Double e1_re = e1.real();
      Rstats::Double e1_im = e1.imag();

      Rstats::Complex e2_t = (
        std::sqrt(
          (e1 * e1)
          -
          Rstats::Complex(1, 0)
        )
        +
        e1
      );
      Rstats::Complex e2_u = std::log(e2_t);
      Rstats::Double e2_re = e2_u.real();
      Rstats::Double e2_im = e2_u.imag();
      
      Rstats::Complex e2;
      if (e1_re < 0 && e1_im == 0) {
        e2 = Rstats::Complex(e2_re, -e2_im);
      }
      else {
        e2 = Rstats::Complex(e2_re, e2_im);
      }
      
      if (e1_re < 0) {
        return -e2;
      }
      else {
        return e2;
      }
    }
    Rstats::Double acosh(Rstats::Double e1) {
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
    Rstats::Double acosh(int32_t e1) { return Rstats::ElementFunc::acosh((Rstats::Double)e1); }

    // atanh
    Rstats::Complex atanh(Rstats::Complex e1) {
      if (e1 == Rstats::Complex(1, 0)) {
        Rstats::add_warn(Rstats::WARN_NAN_PRODUCED);
        return Rstats::Complex(Rstats::Util::Inf(), Rstats::Util::NaN());
      }
      else if (e1 == Rstats::Complex(-1, 0)) {
        Rstats::add_warn(Rstats::WARN_NAN_PRODUCED);
        return Rstats::Complex(-Rstats::Util::Inf(), Rstats::Util::NaN());
      }
      else {
        return Rstats::Complex(0.5, 0)
          *
          std::log(
            (Rstats::Complex(1, 0) + e1)
            /
            (Rstats::Complex(1, 0) - e1)
          );
      }
    }
    Rstats::Double atanh(Rstats::Double e1) {
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
    Rstats::Double atanh(int32_t e1) { return Rstats::ElementFunc::atanh((Rstats::Double)e1); }

    // negate
    Rstats::Complex negate(Rstats::Complex e1) { return -e1; }
    Rstats::Double negate(Rstats::Double e1) { return -e1; }
    int32_t negate(int32_t e1) { return -e1; }

    // atan2
    Rstats::Complex atan2(Rstats::Complex e1, Rstats::Complex e2) {
      Rstats::Complex e3_s = (e1 * e1) + (e2 * e2);
      if (e3_s == Rstats::Complex(0, 0)) {
        return Rstats::Complex(0, 0);
      }
      else {
        Rstats::Complex e3_i = Rstats::Complex(0, 1);
        Rstats::Complex e3_r = e2 + (e1 * e3_i);
        return -e3_i * std::log(e3_r / std::sqrt(e3_s));
      }
    }
    Rstats::Double atan2(Rstats::Double e1, Rstats::Double e2) {
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
    Rstats::Double atan2(int32_t e1, int32_t e2) {
      return Rstats::ElementFunc::atan2((Rstats::Double)e1, (Rstats::Double)e2);
    }

    // And
    Rstats::Double And(Rstats::Complex e1, Rstats::Complex e2) {
      if (e1 != Rstats::Complex(0, 0) && e2 != Rstats::Complex(0, 0)) { return 1; }
      else { return 0; }
    }
    Rstats::Double And(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 && e2 ? 1 : 0; }
    }
    Rstats::Double And(int32_t e1, int32_t e2) { return e1 && e2 ? 1 : 0; }

    // Or
    Rstats::Double Or(Rstats::Complex e1, Rstats::Complex e2) {
      if (e1 != Rstats::Complex(0, 0) || e2 != Rstats::Complex(0, 0)) { return 1; }
      else { return 0; }
    }
    Rstats::Double Or(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 || e2 ? 1 : 0; }
    }
    Rstats::Double Or(int32_t e1, int32_t e2) { return e1 || e2 ? 1 : 0; }
    
    // equal
    Rstats::Double equal(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) == 0 ? 1 : 0; }
    Rstats::Double equal(Rstats::Complex e1, Rstats::Complex e2) { return e1 == e2 ? 1 : 0; }
    Rstats::Double equal(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 == e2 ? 1 : 0; }
    }
    Rstats::Double equal(int32_t e1, int32_t e2) { return e1 == e2 ? 1 : 0; }

    // not equal
    Rstats::Double not_equal(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) != 0 ? 1 : 0; }
    Rstats::Double not_equal(Rstats::Complex e1, Rstats::Complex e2) { return e1 != e2 ? 1 : 0; }
    Rstats::Double not_equal(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 != e2 ? 1 : 0; }
    }
    Rstats::Double not_equal(int32_t e1, int32_t e2) { return e1 != e2 ? 1 : 0; }

    // more_than
    Rstats::Double more_than(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) > 0 ? 1 : 0; }
    Rstats::Double more_than(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 > e2 ? 1 : 0; }
    }
    Rstats::Double more_than(int32_t e1, int32_t e2) { return e1 > e2 ? 1 : 0; }

    // less_than
    Rstats::Double less_than(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) < 0 ? 1 : 0; }
    Rstats::Double less_than(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 < e2 ? 1 : 0; }
    }
    Rstats::Double less_than(int32_t e1, int32_t e2) { return e1 < e2 ? 1 : 0; }

    // more_than_or_equal
    Rstats::Double more_than_or_equal(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) >= 0 ? 1 : 0; }
    Rstats::Double more_than_or_equal(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 >= e2 ? 1 : 0; }
    }
    Rstats::Double more_than_or_equal(int32_t e1, int32_t e2) { return e1 >= e2 ? 1 : 0; }
    // less_than_or_equal
    Rstats::Double less_than_or_equal(Rstats::Character e1, Rstats::Character e2) { return sv_cmp(e1, e2) <= 0 ? 1 : 0; }
    Rstats::Double less_than_or_equal(Rstats::Double e1, Rstats::Double e2) {
      if (Rstats::Util::is_NaN(e1) || Rstats::Util::is_NaN(e2)) { throw Rstats::NaException; }
      else { return e1 <= e2 ? 1 : 0; }
    }
    Rstats::Double less_than_or_equal(int32_t e1, int32_t e2) { return e1 <= e2 ? 1 : 0; }

    // is_infinite
    Rstats::Double is_infinite(Rstats::Character e1) { return 0; }
    Rstats::Double is_infinite(Rstats::Complex e1) {
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
    Rstats::Double is_infinite(Rstats::Double e1) { return Rstats::Util::is_Inf(e1) ? 1 : 0; }
    Rstats::Double is_infinite(int32_t e1) { return 0; }

    // is_finite
    Rstats::Double is_finite(Rstats::Character e1) { return 0; }
    Rstats::Double is_finite(Rstats::Complex e1) {
      if (std::isfinite(e1.real()) && std::isfinite(e1.imag())) {
        return 1;
      }
      else {
        return 0;
      }
    }
    Rstats::Double is_finite(Rstats::Double e1) { return std::isfinite(e1) ? 1 : 0; }
    Rstats::Double is_finite(int32_t e1) { return 1; }

    // is_nan
    Rstats::Double is_nan(Rstats::Character e1) { return 0; }
    Rstats::Double is_nan(Rstats::Complex e1) {
      if (Rstats::Util::is_NaN(e1.real()) || Rstats::Util::is_NaN(e1.imag())) {
        return 1;
      }
      else {
        return 0;
      }
    }
    Rstats::Double is_nan(Rstats::Double e1) { return Rstats::Util::is_NaN(e1) ? 1 : 0; }
    Rstats::Double is_nan(int32_t e1) { return 0; }

    // as_string
    Rstats::Character as_string(Rstats::Character e1) {
      return Rstats::pl_new_sv_sv(e1);
    }
    Rstats::Character as_string(Rstats::Complex e1) {
      Rstats::Double re = e1.real();
      Rstats::Double im = e1.imag();
      
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
    Rstats::Character as_string(Rstats::Double e1) {
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
    Rstats::Complex as_complex(Rstats::Character e1) {
      SV* sv_z = Rstats::Util::looks_like_complex(e1);
      
      if (SvOK(sv_z)) {
        SV* sv_re = Rstats::pl_hv_fetch(sv_z, "re");
        SV* sv_im = Rstats::pl_hv_fetch(sv_z, "im");
        Rstats::Double re = SvNV(sv_re);
        Rstats::Double im = SvNV(sv_im);
        return Rstats::Complex(re, im);
      }
      else {
        throw Rstats::NaException;
      }
    }
    Rstats::Complex as_complex(Rstats::Complex e1) { return e1; }
    Rstats::Complex as_complex(Rstats::Double e1) { return Rstats::Complex(e1, 0); }
    Rstats::Complex as_complex(int32_t e1) { return Rstats::ElementFunc::as_complex((Rstats::Double)e1); }

    // as_double
    Rstats::Double as_double(Rstats::Character e1) {
      SV* sv_value_fix = Rstats::Util::looks_like_double(e1);
      if (SvOK(sv_value_fix)) {
        return SvNV(sv_value_fix);
      }
      else {
        throw Rstats::NaException;
      }
    }
    Rstats::Double as_double(Rstats::Complex e1) {
      if (e1.imag() != 0) {
        Rstats::add_warn(Rstats::WARN_IMAGINARY_PART_DISCARDED);
      }
      return e1.real();
    }
    Rstats::Double as_double(Rstats::Double e1) { return e1; }
    Rstats::Double as_double(int32_t e1) { return (Rstats::Double)e1; }

  }
}

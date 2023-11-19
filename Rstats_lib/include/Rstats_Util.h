#ifndef PERL_RSTATS_UTIL_H
#define PERL_RSTATS_UTIL_H

#include <limits>
#include "Rstats_Main.h"

namespace Rstats {
  namespace Util {
    double is_perl_number(SV*);
    SV* cross_product(SV*);
    SV* pos_to_index(SV*, SV*);
    SV* index_to_pos(SV*, SV*);
    double pi();
    double Inf();
    double NaN();
    double is_Inf(double);
    double is_NaN(double);
  }
}

#endif

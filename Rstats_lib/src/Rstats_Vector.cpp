#include "Rstats_Vector.h"

namespace Rstats {

  template <>
  void Vector<Rstats::Character>::initialize(int32_t length) {
    this->values = new Rstats::Character[length];
    this->length = length;
    this->na_positions = NULL;
    for (int32_t i = 0; i < length; i++) {
      SV** value_ptr = (SV**)this->values;
      *(value_ptr + i) = &PL_sv_undef;
    }
  }

  template <>
  Vector<Rstats::Character>::Vector(int32_t length) {
    this->initialize(length);
  }

  template <>
  void Vector<Rstats::Character>::set_value(int32_t pos, Rstats::Character value) {
    SV* current_value = *(this->get_values() + pos);
    
    if (SvOK(current_value)) {
      SvREFCNT_dec(current_value);
    }
    
    *(this->get_values() + pos) = SvREFCNT_inc(value);
  }

  template<>
  Vector<Rstats::Character>::~Vector() {

    Rstats::Character* values = this->get_values();
    int32_t length = this->get_length();
    for (int32_t i = 0; i < length; i++) {
      if (*(values + i) != NULL) {
        SvREFCNT_dec(*(values + i));
      }
    }
    delete[] values;
    delete[] this->na_positions;
  }
}

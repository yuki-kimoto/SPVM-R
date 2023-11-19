#ifndef PERL_RSTATS_VECTOR_H
#define PERL_RSTATS_VECTOR_H

#include "Rstats_ElementFunc.h"

namespace Rstats {
  
  template <class T>
  class Vector {
    private:
    
    Rstats::NaPosition* na_positions;
    T* values;
    int32_t length;
    
    public:
    
    void initialize(int32_t);
    Vector<T>(int32_t);
    Vector<T>(int32_t, T);

    int32_t get_length();
    void init_na_positions();
    void add_na_position(int32_t);
    double exists_na_position(int32_t);
    void merge_na_positions(Rstats::NaPosition*);
    Rstats::NaPosition* get_na_positions();
    int32_t get_na_positions_length();
    
    T* get_values();
    void set_value(int32_t, T); 
    T get_value(int32_t);
    
    ~Vector();
  };
  template <>
  void Vector<Rstats::Character>::initialize(int32_t);
  template<>
  Vector<Rstats::Character>::Vector(int32_t);
  template <>
  void Vector<Rstats::Character>::set_value(int32_t, Rstats::Character);
  template <>
  Vector<Rstats::Character>::~Vector();
}
#include "Rstats_Vector_impl.h"

#endif

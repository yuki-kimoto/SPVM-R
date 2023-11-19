#include "Rstats_Func.h"

// Rstats::Func
namespace Rstats {
  namespace Func {

    template <>
    void set_vector<Rstats::Character>(SV* sv_r, SV* sv_x1, Rstats::Vector<Rstats::Character>* v1) {
      SV* sv_vector = Rstats::pl_object_wrap<Rstats::Vector<Rstats::Character>*>(v1, "Rstats::Vector::Character");
      Rstats::pl_hv_store(sv_x1, "vector", sv_vector);
    }

    template <>
    void set_vector<std::complex<double>>(SV* sv_r, SV* sv_x1, Rstats::Vector<std::complex<double>>* v1) {
      SV* sv_vector = Rstats::pl_object_wrap<Rstats::Vector<std::complex<double>>*>(v1, "Rstats::Vector::Complex");
      Rstats::pl_hv_store(sv_x1, "vector", sv_vector);
    }

    template <>
    void set_vector<double>(SV* sv_r, SV* sv_x1, Rstats::Vector<double>* v1) {
      SV* sv_vector = Rstats::pl_object_wrap<Rstats::Vector<double>*>(v1, "Rstats::Vector::Double");
      Rstats::pl_hv_store(sv_x1, "vector", sv_vector);
    }

    template <>
    void set_vector<int32_t>(SV* sv_r, SV* sv_x1, Rstats::Vector<int32_t>* v1) {
      SV* sv_vector = Rstats::pl_object_wrap<Rstats::Vector<int32_t>*>(v1, "Rstats::Vector::Integer");
      Rstats::pl_hv_store(sv_x1, "vector", sv_vector);
    }

    template <>
    Rstats::Vector<Rstats::Character>* get_vector<Rstats::Character>(SV* sv_r, SV* sv_x1) {
      SV* sv_vector = Rstats::pl_hv_fetch(sv_x1, "vector");
      
      if (SvOK(sv_vector)) {
        Rstats::Vector<Rstats::Character>* vector
          = Rstats::pl_object_unwrap<Rstats::Vector<Rstats::Character>*>(sv_vector, "Rstats::Vector::Character");
        return vector;
      }
      else {
        return NULL;
      }
    }

    template <>
    Rstats::Vector<std::complex<double>>* get_vector<std::complex<double>>(SV* sv_r, SV* sv_x1) {
      SV* sv_vector = Rstats::pl_hv_fetch(sv_x1, "vector");
      
      if (SvOK(sv_vector)) {
        Rstats::Vector<std::complex<double>>* vector
          = Rstats::pl_object_unwrap<Rstats::Vector<std::complex<double>>*>(sv_vector, "Rstats::Vector::Complex");
        return vector;
      }
      else {
        return NULL;
      }
    }

    template <>
    Rstats::Vector<double>* get_vector<double>(SV* sv_r, SV* sv_x1) {
      SV* sv_vector = Rstats::pl_hv_fetch(sv_x1, "vector");
      
      if (SvOK(sv_vector)) {
        Rstats::Vector<double>* vector
          = Rstats::pl_object_unwrap<Rstats::Vector<double>*>(sv_vector, "Rstats::Vector::Double");
        return vector;
      }
      else {
        return NULL;
      }
    }

    template <>
    Rstats::Vector<int32_t>* get_vector<int32_t>(SV* sv_r, SV* sv_x1) {
      SV* sv_vector = Rstats::pl_hv_fetch(sv_x1, "vector");
      
      if (SvOK(sv_vector)) {
        Rstats::Vector<int32_t>* vector
          = Rstats::pl_object_unwrap<Rstats::Vector<int32_t>*>(sv_vector, "Rstats::Vector::Integer");
        return vector;
      }
      else {
        return NULL;
      }
    }
    
    SV* length(SV* sv_r, SV* x1) {
      int32_t x1_length = Rstats::Func::get_length(sv_r, x1);
      Rstats::Vector<int32_t>* v_out = new Rstats::Vector<int32_t>(1, x1_length);
      SV* sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
      return sv_x_out;
    }

    double to_bool (SV* sv_r, SV* sv_x1) {
      
      if (strEQ(Rstats::Func::get_type(sv_r, sv_x1), "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        double is = v1->get_value(0);
        return is;
      }
      else {
        croak("to_bool receive double array");
      }
    }

    SV* c(SV* sv_r, SV* sv_elements) {
      
      int32_t length = Rstats::pl_av_len(sv_elements);
      
      SV* sv_new_elements = Rstats::pl_new_avrv();
      
      // Convert to Rstats::Object, check type and total length, and remove NULL
      SV* sv_type_h = Rstats::pl_new_hvrv();
      int32_t total_length = 0;
      for (int32_t i = 0; i < length; i++) {
        SV* sv_element = Rstats::pl_av_fetch(sv_elements, i);
        
        SV* sv_new_element = Rstats::Func::to_object(sv_r, sv_element);
        
        char* type = Rstats::Func::get_type(sv_r, sv_new_element);
        
        if (!strEQ(type, "NULL")) {
          total_length += Rstats::Func::get_length(sv_r, sv_new_element);
          Rstats::pl_hv_store(sv_type_h, type, Rstats::pl_new_sv_iv(1));
          Rstats::pl_av_push(sv_new_elements, sv_new_element);
        }
      }
      
      SV* sv_x_out;
      if (total_length == 0) {
        sv_x_out = Rstats::Func::new_NULL(sv_r);
        return sv_x_out;
      }

      // Decide type
      if (Rstats::pl_hv_exists(sv_type_h, "string")) {
        Rstats::Vector<Rstats::Character>* v_out = new Rstats::Vector<Rstats::Character>(total_length);
        int32_t pos = 0;
        for (int32_t i = 0; i < length; i++) {
          SV* sv_element = Rstats::pl_av_fetch(sv_new_elements, i);
          char* type = Rstats::Func::get_type(sv_r, sv_element);
          if (!strEQ(type, "string")) {
            sv_element = Rstats::Func::as_string(sv_r, sv_element);
          }
          Rstats::Vector<Rstats::Character>* v1 =  Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_element);
          int32_t v1_length = v1->get_length();
          for (int32_t k = 0; k < v1_length; k++) {
            if (v1->exists_na_position(k)) {
              v_out->add_na_position(pos);
            }
            else {
              v_out->set_value(pos, v1->get_value(k));
            }
            pos++;
          }
        }
        sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
      }
      else if (Rstats::pl_hv_exists(sv_type_h, "complex")) {
        Rstats::Vector<std::complex<double>>* v_out = new Rstats::Vector<std::complex<double>>(total_length);
        int32_t pos = 0;
        for (int32_t i = 0; i < length; i++) {
          SV* sv_element = Rstats::pl_av_fetch(sv_new_elements, i);
          char* type = Rstats::Func::get_type(sv_r, sv_element);
          if (!strEQ(type, "complex")) {
            sv_element = Rstats::Func::as_complex(sv_r, sv_element);
          }
          Rstats::Vector<std::complex<double>>* v1 =  Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_element);
          int32_t v1_length = v1->get_length();
          for (int32_t k = 0; k < v1_length; k++) {
            if (v1->exists_na_position(k)) {
              v_out->add_na_position(pos);
            }
            else {
              v_out->set_value(pos, v1->get_value(k));
            }
            pos++;
          }
        }
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (Rstats::pl_hv_exists(sv_type_h, "double")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(total_length);
        int32_t pos = 0;
        for (int32_t i = 0; i < length; i++) {
          SV* sv_element = Rstats::pl_av_fetch(sv_new_elements, i);
          char* type = Rstats::Func::get_type(sv_r, sv_element);
          if (!strEQ(type, "double")) {
            sv_element = Rstats::Func::as_double(sv_r, sv_element);
          }
          Rstats::Vector<double>* v1 =  Rstats::Func::get_vector<double>(sv_r, sv_element);
          int32_t v1_length = v1->get_length();
          for (int32_t k = 0; k < v1_length; k++) {
            if (v1->exists_na_position(k)) {
              v_out->add_na_position(pos);
            }
            else {
              v_out->set_value(pos, v1->get_value(k));
            }
            pos++;
          }
        }
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (Rstats::pl_hv_exists(sv_type_h, "integer")) {
        Rstats::Vector<int32_t>* v_out = new Rstats::Vector<int32_t>(total_length);
        int32_t pos = 0;
        for (int32_t i = 0; i < length; i++) {
          SV* sv_element = Rstats::pl_av_fetch(sv_new_elements, i);
          char* type = Rstats::Func::get_type(sv_r, sv_element);
          if (!strEQ(type, "integer")) {
            sv_element = Rstats::Func::as_double(sv_r, sv_element);
          }
          Rstats::Vector<int32_t>* v1 =  Rstats::Func::get_vector<int32_t>(sv_r, sv_element);
          int32_t v1_length = v1->get_length();
          for (int32_t k = 0; k < v1_length; k++) {
            if (v1->exists_na_position(k)) {
              v_out->add_na_position(pos);
            }
            else {
              v_out->set_value(pos, v1->get_value(k));
            }
            pos++;
          }
        }
        sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
      }
      else {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(total_length);
        int32_t pos = 0;
        for (int32_t i = 0; i < length; i++) {
          SV* sv_element = Rstats::pl_av_fetch(sv_new_elements, i);
          char* type = Rstats::Func::get_type(sv_r, sv_element);
          sv_element = Rstats::Func::as_double(sv_r, sv_element);
          Rstats::Vector<double>* v1 =  Rstats::Func::get_vector<double>(sv_r, sv_element);
          int32_t v1_length = v1->get_length();
          for (int32_t k = 0; k < v1_length; k++) {
            if (v1->exists_na_position(k)) {
              v_out->add_na_position(pos);
            }
            else {
              v_out->set_value(pos, v1->get_value(k));
            }
            pos++;
          }
        }
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }

      return sv_x_out;
    }

    int32_t get_length (SV* sv_r, SV* sv_x1) {

      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
        return v1->get_length();
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        return v1->get_length();
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        return v1->get_length();
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        return v1->get_length();
      }
      else if (strEQ(type, "list")) {
        SV* sv_list = Rstats::pl_hv_fetch(sv_x1, "list");
        int32_t length = Rstats::pl_av_len(sv_list);
        return length;
      }
      else if (strEQ(type, "NULL")) {
        return 0;
      }
      else {
        croak("Error in get_length() : default method not implemented for type '%s'", type);
      }
    }

    SV* get_length_sv (SV* sv_r, SV* sv_x1) {
      return Rstats::pl_new_sv_iv(Rstats::Func::get_length(sv_r, sv_x1));
    }
    
    SV* as_string(SV* sv_r, SV* sv_x1) {

      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);

      SV* sv_x_out;
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
        Rstats::Vector<Rstats::Character>* v_out = Rstats::VectorFunc::as_string<Rstats::Character, Rstats::Character>(v1);
        sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<Rstats::Character>* v_out = Rstats::VectorFunc::as_string<std::complex<double>, Rstats::Character>(v1);
        sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<Rstats::Character>* v_out = new Rstats::Vector<Rstats::Character>(v1->get_length());
        for (int32_t i = 0; i < v1->get_length(); i++) {
          double value = v1->get_value(i);
          SV* sv_str = Rstats::pl_new_sv_pv("");
          if (std::isinf(value) && value > 0) {
            sv_catpv(sv_str, "Inf");
          }
          else if (std::isinf(value) && value < 0) {
            sv_catpv(sv_str, "-Inf");
          }
          else if (std::isnan(value)) {
            sv_catpv(sv_str, "NaN");
          }
          else {
            sv_catpv(sv_str, SvPV_nolen(Rstats::pl_new_sv_nv(value)));
          }
          v_out->set_value(i, sv_str);
        }
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        // Factor
        if (to_bool(sv_r, Rstats::Func::is_factor(sv_r, sv_x1))) {
          SV* sv_levels = Rstats::pl_new_hvrv();
          SV* sv_x_levels = Rstats::Func::levels(sv_r, sv_x1);
          SV* sv_x_levels_values = Rstats::Func::values(sv_r, sv_x_levels);
          int32_t levels_length = Rstats::Func::get_length(sv_r, sv_x_levels);
          for (int32_t i = 1; i <= levels_length; i++) {
            Rstats::pl_hv_store(
              sv_levels,
              SvPV_nolen(Rstats::pl_new_sv_iv(i)),
              Rstats::pl_av_fetch(sv_x_levels_values, i - 1)
            );
          }
          
          SV* sv_x1_values = Rstats::Func::values(sv_r, sv_x1);
          SV* sv_x_out_values = Rstats::pl_new_avrv();
          int32_t x1_values_length = Rstats::pl_av_len(sv_x1_values);
          
          Rstats::Vector<Rstats::Character>* v_out = new Rstats::Vector<Rstats::Character>(x1_values_length);
          for (int32_t i = 0; i < x1_values_length; i++) {
            SV* sv_x1_value = Rstats::pl_av_fetch(sv_x1_values, i);
             
            if (SvOK(sv_x1_value)) {
              SV* sv_string = Rstats::pl_hv_fetch(sv_levels, SvPV_nolen(sv_x1_value));
              v_out->set_value(i, Rstats::pl_new_sv_sv(sv_string));
            }
            else {
              v_out->add_na_position(i);
            }
          }
          sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
          
          Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
          Rstats::pl_hv_delete(sv_x_out, "levels");
          Rstats::pl_hv_delete(sv_x_out, "class");
          
          // Todo na positions
          
          return sv_x_out;
        }
        else {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<Rstats::Character>* v_out = Rstats::VectorFunc::as_string<int32_t, Rstats::Character>(v1);
          sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
        }
      }
      else if (strEQ(type, "NULL")) {
        Rstats::Vector<Rstats::Character>* v_out = new Rstats::Vector<Rstats::Character>(0);
        sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
      }
      else {
        croak("Error in as->string() : default method not implemented for type '%s'", type);
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* as_numeric(SV* sv_r, SV* sv_x1) {
      return Rstats::Func::as_double(sv_r, sv_x1);
    }
    
    SV* as_double(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);

      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::as_double<std::complex<double>, double>(v1);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::as_double<double, double>(v1);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::as_double<int32_t, double>(v1);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in as->double() : default method not implemented for type '%s'", type);
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
        
    SV* as_complex(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::as_complex<std::complex<double>, std::complex<double>>(v1);
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::as_complex<double, std::complex<double>>(v1);
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::as_complex<int32_t, std::complex<double>>(v1);
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "NULL")) {
        Rstats::Vector<std::complex<double>>* v_out = new Rstats::Vector<std::complex<double>>(0);
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else {
        croak("Error in as->complex() : default method not implemented for type '%s'", type);
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
        
    SV* create_sv_values(SV* sv_r, SV* sv_x1) {

      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);

      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      SV* sv_values = Rstats::pl_new_avrv();
      if (!strEQ(type, "NULL")) {
        int32_t length = Rstats::Func::get_length(sv_r, sv_x1);
        for (int32_t i = 0; i < length; i++) {
          Rstats::pl_av_push(sv_values, Rstats::Func::create_sv_value(sv_r, sv_x1, i));
        }
      }
      
      return sv_values;
    }
    
    SV* create_sv_value(SV* sv_r, SV* sv_x1, int32_t pos) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);

      SV* sv_value;
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
        if (v1->exists_na_position(pos)) {
          sv_value = &PL_sv_undef;
        }
        else {
          sv_value = v1->get_value(pos);
        }
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        if (v1->exists_na_position(pos)) {
          sv_value = &PL_sv_undef;
        }
        else {
          std::complex<double> z = v1->get_value(pos);
          
          double re = z.real();
          SV* sv_re;
          if (std::isnan(re)) {
            sv_re = Rstats::pl_new_sv_pv("NaN");
          }
          else if (std::isinf(re) && re > 0) {
            sv_re = Rstats::pl_new_sv_pv("Inf");
          }
          else if (std::isinf(re) && re < 0) {
            sv_re = Rstats::pl_new_sv_pv("-Inf");
          }
          else {
            sv_re = Rstats::pl_new_sv_nv(re);
          }
          
          double im = z.imag();
          SV* sv_im;
          if (std::isnan(im)) {
            sv_im = Rstats::pl_new_sv_pv("NaN");
          }
          else if (std::isinf(im) && im > 0) {
            sv_im = Rstats::pl_new_sv_pv("Inf");
          }
          else if (std::isinf(im) && im < 0) {
            sv_im = Rstats::pl_new_sv_pv("-Inf");
          }
          else {
            sv_im = Rstats::pl_new_sv_nv(im);
          }

          sv_value = Rstats::pl_new_hvrv();
          Rstats::pl_hv_store(sv_value, "re", sv_re);
          Rstats::pl_hv_store(sv_value, "im", sv_im);
        }
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        if (v1->exists_na_position(pos)) {
          sv_value = &PL_sv_undef;
        }
        else {
          double value = v1->get_value(pos);
          if (std::isnan(value)) {
            sv_value = Rstats::pl_new_sv_pv("NaN");
          }
          else if (std::isinf(value) && value > 0) {
            sv_value = Rstats::pl_new_sv_pv("Inf");
          }
          else if (std::isinf(value) && value < 0) {
            sv_value = Rstats::pl_new_sv_pv("-Inf");
          }
          else {
            sv_value = Rstats::pl_new_sv_nv(value);
          }
        }
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        if (v1->exists_na_position(pos)) {
          sv_value = &PL_sv_undef;
        }
        else {
          int32_t value = v1->get_value(pos);
          sv_value = Rstats::pl_new_sv_iv(value);
        }
      }
      else {
        croak("Error in create_sv_value : default method not implemented for type '%s'", type);
      }
      
      return sv_value;
    }
        
    SV* cumprod(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<std::complex<double>>* v_out = new Rstats::Vector<std::complex<double>>(v1->get_length());
        std::complex<double> v_out_total(1);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total *= v1->get_value(i);
          v_out->set_value(i, v_out_total);
        }
        
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(v1->get_length());
        double v_out_total(1);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total *= v1->get_value(i);
          v_out->set_value(i, v_out_total);
        }
          
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(v1->get_length());
        double v_out_total(1);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total *= v1->get_value(i);
          v_out->set_value(i, v_out_total);
        }
        
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in cumprod() : non-numeric argument to cumprod()");
      }
      
      return sv_x_out;
    }
    
    SV* cumsum(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);

      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<std::complex<double>>* v_out = new Rstats::Vector<std::complex<double>>(v1->get_length());
        std::complex<double> v_out_total(0);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total += v1->get_value(i);
          v_out->set_value(i, v_out_total);
        }
        
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(v1->get_length());
        double v_out_total(0);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total += v1->get_value(i);
          v_out->set_value(i, v_out_total);
        }
          
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(v1->get_length());
        double v_out_total(0);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total += v1->get_value(i);
          v_out->set_value(i, v_out_total);
        }
        
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in cumsum() : non-numeric argument to cumsum()");
      }
      
      return sv_x_out;
    }
        
    SV* sum(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);

      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<std::complex<double>>* v_out = new Rstats::Vector<std::complex<double>>(1);
        std::complex<double> v_out_total(0);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total += v1->get_value(i);
        }
        v_out->set_value(0, v_out_total);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          if (v1->exists_na_position(i)) {
            v_out->add_na_position(0);
            break;
          }
        }
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(1);
        double v_out_total(0);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total += v1->get_value(i);
        }
        v_out->set_value(0, v_out_total);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          if (v1->exists_na_position(i)) {
            v_out->add_na_position(0);
            break;
          }
        }
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        Rstats::Vector<int32_t>* v_out = new Rstats::Vector<int32_t>(1);
        int32_t v_out_total(0);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total += v1->get_value(i);
        }
        v_out->set_value(0, v_out_total);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          if (v1->exists_na_position(i)) {
            v_out->add_na_position(0);
            break;
          }
        }
        sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
      }
      else if (strEQ(type, "NULL")) {
        Rstats::Vector<int32_t>* v_out = new Rstats::Vector<int32_t>(1, 0);
        sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
      }
      else {
        croak("Error in sum() : non-numeric argument to sum()");
      }
      
      
      return sv_x_out;
    }

    SV* prod(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);

      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<std::complex<double>>* v_out = new Rstats::Vector<std::complex<double>>(1);
        std::complex<double> v_out_total(1);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total *= v1->get_value(i);
        }
        v_out->set_value(0, v_out_total);
        
        for (int32_t i = 0; i < v1->get_length(); i++) {
          if (v1->exists_na_position(i)) {
            v_out->add_na_position(0);
            break;
          }
        }
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(1);
        double v_out_total(1);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total *= v1->get_value(i);
        }
        v_out->set_value(0, v_out_total);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          if (v1->exists_na_position(i)) {
            v_out->add_na_position(0);
            break;
          }
        }
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(1);
        double v_out_total(1);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out_total *= v1->get_value(i);
        }
        v_out->set_value(0, v_out_total);
        for (int32_t i = 0; i < v1->get_length(); i++) {
          if (v1->exists_na_position(i)) {
            v_out->add_na_position(0);
            break;
          }
        }
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(1, 1);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in prod() : non-numeric argument to prod()");
      }
      
      return sv_x_out;
    }
        
    SV* equal(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "string")) {
          Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
          Rstats::Vector<Rstats::Character>* v2 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::equal<Rstats::Character>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          Rstats::Vector<std::complex<double>>* v2 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::equal<std::complex<double>>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::equal<double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::equal<int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in == : default method not implemented for type '%s'", type);
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* not_equal(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "string")) {
          Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
          Rstats::Vector<Rstats::Character>* v2 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::not_equal<Rstats::Character>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          Rstats::Vector<std::complex<double>>* v2 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::not_equal<std::complex<double>>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::not_equal<double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::not_equal<int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in != : default method not implemented for type '%s'", type);
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* more_than(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "string")) {
          Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
          Rstats::Vector<Rstats::Character>* v2 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::more_than<Rstats::Character>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "complex")) {
          croak("Error in > operator : invalid comparison with complex values");
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::more_than<double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::more_than<int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in > : default method not implemented for type '%s'", type);
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* more_than_or_equal(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "string")) {
          Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
          Rstats::Vector<Rstats::Character>* v2 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::more_than_or_equal<Rstats::Character>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "complex")) {
          croak("Error in <= operator : invalid comparison with complex values");
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::more_than_or_equal<double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::more_than_or_equal<int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in >= : default method not implemented for type '%s'", type);
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }
    
    SV* less_than(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "string")) {
          Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
          Rstats::Vector<Rstats::Character>* v2 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::less_than<Rstats::Character>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "complex")) {
          croak("Error in < operator : invalid comparison with complex values");
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::less_than<double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::less_than<int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in < : default method not implemented for type '%s'", type);
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* less_than_or_equal(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "string")) {
          Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
          Rstats::Vector<Rstats::Character>* v2 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::less_than_or_equal<Rstats::Character>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "complex")) {
          croak("Error in <= operator : invalid comparison with complex values");
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::less_than_or_equal<double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::less_than_or_equal<int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in <= : default method not implemented for type '%s'", type);
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* And(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "string")) {
          croak("Error in & : operations are possible only for numeric or complex types");
        }
        else if (strEQ(type1, "complex")) {
          croak("Error in & : invalid comparison with complex values");
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::And<double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::And<int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in & : default method not implemented for type '%s'", type);
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* Or(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "string")) {
          croak("Error in | : operations are possible only for numeric or complex types");
        }
        else if (strEQ(type1, "complex")) {
          croak("Error in | : invalid comparison with complex values");
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::Or<double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::Or<int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in | : default method not implemented for type '%s'", type);
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* add(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          Rstats::Vector<std::complex<double>>* v2 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x2);
          Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::add<std::complex<double>, std::complex<double>>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::add<double, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<int32_t>* v_out = Rstats::VectorFunc::add<int32_t, int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
        }
        else {
          croak("Error in + : non-numeric argument to binary operator");
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* subtract(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          Rstats::Vector<std::complex<double>>* v2 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x2);
          Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::subtract<std::complex<double>, std::complex<double>>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::subtract<double, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<int32_t>* v_out = Rstats::VectorFunc::subtract<int32_t, int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
        }
        else {
          croak("Error in - : non-numeric argument to binary operator");
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* remainder(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "complex")) {
          croak("Error in % : unimplemented complex operation");
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::remainder<double, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::remainder<int32_t, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in % : non-numeric argument to binary operator");
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }
    
    SV* divide(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          Rstats::Vector<std::complex<double>>* v2 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x2);
          Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::divide<std::complex<double>, std::complex<double>>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::divide<double, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::divide<int32_t, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in / : non-numeric argument to binary operator");
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* atan2(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        croak("Error in atan2() : non-numeric argument to mathematical function");
      }
      else {
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          Rstats::Vector<std::complex<double>>* v2 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x2);
          Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::atan2<std::complex<double>, std::complex<double>>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::atan2<double, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::atan2<int32_t, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in atan2() : non-numeric argument to mathematical function");
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }

    SV* pow(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          Rstats::Vector<std::complex<double>>* v2 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x2);
          Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::pow<std::complex<double>, std::complex<double>>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::pow<double, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::pow<int32_t, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else {
          croak("Error in ** : non-numeric argument to binary operator");
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }
                                        
    SV* multiply(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      SV* sv_x_out;
      
      // NULL check
      char* original_type1 = Rstats::Func::get_type(sv_r, sv_x1);
      char* original_type2 = Rstats::Func::get_type(sv_r, sv_x2);
      if (strEQ(original_type1, "NULL") || strEQ(original_type2, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
      
        // Upgrade type and length
        upgrade_type(sv_r, 2, &sv_x1, &sv_x2);
        upgrade_length(sv_r, 2, &sv_x1, &sv_x2);
        
        char* type1 = Rstats::Func::get_type(sv_r, sv_x1);
        if (strEQ(type1, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          Rstats::Vector<std::complex<double>>* v2 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x2);
          Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::multiply<std::complex<double>, std::complex<double>>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
        }
        else if (strEQ(type1, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          Rstats::Vector<double>* v2 = Rstats::Func::get_vector<double>(sv_r, sv_x2);
          Rstats::Vector<double>* v_out = Rstats::VectorFunc::multiply<double, double>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        }
        else if (strEQ(type1, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          Rstats::Vector<int32_t>* v2 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x2);
          Rstats::Vector<int32_t>* v_out = Rstats::VectorFunc::multiply<int32_t, int32_t>(v1, v2);
          sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
        }
        else {
          croak("Error in * : non-numeric argument to binary operator");
        }
        Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      }
      
      return sv_x_out;
    }
                            
    SV* sin(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::sin<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::sin<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::sin<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in sin() : non-numeric argument to sin()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* tanh(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::tanh<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::tanh<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::tanh<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in tanh() : non-numeric argument to tanh()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* cos(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::cos<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::cos<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::cos<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in cos() : non-numeric argument to cos()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* tan(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::tan<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::tan<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::tan<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in tan() : non-numeric argument to tan()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* sinh(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::sinh<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::sinh<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::sinh<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in sinh() : non-numeric argument to sinh()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* cosh(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::cosh<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::cosh<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::cosh<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in cosh() : non-numeric argument to cosh()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* log(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::log<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::log<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::log<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in log() : non-numeric argument to log()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* logb(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::logb<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::logb<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::logb<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in logb() : non-numeric argument to logb()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* log10(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::log10<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::log10<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::log10<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in log10() : non-numeric argument to log10()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* log2(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::log2<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::log2<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::log2<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in log2() : non-numeric argument to log2()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* acos(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::acos<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::acos<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::acos<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in acos() : non-numeric argument to acos()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* acosh(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::acosh<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::acosh<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::acosh<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in acosh() : non-numeric argument to acosh()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* asinh(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::asinh<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::asinh<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::asinh<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in asinh() : non-numeric argument to asinh()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* atanh(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::atanh<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::atanh<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::atanh<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in atanh() : non-numeric argument to atanh()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* Conj(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::Conj<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Conj<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Conj<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in Conj() : non-numeric argument to Conj()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* asin(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::asin<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::asin<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::asin<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in asin() : non-numeric argument to asin()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* atan(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::atan<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::atan<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::atan<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in atan() : non-numeric argument to atan()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* sqrt(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::sqrt<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::sqrt<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::sqrt<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in sqrt() : non-numeric argument to sqrt()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* expm1(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        croak("Error in expm1 : unimplemented complex function");
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::expm1<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::expm1<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in expm1() : non-numeric argument to expm1()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* exp(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::exp<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::exp<double, double>(v1);

        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

        Rstats::Vector<double>* v_out = Rstats::VectorFunc::exp<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in exp() : non-numeric argument to exp()");
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* negate(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<std::complex<double>>* v_out = Rstats::VectorFunc::negate<std::complex<double>, std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::negate<double, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<int32_t>* v_out = Rstats::VectorFunc::negate<int32_t, int32_t>(v1);
        
        sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
      }
      else {
        croak("Error in -$x : non-numeric argument to - operator");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* Arg(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Arg<std::complex<double>, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Arg<double, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Arg<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in Arg() : non-numeric argument to Arg()");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* abs(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::abs<std::complex<double>, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::abs<double, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::abs<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in abs() : non-numeric argument to abs()");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* Mod(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Mod<std::complex<double>, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Mod<double, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Mod<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in Mod() : non-numeric argument to Mod()");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* Re(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Re<std::complex<double>, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Re<double, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Re<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in Re() : non-numeric argument to Re()");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* Im(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Im<std::complex<double>, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Im<double, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::Im<int32_t, double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in Im() : non-numeric argument to Im()");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
            
    SV* is_infinite(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_infinite<Rstats::Character>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_infinite<std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_infinite<double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_infinite<int32_t>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in is_infinite() : non-numeric argument to is_infinite()");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* is_nan(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_nan<Rstats::Character>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_nan<std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_nan<double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_nan<int32_t>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in is_nan() : non-numeric argument to is_nan()");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* is_finite(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_finite<Rstats::Character>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_finite<std::complex<double>>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_finite<double>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_finite<int32_t>(v1);
        
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else {
        croak("Error in is_finite() : non-numeric argument to is_finite()");
      }

      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }
    
    SV* upgrade_length_avrv(SV* sv_r, SV* sv_xs) {
      
      int32_t xs_length = Rstats::pl_av_len(sv_xs);
      int32_t max_length = 0;
      for (int32_t i = 0; i < xs_length; i++) {
        SV* sv_x1 = Rstats::pl_av_fetch(sv_xs, i);
        int32_t x1_length = Rstats::Func::get_length(sv_r, sv_x1);
        
        if (x1_length > max_length) {
          max_length = x1_length;
        }
      }
      
      SV* sv_new_xs = Rstats::pl_new_avrv();;
      for (int32_t i = 0; i < xs_length; i++) {
        SV* sv_x1 = Rstats::pl_av_fetch(sv_xs, i);
        int32_t x1_length = Rstats::Func::get_length(sv_r, sv_x1);
        
        if (x1_length != max_length) {
          Rstats::Vector<double>* v_length = new Rstats::Vector<double>(1, max_length);
          SV* sv_x_length = Rstats::Func::new_vector<double>(sv_r, v_length);
          Rstats::pl_av_push(
            sv_new_xs,
            Rstats::Func::array(sv_r, sv_x1, sv_x_length)
          );
        }
        else {
          Rstats::pl_av_push(sv_new_xs, sv_x1);
        }
      }
      
      return sv_new_xs;
    }
    
    void upgrade_length(SV* sv_r, int32_t num, ...) {
      va_list args;
      
      // Optimization if args count is 2
      va_start(args, num);
      if (num == 2) {
        SV* sv_x1 = *va_arg(args, SV**);
        SV* sv_x2 = *va_arg(args, SV**);

        int32_t x1_length = Rstats::Func::get_length(sv_r, sv_x1);
        int32_t x2_length = Rstats::Func::get_length(sv_r, sv_x2);
        
        if (x1_length == x2_length) {
          return;
        }
      }
      va_end(args);
      
      SV* sv_args = Rstats::pl_new_avrv();
      va_start(args, num);
      for (int32_t i = 0; i < num; i++) {
        SV** arg = va_arg(args, SV**);
        SV* x = *arg;
        Rstats::pl_av_push(sv_args, x);
      }
      va_end(args);
      
      SV* sv_result = Rstats::Func::upgrade_length_avrv(sv_r, sv_args);
      
      va_start(args, num);
      for (int32_t i = 0; i < num; i++) {
        SV** arg = va_arg(args, SV**);
        SV* sv_x = Rstats::pl_av_fetch(sv_result, i);

        *arg = sv_x;
      }
      va_end(args);
    }
        
    void upgrade_type(SV* sv_r, int32_t num, ...) {
      va_list args;
      
      // Optimization if args count is 2
      va_start(args, num);
      if (num == 2) {
        SV* x1 = *va_arg(args, SV**);
        SV* x2 = *va_arg(args, SV**);
        
        if (
            strEQ(
              SvPV_nolen(Rstats::pl_hv_fetch(x1, "type")),
              SvPV_nolen(Rstats::pl_hv_fetch(x2, "type"))
            )
          )
        {
          return;
        }
      }
      va_end(args);
      
      SV* upgrade_type_args = Rstats::pl_new_avrv();
      va_start(args, num);
      for (int32_t i = 0; i < num; i++) {
        SV** arg = va_arg(args, SV**);
        SV* x = *arg;
        Rstats::pl_av_push(upgrade_type_args, x);
      }
      va_end(args);
      
      SV* upgrade_type_result = Rstats::Func::upgrade_type_avrv(sv_r, upgrade_type_args);
      
      va_start(args, num);
      for (int32_t i = 0; i < num; i++) {
        SV** arg = va_arg(args, SV**);
        SV* x = Rstats::pl_av_fetch(upgrade_type_result, i);
        *arg = x;
      }
      va_end(args);
    }
    
    SV* get_type_sv(SV* sv_r, SV* sv_x1) {
      if (sv_isobject(sv_x1) && sv_derived_from(sv_x1, "Rstats::Object")) {
        return Rstats::pl_hv_fetch(sv_x1, "type");
      }
      else {
        return Rstats::pl_new_sv_pv("");
      }
    }

    char* get_type(SV* sv_r, SV* sv_x1) {
      if (sv_isobject(sv_x1) && sv_derived_from(sv_x1, "Rstats::Object")) {
        return SvPV_nolen(Rstats::pl_hv_fetch(sv_x1, "type"));
      }
      else {
        return "";
      }
    }
    
    char* get_object_type(SV* sv_r, SV* sv_x1) {
      if (sv_isobject(sv_x1) && sv_derived_from(sv_x1, "Rstats::Object")) {
        return SvPV_nolen(Rstats::pl_hv_fetch(sv_x1, "object_type"));
      }
      else {
        return "";
      }
    }
    
    SV* as_vector(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      SV* sv_x_out;
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
        Rstats::Vector<Rstats::Character>* v_out = new Rstats::Vector<Rstats::Character>(v1->get_length());
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out->set_value(i, v1->get_value(i));
        }
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<std::complex<double>>* v_out = new Rstats::Vector<std::complex<double>>(v1->get_length());
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out->set_value(i, v1->get_value(i));
        }
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(v1->get_length());
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out->set_value(i, v1->get_value(i));
        }
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        Rstats::Vector<int32_t>* v_out = new Rstats::Vector<int32_t>(v1->get_length());
        for (int32_t i = 0; i < v1->get_length(); i++) {
          v_out->set_value(i, v1->get_value(i));
        }
        v_out->merge_na_positions(v1->get_na_positions());
        sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
      }
      
      return sv_x_out;
    }

    SV* array(SV* sv_r, SV* sv_x1) {
      SV* sv_args_h = Rstats::pl_new_hvrv();
      Rstats::pl_hv_store(sv_args_h, "x", sv_x1);
      return Rstats::Func::array_with_opt(sv_r, sv_args_h);
    }
    
    SV* array(SV* sv_r, SV* sv_x1, SV* sv_dim) {
      
      SV* sv_args_h = Rstats::pl_new_hvrv();
      Rstats::pl_hv_store(sv_args_h, "x", sv_x1);
      Rstats::pl_hv_store(sv_args_h, "dim", sv_dim);
      return Rstats::Func::array_with_opt(sv_r, sv_args_h);
    }
    
    SV* array_with_opt(SV* sv_r, SV* sv_args_h) {

      SV* sv_x1 = Rstats::pl_hv_fetch(sv_args_h, "x");
     
      // Dimention
      SV* sv_x_dim = Rstats::pl_hv_exists(sv_args_h, "dim")
        ? Rstats::pl_hv_fetch(sv_args_h, "dim") : Rstats::Func::new_NULL(sv_r);
      int32_t x1_length = Rstats::Func::get_length(sv_r, sv_x1);
      
      if (!Rstats::Func::get_length(sv_r, sv_x_dim)) {
        Rstats::Vector<int32_t>* v_dim = new Rstats::Vector<int32_t>(1, x1_length);
        sv_x_dim = Rstats::Func::new_vector<int32_t>(sv_r, v_dim);
      }
      int32_t dim_product = 1;
      int32_t x_dim_length = Rstats::Func::get_length(sv_r, sv_x_dim);
      for (int32_t i = 0; i < x_dim_length; i++) {
        SV* sv_values = Rstats::Func::values(sv_r, sv_x_dim);
        dim_product *= SvIV(Rstats::pl_av_fetch(sv_values, i));
      }

      
      // Fix elements length
      SV* sv_elements;
      if (x1_length == dim_product) {
        sv_elements = Rstats::Func::decompose(sv_r, sv_x1);
      }
      else if (x1_length > dim_product) {
        SV* sv_elements_tmp = Rstats::Func::decompose(sv_r, sv_x1);
        sv_elements = Rstats::pl_new_avrv();
        for (int32_t i = 0; i < dim_product; i++) {
          Rstats::pl_av_push(sv_elements, Rstats::pl_av_fetch(sv_elements_tmp, i));
        }
      }
      else if (x1_length < dim_product) {
        SV* sv_elements_tmp = Rstats::Func::decompose(sv_r, sv_x1);
        int32_t elements_tmp_length = Rstats::pl_av_len(sv_elements_tmp);
        int32_t repeat_count = (int32_t)(dim_product / elements_tmp_length) + 1;
        SV* sv_elements_tmp2 = Rstats::pl_new_avrv();
        int32_t elements_tmp2_length = Rstats::pl_av_len(sv_elements_tmp2);
        for (int32_t i = 0; i < repeat_count; i++) {
          for (int32_t k = 0; k < elements_tmp_length; k++) {
            Rstats::pl_av_push(sv_elements_tmp2, Rstats::pl_av_fetch(sv_elements_tmp, k));
          }
        }
        sv_elements = Rstats::pl_new_avrv();
        for (int32_t i = 0; i < dim_product; i++) {
          Rstats::pl_av_push(sv_elements, Rstats::pl_av_fetch(sv_elements_tmp2, i));
        }
      }
      
      SV* sv_x2 = Rstats::Func::c(sv_r, sv_elements);
      Rstats::Func::dim(sv_r, sv_x2, sv_x_dim);
      
      return sv_x2;
    }

    SV* upgrade_type_avrv(SV* sv_r, SV* sv_xs) {
      
      // Check elements
      SV* sv_type_h = Rstats::pl_new_hvrv();
      
      int32_t xs_length = Rstats::pl_av_len(sv_xs);
      for (int32_t i = 0; i < xs_length; i++) {
        SV* sv_x1 = Rstats::pl_av_fetch(sv_xs, i);
        char* type = Rstats::Func::get_type(sv_r, sv_x1);
        
        Rstats::pl_hv_store(sv_type_h, type, Rstats::pl_new_sv_iv(1));
      }

      // Upgrade elements and type if type is different
      SV* sv_new_xs = Rstats::pl_new_avrv();;
      int32_t type_length = Rstats::pl_hv_key_count(sv_type_h);

      if (type_length > 1) {
        SV* sv_to_type;
        if (Rstats::pl_hv_exists(sv_type_h, "string")) {
          sv_to_type = Rstats::pl_new_sv_pv("string");
        }
        else if (Rstats::pl_hv_exists(sv_type_h, "complex")) {
          sv_to_type = Rstats::pl_new_sv_pv("complex");
        }
        else if (Rstats::pl_hv_exists(sv_type_h, "double")) {
          sv_to_type = Rstats::pl_new_sv_pv("double");
        }
        else if (Rstats::pl_hv_exists(sv_type_h, "integer")) {
          sv_to_type = Rstats::pl_new_sv_pv("integer");
        }
        
        for (int32_t i = 0; i < xs_length; i++) {
          SV* sv_x = Rstats::pl_av_fetch(sv_xs, i);
          Rstats::pl_av_push(sv_new_xs, Rstats::Func::as(sv_r, sv_to_type, sv_x));
        }
      }
      else {
        sv_new_xs = sv_xs;
      }
      
      return sv_new_xs;
    }
    
    SV* dim(SV* sv_r, SV* sv_x1, SV* sv_x_dim) {
      sv_x_dim = Rstats::Func::to_object(sv_r, sv_x_dim);
      
      int32_t x1_length = Rstats::Func::get_length(sv_r, sv_x1);
      int32_t x1_length_by_dim = 1;
      
      SV* sv_x_dim_values = values(sv_r, sv_x_dim);
      int32_t x_dim_values_length = Rstats::pl_av_len(sv_x_dim_values);
      
      for (int32_t i = 0; i < x_dim_values_length; i++) {
        SV* sv_x_dim_value = Rstats::pl_av_fetch(sv_x_dim_values, i);
        int32_t x_dim_value = SvIV(sv_x_dim_value);
        x1_length_by_dim *= x_dim_value;
      }
      
      if (x1_length != x1_length_by_dim) {
        croak("dims [product %d] do not match the length of object [%d]", x1_length_by_dim, x1_length);
      }
      
      Rstats::pl_hv_store(sv_x1, "dim", Rstats::Func::as_vector(sv_r, sv_x_dim));
      
      return sv_r;
    }

    SV* dim(SV* sv_r, SV* sv_x1) {
      SV* sv_x_dim;
      
      if (Rstats::pl_hv_exists(sv_x1, "dim")) {
        sv_x_dim = Rstats::Func::as_vector(sv_r, Rstats::pl_hv_fetch(sv_x1, "dim"));
      }
      else {
        sv_x_dim = Rstats::Func::new_NULL(sv_r);
      }
      
      return sv_x_dim;
    }

    SV* values(SV* sv_r, SV* sv_x1) {
      
      SV* sv_values = Rstats::Func::create_sv_values(sv_r, sv_x1);
      
      return sv_values;
    }

    SV* Typeof(SV* sv_r, SV* sv_x1) {
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      Rstats::Vector<Rstats::Character>* v_out = new Rstats::Vector<Rstats::Character>(1, Rstats::pl_new_sv_pv(type));
      SV* sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
      
      return sv_x_out;
    }
    
    SV* type(SV* sv_r, SV* sv_x1) {
      
      return Rstats::pl_new_sv_pv(Rstats::Func::get_type(sv_r, sv_x1));
    }

    SV* is_null (SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_type(sv_r, sv_x1), "NULL");
      
      SV* sv_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_is;
    }
    
    SV* is_vector (SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_object_type(sv_r, sv_x1), "array")
        && !Rstats::pl_hv_exists(sv_x1, "dim");
      
      SV* sv_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
            
      return sv_is;
    }

    SV* is_array(SV* sv_r, SV* sv_x1) {

      bool is = strEQ(Rstats::Func::get_object_type(sv_r, sv_x1), "array")
        && Rstats::pl_hv_exists(sv_x1, "dim");
      
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* is_matrix(SV* sv_r, SV* sv_x1) {

      double is = strEQ(Rstats::Func::get_object_type(sv_r, sv_x1), "array")
        && Rstats::Func::get_length(sv_r, dim(sv_r, sv_x1)) == 2;
      
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* pi (SV* sv_r) {
      double pi = Rstats::Util::pi();
      
      Rstats::Vector<double>* v_out = new Rstats::Vector<double>(1, pi);
      SV* sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      
      return sv_x_out;
    }

    SV* c_string(SV* sv_r, SV* sv_values) {
      if (!sv_derived_from(sv_values, "ARRAY")) {
        SV* sv_values_av_ref = Rstats::pl_new_avrv();
        Rstats::pl_av_push(sv_values_av_ref, sv_values);
        sv_values = sv_values_av_ref;
      }
      
      int32_t length = Rstats::pl_av_len(sv_values);
      
      Rstats::Vector<Rstats::Character>* v1 = new Rstats::Vector<Rstats::Character>(length);
      for (int32_t i = 0; i < length; i++) {
        SV* sv_value = Rstats::pl_av_fetch(sv_values, i);

        if (SvOK(sv_value)) {
          v1->set_value(i, Rstats::pl_new_sv_sv(sv_value));
        }
        else {
          v1->add_na_position(i);
        }
      }
      
      SV* sv_x1 = Rstats::Func::new_vector<Rstats::Character>(sv_r, v1);
      
      return sv_x1;
    }

    template <>
    SV* new_vector<Rstats::Character>(SV* sv_r) {
      SV* sv_x1 = Rstats::pl_new_hvrv();
      
      sv_bless(sv_x1, gv_stashpv("Rstats::Object", 1));
      Rstats::pl_hv_store(sv_x1, "r", sv_r);
      Rstats::pl_hv_store(sv_x1, "object_type", Rstats::pl_new_sv_pv("array"));
      Rstats::pl_hv_store(sv_x1, "type", Rstats::pl_new_sv_pv("string"));
      
      return sv_x1;
    }

    template <>
    SV* new_vector<std::complex<double>>(SV* sv_r) {
      SV* sv_x1 = Rstats::pl_new_hvrv();
      
      sv_bless(sv_x1, gv_stashpv("Rstats::Object", 1));
      Rstats::pl_hv_store(sv_x1, "r", sv_r);
      Rstats::pl_hv_store(sv_x1, "object_type", Rstats::pl_new_sv_pv("array"));
      Rstats::pl_hv_store(sv_x1, "type", Rstats::pl_new_sv_pv("complex"));
      
      return sv_x1;
    }
    
    template <>
    SV* new_vector<double>(SV* sv_r) {
      SV* sv_x1 = Rstats::pl_new_hvrv();
      
      sv_bless(sv_x1, gv_stashpv("Rstats::Object", 1));
      Rstats::pl_hv_store(sv_x1, "r", sv_r);
      Rstats::pl_hv_store(sv_x1, "object_type", Rstats::pl_new_sv_pv("array"));
      Rstats::pl_hv_store(sv_x1, "type", Rstats::pl_new_sv_pv("double"));
      
      return sv_x1;
    }

    template <>
    SV* new_vector<int32_t>(SV* sv_r) {
      SV* sv_x1 = Rstats::pl_new_hvrv();
      
      sv_bless(sv_x1, gv_stashpv("Rstats::Object", 1));
      Rstats::pl_hv_store(sv_x1, "r", sv_r);
      Rstats::pl_hv_store(sv_x1, "object_type", Rstats::pl_new_sv_pv("array"));
      Rstats::pl_hv_store(sv_x1, "type", Rstats::pl_new_sv_pv("integer"));
      
      return sv_x1;
    }

    SV* c_double(SV* sv_r, SV* sv_values) {
      
      if (!sv_derived_from(sv_values, "ARRAY")) {
        croak("Invalid argment(c_double()");
      }
      
      int32_t length = Rstats::pl_av_len(sv_values);
      
      Rstats::Vector<double>* v1 = new Rstats::Vector<double>(length);
      for (int32_t i = 0; i < length; i++) {
        SV* sv_value = Rstats::pl_av_fetch(sv_values, i);

        if (SvOK(sv_value)) {
          char* sv_value_str = SvPV_nolen(sv_value);
          if (strEQ(sv_value_str, "NaN")) {
            v1->set_value(i, NAN);
          }
          else if (strEQ(sv_value_str, "Inf")) {
            v1->set_value(i, INFINITY);
          }
          else if (strEQ(sv_value_str, "-Inf")) {
            v1->set_value(i, -(INFINITY));
          }
          else {
            double value = SvNV(sv_value);
            v1->set_value(i, value);
          }
        }
        else {
          v1->add_na_position(i);
        }
      }
      
      SV* sv_x1 = Rstats::Func::new_vector<double>(sv_r, v1);
      
      return sv_x1;
    }

    SV* c_complex(SV* sv_r, SV* sv_values) {
      if (!sv_derived_from(sv_values, "ARRAY")) {
        croak("Invalid argment(c_complex()");
      }
      
      int32_t length = Rstats::pl_av_len(sv_values);
      
      Rstats::Vector<std::complex<double>>* v1 = new Rstats::Vector<std::complex<double>>(length);
      for (int32_t i = 0; i < length; i++) {
        SV* sv_value = Rstats::pl_av_fetch(sv_values, i);
        
        if (SvOK(sv_value)) {
          SV* sv_value_re = Rstats::pl_hv_fetch(sv_value, "re");
          SV* sv_value_im = Rstats::pl_hv_fetch(sv_value, "im");

          double re;
          if (SvOK(sv_value_re)) {
            char* sv_value_re_str = SvPV_nolen(sv_value_re);
            if (strEQ(sv_value_re_str, "NaN")) {
              re = NAN;
            }
            else if (strEQ(sv_value_re_str, "Inf")) {
              re = INFINITY;
            }
            else if (strEQ(sv_value_re_str, "-Inf")) {
              re = -(INFINITY);
            }
            else {
              re = SvNV(sv_value_re);
            }
          }
          else {
            re = 0;
          }
          

          double im;
          if (SvOK(sv_value_im)) {
            char* sv_value_im_str = SvPV_nolen(sv_value_im);
            if (strEQ(sv_value_im_str, "NaN")) {
              im = NAN;
            }
            else if (strEQ(sv_value_im_str, "Inf")) {
              im = INFINITY;
            }
            else if (strEQ(sv_value_im_str, "-Inf")) {
              im = -(INFINITY);
            }
            else {
              im = SvNV(sv_value_im);
            }
          }
          else {
            im = 0;
          }
          
          v1->set_value(
            i,
            std::complex<double>(re, im)
          );
        }
        else {
          v1->add_na_position(i);
        }
      }
      
      SV* sv_x1 = Rstats::Func::new_vector<std::complex<double>>(sv_r, v1);
      
      return sv_x1;
    }

    SV* c_integer(SV* sv_r, SV* sv_values) {
      if (!sv_derived_from(sv_values, "ARRAY")) {
        croak("Invalid argment(c_integer()");
      }
      
      int32_t length = Rstats::pl_av_len(sv_values);
      
      Rstats::Vector<int32_t>* v1 = new Rstats::Vector<int32_t>(length);
      for (int32_t i = 0; i < length; i++) {
        SV* sv_value = Rstats::pl_av_fetch(sv_values, i);
        
        if (SvOK(sv_value)) {
          v1->set_value(
            i,
            SvIV(sv_value)
          );
        }
        else {
          v1->add_na_position(i);
        }
      }
      
      SV* sv_x1 = Rstats::Func::new_vector<int32_t>(sv_r, v1);
      
      return sv_x1;
    }

    SV* new_NULL(SV* sv_r) {
      
      SV* sv_x1 = Rstats::pl_new_hvrv();
      sv_bless(sv_x1, gv_stashpv("Rstats::Object", 1));
      Rstats::pl_hv_store(sv_x1, "r", sv_r);
      Rstats::pl_hv_store(sv_x1, "object_type", Rstats::pl_new_sv_pv("NULL"));
      Rstats::pl_hv_store(sv_x1, "type", Rstats::pl_new_sv_pv("NULL"));
      
      return sv_x1;
    }
    
    SV* new_NA(SV* sv_r) {
      Rstats::Vector<double>* v1 = new Rstats::Vector<double>(1, 0);
      v1->add_na_position(0);

      SV* sv_x1 = Rstats::Func::new_vector<double>(sv_r, v1);
      
      return sv_x1;
    }

    SV* new_NaN(SV* sv_r) {
      Rstats::Vector<double>* v1 = new Rstats::Vector<double>(1, NAN);
      
      SV* sv_x1 = Rstats::Func::new_vector<double>(sv_r, v1);
      
      return sv_x1;
    }

    SV* new_Inf(SV* sv_r) {
      Rstats::Vector<double>* v1 = new Rstats::Vector<double>(1, INFINITY);
      
      SV* sv_x1 = Rstats::Func::new_vector<double>(sv_r, v1);
      
      return sv_x1;
    }

    SV* new_FALSE(SV* sv_r) {
      Rstats::Vector<double>* v1 = new Rstats::Vector<double>(1, 0);
      
      SV* sv_x1 = Rstats::Func::new_vector<double>(sv_r, v1);
      
      return sv_x1;
    }

    SV* new_TRUE(SV* sv_r) {
      Rstats::Vector<double>* v1 = new Rstats::Vector<double>(1, 1);
      
      SV* sv_x1 = Rstats::Func::new_vector<double>(sv_r, v1);
      
      return sv_x1;
    }

    SV* to_object(SV* sv_r, SV* sv_element) {
      
      
      SV* sv_x_out;
      if (SvOK(sv_element)) {
        if (SvROK(sv_element)) {
          double is_object = sv_isobject(sv_element) && sv_derived_from(sv_element, "Rstats::Object");
          if (is_object) {
            sv_x_out = sv_element;
          }
          else {
            croak("Can't receive reference value except Rstats::Object object");
          }
        }
        else {
          if (Rstats::Util::is_perl_number(sv_element)) {
            Rstats::Vector<double>* v_out = new Rstats::Vector<double>(1, SvNV(sv_element));
            sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
          }
          else {
            Rstats::Vector<Rstats::Character>* v_out = new Rstats::Vector<Rstats::Character>(1, Rstats::pl_new_sv_sv(sv_element));
            sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
          }
        }
      }
      else {
        sv_x_out = Rstats::Func::new_NA(sv_r);
      }
      
      return sv_x_out;
    }

    SV* is_numeric(SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_type(sv_r, sv_x1), "double")
        || strEQ(Rstats::Func::get_type(sv_r, sv_x1), "integer");
        
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* is_double(SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_type(sv_r, sv_x1), "double");
        
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* is_integer(SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_type(sv_r, sv_x1), "integer");
        
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* is_complex(SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_type(sv_r, sv_x1), "complex");
        
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* is_string(SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_type(sv_r, sv_x1), "string");
        
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* is_data_frame(SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_object_type(sv_r, sv_x1), "data.frame");
        
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* is_list(SV* sv_r, SV* sv_x1) {
      
      bool is = strEQ(Rstats::Func::get_type(sv_r, sv_x1), "list");
        
      SV* sv_x_is = is ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
      
      return sv_x_is;
    }

    SV* new_data_frame(SV* sv_r) {
      SV* sv_data_frame = Rstats::pl_new_hvrv();
      Rstats::pl_sv_bless(sv_data_frame, "Rstats::Object");
      Rstats::pl_hv_store(sv_data_frame, "r", sv_r);
      Rstats::pl_hv_store(sv_data_frame, "object_type", Rstats::pl_new_sv_pv("data.frame"));
      Rstats::pl_hv_store(sv_data_frame, "type", Rstats::pl_new_sv_pv("list"));
      
      return sv_data_frame;
    }

    SV* new_list(SV* sv_r) {
      SV* sv_list = Rstats::pl_new_hvrv();
      Rstats::pl_sv_bless(sv_list, "Rstats::Object");
      Rstats::pl_hv_store(sv_list, "r", sv_r);
      Rstats::pl_hv_store(sv_list, "object_type", Rstats::pl_new_sv_pv("list"));
      Rstats::pl_hv_store(sv_list, "type", Rstats::pl_new_sv_pv("list"));
      
      return sv_list;
    }

    SV* copy_attrs_to(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x2, &PL_sv_undef);
    }

    SV* copy_attrs_to(SV* sv_r, SV* sv_x1, SV* sv_x2, SV* sv_opt) {
      
      if (!SvOK(sv_opt)) {
        sv_opt = Rstats::pl_new_hvrv();
      }
      
      SV* sv_new_indexes = Rstats::pl_hv_fetch(sv_opt, "new_indexes");
      
      // type
      if (!SvOK(Rstats::pl_hv_fetch(sv_x2, "type")) && Rstats::pl_hv_exists(sv_x1, "type")) {
        Rstats::pl_hv_store(sv_x2, "type", Rstats::pl_hv_fetch(sv_x1, "type"));
      }

      // object_type
      if (!SvOK(Rstats::pl_hv_fetch(sv_x2, "object_type")) && Rstats::pl_hv_exists(sv_x1, "object_type")) {
        Rstats::pl_hv_store(sv_x2, "object_type", Rstats::pl_hv_fetch(sv_x1, "object_type"));
      }

      // dim
      if (!SvOK(Rstats::pl_hv_fetch(sv_x2, "dim")) && Rstats::pl_hv_exists(sv_x1, "dim")) {
        Rstats::pl_hv_store(sv_x2, "dim", Rstats::Func::as_vector(sv_r, Rstats::pl_hv_fetch(sv_x1, "dim")));
      }

      // class
      if (!SvOK(Rstats::pl_hv_fetch(sv_x2, "class")) && Rstats::pl_hv_exists(sv_x1, "class")) {
        Rstats::pl_hv_store(sv_x2, "class", Rstats::Func::as_vector(sv_r, Rstats::pl_hv_fetch(sv_x1, "class")));
      }
      
      // levels
      if (!SvOK(Rstats::pl_hv_fetch(sv_x2, "levels")) && Rstats::pl_hv_exists(sv_x1, "levels")) {
        Rstats::pl_hv_store(sv_x2, "levels", Rstats::Func::as_vector(sv_r, Rstats::pl_hv_fetch(sv_x1, "levels")));
      }
      
      // names
      if (!SvOK(Rstats::pl_hv_fetch(sv_x2, "names")) && Rstats::pl_hv_exists(sv_x1, "names")) {
        SV* sv_x2_names_values = Rstats::pl_new_avrv();
        SV* sv_index;
        if (SvOK(sv_new_indexes)) {
          sv_index = Rstats::Func::to_bool(sv_r, Rstats::Func::is_data_frame(sv_r, sv_x1))
            ? Rstats::pl_av_fetch(sv_new_indexes, 1) : Rstats::pl_av_fetch(sv_new_indexes, 0);
        }
        else {
          sv_index = &PL_sv_undef;
        }
        
        SV* sv_x2_names;
        if (SvOK(sv_index)) {
          
          SV* sv_x1_names_values = Rstats::Func::values(sv_r, Rstats::pl_hv_fetch(sv_x1, "names"));
          SV* sv_index_values = Rstats::Func::values(sv_r, sv_index);
          Rstats::Vector<Rstats::Character>* v_out_names = new Rstats::Vector<Rstats::Character>(Rstats::pl_av_len(sv_index_values));
          
          for (int32_t i = 0; i < Rstats::pl_av_len(sv_index_values); i++) {
            int32_t idx = SvIV(Rstats::pl_av_fetch(sv_index_values, i));
            SV* sv_x2_names_value = Rstats::pl_av_fetch(sv_x1_names_values, idx - 1);
            v_out_names->set_value(i, Rstats::pl_new_sv_sv(sv_x2_names_value));
          }
          sv_x2_names = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out_names);
        }
        else {
          sv_x2_names = Rstats::Func::clone(sv_r, Rstats::pl_hv_fetch(sv_x1, "names"));
        }
        Rstats::pl_hv_store(sv_x2, "names", sv_x2_names);
      }
      
      // dimnames
      if (!SvOK(Rstats::pl_hv_fetch(sv_x2, "dimnames")) && Rstats::pl_hv_exists(sv_x1, "dimnames")) {
        SV* sv_new_dimnames = Rstats::pl_new_avrv();
        SV* sv_dimnames = Rstats::pl_hv_fetch(sv_x1, "dimnames");
        int32_t length = Rstats::pl_av_len(sv_dimnames);
        for (int32_t i = 0; i < length; i++) {
          SV* sv_dimname = Rstats::pl_av_fetch(sv_dimnames, i);
          if (SvOK(sv_dimname) && Rstats::Func::get_length(sv_r, sv_dimname) > 0) {
            SV* sv_index = SvOK(sv_new_indexes) ? Rstats::pl_av_fetch(sv_new_indexes, i) : &PL_sv_undef;
            SV* sv_dimname_values = Rstats::Func::values(sv_r, sv_dimname);
            SV* sv_new_dimname_values = Rstats::pl_new_avrv();
            SV* sv_x2_dimnames;
            if (SvOK(sv_index)) {
              SV* sv_index_values = Rstats::Func::values(sv_r, sv_index);
              Rstats::Vector<Rstats::Character>* v_k = new Rstats::Vector<Rstats::Character>(Rstats::pl_av_len(sv_index_values));
              for (int32_t i = 0; i < Rstats::pl_av_len(sv_index_values); i++) {
                SV* sv_k = Rstats::pl_av_fetch(sv_index_values, i);
                v_k->set_value(i, Rstats::pl_new_sv_sv(Rstats::pl_av_fetch(sv_dimname_values, SvIV(sv_k) - 1)));
              }
              sv_x2_dimnames = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_k);
            }
            else {
              sv_x2_dimnames = Rstats::Func::clone(sv_r, sv_dimname);
            }
            Rstats::pl_av_push(sv_new_dimnames, sv_x2_dimnames);
          }
        }
        Rstats::pl_hv_store(sv_x2, "dimnames", sv_new_dimnames);
      }
    }

    SV* is_na(SV* sv_r, SV* sv_x1) {
      
      sv_x1 = Rstats::Func::to_object(sv_r, sv_x1);

      char* type = Rstats::Func::get_type(sv_r, sv_x1);

      SV* sv_x_out;
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_na<Rstats::Character>(v1);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_na<std::complex<double>>(v1);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_na<double>(v1);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = Rstats::VectorFunc::is_na<int32_t>(v1);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "NULL")) {
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(0, 0);
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        warn("Warning message:\nIn is->na(NULL) : is->na() applied to non-(list or vector) of type 'NULL'\n");
      }
      else if (strEQ(type, "list")) {
        sv_x_out = Rstats::Func::new_FALSE(sv_r);
      }
      else {
        croak("Error in is->na() : default method not implemented for type '%s'", type);
      }
      
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* Class(SV* sv_r, SV* sv_x1, SV* sv_x2) {
      
      // Set class
      sv_x2 = Rstats::Func::to_object(sv_r, sv_x2);
      Rstats::pl_hv_store(sv_x1, "class", Rstats::Func::as_vector(sv_r, sv_x2));
      
      return sv_x1;
    }

    SV* Class(SV* sv_r, SV* sv_x1) {
      
      // Get class
      SV* sv_x_class;
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      if (Rstats::pl_hv_exists(sv_x1, "class")) {
        sv_x_class = Rstats::Func::as_vector(sv_r, Rstats::pl_hv_fetch(sv_x1, "class"));
      }
      else {
        char* class_name;
        if (strEQ(type, "NULL")) {
          class_name = "NULL";
        }
        else if (Rstats::Func::to_bool(sv_r, Rstats::Func::is_vector(sv_r, sv_x1))) {
          if (strEQ(type, "double") || strEQ(type, "integer")) {
            class_name = "numeric";
          }
          else {
            class_name = type; 
          }
        }
        else if (Rstats::Func::to_bool(sv_r, Rstats::Func::is_matrix(sv_r, sv_x1))) {
          class_name = "matrix";
        }
        else if (Rstats::Func::to_bool(sv_r, Rstats::Func::is_array(sv_r, sv_x1))) {
          class_name = "array";
        }
        else if (Rstats::Func::to_bool(sv_r, Rstats::Func::is_data_frame(sv_r, sv_x1))) {
          class_name = "data.frame";
        }
        else if (Rstats::Func::to_bool(sv_r, Rstats::Func::is_list(sv_r, sv_x1))) {
          class_name = "list";
        }
        else {
          croak("Error in class() : Invalid class");
        }
        Rstats::Vector<Rstats::Character>* v_class = new Rstats::Vector<Rstats::Character>(1, Rstats::pl_new_sv_pv(class_name));
        sv_x_class = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_class);
      }
      
      return sv_x_class;
    }

    SV* is_factor(SV* sv_r, SV* sv_x1) {
      
      SV* sv_classes = Rstats::Func::Class(sv_r, sv_x1);
      Rstats::Vector<Rstats::Character>* v_classes = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_classes);
      int32_t v_classes_length = Rstats::Func::get_length(sv_r, sv_classes);
      
      double match = 0;
      for (int32_t i = 0; i < v_classes_length; i++) {
        SV* sv_class = v_classes->get_value(i);
        if (strEQ(SvPV_nolen(sv_class), "factor")) {
          match = 1;
          break;
        }
      }
      
      return match ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
    }

    SV* is_ordered(SV* sv_r, SV* sv_x1) {
      
      SV* sv_classes = Rstats::Func::Class(sv_r, sv_x1);
      Rstats::Vector<Rstats::Character>* v_classes = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_classes);
      int32_t v_classes_length = Rstats::Func::get_length(sv_r, sv_classes);
      
      double match = 0;
      for (int32_t i = 0; i < v_classes_length; i++) {
        SV* sv_class = v_classes->get_value(i);
        if (strEQ(SvPV_nolen(sv_class), "ordered")) {
          match = 1;
          break;
        }
      }
      
      return match ? Rstats::Func::new_TRUE(sv_r) : Rstats::Func::new_FALSE(sv_r);
    }

    SV* clone(SV* sv_r, SV* sv_x1) {
      
      SV* sv_x_out = Rstats::Func::as_vector(sv_r, sv_x1);
      Rstats::Func::copy_attrs_to(sv_r, sv_x1, sv_x_out);
      
      return sv_x_out;
    }

    SV* dim_as_array(SV* sv_r, SV* sv_x1) {
      
      if (Rstats::pl_hv_exists(sv_x1, "dim")) {
        return Rstats::Func::dim(sv_r, sv_x1);
      }
      else {
        int32_t length = Rstats::Func::get_length(sv_r, sv_x1);
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(1, length);
        SV* sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
        return sv_x_out;
      }
    }

    SV* decompose(SV* sv_r, SV* sv_x1) {
      
      SV* sv_elements = Rstats::pl_new_avrv();
      
      int32_t length = Rstats::Func::get_length(sv_r, sv_x1);
      
      if (length > 0) {
      
        av_extend(Rstats::pl_av_deref(sv_elements), length);
        
        char* type = Rstats::Func::get_type(sv_r, sv_x1);

        if (strEQ(type, "string")) {
          Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
          for (int32_t i = 0; i < length; i++) {
            Rstats::Vector<Rstats::Character>* v_out
              = new Rstats::Vector<Rstats::Character>(1, v1->get_value(i));
            if (v1->exists_na_position(i)) {
              v_out->add_na_position(0);
            }
            SV* sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
            Rstats::pl_av_push(sv_elements, sv_x_out);
          }
        }
        else if (strEQ(type, "complex")) {
          Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);
          for (int32_t i = 0; i < length; i++) {
            Rstats::Vector<std::complex<double>>* v_out
              = new Rstats::Vector<std::complex<double>>(1, v1->get_value(i));
            if (v1->exists_na_position(i)) {
              v_out->add_na_position(0);
            }
            SV* sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
            Rstats::pl_av_push(sv_elements, sv_x_out);
          }
        }
        else if (strEQ(type, "double")) {
          Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);
          for (int32_t i = 0; i < length; i++) {
            Rstats::Vector<double>* v_out
              = new Rstats::Vector<double>(1, v1->get_value(i));
            if (v1->exists_na_position(i)) {
              v_out->add_na_position(0);
            }
            SV* sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
            Rstats::pl_av_push(sv_elements, sv_x_out);
          }
        }
        else if (strEQ(type, "integer")) {
          Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);
          for (int32_t i = 0; i < length; i++) {
            Rstats::Vector<int32_t>* v_out
              = new Rstats::Vector<int32_t>(1, v1->get_value(i));
            if (v1->exists_na_position(i)) {
              v_out->add_na_position(0);
            }
            SV* sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
            Rstats::pl_av_push(sv_elements, sv_x_out);
          }
        }
      }
      
      return sv_elements;
    }

    SV* compose(SV* sv_r, SV* sv_type, SV* sv_elements)
    {
      int32_t len = Rstats::pl_av_len(sv_elements);
      
      std::vector<int32_t> na_positions;
      char* type = SvPV_nolen(sv_type);
      SV* sv_x_out;
      if (strEQ(type, "string")) {
        Rstats::Vector<Rstats::Character>* v_out = new Rstats::Vector<Rstats::Character>(len);
        for (int32_t i = 0; i < len; i++) {
          SV* sv_x1 = Rstats::pl_av_fetch(sv_elements, i);
          if (!SvOK(sv_x1)) {
            na_positions.push_back(i);
          }
          else {
            Rstats::Vector<Rstats::Character>* v1 = Rstats::Func::get_vector<Rstats::Character>(sv_r, sv_x1);
            
            if (v1->exists_na_position(0)) {
              na_positions.push_back(i);
            }
            else {
              v_out->set_value(i, v1->get_value(0));
            }
          }
        }
        for (int32_t i = 0; i < na_positions.size(); i++) {
          v_out->add_na_position(na_positions[i]);
        }
        sv_x_out = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_out);
      }
      else if (strEQ(type, "complex")) {
        Rstats::Vector<std::complex<double>>* v_out = new Rstats::Vector<std::complex<double>>(len);
        for (int32_t i = 0; i < len; i++) {
          SV* sv_x1 = Rstats::pl_av_fetch(sv_elements, i);
          if (!SvOK(sv_x1)) {
            na_positions.push_back(i);
          }
          else {
            Rstats::Vector<std::complex<double>>* v1 = Rstats::Func::get_vector<std::complex<double>>(sv_r, sv_x1);

            if (v1->exists_na_position(0)) {
              na_positions.push_back(i);
            }
            else {
              v_out->set_value(i, v1->get_value(0));
            }
          }
        }
        for (int32_t i = 0; i < na_positions.size(); i++) {
          v_out->add_na_position(na_positions[i]);
        }
        sv_x_out = Rstats::Func::new_vector<std::complex<double>>(sv_r, v_out);
      }
      else if (strEQ(type, "double")) {
        
        Rstats::Vector<double>* v_out = new Rstats::Vector<double>(len);
        for (int32_t i = 0; i < len; i++) {
          SV* sv_x1 = Rstats::pl_av_fetch(sv_elements, i);
          if (!SvOK(sv_x1)) {
            na_positions.push_back(i);
          }
          else {
            Rstats::Vector<double>* v1 = Rstats::Func::get_vector<double>(sv_r, sv_x1);

            if (v1->exists_na_position(0)) {
              na_positions.push_back(i);
            }
            else {
              v_out->set_value(i, v1->get_value(0));
            }
          }
        }
        for (int32_t i = 0; i < na_positions.size(); i++) {
          v_out->add_na_position(na_positions[i]);
        }
        sv_x_out = Rstats::Func::new_vector<double>(sv_r, v_out);
      }
      else if (strEQ(type, "integer")) {
        Rstats::Vector<int32_t>* v_out = new Rstats::Vector<int32_t>(len);
        int32_t* values = v_out->get_values();
        for (int32_t i = 0; i < len; i++) {
          SV* sv_x1 = Rstats::pl_av_fetch(sv_elements, i);
          if (!SvOK(sv_x1)) {
            na_positions.push_back(i);
          }
          else {
            Rstats::Vector<int32_t>* v1 = Rstats::Func::get_vector<int32_t>(sv_r, sv_x1);

            if (v1->exists_na_position(0)) {
              na_positions.push_back(i);
            }
            else {
              v_out->set_value(i, v1->get_value(0));
            }
          }
        }
        for (int32_t i = 0; i < na_positions.size(); i++) {
          v_out->add_na_position(na_positions[i]);
        }
        sv_x_out = Rstats::Func::new_vector<int32_t>(sv_r, v_out);
      }
      else if (strEQ(type, "NULL")) {
        // Nothing to do
      }
      else {
        croak("Unknown type(Rstats::Func::compose())");
      }
      
      return sv_x_out;
    }

    SV* args_h(SV* sv_r, SV* sv_names, SV* sv_args) {
      
      int32_t args_length = Rstats::pl_av_len(sv_args);
      SV* sv_opt;
      SV* sv_arg_last = Rstats::pl_av_fetch(sv_args, args_length - 1);
      if (!sv_isobject(sv_arg_last) && sv_derived_from(sv_arg_last, "HASH")) {
        sv_opt = Rstats::pl_av_pop(sv_args);
      }
      else {
        sv_opt = Rstats::pl_new_hvrv();
      }
      
      SV* sv_new_opt = Rstats::pl_new_hvrv();
      int32_t names_length = Rstats::pl_av_len(sv_names);
      for (int32_t i = 0; i < names_length; i++) {
        SV* sv_name = Rstats::pl_av_fetch(sv_names, i);
        if (Rstats::pl_hv_exists(sv_opt, SvPV_nolen(sv_name))) {
          Rstats::pl_hv_store(
            sv_new_opt,
            SvPV_nolen(sv_name),
            Rstats::Func::to_object(sv_r, Rstats::pl_hv_delete(sv_opt, SvPV_nolen(sv_name)))
          );
        }
        else if (i < names_length) {
          SV* sv_name = Rstats::pl_av_fetch(sv_names, i);
          SV* sv_arg = Rstats::pl_av_fetch(sv_args, i);
          if (SvOK(sv_arg)) {
            Rstats::pl_hv_store(
              sv_new_opt,
              SvPV_nolen(sv_name),
              Rstats::Func::to_object(sv_r, sv_arg)
            );
          }
        }
      }

      return sv_new_opt;
    }
    
    SV* as_array(SV* sv_r, SV* sv_x1) {
      
      SV* sv_x_out = Rstats::Func::as_vector(sv_r, sv_x1);
      SV* sv_x_out_dim = Rstats::Func::dim_as_array(sv_r, sv_x1);
      
      return Rstats::Func::array(sv_r, sv_x_out, sv_x_out_dim);
    }

    SV* levels(SV* sv_r, SV* sv_x1, SV* sv_x_class) {
      
      sv_x_class = Rstats::Func::to_object(sv_r, sv_x_class);
      if (!Rstats::Func::to_bool(sv_r, Rstats::Func::is_string(sv_r, sv_x_class))) {
        sv_x_class = Rstats::Func::as_string(sv_r, sv_x_class);
      }
      
      Rstats::pl_hv_store(sv_x1, "levels", Rstats::Func::as_vector(sv_r, sv_x_class));
      
      return sv_x1;
    }
    
    SV* levels(SV* sv_r, SV* sv_x1) {
      SV* sv_x_levels;
      
      if (Rstats::pl_hv_exists(sv_x1, "levels")) {
        sv_x_levels = Rstats::Func::as_vector(sv_r, Rstats::pl_hv_fetch(sv_x1, "levels"));
      }
      else {
        sv_x_levels = Rstats::Func::new_NULL(sv_r);
      }
      
      return sv_x_levels;
    }

    SV* mode(SV* sv_r, SV* sv_x1, SV* sv_x_type) {
      
      sv_x_type = Rstats::Func::to_object(sv_r, sv_x_type);
      
      SV* sv_type = Rstats::pl_av_fetch(Rstats::Func::values(sv_r, sv_x_type), 0);
      char* type = SvPV_nolen(sv_type);
      
      if (!strEQ(type, "string")
        && !strEQ(type, "complex")
        && !strEQ(type, "numeric")
        && !strEQ(type, "double")
        && !strEQ(type, "integer")
      )
      {
        croak("Error in eval(expr, envir, enclos) : could not find function \"as_%s\"", type);
      }
      
      sv_x1 = Rstats::Func::as(sv_r, sv_type, sv_x1);
      
      return sv_r;
    }
    
    SV* mode(SV* sv_r, SV* sv_x1) {
      
      char* type = Rstats::Func::get_type(sv_r, sv_x1);
      
      char* mode;
      if (strEQ(type, "NULL")) {
        mode = "NULL";
      }
      else if (strEQ(type, "integer") || strEQ(type, "double")) {
        mode = "numeric";
      }
      else {
        mode = type;
      }
      
      Rstats::Vector<Rstats::Character>* v_mode = new Rstats::Vector<Rstats::Character>(1, Rstats::pl_new_sv_pv(mode));
      
      SV* sv_mode = Rstats::Func::new_vector<Rstats::Character>(sv_r, v_mode);
      
      return sv_mode;
    }
    
    SV* as(SV* sv_r, SV* sv_type, SV* sv_x1) {
      
      char* type = SvPV_nolen(sv_type);
      if (strEQ(type, "string")) {
        return Rstats::Func::as_string(sv_r, sv_x1);
      }
      else if (strEQ(type, "complex")) {

        return Rstats::Func::as_complex(sv_r, sv_x1);
      }
      else if (strEQ(type, "double")) {
        return Rstats::Func::as_double(sv_r, sv_x1);
      }
      else if (strEQ(type, "numeric")) {
        return Rstats::Func::as_numeric(sv_r, sv_x1);
      }
      else if (strEQ(type, "integer")) {
        return Rstats::Func::as_double(sv_r, sv_x1);
      }
      else {
        croak("Invalid mode %s is passed", type);
      }
    }

    SV* names(SV* sv_r, SV* sv_x1, SV* sv_x_names) {
      sv_x_names = Rstats::Func::to_object(sv_r, sv_x_names);
      
      if (!Rstats::Func::to_bool(sv_r, Rstats::Func::is_string(sv_r, sv_x_names))) {
        sv_x_names = Rstats::Func::as_string(sv_r, sv_x_names);
      }
      Rstats::pl_hv_store(sv_x1, "names", Rstats::Func::as_vector(sv_r, sv_x_names));
      
      if (Rstats::Func::to_bool(sv_r, Rstats::Func::is_data_frame(sv_r, sv_x1))) {
        SV* sv_x1_dimnames = Rstats::pl_hv_fetch(sv_x1, "dimnames");
        Rstats::pl_av_store(
          sv_x1_dimnames,
          1,
          Rstats::Func::as_vector(sv_r, Rstats::pl_hv_fetch(sv_x1, "names"))
        );
      }
      
      return sv_r;
    }
    
    SV* names(SV* sv_r, SV* sv_x1) {
      SV* sv_x_names;
      if (Rstats::pl_hv_exists(sv_x1, "names")) {
        sv_x_names = Rstats::Func::as_vector(sv_r, Rstats::pl_hv_fetch(sv_x1, "names"));
      }
      else {
        sv_x_names = Rstats::Func::new_NULL(sv_r);
      }
      return sv_x_names;
    }
  }
}

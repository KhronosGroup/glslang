#version 450

layout(constant_id = 200) const int my_int = 3;
layout(constant_id = 201) const float my_float = 3.14;
layout(constant_id = 202) const
    double my_double = 3.1415926535897932384626433832795;
layout(constant_id = 203) const bool my_bool = true;

// Flat struct
struct flat_struct {
  int i;
  float f;
  double d;
  bool b;
};

// Nesting struct
struct nesting_struct {
  flat_struct nested;
  vec4 v;
  int i;
};

// Expect OpSpecConstantComposite
const flat_struct my_flat_full_spec = {my_int, my_float, my_double,
                                                 my_bool};
const flat_struct my_flat_partial_spec = {30, 30.14, my_double,
                                                    my_bool};

const vec4 my_vec4_full_spec = vec4(my_float, my_float, my_float, my_float);
const vec4 my_vec4_partial_spec = vec4(my_float, my_float, 300.14, 300.14);

const nesting_struct my_nesting_full_spec = {my_flat_full_spec, my_vec4_full_spec,
                                      my_int};
const nesting_struct my_nesting_partial_spec = {my_flat_partial_spec,
                                         my_vec4_partial_spec, 3000};

const float my_array[3] = {my_float, my_float, 1.0};

layout(constant_id = 16) const int arraySize = 5;
in vec4 ucol[arraySize];

out vec4 color;
out int size;

void refer_primary_spec_const() {
  if (my_bool) color *= my_int;
}

void refer_composite_spec_const() {
  color += my_vec4_full_spec;
  color -= my_vec4_partial_spec;
}

void refer_copmosite_dot_dereference() {
  color *= my_nesting_full_spec.i;
}

void refer_composite_bracket_dereference() {
  color -= my_array[1];
}

void declare_spec_const_in_func() {
  const nesting_struct spec_const_declared_in_func = {my_flat_partial_spec,
                                               my_vec4_partial_spec, 10};
  color /= spec_const_declared_in_func.i;
}

void main() {
  refer_primary_spec_const();
  refer_composite_spec_const();
  refer_copmosite_dot_dereference();
  refer_composite_bracket_dereference();
  declare_spec_const_in_func();
}

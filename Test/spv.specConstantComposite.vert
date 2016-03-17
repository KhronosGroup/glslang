#version 450

layout(constant_id = 200) const int my_int = 3;
layout(constant_id = 201) const float my_float = 3.14;
layout(constant_id = 202) const
    double my_double = 3.1415926535897932384626433832795;
layout(constant_id = 203) const bool my_bool = true;

// Flat struct
struct int_float_double_bool {
  int i;
  float f;
  double d;
  bool b;
};

// Nesting struct
struct nesting {
  int_float_double_bool nested;
  vec4 v;
  int i;
};

// Expect OpSpecConstantComposite
const int_float_double_bool my_flat_full_spec = {my_int, my_float, my_double,
                                                 my_bool};
const int_float_double_bool my_flat_partial_spec = {30, 30.14, my_double,
                                                    my_bool};

const vec4 my_vec4_full_spec = vec4(my_float, my_float, my_float, my_float);
const vec4 my_vec4_partial_spec = vec4(my_float, my_float, 300.14, 300.14);

const nesting my_nesting_full_spec = {my_flat_full_spec, my_vec4_full_spec,
                                      my_int};
const nesting my_nesting_partial_spec = {my_flat_partial_spec,
                                         my_vec4_partial_spec, 3000};

const float my_array[3] = {my_float, my_float, 1.0};

layout(constant_id = 16) const int arraySize = 5;
in vec4 ucol[arraySize];

out vec4 color;
out int size;

void main() {
  const nesting spec_const_declared_in_func = {my_flat_partial_spec,
                                               my_vec4_partial_spec, 10};
  color = ucol[2];
  size = arraySize;
  if (my_bool) color *= my_int;
  color += float(my_double / my_float);
  color += my_vec4_full_spec;
  color += vec4(1.0, 2.0, 3.0, 4.0);
  color -= my_vec4_partial_spec;
  color *= my_nesting_full_spec.i;
  color /= spec_const_declared_in_func.i;
  color -= my_array[1];
}

#version 450

layout(constant_id = 200) const int spec_int = 3;
layout(constant_id = 201) const float spec_float = 3.14;
layout(constant_id = 202) const
    double spec_double = 3.1415926535897932384626433832795;
layout(constant_id = 203) const bool spec_bool = true;

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
const flat_struct spec_flat_struct_all_spec = {spec_int, spec_float,
                                               spec_double, spec_bool};
const flat_struct spec_flat_struct_partial_spec = {30, 30.14, spec_double,
                                                   spec_bool};

const vec4 spec_vec4_all_spec =
    vec4(spec_float, spec_float, spec_float, spec_float);
const vec4 spec_vec4_partial_spec =
    vec4(spec_float, spec_float, 300.14, 300.14);

const nesting_struct spec_nesting_struct_all_spec = {
    spec_flat_struct_all_spec, spec_vec4_all_spec, spec_int};
const nesting_struct spec_nesting_struct_partial_spec = {
    spec_flat_struct_partial_spec, spec_vec4_partial_spec, 3000};

const float spec_float_array[5] = {spec_float, spec_float, 1.0, 2.0, 3.0};
const int spec_int_array[5] = {spec_int, spec_int, 1, 2, 3};

// global_vec4_array_with_spec_length is not a spec constant, but its array
// size is. When calling global_vec4_array_with_spec_length.length(), A
// TIntermSymbol Node shoule be returned, instead of a TIntermConstantUnion
// node which represents a known constant value.
in vec4 global_vec4_array_with_spec_length[spec_int];

out vec4 color;

void refer_primary_spec_const() {
  if (spec_bool) color *= spec_int;
}

void refer_composite_spec_const() {
  color += spec_vec4_all_spec;
  color -= spec_vec4_partial_spec;
}

void refer_copmosite_dot_dereference() {
  color *= spec_nesting_struct_all_spec.i;
  color += spec_vec4_all_spec.x;
}

void refer_composite_bracket_dereference() {
  color -= spec_float_array[1];
  color /= spec_int_array[spec_int_array[spec_int]];
}

int refer_spec_const_array_length() {
  int len = global_vec4_array_with_spec_length.length();
  return len;
}

void declare_spec_const_in_func() {
  const nesting_struct spec_const_declared_in_func = {
      spec_flat_struct_partial_spec, spec_vec4_partial_spec, 10};
  color /= spec_const_declared_in_func.i;
}

void main() {}

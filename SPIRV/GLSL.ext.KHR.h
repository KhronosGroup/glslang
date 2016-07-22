/*
** Copyright (c) 2014-2016 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and/or associated documentation files (the "Materials"),
** to deal in the Materials without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Materials, and to permit persons to whom the
** Materials are furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Materials.
**
** MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS KHRONOS
** STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS SPECIFICATIONS AND
** HEADER INFORMATION ARE LOCATED AT https://www.khronos.org/registry/
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM,OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE USE OR OTHER DEALINGS
** IN THE MATERIALS.
*/

#ifndef GLSLextKHR_H
#define GLSLextKHR_H

enum BuiltIn;

static const int GLSLextKHRVersion = 100;
static const int GLSLextKHRRevision = 1;

// SPV_KHR_shader_draw_parameters
static const char* const E_SPV_KHR_shader_draw_parameters = "SPV_KHR_shader_draw_parameters";

static const BuiltIn BuiltInBaseVertexKHR       = static_cast<BuiltIn>(5504);
static const BuiltIn BuiltInBaseInstanceKHR     = static_cast<BuiltIn>(5505);
static const BuiltIn BuiltInDrawIDKHR           = static_cast<BuiltIn>(5506);

#endif  // #ifndef GLSLextKHR_H

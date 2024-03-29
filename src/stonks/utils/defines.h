// MIT License
//
// Copyright (c) [2024] [Aleksei Kutasov]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef STONKS_UTILS_DEFINES_H
#define STONKS_UTILS_DEFINES_H

#include "stonks/../defines.h"

#define FIELD_TYPE(struct_name, field_name) decltype(std::declval<struct_name>().field_name)

#ifdef _MSC_VER
#define ALIGNED_MALLOC(size, alignment) _aligned_malloc(size, alignment)
#else
#define ALIGNED_MALLOC(size, alignment) std::malloc(size)
#endif

#ifdef _MSC_VER
#define ALIGNED_FREE(ptr) _aligned_free(ptr)
#else
#define ALIGNED_FREE(ptr) std::free(ptr)
#endif

#endif// #ifndef STONKS_UTILS_DEFINES_H

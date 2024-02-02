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

#ifndef STONKS_DEFINE
#define STONKS_DEFINE

#include <cassert>

#ifndef STONKS_NAMESPACE
#define STONKS_NAMESPACE stonks
#endif

#ifndef STONKS_ASSERT
#define STONKS_ASSERT(condition, formatted_message, ...) \
    do {                                                 \
        assert(condition);                               \
    } while (false);
#endif

#ifndef STONKS_DYNAMIC_LIB
#define STONKS_DYNAMIC_LIB false
#endif

#ifndef STONKS_API
#if STONKS_DYNAMIC_LIB
#define STONKS_API __declspec(dllexport)
#else
#define STONKS_API
#endif
#endif

#ifndef STONKS_ALWAYS_INLINE
#ifdef __GNUC__
#define STONKS_ALWAYS_INLINE __attribute__((always_inline))
#elif defined(_MSC_VER)
#define STONKS_ALWAYS_INLINE __forceinline
#else
#define STONKS_ALWAYS_INLINE inline
#endif
#endif

#ifndef STONKS_DO_PRAGMA
#if defined(_MSC_VER)
#define STONKS_DO_PRAGMA(x) __pragma(x)
#else
#define STONKS_DO_PRAGMA(x) _Pragma(#x)
#endif
#endif

#ifndef STONKS_DIAGNOSTIC_PUSH
#ifdef __GNUC__
#define STONKS_DIAGNOSTIC_PUSH STONKS_DO_PRAGMA(gcc diagnostic push)
#elif defined(_MSC_VER)
#define STONKS_DIAGNOSTIC_PUSH STONKS_DO_PRAGMA(warning(push))
#else
#define STONKS_DIAGNOSTIC_PUSH STONKS_DO_PRAGMA(clang diagnostic push)
#endif
#endif

#ifndef STONKS_DIAGNOSTIC_POP
#ifdef __GNUC__
#define STONKS_DIAGNOSTIC_POP STONKS_DO_PRAGMA(GCC diagnostic pop)
#elif defined(_MSC_VER)
#define STONKS_DIAGNOSTIC_POP STONKS_DO_PRAGMA(warning(pop))
#else
#define STONKS_DIAGNOSTIC_POP STONKS_DO_PRAGMA(clang diagnostic pop)
#endif
#endif

#ifndef STONKS_DIAGNOSTIC_ATTRIBUTE
#ifdef __GNUC__
#define STONKS_DIAGNOSTIC_ATTRIBUTE STONKS_DO_PRAGMA(GCC diagnostic ignored "-Wattributes")
#elif defined(_MSC_VER)
#define STONKS_DIAGNOSTIC_ATTRIBUTE
#else
#define STONKS_DIAGNOSTIC_ATTRIBUTE STONKS_DO_PRAGMA(clang diagnostic ignored "-Wattributes")
#endif
#endif

#endif// #ifndef STONKS_DEFINE

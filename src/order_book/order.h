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

#ifndef STONKS_ORDER_H
#define STONKS_ORDER_H

#include "utils/defines.h"
#include <cstddef>
#include <cstdint>

#if __cplusplus >= 202002L
#include <compare>
#endif

namespace STONKS_NAMESPACE {

    struct STONKS_API Order final {
    public:
        enum class order_type : uint8_t {
            buy = 0,
            sell = 1,
        };
        size_t price;
        size_t amount;
        order_type type;

        bool operator<(const Order &other) const;

#if __cplusplus >= 202002L
        std::strong_ordering operator<=>(const Order &other) const;
#endif
    };

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_ORDER_H

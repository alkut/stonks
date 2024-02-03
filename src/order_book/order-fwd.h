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

#ifndef STONKS_ORDER_FWD_H
#define STONKS_ORDER_FWD_H

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

        constexpr bool operator<(const Order &other) const;
        constexpr bool operator==(const Order &other) const = default;
        constexpr bool operator!=(const Order &other) const = default;

        template<typename OutputStream>
        friend OutputStream &operator<<(OutputStream &out, const Order &order);

        template<typename InputStream>
        friend InputStream &operator>>(InputStream &in, Order &order);

        static Order GetRandom();

#if __cplusplus >= 202002L
        constexpr std::strong_ordering operator<=>(const Order &other) const;
#endif
    };

    template<typename OutputStream>
    STONKS_API OutputStream &operator<<(OutputStream &out, const Order &order) {
        out << "price: " << order.price << ", amount: " << order.amount << ", type: " << (order.type == Order::order_type::buy ? "buy" : "sell");
        return out;
    }

    template<typename InputStream>
    STONKS_API InputStream &operator>>(InputStream &in, Order &order) {
        bool buy;
        in >> order.price >> order.amount >> buy;
        order.type = buy ? Order::order_type::buy : Order::order_type::sell;
        return in;
    }

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_ORDER_H

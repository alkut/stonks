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

#include "order_book/order.h"

namespace STONKS_NAMESPACE {

bool Order::operator<(const Order &other) const {
    if (type != other.type) {
        STONKS_ASSERT(false, "attempt to compare orders with different types - it's illegal");
        return false;
    }
    switch (type) {
        case Order::order_type::buy:
            return price < other.price;
        case Order::order_type::sell:
            return other.price < price;
    }
    STONKS_ASSERT(false, "unhandled order type");
    return false;
}

#if __cplusplus >= 202002L
std::strong_ordering Order::operator<=>(const Order &other) const {
    if (type != other.type) {
        STONKS_ASSERT(false, "attempt to compare orders with different types - it's illegal");
        return {};
    }
    switch (type) {
        case Order::order_type::buy:
            return price <=> other.price;
        case Order::order_type::sell:
            return other.price <=> price;
    }
    STONKS_ASSERT(false, "unhandled order type");
    return {};
}
#endif

} // end namespace STONKS_NAMESPACE

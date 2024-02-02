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

#include "order_book/book.h"
#include <iostream>

int main() {
    static constexpr int countBuy = 3;
    static constexpr int countSell = 2;
    STONKS_NAMESPACE::Book book(countBuy, countSell);
    STONKS_NAMESPACE::Order orders[countBuy + countSell];
    for (int i = 0; i < (countBuy + countSell) * 2; ++i) {
        book.AddOrder(i, 1, STONKS_NAMESPACE::Order::order_type::buy);
        book.AddOrder(i, 1, STONKS_NAMESPACE::Order::order_type::sell);
    }
    book.ChooseBest(orders, orders + countBuy);
    for (auto & order : orders) {
        std::cout <<  order.price << " " << order.amount <<  " " <<
                (order.type == STONKS_NAMESPACE::Order::order_type::buy ? "buy" : "sell") << '\n';
    }
    return 0;
}

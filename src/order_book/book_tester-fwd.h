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

#ifndef STONKS_BOOK_TESTER_FWD_H
#define STONKS_BOOK_TESTER_FWD_H

#include "utils/defines.h"
#include <concepts>

namespace STONKS_NAMESPACE {

    struct Order;

    template<typename T>
    concept BookImpl = std::constructible_from<T, size_t, size_t> && requires(T book, Order order) {
        { book.AddOrder(order.price, order.amount, order.type) };
        { book.ChangeOrder(order.price, order.amount, order.type) } -> std::convertible_to<bool>;
        { book.AddOrder(order) };
        { book.ChangeOrder(order) } -> std::convertible_to<bool>;
        { book.EraseOrder(order.price, order.type) };
    };

    template<BookImpl BookImplementation>
    class STONKS_API BookTester final {
    public:
        explicit BookTester(size_t numOrders, size_t buyBestCount = 5, size_t sellBestCount = 5);
        ~BookTester() noexcept;

        void BenchmarkChooseBest();
        void BenchmarkChangeOrder();
        void BenchmarkAddErase();

        static bool TestEraseNonExistingOrder();
        static bool TestChooseBestSmallBook();
        static bool TestChangeNonExistingOrder();

    private:
        BookImplementation m_book;
        Order *m_bufferBuy;
        Order *m_bufferSell;

        static constexpr Order kOrder = {
                .price = 1,
                .amount = 20,
                .type = Order::order_type::buy};
    };

}// end namespace STONKS_NAMESPACE

#endif//STONKS_BOOK_TESTER_FWD_H
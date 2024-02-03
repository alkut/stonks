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

#include "stonks/utils/defines.h"
#include <concepts>

namespace STONKS_NAMESPACE {

    struct Order;

    template<typename TBookImplementation>
    concept BookImplementation = std::constructible_from<TBookImplementation, size_t, size_t> && requires(TBookImplementation book, Order order) {
        { book.AddOrder(order.price, order.amount, order.type) };
        { book.ChooseBest(&order, &order).first } -> std::convertible_to<Order *>;
        { book.ChooseBest(&order, &order).second } -> std::convertible_to<Order *>;
        { book.ChangeOrder(order.price, order.amount, order.type) } -> std::convertible_to<bool>;
        { book.AddOrder(order) };
        { book.ChangeOrder(order) } -> std::convertible_to<bool>;
        { book.EraseOrder(order.price, order.type) };
    };

    /**
     * Class for unit test and benchmark of different OrderBook implementation
     * @tparam BookImplementation OrderBook implementation @see BookImplementation concept
     */
    template<BookImplementation BookImplementation>
    class STONKS_API BookTester final {
    public:
        /**
         *
         * @param numOrders book order initial capacity
         * @param buyBestCount choose buyBestCount best buy orders
         * @param sellBestCount choose sellBestCount best sell orders
         */
        explicit BookTester(size_t numOrders, size_t buyBestCount = 5, size_t sellBestCount = 5);
        ~BookTester() noexcept;

        /**
         * invoke ChooseBest method with minimal overhead
         */
        void BenchmarkChooseBest();
        /**
         * invoke ChangeOrder method with minimal overhead
         */
        void BenchmarkChangeOrder();
        /**
         * invoke AddOrder then EraseOrder of the same order with minimal overhead
         */
        void BenchmarkAddErase();
        /**
         * unit test for EraseOrder. Book must handle case erase order, that doesn't exist correctly
         * @return false on any failure
         */
        static bool TestEraseNonExistingOrder();
        /**
         * unit test for Choose. Book must handle case when count of orders less then buyBestCount correctly
         * @return false on any failure
         */
        static bool TestChooseBestSmallBook();
        /**
         * unit test for ChangeOrder. Book must handle case change order, that doesn't exist correctly
         * @return false on any failure
         */
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

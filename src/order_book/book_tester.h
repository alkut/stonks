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

#ifndef STONKS_BOOK_TESTER_H
#define STONKS_BOOK_TESTER_H

#include "order_book/book_tester-fwd.h"
#include <cstdlib>

namespace STONKS_NAMESPACE {

    template<BookImpl BookImplementation>
    BookTester<BookImplementation>::BookTester(size_t numOrders, size_t buyBestCount, size_t sellBestCount)
        : m_book(buyBestCount, sellBestCount) {
        for (size_t i = 0; i < numOrders; ++i) {
            m_book.AddOrder(Order::GetRandom());
        }
        m_bufferBuy = static_cast<Order *>(ALIGNED_MALLOC(buyBestCount * sizeof(Order), alignof(Order)));
        m_bufferSell = static_cast<Order *>(ALIGNED_MALLOC(sellBestCount * sizeof(Order), alignof(Order)));
    }

    template<BookImpl BookImplementation>
    BookTester<BookImplementation>::~BookTester() noexcept {
        ALIGNED_FREE(m_bufferBuy);
        ALIGNED_FREE(m_bufferSell);
    }

    template<BookImpl BookImplementation>
    void BookTester<BookImplementation>::BenchmarkChooseBest() {
        m_book.ChooseBest(m_bufferBuy, m_bufferSell);
    }

    template<BookImpl BookImplementation>
    void BookTester<BookImplementation>::BenchmarkChangeOrder() {
        m_book.ChangeOrder(kOrder);
    }

    template<BookImpl BookImplementation>
    void BookTester<BookImplementation>::BenchmarkAddErase() {
        m_book.AddOrder(kOrder);
        m_book.EraseOrder(kOrder.price, kOrder.type);
    }

    template<BookImpl BookImplementation>
    bool BookTester<BookImplementation>::TestEraseNonExistingOrder() {
        {
            BookImplementation book(5, 5);
            book.AddOrder(1, 2, Order::order_type::buy);
            book.AddOrder(1, 2, Order::order_type::buy);
            book.EraseOrder(1, Order::order_type::sell);
        }
        {
            BookImplementation book(5, 5);
            book.AddOrder(1, 2, Order::order_type::buy);
            book.AddOrder(1, 2, Order::order_type::buy);
            book.EraseOrder(2, Order::order_type::buy);
        }
        return true;
    }

    template<BookImpl BookImplementation>
    bool BookTester<BookImplementation>::TestChooseBestSmallBook() {
        {
            BookImplementation book(5, 5);
            book.AddOrder(1, 2, Order::order_type::buy);
            book.AddOrder(1, 3, Order::order_type::buy);
            book.AddOrder(1, 2, Order::order_type::sell);
            Order buyBuffer[5];
            Order sellBuffer[5];
            const auto [lastBuy, lastSell] = book.ChooseBest(buyBuffer, sellBuffer);
            if (lastBuy != buyBuffer + 1 || lastSell != sellBuffer + 1) {
                STONKS_ASSERT(false, "wrong size of result");
                return false;
            }
            const Order buyExpected = {
                    .price = 1,
                    .amount = 2 + 3,
                    .type = Order::order_type::buy};
            const Order sellExpected = {
                    .price = 1,
                    .amount = 2,
                    .type = Order::order_type::sell};
            const Order buyActual = buyBuffer[0];
            const Order sellActual = sellBuffer[0];
            if (buyActual != buyExpected) {
                return false;
            }
            if (sellActual != sellExpected) {
                return false;
            }
        }
        return true;
    }

    template<BookImpl BookImplementation>
    bool BookTester<BookImplementation>::TestChangeNonExistingOrder() {
        {
            BookImplementation book(5, 5);
            book.AddOrder(1, 2, Order::order_type::buy);
            book.AddOrder(1, 2, Order::order_type::buy);
            bool successfullyAdded = book.ChangeOrder(1, 2, Order::order_type::sell);
            if (!successfullyAdded) {
                return false;
            }
            bool alreadyAdded = !book.ChangeOrder(1, 2, Order::order_type::sell);
            if (!alreadyAdded) {
                return false;
            }
        }
        {
            BookImplementation book(5, 5);
            book.AddOrder(1, 2, Order::order_type::buy);
            book.AddOrder(1, 2, Order::order_type::buy);
            bool successfullyAdded = book.ChangeOrder(2, 2, Order::order_type::buy);
            if (!successfullyAdded) {
                return false;
            }
            bool alreadyAdded = !book.ChangeOrder(2, 2, Order::order_type::buy);
            if (!alreadyAdded) {
                return false;
            }
        }
        return true;
    }

}// namespace STONKS_NAMESPACE

#endif//STONKS_BOOK_TESTER_H

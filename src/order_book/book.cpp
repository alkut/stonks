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

namespace STONKS_NAMESPACE {

    Book::Book(size_t buyBestCount, size_t sellBestCount) : m_bestBuyStorage(buyBestCount), m_bestSellStorage(sellBestCount) {}

    void Book::AddOrder(size_t price, size_t amount, Order::order_type type) {
        switch (type) {
            case Order::order_type::buy:
                m_bestBuyStorage.Emplace(price, amount);
                return;
            case Order::order_type::sell:
                m_bestSellStorage.Emplace(price, amount);
                return;
        }
        STONKS_ASSERT(false, "unhandled order type");
    }

    bool Book::ChangeOrder(size_t price, size_t newAmount, Order::order_type type) {
        switch (type) {
            case Order::order_type::buy:
                return m_bestBuyStorage.Change(price, newAmount).second;
            case Order::order_type::sell:
                return m_bestSellStorage.Change(price, newAmount).second;
        }
        STONKS_ASSERT(false, "unhandled order type");
        return false;
    }

    void Book::EraseOrder(size_t price, Order::order_type type) {
        switch (type) {
            case Order::order_type::buy:
                m_bestBuyStorage.Erase(price);
                return;
            case Order::order_type::sell:
                m_bestSellStorage.Erase(price);
                return;
        }
        STONKS_ASSERT(false, "unhandled order type");
    }

}// end namespace STONKS_NAMESPACE

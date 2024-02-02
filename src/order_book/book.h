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

#ifndef STONKS_BOOK_H
#define STONKS_BOOK_H

#include "order_book/order.h"
#include "storage/bestNStorage.h"
#include "utils/proxy_output_iterator.h"

namespace STONKS_NAMESPACE {

    // I hope, that would be inlined
    inline constexpr auto bestBuy = [](const FIELD_TYPE(Order, price) & lhs, const FIELD_TYPE(Order, price) & rhs) -> bool {
        return lhs < rhs;
    };

    // I hope, that would be inlined
    inline constexpr auto bestSell = [](const FIELD_TYPE(Order, price) & lhs, const FIELD_TYPE(Order, price) & rhs) -> bool {
        return lhs > rhs;
    };

    class STONKS_API Book {
    public:
        using price_type = FIELD_TYPE(Order, price);
        using amount_type = FIELD_TYPE(Order, amount);

        Book(size_t buyBestCount, size_t sellBestCount);
        void AddOrder(price_type price, amount_type amount, Order::order_type type);
        bool ChangeOrder(price_type price, amount_type newAmount, Order::order_type type);
        void EraseOrder(price_type price, Order::order_type type);
        template<typename OutputIteratorBuy, typename OutputIteratorSell>
        std::pair<OutputIteratorBuy, OutputIteratorSell> ChooseBest(OutputIteratorBuy firstBuy, OutputIteratorSell firstSell);

    private:
        using price_amount_type = std::pair<const price_type, amount_type>;

        BestNStorage<price_type, amount_type,
                     decltype(bestBuy),
                     std::allocator<price_amount_type>>
                m_bestBuyStorage;
        BestNStorage<price_type, amount_type,
                     decltype(bestSell),
                     std::allocator<price_amount_type>>
                m_bestSellStorage;
    };

    inline constexpr auto makeBuyOrder = [](const std::pair<Book::price_type, Book::amount_type> &pair) -> Order {
        return {
                .price = pair.first,
                .amount = pair.second,
                .type = Order::order_type::buy,
        };
    };

    inline constexpr auto makeSellOrder = [](const std::pair<Book::price_type, Book::amount_type> &pair) -> Order {
        return {
                .price = pair.first,
                .amount = pair.second,
                .type = Order::order_type::sell,
        };
    };

    template<typename OutputIteratorBuy, typename OutputIteratorSell>
    std::pair<OutputIteratorBuy, OutputIteratorSell> Book::ChooseBest(OutputIteratorBuy firstBuy, OutputIteratorSell firstSell) {
        auto proxyBuyIterator = OutputIteratorProxy<OutputIteratorBuy, decltype(makeBuyOrder), std::pair<Book::price_type, Book::amount_type>>{firstBuy};
        auto proxySellIterator = OutputIteratorProxy<OutputIteratorSell, decltype(makeSellOrder), std::pair<Book::price_type, Book::amount_type>>{firstSell};
        return {
                m_bestBuyStorage.GetBest(proxyBuyIterator),
                m_bestSellStorage.GetBest(proxySellIterator),
        };
    }

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_BOOK_H

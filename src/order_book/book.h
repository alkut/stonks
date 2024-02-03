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

#include "order_book/book-fwd.h"
#include "order_book/order.h"

#ifndef STONKS_BOOK_H
#define STONKS_BOOK_H

namespace STONKS_NAMESPACE {

    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    constexpr Book<TStorageBuy, TStorageSell>::Book(size_t buyBestCount, size_t sellBestCount) : m_bestBuyStorage(buyBestCount), m_bestSellStorage(sellBestCount) {}

    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    constexpr void Book<TStorageBuy, TStorageSell>::AddOrder(size_t price, size_t amount, Order::order_type type) {
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

    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    constexpr bool Book<TStorageBuy, TStorageSell>::ChangeOrder(size_t price, size_t newAmount, Order::order_type type) {
        switch (type) {
            case Order::order_type::buy:
                return m_bestBuyStorage.Change(price, newAmount).second;
            case Order::order_type::sell:
                return m_bestSellStorage.Change(price, newAmount).second;
        }
        STONKS_ASSERT(false, "unhandled order type");
        return false;
    }

    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    constexpr STONKS_ALWAYS_INLINE void Book<TStorageBuy, TStorageSell>::AddOrder(const Order &order) {
        AddOrder(order.price, order.amount, order.type);
    }

    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    constexpr STONKS_ALWAYS_INLINE bool Book<TStorageBuy, TStorageSell>::ChangeOrder(const Order &order) {
        return ChangeOrder(order.price, order.amount, order.type);
    }

    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    constexpr void Book<TStorageBuy, TStorageSell>::EraseOrder(size_t price, Order::order_type type) {
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

    // I hope, that would be inlined
    inline constexpr auto bestBuy = [](const price_type &lhs, const price_type &rhs) -> bool {
        return lhs < rhs;
    };

    // I hope, that would be inlined
    inline constexpr auto bestSell = [](const price_type &lhs, const price_type &rhs) -> bool {
        return lhs > rhs;
    };

    // I hope, that would be inlined
    inline constexpr auto makeBuyOrder = [](const price_amount_type &pair) -> Order {
        return {
                .price = pair.first,
                .amount = pair.second,
                .type = Order::order_type::buy,
        };
    };

    // I hope, that would be inlined
    inline constexpr auto makeSellOrder = [](const price_amount_type &pair) -> Order {
        return {
                .price = pair.first,
                .amount = pair.second,
                .type = Order::order_type::sell,
        };
    };

    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    template<OrderOutputIterator OutputIteratorBuy, OrderOutputIterator OutputIteratorSell>
    constexpr std::pair<OutputIteratorBuy, OutputIteratorSell> Book<TStorageBuy, TStorageSell>::ChooseBest(OutputIteratorBuy firstBuy, OutputIteratorSell firstSell) {
        auto proxyBuyIterator = OutputIteratorProxy<OutputIteratorBuy, decltype(makeBuyOrder), price_amount_type>{firstBuy};
        auto proxySellIterator = OutputIteratorProxy<OutputIteratorSell, decltype(makeSellOrder), price_amount_type>{firstSell};
        return {
                m_bestBuyStorage.GetBest(proxyBuyIterator),
                m_bestSellStorage.GetBest(proxySellIterator),
        };
    }

    using BaseBook = Book<BestNStorage<price_type, amount_type, decltype(bestBuy), std::allocator<price_amount_type>>,
                          BestNStorage<price_type, amount_type, decltype(bestSell), std::allocator<price_amount_type>>>;

    using BufferedBook = Book<BestNStorageBuffered<price_type, amount_type, decltype(bestBuy), std::allocator<price_amount_type>, STONKS_MAX_SSO_BUFFER_SIZE>,
                              BestNStorageBuffered<price_type, amount_type, decltype(bestSell), std::allocator<price_amount_type>, STONKS_MAX_SSO_BUFFER_SIZE>>;

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_BOOK_H

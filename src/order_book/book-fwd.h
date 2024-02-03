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

#ifndef STONKS_BOOK_FWD_H
#define STONKS_BOOK_FWD_H

#include "order_book/order-fwd.h"
#include "storage/bestNStorage.h"
#include "utils/proxy_output_iterator.h"
#include <concepts>

namespace STONKS_NAMESPACE {

    using price_type = FIELD_TYPE(Order, price);
    using amount_type = FIELD_TYPE(Order, amount);
    using price_amount_type = std::pair<const price_type, amount_type>;

    template<typename TStorage>
    concept ChooseBestStorage = std::constructible_from<TStorage, size_t> && requires(TStorage storage, price_type price, amount_type amount, price_amount_type pair) {
        { storage.GetBest((std::pair<price_type, amount_type> *) (nullptr)) } -> std::convertible_to<std::pair<price_type, amount_type> *>;
        { storage.Insert(pair).second } -> std::convertible_to<bool>;
        { storage.Emplace(price, amount).second } -> std::convertible_to<bool>;
        { storage.Erase(price) } -> std::convertible_to<size_t>;
        { storage.Change(pair).second } -> std::convertible_to<bool>;
        { storage.Change(price, amount).second } -> std::convertible_to<bool>;
    };

    template<typename TOutputIterator>
    concept OrderOutputIterator = std::output_iterator<TOutputIterator, Order>;

    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    class STONKS_API Book {
    public:
        constexpr Book(size_t buyBestCount, size_t sellBestCount);
        constexpr void AddOrder(price_type price, amount_type amount, Order::order_type type);
        constexpr bool ChangeOrder(price_type price, amount_type newAmount, Order::order_type type);
        constexpr void AddOrder(const Order &order);
        constexpr bool ChangeOrder(const Order &order);
        constexpr void EraseOrder(price_type price, Order::order_type type);
        template<OrderOutputIterator OutputIteratorBuy, OrderOutputIterator OutputIteratorSell>
        constexpr std::pair<OutputIteratorBuy, OutputIteratorSell> ChooseBest(OutputIteratorBuy firstBuy, OutputIteratorSell firstSell);

    private:
        TStorageBuy m_bestBuyStorage;
        TStorageSell m_bestSellStorage;
    };

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_BOOK_FWD_H

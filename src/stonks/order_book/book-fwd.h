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

#include "stonks/order_book/order-fwd.h"
#include "stonks/storage/bestNStorage.h"
#include "stonks/utils/proxy_output_iterator.h"
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
    concept OrderOutputIterator = requires(TOutputIterator iterator, const Order &order) {
        { *iterator++ = order };
    };

    /**
     * Generic class implementing order book. Allows creates orders, change it, remove and get best ones
     * @tparam TStorageBuy storage for buy orders. @see ChooseBestStorage concept
     * @tparam TStorageSell storage for sell orders. @see ChooseBestStorage concept
     */
    template<ChooseBestStorage TStorageBuy, ChooseBestStorage TStorageSell>
    class STONKS_API Book {
    public:
        /**
         *
         * @param buyBestCount Choose best buyBestCount buy orders
         * @param sellBestCount Choose best sellBestCount sell orders
         */
        constexpr Book(size_t buyBestCount, size_t sellBestCount);
        /**
         * If order with the same type and price exists, amounts added up
         * @param price price of new order
         * @param amount amount of new order
         * @param type type of new order (buy or sell)
         */
        constexpr void AddOrder(price_type price, amount_type amount, Order::order_type type);
        /**
         * If there is no order with the same type and price, order inserted
         * @param price price of the order
         * @param newAmount amount of the order
         * @param type type of the order (buy or sell)
         * @return True, if new was created. False if amount was overwritten
         */
        constexpr bool ChangeOrder(price_type price, amount_type newAmount, Order::order_type type);
        /**
         * If order with the same type and price exists, amounts added up
         * @param order same as AddOrder(price_type price, amount_type amount, Order::order_type type)
         */
        constexpr void AddOrder(const Order &order);
        /**
         * If there is no order with the same type and price, order inserted
         * @param order same as ChangeOrder(price_type price, amount_type newAmount, Order::order_type type)
         * @return True, if new was created. False if amount was overwritten
         */
        constexpr bool ChangeOrder(const Order &order);
        /**
         * Remove order. If order with following price and type doesn't exist, do nothing
         * @param price price of the order
         * @param type type of the order (buy or sell)
         */
        constexpr void EraseOrder(price_type price, Order::order_type type);
        /**
         * Get buyBestCount best buy orders and write it via firstBuy output iterator
         * Get sellBestCount best sell orders and write it via firstSell output iterator
         * @tparam OutputIteratorBuy output iterator fow writing best buy orders. @see OrderOutputIterator concept
         * @tparam OutputIteratorSell output iterator fow writing best sell orders. @see OrderOutputIterator concept
         * @param firstBuy output iterator fow writing best buy orders
         * @param firstSell output iterator fow writing best sell orders
         * @return pair of iterators right after last written elements
         */
        template<OrderOutputIterator OutputIteratorBuy, OrderOutputIterator OutputIteratorSell>
        constexpr std::pair<OutputIteratorBuy, OutputIteratorSell> ChooseBest(OutputIteratorBuy firstBuy, OutputIteratorSell firstSell);

    private:
        TStorageBuy m_bestBuyStorage;
        TStorageSell m_bestSellStorage;
    };

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_BOOK_FWD_H

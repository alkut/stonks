#include "order_book/book.h"
#include <benchmark/benchmark.h>

void DifferentPrices(benchmark::State &state) {
    static constexpr int countBuy = 5, countSell = 5;
    int countOrders = state.range(0);
    STONKS_NAMESPACE::Book book(countBuy, countSell);
    STONKS_NAMESPACE::Order ordersBuy[countBuy];
    STONKS_NAMESPACE::Order ordersSell[countSell];
    for (int i = 0; i < countOrders; ++i) {
        book.AddOrder(i, 1, STONKS_NAMESPACE::Order::order_type::buy);
        book.AddOrder(i, 1, STONKS_NAMESPACE::Order::order_type::sell);
    }
    for (auto _: state) {
        book.ChooseBest(ordersBuy, ordersSell);
        benchmark::ClobberMemory();
    }
}

void DifferentPricesX10(benchmark::State &state) {
    static constexpr int countBuy = 50, countSell = 50;
    int countOrders = state.range(0);
    STONKS_NAMESPACE::Book book(countBuy, countSell);
    STONKS_NAMESPACE::Order ordersBuy[countBuy];
    STONKS_NAMESPACE::Order ordersSell[countSell];
    for (int i = 0; i < countOrders; ++i) {
        book.AddOrder(i, 1, STONKS_NAMESPACE::Order::order_type::buy);
        book.AddOrder(i, 1, STONKS_NAMESPACE::Order::order_type::sell);
    }
    for (auto _: state) {
        book.ChooseBest(ordersBuy, ordersSell);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(DifferentPrices)->RangeMultiplier(2)->Range(1 << 2, 1 << 16);
BENCHMARK(DifferentPricesX10)->RangeMultiplier(2)->Range(1 << 2, 1 << 16);

BENCHMARK_MAIN();

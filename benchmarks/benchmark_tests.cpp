#include "order_book/book.h"
#include "order_book/book_tester.h"
#include <benchmark/benchmark.h>

namespace {

    void ChooseBest(benchmark::State &state) {
        static constexpr int countBuy = 5, countSell = 5;
        size_t countOrders = state.range(0);
        STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::Book> tester(countOrders, countBuy, countSell);
        for (auto _: state) {
            tester.BenchmarkChooseBest();
            benchmark::ClobberMemory();
        }
    }

    void ChooseBestX10(benchmark::State &state) {
        static constexpr int countBuy = 50, countSell = 50;
        size_t countOrders = state.range(0);
        STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::Book> tester(countOrders, countBuy, countSell);
        for (auto _: state) {
            tester.BenchmarkChooseBest();
            benchmark::ClobberMemory();
        }
    }

    void ChangeOrder(benchmark::State &state) {
        static constexpr int countBuy = 5, countSell = 5;
        size_t countOrders = state.range(0);
        STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::Book> tester(countOrders, countBuy, countSell);
        for (auto _: state) {
            tester.BenchmarkChangeOrder();
            benchmark::ClobberMemory();
        }
    }

    void AddEraseOrder(benchmark::State &state) {
        static constexpr int countBuy = 5, countSell = 5;
        size_t countOrders = state.range(0);
        STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::Book> tester(countOrders, countBuy, countSell);
        for (auto _: state) {
            tester.BenchmarkAddErase();
            benchmark::ClobberMemory();
        }
    }

}// namespace

BENCHMARK(ChooseBest)->RangeMultiplier(2)->Range(1 << 2, 1 << 16);
BENCHMARK(ChooseBestX10)->RangeMultiplier(2)->Range(1 << 2, 1 << 16);

BENCHMARK(ChangeOrder)->RangeMultiplier(2)->Range(1 << 2, 1 << 16);
BENCHMARK(AddEraseOrder)->RangeMultiplier(2)->Range(1 << 2, 1 << 16);

BENCHMARK_MAIN();

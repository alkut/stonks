#include "stonks/order_book/book.h"
#include "stonks/order_book/book_tester.h"
#include <benchmark/benchmark.h>

namespace {

    template<STONKS_NAMESPACE::BookImplementation BookImplementation>
    void ChooseBest(benchmark::State &state) {
        static constexpr int countBuy = 5, countSell = 5;
        size_t countOrders = state.range(0);
        STONKS_NAMESPACE::BookTester<BookImplementation> tester(countOrders, countBuy, countSell);
        for (auto _: state) {
            tester.BenchmarkChooseBest();
            benchmark::ClobberMemory();
        }
    }

    template<STONKS_NAMESPACE::BookImplementation BookImplementation>
    void ChooseBestX10(benchmark::State &state) {
        static constexpr int countBuy = 50, countSell = 50;
        size_t countOrders = state.range(0);
        STONKS_NAMESPACE::BookTester<BookImplementation> tester(countOrders, countBuy, countSell);
        for (auto _: state) {
            tester.BenchmarkChooseBest();
            benchmark::ClobberMemory();
        }
    }

    template<STONKS_NAMESPACE::BookImplementation BookImplementation>
    void ChangeOrder(benchmark::State &state) {
        static constexpr int countBuy = 5, countSell = 5;
        size_t countOrders = state.range(0);
        STONKS_NAMESPACE::BookTester<BookImplementation> tester(countOrders, countBuy, countSell);
        for (auto _: state) {
            tester.BenchmarkChangeOrder();
            benchmark::ClobberMemory();
        }
    }

    template<STONKS_NAMESPACE::BookImplementation BookImplementation>
    void AddEraseOrder(benchmark::State &state) {
        static constexpr int countBuy = 5, countSell = 5;
        size_t countOrders = state.range(0);
        STONKS_NAMESPACE::BookTester<BookImplementation> tester(countOrders, countBuy, countSell);
        for (auto _: state) {
            tester.BenchmarkAddErase();
            benchmark::ClobberMemory();
        }
    }

}// namespace

namespace details {
    /**
     * Don't forget register all book implementation -> benchmark name mapping
     * @tparam BookImplementation
     * @return string literal, name of benchmark parametrized by following template parameter
     */
    template<STONKS_NAMESPACE::BookImplementation BookImplementation>
    consteval const char *GetName();

    template<>
    consteval const char *GetName<STONKS_NAMESPACE::BaseBook>() {
        return "BaseBook";
    }

    template<>
    consteval const char *GetName<STONKS_NAMESPACE::BufferedBook>() {
        return "BufferedBook";
    }
}// namespace details

/**
 * Helper to register all benchmarks
 */
template<typename T>
struct RegisterBenchmarkHelper {};

template<STONKS_NAMESPACE::BookImplementation... BookImplementations>
struct RegisterBenchmarkHelper<std::tuple<BookImplementations...>> {
    static void RegisterBenchmarks() {
        (benchmark::RegisterBenchmark(std::string{"ChooseBest/"} += details::GetName<BookImplementations>(),
                                      ChooseBest<BookImplementations>)
                 ->RangeMultiplier(2)
                 ->Range(1 << 2, 1 << 10),
         ...);

        (benchmark::RegisterBenchmark(std::string{"ChooseBestX10/"} += details::GetName<BookImplementations>(),
                                      ChooseBestX10<BookImplementations>)
                 ->RangeMultiplier(2)
                 ->Range(1 << 2, 1 << 10),
         ...);

        (benchmark::RegisterBenchmark(std::string{"ChangeOrder/"} += details::GetName<BookImplementations>(),
                                      ChangeOrder<BookImplementations>)
                 ->RangeMultiplier(2)
                 ->Range(1 << 2, 1 << 10),
         ...);

        (benchmark::RegisterBenchmark(std::string{"AddEraseOrder/"} += details::GetName<BookImplementations>(),
                                      AddEraseOrder<BookImplementations>)
                 ->RangeMultiplier(2)
                 ->Range(1 << 2, 1 << 10),
         ...);
    }
};

/**
 * define here all implementations to benchmark
 */
using BookImplementations = std::tuple<STONKS_NAMESPACE::BaseBook, STONKS_NAMESPACE::BufferedBook>;

bool _ = []() {
    RegisterBenchmarkHelper<BookImplementations>::RegisterBenchmarks();
    return false;
}();

BENCHMARK_MAIN();

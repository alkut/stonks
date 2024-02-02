#include "order_book/book.h"
#include <gtest/gtest.h>

TEST(manual, different_prices) {
    static constexpr int countBuy = 3, countSell = 2, countOrders = (countBuy + countSell) * 2;
    STONKS_NAMESPACE::Book book(countBuy, countSell);
    STONKS_NAMESPACE::Order ordersBuy[countBuy];
    STONKS_NAMESPACE::Order ordersSell[countSell];
    for (int i = 0; i < countOrders; ++i) {
        book.AddOrder(i, 1, STONKS_NAMESPACE::Order::order_type::buy);
        book.AddOrder(i, 1, STONKS_NAMESPACE::Order::order_type::sell);
    }
    book.ChooseBest(ordersBuy, ordersSell);
    for (int i = 0; i < countBuy; ++i) {
        ASSERT_EQ(ordersBuy[i].price, i);
    }
    for (int i = 0; i < countSell; ++i) {
        ASSERT_EQ(ordersSell[i].price, countOrders - 1 - i);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

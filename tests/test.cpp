#include "order_book/book.h"
#include "order_book/book_tester.h"
#include <gtest/gtest.h>

TEST(erase, non_exist) {
    ASSERT_TRUE(STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::Book>::TestEraseNonExistingOrder());
}

TEST(choose_best, small_book) {
    ASSERT_TRUE(STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::Book>::TestChooseBestSmallBook());
}

TEST(change_order, non_exist) {
    ASSERT_TRUE(STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::Book>::TestChangeNonExistingOrder());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

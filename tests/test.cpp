#include "order_book/book.h"
#include "order_book/book_tester.h"
#include <gtest/gtest.h>

using BookImplementationsTesters = ::testing::Types<STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::BaseBook>,
                                                    STONKS_NAMESPACE::BookTester<STONKS_NAMESPACE::BufferedBook>>;

template<typename TBookTester>
class EraseTest : public ::testing::Test {};

TYPED_TEST_SUITE(EraseTest, BookImplementationsTesters);

TYPED_TEST(EraseTest, EraseNonExist) {
    ASSERT_TRUE(TypeParam::TestEraseNonExistingOrder());
}

template<typename TBookTester>
class ChooseBestTest : public ::testing::Test {};

TYPED_TEST_SUITE(ChooseBestTest, BookImplementationsTesters);

TYPED_TEST(ChooseBestTest, SmallBook) {
    ASSERT_TRUE(TypeParam::TestEraseNonExistingOrder());
}

template<typename TBookTester>
class ChangeOrderTest : public ::testing::Test {};

TYPED_TEST_SUITE(ChangeOrderTest, BookImplementationsTesters);

TYPED_TEST(ChangeOrderTest, ChangeOrderNonExist) {
    ASSERT_TRUE(TypeParam::TestEraseNonExistingOrder());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

include(GNUInstallDirs)

project(
        order_book_lib
        LANGUAGES CXX
        DESCRIPTION "main lib for whole project"
        VERSION 1.0.1
        HOMEPAGE_URL https://alkut.github.io/stonks/)

set(order_book_lib_headers
        stonks/order_book/book-fwd.h
        stonks/order_book/order-fwd.h
        stonks/order_book/book_tester-fwd.h
        stonks/order_book/book_tester.h
        stonks/order_book/book.h
        stonks/order_book/order.h
        stonks/storage/bestNStorage.h
        stonks/storage/bestNStorage-fwd.h
        stonks/utils/proxy_output_iterator-fwd.h
        stonks/utils/proxy_output_iterator.h)

set(order_book_lib_headers___order_book
        stonks/order_book/book-fwd.h
        stonks/order_book/order-fwd.h
        stonks/order_book/book_tester-fwd.h
        stonks/order_book/book_tester.h
        stonks/order_book/book.h
        stonks/order_book/order.h
)

set(order_book_lib_headers___storage
        stonks/storage/bestNStorage.h
        stonks/storage/bestNStorage-fwd.h
)

set(order_book_lib_headers___utils
        stonks/utils/proxy_output_iterator-fwd.h
        stonks/utils/proxy_output_iterator.h
        stonks/utils/defines.h
)

add_library(order_book_lib_headers INTERFACE ${order_book_lib_headers})

if (${STONKS_ENABLE_DYNAMIC_LIBS})
    target_compile_definitions(order_book_lib PRIVATE STONKS_DYNAMIC_LIB)
endif ()

if (${STONKS_ENABLE_INSTALL})
    include(../cmake/ConfigureInstallation.cmake)
endif ()

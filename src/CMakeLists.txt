include(GNUInstallDirs)

project(
  order_book_lib
  LANGUAGES CXX
  DESCRIPTION "main lib for whole project")

set(order_book_lib_headers
    order_book/book-fwd.h
    order_book/order-fwd.h
    order_book/book_tester-fwd.h
    order_book/book_tester.h
    order_book/book.h
    order_book/order.h
    storage/bestNStorage.h
    storage/bestNStorage-fwd.h
    utils/proxy_output_iterator-fwd.h
    utils/proxy_output_iterator.h)

set(order_book_lib_sources order_book/tmp.cpp)

add_library(order_book_lib STATIC ${order_book_lib_headers} ${order_book_lib_sources})

add_library(stonks::order_book ALIAS order_book_lib)

target_include_directories(order_book_lib PRIVATE ${PROJECT_SOURCE_DIR})

if(${STONKS_ENABLE_DYNAMIC_LIBS})
  target_compile_definitions(order_book_lib PRIVATE STONKS_DYNAMIC_LIB)
endif()

if(${STONKS_ENABLE_INSTALL})
  install(
    TARGETS order_book_lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/stonks"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES ${order_book_lib_headers})
endif()

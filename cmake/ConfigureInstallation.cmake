install(FILES ${order_book_lib_headers___order_book} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/stonks/order_book)

install(FILES ${order_book_lib_headers___storage} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/stonks/storage)
install(FILES ${order_book_lib_headers___utils} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/stonks/utils)

install(FILES "${CMAKE_SOURCE_DIR}/src/defines.h" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
configure_package_config_file("${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/StonksConfig.cmake" INSTALL_DESTINATION lib/cmake/Stonks)

write_basic_package_version_file(
        "StonksConfigVersion.cmake"
        VERSION ${order_book_lib_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/StonksConfig.cmake" DESTINATION lib/cmake/Stonks)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/StonksConfigVersion.cmake" DESTINATION lib/cmake/Stonks)

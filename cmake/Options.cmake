option(STONKS_ENABLE_INSTALL "required for cmake --install working correctly" OFF)

option(STONKS_ENABLE_TESTS "required for ctest working correctly" OFF)

option(STONKS_ENABLE_EXAMPLES "build examples" OFF)

option(STONKS_ENABLE_BENCHMARKS "enable benchmark target" OFF)

option(STONKS_ENABLE_DOCS "enable doxygen docs" OFF)

option(STONKS_ENABLE_CCACHE "enable Ccache" OFF)

option(STONKS_ENABLE_DYNAMIC_LIBS "use dynamic libs instead of static" OFF)

option(STONKS_RUN_ON_CI "used for ci/cd" OFF)

option(STONKS_BINARY_IN_BUILD "store build artifact inside temp folder" OFF)

option(STONKS_SANITIZE "memory sanitizer" OFF)

include(CMakeDependentOption)

cmake_dependent_option(
        STONKS_UBSan
        "UB Sanitizer"
        ON
        "STONKS_SANITIZE"
        OFF)

cmake_dependent_option(
        STONKS_ASan
        "Address Sanitizer"
        ON
        "STONKS_SANITIZE"
        OFF)

cmake_dependent_option(
        STONKS_TSan
        "Thread Sanitizer"
        ON
        "STONKS_SANITIZE"
        OFF)

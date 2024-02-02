set(CCACHE_BINARY ccache)

find_program(CCACHE_FOUND ${CCACHE_BINARY})
if (${CCACHE_FOUND})
    message(STATUS "Ccache found successfully")
    set(CMAKE_C_COMPILER_LAUNCHER
            ${CCACHE_BINARY}
            CACHE FILEPATH "CXX compiler cache used")
    set(CMAKE_CXX_COMPILER_LAUNCHER
            ${CCACHE_BINARY}
            CACHE FILEPATH "C compiler cache used")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_BINARY})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_BINARY})
else ()
    message(WARNING "Couldn't find Ccache - it disabled")
endif (${CCACHE_FOUND})

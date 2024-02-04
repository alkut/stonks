if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

    if (${STONKS_UBSan})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    endif ()

    if (${STONKS_ASan})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    endif ()

    if (${STONKS_TSan})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    endif ()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    if (${STONKS_UBSan})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    endif ()

    if (${STONKS_ASan})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    endif ()

    if (${STONKS_TSan})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
    endif ()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")

    if (${STONKS_UBSan})
        message(SEND_ERROR "not implemented")
    endif ()

    if (${STONKS_ASan})
        message(SEND_ERROR "not implemented")
    endif ()

    if (${STONKS_TSan})
        message(SEND_ERROR "not implemented")
    endif ()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

    if (${STONKS_UBSan})
        message(SEND_ERROR "not implemented")
    endif ()

    if (${STONKS_ASan})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fsanitize=address")
    endif ()

    if (${STONKS_TSan})
        message(SEND_ERROR "not implemented")
    endif ()

endif ()

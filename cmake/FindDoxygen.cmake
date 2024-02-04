set(STONKS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(STONKS_DOCS_VERSION ${order_book_lib_VERSION})
set(STONKS_DOCS_ROOT ${STONKS_ROOT}/docs)
set(STONKS_DOCS_DOXYGEN_IN ${STONKS_DOCS_ROOT}/Doxyfile.in)
set(STONKS_DOCS_DOXYGEN_OUT ${STONKS_DOCS_ROOT}/Doxyfile)

configure_file(${STONKS_DOCS_DOXYGEN_IN} ${STONKS_DOCS_DOXYGEN_OUT} @ONLY)

find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile.out)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(
            docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

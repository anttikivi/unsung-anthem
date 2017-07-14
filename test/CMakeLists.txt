add_subdirectory(std)

set(ANTHEM_TEST_SOURCES ${ANTHEM_TEST_SOURCES}

    ${CMAKE_CURRENT_SOURCE_DIR}/arguments_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp

    PARENT_SCOPE)

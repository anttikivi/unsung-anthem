add_subdirectory(functor)
add_subdirectory(internal)

set(ANTHEM_LIB_INCLUDES ${ANTHEM_LIB_INCLUDES}

    ${CMAKE_CURRENT_SOURCE_DIR}/fmap.h
    ${CMAKE_CURRENT_SOURCE_DIR}/macro_config.h

    PARENT_SCOPE)

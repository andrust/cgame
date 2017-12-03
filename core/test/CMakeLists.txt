set(TESTBIN test_ulti_core)
include_directories(..)

add_executable(${TESTBIN}
    TestCard.cc
    TestDeck.cc
)

target_link_libraries(${TESTBIN}
    ulti_core
    gmock
    gmock_main
)

add_test(${TESTBIN} ${CMAKE_CURRENT_BINARY_DIR}/${TESTBIN})

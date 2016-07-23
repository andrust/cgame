set(TESTBIN test_ulti_core)
include_directories(..)

add_executable(${TESTBIN}
    TestMain.cc
    TestCard.cc
    TestDeck.cc
)

target_link_libraries(${TESTBIN}
    ulti_core
    boost_unit_test_framework
)

add_test(${TESTBIN} ${CMAKE_CURRENT_BINARY_DIR}/${TESTBIN})

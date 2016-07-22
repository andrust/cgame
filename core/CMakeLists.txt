add_library(ulti_core SHARED
    Card.cc
    Card.h
    CardComparison.cc
    CardComparison.h
    CardProperties.h
    Deck.cc
    Deck.h
)

add_subdirectory(test)

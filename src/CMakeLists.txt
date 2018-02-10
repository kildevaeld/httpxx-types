
set(SOURCES
    header.cpp
    request.cpp
    url.cpp
)

add_library(httpxx_types ${SOURCES})
target_link_libraries(httpxx_types http_parser)
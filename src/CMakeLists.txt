
set(SOURCES
    header.cpp
    url.cpp
)

add_library(httpxx_types ${SOURCES})
target_link_libraries(httpxx_types http_parser)
target_include_directories(httpxx_types PUBLIC ${PROJECT_SOURCE_DIR}/vendor/http-parser)
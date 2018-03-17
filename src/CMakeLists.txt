
set(SOURCES
    header.cpp
    url.cpp
    status-codes.cpp
)

add_library(httpxx_types ${SOURCES})

target_link_libraries(httpxx_types ${HTTP_PARSER_LIBRARIES})

target_include_directories(httpxx_types PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>  # <prefix>/include/mylib
    $<BUILD_INTERFACE:${HTTP_PARSER_INCLUDE_DIRS}>
    #${PROJECT_SOURCE_DIR}/include
    #${HTTP_PARSER_INCLUDE_DIRS}
)
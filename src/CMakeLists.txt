
set(SOURCES
    header.cpp
    url.cpp
    methods.cpp
    request.cpp
    status-codes.cpp
    methods.cpp
)

add_library(httptypes++ ${SOURCES})

target_link_libraries(httptypes++ ${HTTP_PARSER_LIBRARIES} ${STREAMS_CPP_LIBRARIES})

target_include_directories(httptypes++ PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HTTP_PARSER_INCLUDE_DIRS}>
)
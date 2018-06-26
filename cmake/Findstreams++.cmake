

find_package(PkgConfig)
pkg_check_modules(PC_STREAMS_CPP QUIET http_parser)

find_path(STREAMS_CPP_INCLUDE_DIR csystem.h
          HINTS ${PC_STREAMS_CPP_INCLUDEDIR} ${PC_STREAMS_CPP_INCLUDE_DIRS}
          PATH_SUFFIXES csystem)

find_library(STREAMS_CPP_LIBRARY NAMES csystem STREAMS_CPPcrypto
             HINTS ${PC_STREAMS_CPP_LIBDIR} ${PC_STREAMS_CPP_LIBRARY_DIRS} )

#include(FindPackageHandleStandardArgs)
#                      STREAMS_CPP_LIBRARY STREAMS_CPP_INCLUDE_DIR)

if(NOT STREAMS_CPP_LIBRARY)
    add_subdirectory(vendor/streamscpp)
    
    #add_library(http_parser ${PROJECT_SOURCE_DIR}/vendor/http-parser/http_parser.c)
    set(STREAMS_CPP_LIBRARY streams++)
    set(STREAMS_CPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/streamscpp/include)
    set(STREAMS_CPP_FOUND on)
    message(STATUS "Using local streams++")
else()
    message(STATUS "Using system streams++")
    set(STREAMS_CPP_FOUND on)
endif(NOT STREAMS_CPP_LIBRARY)

mark_as_advanced(STREAMS_CPP_INCLUDE_DIR STREAMS_CPP_LIBRARY)

set(STREAMS_CPP_LIBRARIES ${STREAMS_CPP_LIBRARY} )
set(STREAMS_CPP_INCLUDE_DIRS ${STREAMS_CPP_INCLUDE_DIR})
# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  HTTP_PARSER_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_package(PkgConfig)
pkg_check_modules(PC_HTTP_PARSER QUIET http_parser)
#set(MBEDTLS_DEFINITIONS ${PC_HTTP_PARSER_CFLAGS_OTHER})

find_path(HTTP_PARSER_INCLUDE_DIR csystem.h
          HINTS ${PC_HTTP_PARSER_INCLUDEDIR} ${PC_HTTP_PARSER_INCLUDE_DIRS}
          PATH_SUFFIXES csystem)

find_library(HTTP_PARSER_LIBRARY NAMES csystem HTTP_PARSER_crypto
             HINTS ${PC_HTTP_PARSER_LIBDIR} ${PC_HTTP_PARSER_LIBRARY_DIRS} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
##find_package_handle_standard_args(CSYSTEM ""
  ##                                HTTP_PARSER_LIBRARY HTTP_PARSER_INCLUDE_DIR)

if(NOT HTTP_PARSER_LIBRARY)
    #option(CS_BUILD_CRYPTO "" on)
    #add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/http)
    #include_directories(${PROJECT_SOURCE_DIR}/vendor/csystem/include)
    add_library(http_parser ${PROJECT_SOURCE_DIR}/vendor/http-parser/http_parser.c)
    set(HTTP_PARSER_LIBRARY http_parser)
    set(HTTP_PARSER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/http-parser)
    set(HTTP_PARSER_FOUND on)
    message(STATUS "Using local http_parser")
else()
    message(STATUS "Found http_parser")
    set(HTTP_PARSER_FOUND on)
endif(NOT HTTP_PARSER_LIBRARY)

mark_as_advanced(HTTP_PARSER_INCLUDE_DIR HTTP_PARSER_LIBRARY)

set(HTTP_PARSER_LIBRARIES ${HTTP_PARSER_LIBRARY} )
set(HTTP_PARSER_INCLUDE_DIRS ${HTTP_PARSER_INCLUDE_DIR})
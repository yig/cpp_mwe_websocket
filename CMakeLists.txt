cmake_minimum_required(VERSION 3.12...3.25)
project(
    Curve
    LANGUAGES CXX C
)

## Set a global C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## Load packages
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    LibDataChannel
    GIT_REPOSITORY https://github.com/paullouisageneau/libdatachannel
    GIT_TAG v0.21.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    )
set(NO_EXAMPLES ON CACHE BOOL "" FORCE)
set(NO_TESTS ON CACHE BOOL "" FORCE)
set(NO_MEDIA ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable( LibDataChannel )

## Declare the http server executable
add_executable( echo src/echo.cpp )
target_link_libraries( echo
    PRIVATE
        LibDataChannel::LibDataChannel
)

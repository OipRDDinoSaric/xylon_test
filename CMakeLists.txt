cmake_minimum_required(VERSION 3.17.3)
project(XylonTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(XylonTest)

target_sources(XylonTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Scheduler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/SystemTimer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Timer.cpp)

target_include_directories(XylonTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(XylonTest PRIVATE
        -Wall -Wextra -Wconversion -Wpedantic -O0 -g3)

set(CPM_DOWNLOAD_VERSION "v0.40.0")
include(./cmake/install_cpm_if_not_available.cmake)
unset(CPM_DOWNLOAD_VERSION)

include(./cmake/install_cpm_packages.cmake)

target_link_libraries(XylonTest PRIVATE
        fmt::fmt)
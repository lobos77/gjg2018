cmake_minimum_required(VERSION 3.9)
project(server)

set(CMAKE_CXX_STANDARD 11)
set(Boost_USE_MULTITHREADED      ON)

find_package(Threads REQUIRED)
find_package( Boost REQUIRED filesystem system thread)

include_directories(
        ${BOOST_INCLUDE_DIRS}
)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
else()
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
endif()

add_executable(server main.cpp)
target_link_libraries(server ${Boost_LIBRARIES} Threads::Threads)
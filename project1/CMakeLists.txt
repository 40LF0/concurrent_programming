cmake_minimum_required (VERSION 2.6)
project (Sig18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_C_COMPILER /usr/local/bin/gcc)
# set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address -Wall" )
set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(include)



add_library(database Relation.cpp Operators.cpp Parser.cpp Utils.cpp Joiner.cpp)
target_include_directories(database PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

OPTION(FORCE_TESTS "Build tests, regardless of build type." ON)
if (CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]" OR FORCE_TESTS)
    add_subdirectory(test)
endif()

find_package(Threads REQUIRED)

add_executable(Driver main.cpp)
target_link_libraries(Driver database Threads::Threads)

# Interactive command line tool to translate our query format to SQL queries
add_executable(Query2SQL Query2SQL.cpp)
target_link_libraries(Query2SQL database Threads::Threads)

# Test harness
add_executable(harness harness.cpp)

ADD_CUSTOM_TARGET(link_target ALL
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/workloads
  ${CMAKE_CURRENT_BINARY_DIR}/workloads)

cmake_minimum_required(VERSION 3.17)

project(atomic_snap_shot VERSION 1.0.0)

include(CTest)

# C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Options for libraries
option(USE_CP "Use the CP library" ON)
option(USE_GOOGLE_TEST "Use GoogleTest for testing" ON)

# DB project library
if(USE_CP)
  add_subdirectory(cp)
  list(APPEND EXTRA_LIBS cp)
endif()

# GoogleTest
if(USE_GOOGLE_TEST)
  add_subdirectory(test)
endif()

add_executable(${CMAKE_PROJECT_NAME} main.cc)

target_link_libraries(${CMAKE_PROJECT_NAME} 
	PUBLIC ${EXTRA_LIBS}
	PUBLIC cp
	PUBLIC Threads::Threads)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
  )


# GoogleTest

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e4717df71a4f45bf9f0ac88c6cd9846a0bc248dd.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(DB_TESTS
  #file_test.cc
  #basic_test.cc
  atomic_snapshot_test.cc
  # Add your test files here
  # foo/bar/your_test.cc
  )

add_executable(google_test ${DB_TESTS})

target_link_libraries(
  google_test
  cp
  gtest_main
  Threads::Threads
  )

include(GoogleTest)
gtest_discover_tests(google_test)


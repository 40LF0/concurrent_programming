# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build

# Include any dependencies generated for this target.
include test/CMakeFiles/google_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/google_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/google_test.dir/flags.make

test/CMakeFiles/google_test.dir/file_test.cc.o: test/CMakeFiles/google_test.dir/flags.make
test/CMakeFiles/google_test.dir/file_test.cc.o: ../test/file_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/google_test.dir/file_test.cc.o"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/google_test.dir/file_test.cc.o -c /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/file_test.cc

test/CMakeFiles/google_test.dir/file_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/google_test.dir/file_test.cc.i"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/file_test.cc > CMakeFiles/google_test.dir/file_test.cc.i

test/CMakeFiles/google_test.dir/file_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/google_test.dir/file_test.cc.s"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/file_test.cc -o CMakeFiles/google_test.dir/file_test.cc.s

test/CMakeFiles/google_test.dir/basic_test.cc.o: test/CMakeFiles/google_test.dir/flags.make
test/CMakeFiles/google_test.dir/basic_test.cc.o: ../test/basic_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/google_test.dir/basic_test.cc.o"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/google_test.dir/basic_test.cc.o -c /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/basic_test.cc

test/CMakeFiles/google_test.dir/basic_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/google_test.dir/basic_test.cc.i"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/basic_test.cc > CMakeFiles/google_test.dir/basic_test.cc.i

test/CMakeFiles/google_test.dir/basic_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/google_test.dir/basic_test.cc.s"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/basic_test.cc -o CMakeFiles/google_test.dir/basic_test.cc.s

test/CMakeFiles/google_test.dir/atomic_snapshot_test.cc.o: test/CMakeFiles/google_test.dir/flags.make
test/CMakeFiles/google_test.dir/atomic_snapshot_test.cc.o: ../test/atomic_snapshot_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/google_test.dir/atomic_snapshot_test.cc.o"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/google_test.dir/atomic_snapshot_test.cc.o -c /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/atomic_snapshot_test.cc

test/CMakeFiles/google_test.dir/atomic_snapshot_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/google_test.dir/atomic_snapshot_test.cc.i"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/atomic_snapshot_test.cc > CMakeFiles/google_test.dir/atomic_snapshot_test.cc.i

test/CMakeFiles/google_test.dir/atomic_snapshot_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/google_test.dir/atomic_snapshot_test.cc.s"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test/atomic_snapshot_test.cc -o CMakeFiles/google_test.dir/atomic_snapshot_test.cc.s

# Object files for target google_test
google_test_OBJECTS = \
"CMakeFiles/google_test.dir/file_test.cc.o" \
"CMakeFiles/google_test.dir/basic_test.cc.o" \
"CMakeFiles/google_test.dir/atomic_snapshot_test.cc.o"

# External object files for target google_test
google_test_EXTERNAL_OBJECTS =

bin/google_test: test/CMakeFiles/google_test.dir/file_test.cc.o
bin/google_test: test/CMakeFiles/google_test.dir/basic_test.cc.o
bin/google_test: test/CMakeFiles/google_test.dir/atomic_snapshot_test.cc.o
bin/google_test: test/CMakeFiles/google_test.dir/build.make
bin/google_test: lib/libcp.a
bin/google_test: lib/libgtest_main.a
bin/google_test: lib/libgtest.a
bin/google_test: test/CMakeFiles/google_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/google_test"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/google_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && /usr/local/bin/cmake -D TEST_TARGET=google_test -D TEST_EXECUTABLE=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/bin/google_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=google_test_TESTS -D CTEST_FILE=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test/google_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -P /usr/local/share/cmake-3.17/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
test/CMakeFiles/google_test.dir/build: bin/google_test

.PHONY : test/CMakeFiles/google_test.dir/build

test/CMakeFiles/google_test.dir/clean:
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test && $(CMAKE_COMMAND) -P CMakeFiles/google_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/google_test.dir/clean

test/CMakeFiles/google_test.dir/depend:
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2 /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/test /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/build/test/CMakeFiles/google_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/google_test.dir/depend


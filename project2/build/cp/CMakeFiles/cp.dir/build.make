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
CMAKE_SOURCE_DIR = /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build

# Include any dependencies generated for this target.
include cp/CMakeFiles/cp.dir/depend.make

# Include the progress variables for this target.
include cp/CMakeFiles/cp.dir/progress.make

# Include the compile flags for this target's objects.
include cp/CMakeFiles/cp.dir/flags.make

cp/CMakeFiles/cp.dir/src/bpt.cc.o: cp/CMakeFiles/cp.dir/flags.make
cp/CMakeFiles/cp.dir/src/bpt.cc.o: ../cp/src/bpt.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object cp/CMakeFiles/cp.dir/src/bpt.cc.o"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cp.dir/src/bpt.cc.o -c /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/cp/src/bpt.cc

cp/CMakeFiles/cp.dir/src/bpt.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/bpt.cc.i"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/cp/src/bpt.cc > CMakeFiles/cp.dir/src/bpt.cc.i

cp/CMakeFiles/cp.dir/src/bpt.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/bpt.cc.s"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/cp/src/bpt.cc -o CMakeFiles/cp.dir/src/bpt.cc.s

cp/CMakeFiles/cp.dir/src/file.cc.o: cp/CMakeFiles/cp.dir/flags.make
cp/CMakeFiles/cp.dir/src/file.cc.o: ../cp/src/file.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object cp/CMakeFiles/cp.dir/src/file.cc.o"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cp.dir/src/file.cc.o -c /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/cp/src/file.cc

cp/CMakeFiles/cp.dir/src/file.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cp.dir/src/file.cc.i"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/cp/src/file.cc > CMakeFiles/cp.dir/src/file.cc.i

cp/CMakeFiles/cp.dir/src/file.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cp.dir/src/file.cc.s"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/cp/src/file.cc -o CMakeFiles/cp.dir/src/file.cc.s

# Object files for target cp
cp_OBJECTS = \
"CMakeFiles/cp.dir/src/bpt.cc.o" \
"CMakeFiles/cp.dir/src/file.cc.o"

# External object files for target cp
cp_EXTERNAL_OBJECTS =

lib/libcp.a: cp/CMakeFiles/cp.dir/src/bpt.cc.o
lib/libcp.a: cp/CMakeFiles/cp.dir/src/file.cc.o
lib/libcp.a: cp/CMakeFiles/cp.dir/build.make
lib/libcp.a: cp/CMakeFiles/cp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library ../lib/libcp.a"
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && $(CMAKE_COMMAND) -P CMakeFiles/cp.dir/cmake_clean_target.cmake
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cp/CMakeFiles/cp.dir/build: lib/libcp.a

.PHONY : cp/CMakeFiles/cp.dir/build

cp/CMakeFiles/cp.dir/clean:
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp && $(CMAKE_COMMAND) -P CMakeFiles/cp.dir/cmake_clean.cmake
.PHONY : cp/CMakeFiles/cp.dir/clean

cp/CMakeFiles/cp.dir/depend:
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/cp /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/project2/db_project/build/cp/CMakeFiles/cp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cp/CMakeFiles/cp.dir/depend

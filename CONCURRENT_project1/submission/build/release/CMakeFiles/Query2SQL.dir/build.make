# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/build/release

# Include any dependencies generated for this target.
include CMakeFiles/Query2SQL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Query2SQL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Query2SQL.dir/flags.make

CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o: CMakeFiles/Query2SQL.dir/flags.make
CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o: ../../Query2SQL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o -c /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/Query2SQL.cpp

CMakeFiles/Query2SQL.dir/Query2SQL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Query2SQL.dir/Query2SQL.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/Query2SQL.cpp > CMakeFiles/Query2SQL.dir/Query2SQL.cpp.i

CMakeFiles/Query2SQL.dir/Query2SQL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Query2SQL.dir/Query2SQL.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/Query2SQL.cpp -o CMakeFiles/Query2SQL.dir/Query2SQL.cpp.s

CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o.requires:

.PHONY : CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o.requires

CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o.provides: CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o.requires
	$(MAKE) -f CMakeFiles/Query2SQL.dir/build.make CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o.provides.build
.PHONY : CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o.provides

CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o.provides.build: CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o


# Object files for target Query2SQL
Query2SQL_OBJECTS = \
"CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o"

# External object files for target Query2SQL
Query2SQL_EXTERNAL_OBJECTS =

Query2SQL: CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o
Query2SQL: CMakeFiles/Query2SQL.dir/build.make
Query2SQL: libdatabase.a
Query2SQL: CMakeFiles/Query2SQL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Query2SQL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Query2SQL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Query2SQL.dir/build: Query2SQL

.PHONY : CMakeFiles/Query2SQL.dir/build

CMakeFiles/Query2SQL.dir/requires: CMakeFiles/Query2SQL.dir/Query2SQL.cpp.o.requires

.PHONY : CMakeFiles/Query2SQL.dir/requires

CMakeFiles/Query2SQL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Query2SQL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Query2SQL.dir/clean

CMakeFiles/Query2SQL.dir/depend:
	cd /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/build/release /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/build/release /home/seungyeon/CONCURRENT_PROGRAMING/2022_ite4065_2019082851/CONCURRENT_project1/submission/build/release/CMakeFiles/Query2SQL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Query2SQL.dir/depend


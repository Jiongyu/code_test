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
CMAKE_COMMAND = /home/tan/software/cmake-3.17.0/bin/cmake

# The command to remove a file.
RM = /home/tan/software/cmake-3.17.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tan/Documents/code_exercise/code_test/gdb_test/cmakelist_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tan/Documents/code_exercise/code_test/gdb_test/cmakelist_test/build

# Utility rule file for NightlySubmit.

# Include the progress variables for this target.
include CMakeFiles/NightlySubmit.dir/progress.make

CMakeFiles/NightlySubmit:
	/home/tan/software/cmake-3.17.0/bin/ctest -D NightlySubmit

NightlySubmit: CMakeFiles/NightlySubmit
NightlySubmit: CMakeFiles/NightlySubmit.dir/build.make

.PHONY : NightlySubmit

# Rule to build all files generated by this target.
CMakeFiles/NightlySubmit.dir/build: NightlySubmit

.PHONY : CMakeFiles/NightlySubmit.dir/build

CMakeFiles/NightlySubmit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NightlySubmit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NightlySubmit.dir/clean

CMakeFiles/NightlySubmit.dir/depend:
	cd /home/tan/Documents/code_exercise/code_test/gdb_test/cmakelist_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tan/Documents/code_exercise/code_test/gdb_test/cmakelist_test /home/tan/Documents/code_exercise/code_test/gdb_test/cmakelist_test /home/tan/Documents/code_exercise/code_test/gdb_test/cmakelist_test/build /home/tan/Documents/code_exercise/code_test/gdb_test/cmakelist_test/build /home/tan/Documents/code_exercise/code_test/gdb_test/cmakelist_test/build/CMakeFiles/NightlySubmit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NightlySubmit.dir/depend


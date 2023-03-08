# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /srv/_applications_/intellij/clion/clion-2022.2.4/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /srv/_applications_/intellij/clion/clion-2022.2.4/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /srv/workspace/public/game-engine-sdl-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /srv/workspace/public/game-engine-sdl-cpp

# Include any dependencies generated for this target.
include include/sol/CMakeFiles/sol.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include include/sol/CMakeFiles/sol.dir/compiler_depend.make

# Include the progress variables for this target.
include include/sol/CMakeFiles/sol.dir/progress.make

# Include the compile flags for this target's objects.
include include/sol/CMakeFiles/sol.dir/flags.make

# Object files for target sol
sol_OBJECTS =

# External object files for target sol
sol_EXTERNAL_OBJECTS =

include/sol/libsol.so: include/sol/CMakeFiles/sol.dir/build.make
include/sol/libsol.so: include/sol/CMakeFiles/sol.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/srv/workspace/public/game-engine-sdl-cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX shared library libsol.so"
	cd /srv/workspace/public/game-engine-sdl-cpp/include/sol && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sol.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/sol/CMakeFiles/sol.dir/build: include/sol/libsol.so
.PHONY : include/sol/CMakeFiles/sol.dir/build

include/sol/CMakeFiles/sol.dir/clean:
	cd /srv/workspace/public/game-engine-sdl-cpp/include/sol && $(CMAKE_COMMAND) -P CMakeFiles/sol.dir/cmake_clean.cmake
.PHONY : include/sol/CMakeFiles/sol.dir/clean

include/sol/CMakeFiles/sol.dir/depend:
	cd /srv/workspace/public/game-engine-sdl-cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /srv/workspace/public/game-engine-sdl-cpp /srv/workspace/public/game-engine-sdl-cpp/include/sol /srv/workspace/public/game-engine-sdl-cpp /srv/workspace/public/game-engine-sdl-cpp/include/sol /srv/workspace/public/game-engine-sdl-cpp/include/sol/CMakeFiles/sol.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/sol/CMakeFiles/sol.dir/depend

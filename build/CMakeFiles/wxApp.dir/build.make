# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cd2groupea/Documents/AgenceVoyageIHM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cd2groupea/Documents/AgenceVoyageIHM/build

# Include any dependencies generated for this target.
include CMakeFiles/wxApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/wxApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/wxApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wxApp.dir/flags.make

CMakeFiles/wxApp.dir/main.cpp.o: CMakeFiles/wxApp.dir/flags.make
CMakeFiles/wxApp.dir/main.cpp.o: ../main.cpp
CMakeFiles/wxApp.dir/main.cpp.o: CMakeFiles/wxApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cd2groupea/Documents/AgenceVoyageIHM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wxApp.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wxApp.dir/main.cpp.o -MF CMakeFiles/wxApp.dir/main.cpp.o.d -o CMakeFiles/wxApp.dir/main.cpp.o -c /home/cd2groupea/Documents/AgenceVoyageIHM/main.cpp

CMakeFiles/wxApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxApp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cd2groupea/Documents/AgenceVoyageIHM/main.cpp > CMakeFiles/wxApp.dir/main.cpp.i

CMakeFiles/wxApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxApp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cd2groupea/Documents/AgenceVoyageIHM/main.cpp -o CMakeFiles/wxApp.dir/main.cpp.s

# Object files for target wxApp
wxApp_OBJECTS = \
"CMakeFiles/wxApp.dir/main.cpp.o"

# External object files for target wxApp
wxApp_EXTERNAL_OBJECTS =

wxApp: CMakeFiles/wxApp.dir/main.cpp.o
wxApp: CMakeFiles/wxApp.dir/build.make
wxApp: CMakeFiles/wxApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cd2groupea/Documents/AgenceVoyageIHM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wxApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wxApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wxApp.dir/build: wxApp
.PHONY : CMakeFiles/wxApp.dir/build

CMakeFiles/wxApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wxApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wxApp.dir/clean

CMakeFiles/wxApp.dir/depend:
	cd /home/cd2groupea/Documents/AgenceVoyageIHM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cd2groupea/Documents/AgenceVoyageIHM /home/cd2groupea/Documents/AgenceVoyageIHM /home/cd2groupea/Documents/AgenceVoyageIHM/build /home/cd2groupea/Documents/AgenceVoyageIHM/build /home/cd2groupea/Documents/AgenceVoyageIHM/build/CMakeFiles/wxApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wxApp.dir/depend


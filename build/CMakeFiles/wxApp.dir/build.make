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
CMAKE_SOURCE_DIR = /home/major/Documents/AgenceVoyageCpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/major/Documents/AgenceVoyageCpp/build

# Include any dependencies generated for this target.
include CMakeFiles/wxApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/wxApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/wxApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wxApp.dir/flags.make

CMakeFiles/wxApp.dir/src/main.cpp.o: CMakeFiles/wxApp.dir/flags.make
CMakeFiles/wxApp.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/wxApp.dir/src/main.cpp.o: CMakeFiles/wxApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/major/Documents/AgenceVoyageCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wxApp.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wxApp.dir/src/main.cpp.o -MF CMakeFiles/wxApp.dir/src/main.cpp.o.d -o CMakeFiles/wxApp.dir/src/main.cpp.o -c /home/major/Documents/AgenceVoyageCpp/src/main.cpp

CMakeFiles/wxApp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxApp.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/major/Documents/AgenceVoyageCpp/src/main.cpp > CMakeFiles/wxApp.dir/src/main.cpp.i

CMakeFiles/wxApp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxApp.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/major/Documents/AgenceVoyageCpp/src/main.cpp -o CMakeFiles/wxApp.dir/src/main.cpp.s

CMakeFiles/wxApp.dir/src/Client.cpp.o: CMakeFiles/wxApp.dir/flags.make
CMakeFiles/wxApp.dir/src/Client.cpp.o: ../src/Client.cpp
CMakeFiles/wxApp.dir/src/Client.cpp.o: CMakeFiles/wxApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/major/Documents/AgenceVoyageCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wxApp.dir/src/Client.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wxApp.dir/src/Client.cpp.o -MF CMakeFiles/wxApp.dir/src/Client.cpp.o.d -o CMakeFiles/wxApp.dir/src/Client.cpp.o -c /home/major/Documents/AgenceVoyageCpp/src/Client.cpp

CMakeFiles/wxApp.dir/src/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxApp.dir/src/Client.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/major/Documents/AgenceVoyageCpp/src/Client.cpp > CMakeFiles/wxApp.dir/src/Client.cpp.i

CMakeFiles/wxApp.dir/src/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxApp.dir/src/Client.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/major/Documents/AgenceVoyageCpp/src/Client.cpp -o CMakeFiles/wxApp.dir/src/Client.cpp.s

CMakeFiles/wxApp.dir/src/Trek.cpp.o: CMakeFiles/wxApp.dir/flags.make
CMakeFiles/wxApp.dir/src/Trek.cpp.o: ../src/Trek.cpp
CMakeFiles/wxApp.dir/src/Trek.cpp.o: CMakeFiles/wxApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/major/Documents/AgenceVoyageCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/wxApp.dir/src/Trek.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wxApp.dir/src/Trek.cpp.o -MF CMakeFiles/wxApp.dir/src/Trek.cpp.o.d -o CMakeFiles/wxApp.dir/src/Trek.cpp.o -c /home/major/Documents/AgenceVoyageCpp/src/Trek.cpp

CMakeFiles/wxApp.dir/src/Trek.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxApp.dir/src/Trek.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/major/Documents/AgenceVoyageCpp/src/Trek.cpp > CMakeFiles/wxApp.dir/src/Trek.cpp.i

CMakeFiles/wxApp.dir/src/Trek.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxApp.dir/src/Trek.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/major/Documents/AgenceVoyageCpp/src/Trek.cpp -o CMakeFiles/wxApp.dir/src/Trek.cpp.s

CMakeFiles/wxApp.dir/src/Reservation.cpp.o: CMakeFiles/wxApp.dir/flags.make
CMakeFiles/wxApp.dir/src/Reservation.cpp.o: ../src/Reservation.cpp
CMakeFiles/wxApp.dir/src/Reservation.cpp.o: CMakeFiles/wxApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/major/Documents/AgenceVoyageCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/wxApp.dir/src/Reservation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wxApp.dir/src/Reservation.cpp.o -MF CMakeFiles/wxApp.dir/src/Reservation.cpp.o.d -o CMakeFiles/wxApp.dir/src/Reservation.cpp.o -c /home/major/Documents/AgenceVoyageCpp/src/Reservation.cpp

CMakeFiles/wxApp.dir/src/Reservation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxApp.dir/src/Reservation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/major/Documents/AgenceVoyageCpp/src/Reservation.cpp > CMakeFiles/wxApp.dir/src/Reservation.cpp.i

CMakeFiles/wxApp.dir/src/Reservation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxApp.dir/src/Reservation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/major/Documents/AgenceVoyageCpp/src/Reservation.cpp -o CMakeFiles/wxApp.dir/src/Reservation.cpp.s

CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o: CMakeFiles/wxApp.dir/flags.make
CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o: ../src/Client/ClientEditDialog.cpp
CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o: CMakeFiles/wxApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/major/Documents/AgenceVoyageCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o -MF CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o.d -o CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o -c /home/major/Documents/AgenceVoyageCpp/src/Client/ClientEditDialog.cpp

CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/major/Documents/AgenceVoyageCpp/src/Client/ClientEditDialog.cpp > CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.i

CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/major/Documents/AgenceVoyageCpp/src/Client/ClientEditDialog.cpp -o CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.s

CMakeFiles/wxApp.dir/src/db_setup.cpp.o: CMakeFiles/wxApp.dir/flags.make
CMakeFiles/wxApp.dir/src/db_setup.cpp.o: ../src/db_setup.cpp
CMakeFiles/wxApp.dir/src/db_setup.cpp.o: CMakeFiles/wxApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/major/Documents/AgenceVoyageCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/wxApp.dir/src/db_setup.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wxApp.dir/src/db_setup.cpp.o -MF CMakeFiles/wxApp.dir/src/db_setup.cpp.o.d -o CMakeFiles/wxApp.dir/src/db_setup.cpp.o -c /home/major/Documents/AgenceVoyageCpp/src/db_setup.cpp

CMakeFiles/wxApp.dir/src/db_setup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wxApp.dir/src/db_setup.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/major/Documents/AgenceVoyageCpp/src/db_setup.cpp > CMakeFiles/wxApp.dir/src/db_setup.cpp.i

CMakeFiles/wxApp.dir/src/db_setup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wxApp.dir/src/db_setup.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/major/Documents/AgenceVoyageCpp/src/db_setup.cpp -o CMakeFiles/wxApp.dir/src/db_setup.cpp.s

# Object files for target wxApp
wxApp_OBJECTS = \
"CMakeFiles/wxApp.dir/src/main.cpp.o" \
"CMakeFiles/wxApp.dir/src/Client.cpp.o" \
"CMakeFiles/wxApp.dir/src/Trek.cpp.o" \
"CMakeFiles/wxApp.dir/src/Reservation.cpp.o" \
"CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o" \
"CMakeFiles/wxApp.dir/src/db_setup.cpp.o"

# External object files for target wxApp
wxApp_EXTERNAL_OBJECTS =

wxApp: CMakeFiles/wxApp.dir/src/main.cpp.o
wxApp: CMakeFiles/wxApp.dir/src/Client.cpp.o
wxApp: CMakeFiles/wxApp.dir/src/Trek.cpp.o
wxApp: CMakeFiles/wxApp.dir/src/Reservation.cpp.o
wxApp: CMakeFiles/wxApp.dir/src/Client/ClientEditDialog.cpp.o
wxApp: CMakeFiles/wxApp.dir/src/db_setup.cpp.o
wxApp: CMakeFiles/wxApp.dir/build.make
wxApp: /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so
wxApp: CMakeFiles/wxApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/major/Documents/AgenceVoyageCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable wxApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wxApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wxApp.dir/build: wxApp
.PHONY : CMakeFiles/wxApp.dir/build

CMakeFiles/wxApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wxApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wxApp.dir/clean

CMakeFiles/wxApp.dir/depend:
	cd /home/major/Documents/AgenceVoyageCpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/major/Documents/AgenceVoyageCpp /home/major/Documents/AgenceVoyageCpp /home/major/Documents/AgenceVoyageCpp/build /home/major/Documents/AgenceVoyageCpp/build /home/major/Documents/AgenceVoyageCpp/build/CMakeFiles/wxApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wxApp.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yuting/Desktop/MTest/ROB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuting/Desktop/MTest/ROB-build

# Include any dependencies generated for this target.
include CMakeFiles/interface.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/interface.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/interface.dir/flags.make

CMakeFiles/interface.dir/interface.o: CMakeFiles/interface.dir/flags.make
CMakeFiles/interface.dir/interface.o: /home/yuting/Desktop/MTest/ROB/interface.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yuting/Desktop/MTest/ROB-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/interface.dir/interface.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/interface.dir/interface.o -c /home/yuting/Desktop/MTest/ROB/interface.cpp

CMakeFiles/interface.dir/interface.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/interface.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yuting/Desktop/MTest/ROB/interface.cpp > CMakeFiles/interface.dir/interface.i

CMakeFiles/interface.dir/interface.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/interface.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yuting/Desktop/MTest/ROB/interface.cpp -o CMakeFiles/interface.dir/interface.s

CMakeFiles/interface.dir/interface.o.requires:
.PHONY : CMakeFiles/interface.dir/interface.o.requires

CMakeFiles/interface.dir/interface.o.provides: CMakeFiles/interface.dir/interface.o.requires
	$(MAKE) -f CMakeFiles/interface.dir/build.make CMakeFiles/interface.dir/interface.o.provides.build
.PHONY : CMakeFiles/interface.dir/interface.o.provides

CMakeFiles/interface.dir/interface.o.provides.build: CMakeFiles/interface.dir/interface.o

# Object files for target interface
interface_OBJECTS = \
"CMakeFiles/interface.dir/interface.o"

# External object files for target interface
interface_EXTERNAL_OBJECTS =

interface: CMakeFiles/interface.dir/interface.o
interface: CMakeFiles/interface.dir/build.make
interface: libMrsvrCom.a
interface: libMrsvrIF.a
interface: libMrsvrCom.a
interface: CMakeFiles/interface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable interface"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/interface.dir/build: interface
.PHONY : CMakeFiles/interface.dir/build

CMakeFiles/interface.dir/requires: CMakeFiles/interface.dir/interface.o.requires
.PHONY : CMakeFiles/interface.dir/requires

CMakeFiles/interface.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/interface.dir/cmake_clean.cmake
.PHONY : CMakeFiles/interface.dir/clean

CMakeFiles/interface.dir/depend:
	cd /home/yuting/Desktop/MTest/ROB-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuting/Desktop/MTest/ROB /home/yuting/Desktop/MTest/ROB /home/yuting/Desktop/MTest/ROB-build /home/yuting/Desktop/MTest/ROB-build /home/yuting/Desktop/MTest/ROB-build/CMakeFiles/interface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/interface.dir/depend


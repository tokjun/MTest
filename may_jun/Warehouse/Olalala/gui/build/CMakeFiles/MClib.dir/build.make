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
CMAKE_SOURCE_DIR = /home/yuting/Desktop/MTest/Olalala/gui

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yuting/Desktop/MTest/Olalala/gui/build

# Include any dependencies generated for this target.
include CMakeFiles/MClib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MClib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MClib.dir/flags.make

CMakeFiles/MClib.dir/MConnectorWindow.o: CMakeFiles/MClib.dir/flags.make
CMakeFiles/MClib.dir/MConnectorWindow.o: ../MConnectorWindow.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yuting/Desktop/MTest/Olalala/gui/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MClib.dir/MConnectorWindow.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MClib.dir/MConnectorWindow.o -c /home/yuting/Desktop/MTest/Olalala/gui/MConnectorWindow.cpp

CMakeFiles/MClib.dir/MConnectorWindow.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MClib.dir/MConnectorWindow.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yuting/Desktop/MTest/Olalala/gui/MConnectorWindow.cpp > CMakeFiles/MClib.dir/MConnectorWindow.i

CMakeFiles/MClib.dir/MConnectorWindow.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MClib.dir/MConnectorWindow.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yuting/Desktop/MTest/Olalala/gui/MConnectorWindow.cpp -o CMakeFiles/MClib.dir/MConnectorWindow.s

CMakeFiles/MClib.dir/MConnectorWindow.o.requires:
.PHONY : CMakeFiles/MClib.dir/MConnectorWindow.o.requires

CMakeFiles/MClib.dir/MConnectorWindow.o.provides: CMakeFiles/MClib.dir/MConnectorWindow.o.requires
	$(MAKE) -f CMakeFiles/MClib.dir/build.make CMakeFiles/MClib.dir/MConnectorWindow.o.provides.build
.PHONY : CMakeFiles/MClib.dir/MConnectorWindow.o.provides

CMakeFiles/MClib.dir/MConnectorWindow.o.provides.build: CMakeFiles/MClib.dir/MConnectorWindow.o

# Object files for target MClib
MClib_OBJECTS = \
"CMakeFiles/MClib.dir/MConnectorWindow.o"

# External object files for target MClib
MClib_EXTERNAL_OBJECTS =

libMClib.a: CMakeFiles/MClib.dir/MConnectorWindow.o
libMClib.a: CMakeFiles/MClib.dir/build.make
libMClib.a: CMakeFiles/MClib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libMClib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/MClib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MClib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MClib.dir/build: libMClib.a
.PHONY : CMakeFiles/MClib.dir/build

CMakeFiles/MClib.dir/requires: CMakeFiles/MClib.dir/MConnectorWindow.o.requires
.PHONY : CMakeFiles/MClib.dir/requires

CMakeFiles/MClib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MClib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MClib.dir/clean

CMakeFiles/MClib.dir/depend:
	cd /home/yuting/Desktop/MTest/Olalala/gui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yuting/Desktop/MTest/Olalala/gui /home/yuting/Desktop/MTest/Olalala/gui /home/yuting/Desktop/MTest/Olalala/gui/build /home/yuting/Desktop/MTest/Olalala/gui/build /home/yuting/Desktop/MTest/Olalala/gui/build/CMakeFiles/MClib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MClib.dir/depend


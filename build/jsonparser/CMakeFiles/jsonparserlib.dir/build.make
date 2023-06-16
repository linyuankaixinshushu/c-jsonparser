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
CMAKE_COMMAND = /usr/local/cmake-3.24.4-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake-3.24.4-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/j/桌面/JSON_Parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/j/桌面/JSON_Parser/build

# Include any dependencies generated for this target.
include jsonparser/CMakeFiles/jsonparserlib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include jsonparser/CMakeFiles/jsonparserlib.dir/compiler_depend.make

# Include the progress variables for this target.
include jsonparser/CMakeFiles/jsonparserlib.dir/progress.make

# Include the compile flags for this target's objects.
include jsonparser/CMakeFiles/jsonparserlib.dir/flags.make

jsonparser/CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o: jsonparser/CMakeFiles/jsonparserlib.dir/flags.make
jsonparser/CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o: /home/j/桌面/JSON_Parser/jsonparser/jsonparser.cpp
jsonparser/CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o: jsonparser/CMakeFiles/jsonparserlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/j/桌面/JSON_Parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object jsonparser/CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o"
	cd /home/j/桌面/JSON_Parser/build/jsonparser && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsonparser/CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o -MF CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o.d -o CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o -c /home/j/桌面/JSON_Parser/jsonparser/jsonparser.cpp

jsonparser/CMakeFiles/jsonparserlib.dir/jsonparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsonparserlib.dir/jsonparser.cpp.i"
	cd /home/j/桌面/JSON_Parser/build/jsonparser && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/j/桌面/JSON_Parser/jsonparser/jsonparser.cpp > CMakeFiles/jsonparserlib.dir/jsonparser.cpp.i

jsonparser/CMakeFiles/jsonparserlib.dir/jsonparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsonparserlib.dir/jsonparser.cpp.s"
	cd /home/j/桌面/JSON_Parser/build/jsonparser && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/j/桌面/JSON_Parser/jsonparser/jsonparser.cpp -o CMakeFiles/jsonparserlib.dir/jsonparser.cpp.s

# Object files for target jsonparserlib
jsonparserlib_OBJECTS = \
"CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o"

# External object files for target jsonparserlib
jsonparserlib_EXTERNAL_OBJECTS =

jsonparser/libjsonparserlib.a: jsonparser/CMakeFiles/jsonparserlib.dir/jsonparser.cpp.o
jsonparser/libjsonparserlib.a: jsonparser/CMakeFiles/jsonparserlib.dir/build.make
jsonparser/libjsonparserlib.a: jsonparser/CMakeFiles/jsonparserlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/j/桌面/JSON_Parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libjsonparserlib.a"
	cd /home/j/桌面/JSON_Parser/build/jsonparser && $(CMAKE_COMMAND) -P CMakeFiles/jsonparserlib.dir/cmake_clean_target.cmake
	cd /home/j/桌面/JSON_Parser/build/jsonparser && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsonparserlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
jsonparser/CMakeFiles/jsonparserlib.dir/build: jsonparser/libjsonparserlib.a
.PHONY : jsonparser/CMakeFiles/jsonparserlib.dir/build

jsonparser/CMakeFiles/jsonparserlib.dir/clean:
	cd /home/j/桌面/JSON_Parser/build/jsonparser && $(CMAKE_COMMAND) -P CMakeFiles/jsonparserlib.dir/cmake_clean.cmake
.PHONY : jsonparser/CMakeFiles/jsonparserlib.dir/clean

jsonparser/CMakeFiles/jsonparserlib.dir/depend:
	cd /home/j/桌面/JSON_Parser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/j/桌面/JSON_Parser /home/j/桌面/JSON_Parser/jsonparser /home/j/桌面/JSON_Parser/build /home/j/桌面/JSON_Parser/build/jsonparser /home/j/桌面/JSON_Parser/build/jsonparser/CMakeFiles/jsonparserlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jsonparser/CMakeFiles/jsonparserlib.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/user/hal-core-2.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/hal-core-2.0/build

# Include any dependencies generated for this target.
include src/hal/halcmd/CMakeFiles/halcmd.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/hal/halcmd/CMakeFiles/halcmd.dir/compiler_depend.make

# Include the progress variables for this target.
include src/hal/halcmd/CMakeFiles/halcmd.dir/progress.make

# Include the compile flags for this target's objects.
include src/hal/halcmd/CMakeFiles/halcmd.dir/flags.make

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/flags.make
src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd.c.o: /home/user/hal-core-2.0/src/hal/utils/halcmd.c
src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/hal-core-2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd.c.o"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd.c.o -MF CMakeFiles/halcmd.dir/__/utils/halcmd.c.o.d -o CMakeFiles/halcmd.dir/__/utils/halcmd.c.o -c /home/user/hal-core-2.0/src/hal/utils/halcmd.c

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/halcmd.dir/__/utils/halcmd.c.i"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/hal-core-2.0/src/hal/utils/halcmd.c > CMakeFiles/halcmd.dir/__/utils/halcmd.c.i

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/halcmd.dir/__/utils/halcmd.c.s"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/hal-core-2.0/src/hal/utils/halcmd.c -o CMakeFiles/halcmd.dir/__/utils/halcmd.c.s

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/flags.make
src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o: /home/user/hal-core-2.0/src/hal/utils/halcmd_commands.c
src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/hal-core-2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o -MF CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o.d -o CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o -c /home/user/hal-core-2.0/src/hal/utils/halcmd_commands.c

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.i"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/hal-core-2.0/src/hal/utils/halcmd_commands.c > CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.i

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.s"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/hal-core-2.0/src/hal/utils/halcmd_commands.c -o CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.s

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/flags.make
src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o: /home/user/hal-core-2.0/src/hal/utils/halcmd_main.c
src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/hal-core-2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o -MF CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o.d -o CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o -c /home/user/hal-core-2.0/src/hal/utils/halcmd_main.c

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.i"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/hal-core-2.0/src/hal/utils/halcmd_main.c > CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.i

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.s"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/hal-core-2.0/src/hal/utils/halcmd_main.c -o CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.s

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/flags.make
src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o: /home/user/hal-core-2.0/src/hal/utils/halcmd_completion.c
src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/hal-core-2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o -MF CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o.d -o CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o -c /home/user/hal-core-2.0/src/hal/utils/halcmd_completion.c

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.i"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/hal-core-2.0/src/hal/utils/halcmd_completion.c > CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.i

src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.s"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/hal-core-2.0/src/hal/utils/halcmd_completion.c -o CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.s

src/hal/halcmd/CMakeFiles/halcmd.dir/__/hal_lib.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/flags.make
src/hal/halcmd/CMakeFiles/halcmd.dir/__/hal_lib.c.o: /home/user/hal-core-2.0/src/hal/hal_lib.c
src/hal/halcmd/CMakeFiles/halcmd.dir/__/hal_lib.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/hal-core-2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/hal/halcmd/CMakeFiles/halcmd.dir/__/hal_lib.c.o"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/hal/halcmd/CMakeFiles/halcmd.dir/__/hal_lib.c.o -MF CMakeFiles/halcmd.dir/__/hal_lib.c.o.d -o CMakeFiles/halcmd.dir/__/hal_lib.c.o -c /home/user/hal-core-2.0/src/hal/hal_lib.c

src/hal/halcmd/CMakeFiles/halcmd.dir/__/hal_lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/halcmd.dir/__/hal_lib.c.i"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/hal-core-2.0/src/hal/hal_lib.c > CMakeFiles/halcmd.dir/__/hal_lib.c.i

src/hal/halcmd/CMakeFiles/halcmd.dir/__/hal_lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/halcmd.dir/__/hal_lib.c.s"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/hal-core-2.0/src/hal/hal_lib.c -o CMakeFiles/halcmd.dir/__/hal_lib.c.s

src/hal/halcmd/CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/flags.make
src/hal/halcmd/CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o: /home/user/hal-core-2.0/src/rtapi/uspace_ulapi.c
src/hal/halcmd/CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o: src/hal/halcmd/CMakeFiles/halcmd.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/hal-core-2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/hal/halcmd/CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/hal/halcmd/CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o -MF CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o.d -o CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o -c /home/user/hal-core-2.0/src/rtapi/uspace_ulapi.c

src/hal/halcmd/CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.i"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/hal-core-2.0/src/rtapi/uspace_ulapi.c > CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.i

src/hal/halcmd/CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.s"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/hal-core-2.0/src/rtapi/uspace_ulapi.c -o CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.s

# Object files for target halcmd
halcmd_OBJECTS = \
"CMakeFiles/halcmd.dir/__/utils/halcmd.c.o" \
"CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o" \
"CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o" \
"CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o" \
"CMakeFiles/halcmd.dir/__/hal_lib.c.o" \
"CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o"

# External object files for target halcmd
halcmd_EXTERNAL_OBJECTS =

src/hal/halcmd/halcmd: src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd.c.o
src/hal/halcmd/halcmd: src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_commands.c.o
src/hal/halcmd/halcmd: src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_main.c.o
src/hal/halcmd/halcmd: src/hal/halcmd/CMakeFiles/halcmd.dir/__/utils/halcmd_completion.c.o
src/hal/halcmd/halcmd: src/hal/halcmd/CMakeFiles/halcmd.dir/__/hal_lib.c.o
src/hal/halcmd/halcmd: src/hal/halcmd/CMakeFiles/halcmd.dir/__/__/rtapi/uspace_ulapi.c.o
src/hal/halcmd/halcmd: src/hal/halcmd/CMakeFiles/halcmd.dir/build.make
src/hal/halcmd/halcmd: src/hal/halcmd/CMakeFiles/halcmd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/hal-core-2.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable halcmd"
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/halcmd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/hal/halcmd/CMakeFiles/halcmd.dir/build: src/hal/halcmd/halcmd
.PHONY : src/hal/halcmd/CMakeFiles/halcmd.dir/build

src/hal/halcmd/CMakeFiles/halcmd.dir/clean:
	cd /home/user/hal-core-2.0/build/src/hal/halcmd && $(CMAKE_COMMAND) -P CMakeFiles/halcmd.dir/cmake_clean.cmake
.PHONY : src/hal/halcmd/CMakeFiles/halcmd.dir/clean

src/hal/halcmd/CMakeFiles/halcmd.dir/depend:
	cd /home/user/hal-core-2.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/hal-core-2.0 /home/user/hal-core-2.0/src/hal/halcmd /home/user/hal-core-2.0/build /home/user/hal-core-2.0/build/src/hal/halcmd /home/user/hal-core-2.0/build/src/hal/halcmd/CMakeFiles/halcmd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/hal/halcmd/CMakeFiles/halcmd.dir/depend


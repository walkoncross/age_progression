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
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression

# Include any dependencies generated for this target.
include 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/depend.make

# Include the progress variables for this target.
include 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/progress.make

# Include the compile flags for this target's objects.
include 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/flags.make

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o: 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/flags.make
3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o: 3rdparty/face-analysis-sdk-master/src/display-avatar/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o"
	cd /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/display-avatar.dir/main.cpp.o -c /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar/main.cpp

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display-avatar.dir/main.cpp.i"
	cd /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar/main.cpp > CMakeFiles/display-avatar.dir/main.cpp.i

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display-avatar.dir/main.cpp.s"
	cd /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar/main.cpp -o CMakeFiles/display-avatar.dir/main.cpp.s

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o.requires:
.PHONY : 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o.requires

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o.provides: 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o.requires
	$(MAKE) -f 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/build.make 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o.provides.build
.PHONY : 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o.provides

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o.provides.build: 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o

# Object files for target display-avatar
display__avatar_OBJECTS = \
"CMakeFiles/display-avatar.dir/main.cpp.o"

# External object files for target display-avatar
display__avatar_EXTERNAL_OBJECTS =

3rdparty/face-analysis-sdk-master/bin/display-avatar: 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o
3rdparty/face-analysis-sdk-master/bin/display-avatar: 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/build.make
3rdparty/face-analysis-sdk-master/bin/display-avatar: 3rdparty/face-analysis-sdk-master/lib/libutilities.so
3rdparty/face-analysis-sdk-master/bin/display-avatar: 3rdparty/face-analysis-sdk-master/lib/libavatarAnim.so
3rdparty/face-analysis-sdk-master/bin/display-avatar: /usr/local/lib/libopencv_core.so.2.4.9
3rdparty/face-analysis-sdk-master/bin/display-avatar: /usr/local/lib/libopencv_highgui.so.2.4.9
3rdparty/face-analysis-sdk-master/bin/display-avatar: /usr/local/lib/libopencv_imgproc.so.2.4.9
3rdparty/face-analysis-sdk-master/bin/display-avatar: /usr/local/lib/libopencv_objdetect.so.2.4.9
3rdparty/face-analysis-sdk-master/bin/display-avatar: 3rdparty/face-analysis-sdk-master/lib/libutilities.so
3rdparty/face-analysis-sdk-master/bin/display-avatar: 3rdparty/face-analysis-sdk-master/lib/libclmTracker.so
3rdparty/face-analysis-sdk-master/bin/display-avatar: /usr/local/lib/libopencv_objdetect.so.2.4.9
3rdparty/face-analysis-sdk-master/bin/display-avatar: /usr/local/lib/libopencv_highgui.so.2.4.9
3rdparty/face-analysis-sdk-master/bin/display-avatar: /usr/local/lib/libopencv_imgproc.so.2.4.9
3rdparty/face-analysis-sdk-master/bin/display-avatar: /usr/local/lib/libopencv_core.so.2.4.9
3rdparty/face-analysis-sdk-master/bin/display-avatar: 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/display-avatar"
	cd /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/display-avatar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/build: 3rdparty/face-analysis-sdk-master/bin/display-avatar
.PHONY : 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/build

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/requires: 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/main.cpp.o.requires
.PHONY : 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/requires

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/clean:
	cd /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar && $(CMAKE_COMMAND) -P CMakeFiles/display-avatar.dir/cmake_clean.cmake
.PHONY : 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/clean

3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/depend:
	cd /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar /home/savuor/Dropbox/Public/hse/diploma_mag/age_progression/3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3rdparty/face-analysis-sdk-master/src/display-avatar/CMakeFiles/display-avatar.dir/depend


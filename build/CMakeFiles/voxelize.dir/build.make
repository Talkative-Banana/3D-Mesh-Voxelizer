# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lucky/Computer_Graphics/Project_GitHub

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucky/Computer_Graphics/Project_GitHub/build

# Include any dependencies generated for this target.
include CMakeFiles/voxelize.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/voxelize.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/voxelize.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/voxelize.dir/flags.make

CMakeFiles/voxelize.dir/src/main.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/src/main.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/src/main.cpp
CMakeFiles/voxelize.dir/src/main.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/voxelize.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/src/main.cpp.o -MF CMakeFiles/voxelize.dir/src/main.cpp.o.d -o CMakeFiles/voxelize.dir/src/main.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/src/main.cpp

CMakeFiles/voxelize.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/src/main.cpp > CMakeFiles/voxelize.dir/src/main.cpp.i

CMakeFiles/voxelize.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/src/main.cpp -o CMakeFiles/voxelize.dir/src/main.cpp.s

CMakeFiles/voxelize.dir/src/utils.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/src/utils.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/src/utils.cpp
CMakeFiles/voxelize.dir/src/utils.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/voxelize.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/src/utils.cpp.o -MF CMakeFiles/voxelize.dir/src/utils.cpp.o.d -o CMakeFiles/voxelize.dir/src/utils.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/src/utils.cpp

CMakeFiles/voxelize.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/src/utils.cpp > CMakeFiles/voxelize.dir/src/utils.cpp.i

CMakeFiles/voxelize.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/src/utils.cpp -o CMakeFiles/voxelize.dir/src/utils.cpp.s

CMakeFiles/voxelize.dir/src/chunk.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/src/chunk.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/src/chunk.cpp
CMakeFiles/voxelize.dir/src/chunk.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/voxelize.dir/src/chunk.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/src/chunk.cpp.o -MF CMakeFiles/voxelize.dir/src/chunk.cpp.o.d -o CMakeFiles/voxelize.dir/src/chunk.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/src/chunk.cpp

CMakeFiles/voxelize.dir/src/chunk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/src/chunk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/src/chunk.cpp > CMakeFiles/voxelize.dir/src/chunk.cpp.i

CMakeFiles/voxelize.dir/src/chunk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/src/chunk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/src/chunk.cpp -o CMakeFiles/voxelize.dir/src/chunk.cpp.s

CMakeFiles/voxelize.dir/src/block.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/src/block.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/src/block.cpp
CMakeFiles/voxelize.dir/src/block.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/voxelize.dir/src/block.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/src/block.cpp.o -MF CMakeFiles/voxelize.dir/src/block.cpp.o.d -o CMakeFiles/voxelize.dir/src/block.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/src/block.cpp

CMakeFiles/voxelize.dir/src/block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/src/block.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/src/block.cpp > CMakeFiles/voxelize.dir/src/block.cpp.i

CMakeFiles/voxelize.dir/src/block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/src/block.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/src/block.cpp -o CMakeFiles/voxelize.dir/src/block.cpp.s

CMakeFiles/voxelize.dir/src/Renderer.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/src/Renderer.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/src/Renderer.cpp
CMakeFiles/voxelize.dir/src/Renderer.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/voxelize.dir/src/Renderer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/src/Renderer.cpp.o -MF CMakeFiles/voxelize.dir/src/Renderer.cpp.o.d -o CMakeFiles/voxelize.dir/src/Renderer.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/src/Renderer.cpp

CMakeFiles/voxelize.dir/src/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/src/Renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/src/Renderer.cpp > CMakeFiles/voxelize.dir/src/Renderer.cpp.i

CMakeFiles/voxelize.dir/src/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/src/Renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/src/Renderer.cpp -o CMakeFiles/voxelize.dir/src/Renderer.cpp.s

CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/src/VertexBuffer.cpp
CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o -MF CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o.d -o CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/src/VertexBuffer.cpp

CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/src/VertexBuffer.cpp > CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.i

CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/src/VertexBuffer.cpp -o CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.s

CMakeFiles/voxelize.dir/src/VertexArray.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/src/VertexArray.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/src/VertexArray.cpp
CMakeFiles/voxelize.dir/src/VertexArray.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/voxelize.dir/src/VertexArray.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/src/VertexArray.cpp.o -MF CMakeFiles/voxelize.dir/src/VertexArray.cpp.o.d -o CMakeFiles/voxelize.dir/src/VertexArray.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/src/VertexArray.cpp

CMakeFiles/voxelize.dir/src/VertexArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/src/VertexArray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/src/VertexArray.cpp > CMakeFiles/voxelize.dir/src/VertexArray.cpp.i

CMakeFiles/voxelize.dir/src/VertexArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/src/VertexArray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/src/VertexArray.cpp -o CMakeFiles/voxelize.dir/src/VertexArray.cpp.s

CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/src/IndexBuffer.cpp
CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o -MF CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o.d -o CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/src/IndexBuffer.cpp

CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/src/IndexBuffer.cpp > CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.i

CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/src/IndexBuffer.cpp -o CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.s

CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_impl_glfw.cpp
CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o -MF CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o.d -o CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_impl_glfw.cpp

CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_impl_glfw.cpp > CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.i

CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_impl_glfw.cpp -o CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.s

CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_impl_opengl3.cpp
CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o -MF CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_impl_opengl3.cpp

CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_impl_opengl3.cpp > CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.i

CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_impl_opengl3.cpp -o CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.s

CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui.cpp
CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o -MF CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o.d -o CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui.cpp

CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui.cpp > CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.i

CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui.cpp -o CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.s

CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_demo.cpp
CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o -MF CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o.d -o CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_demo.cpp

CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_demo.cpp > CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.i

CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_demo.cpp -o CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.s

CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_draw.cpp
CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o -MF CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o.d -o CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_draw.cpp

CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_draw.cpp > CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.i

CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_draw.cpp -o CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.s

CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o: CMakeFiles/voxelize.dir/flags.make
CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o: /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_widgets.cpp
CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o: CMakeFiles/voxelize.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o -MF CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o -c /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_widgets.cpp

CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_widgets.cpp > CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.i

CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucky/Computer_Graphics/Project_GitHub/depends/imgui/imgui_widgets.cpp -o CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.s

# Object files for target voxelize
voxelize_OBJECTS = \
"CMakeFiles/voxelize.dir/src/main.cpp.o" \
"CMakeFiles/voxelize.dir/src/utils.cpp.o" \
"CMakeFiles/voxelize.dir/src/chunk.cpp.o" \
"CMakeFiles/voxelize.dir/src/block.cpp.o" \
"CMakeFiles/voxelize.dir/src/Renderer.cpp.o" \
"CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o" \
"CMakeFiles/voxelize.dir/src/VertexArray.cpp.o" \
"CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o" \
"CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o" \
"CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o" \
"CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o" \
"CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o" \
"CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o"

# External object files for target voxelize
voxelize_EXTERNAL_OBJECTS =

/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/src/main.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/src/utils.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/src/chunk.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/src/block.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/src/Renderer.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/src/VertexBuffer.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/src/VertexArray.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/src/IndexBuffer.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_glfw.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/depends/imgui/imgui_impl_opengl3.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/depends/imgui/imgui.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/depends/imgui/imgui_demo.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/depends/imgui/imgui_draw.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/depends/imgui/imgui_widgets.cpp.o
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/build.make
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: /usr/lib/x86_64-linux-gnu/libGL.so
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: /usr/lib/x86_64-linux-gnu/libGLU.so
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: /usr/lib/x86_64-linux-gnu/libGLEW.so
/home/lucky/Computer_Graphics/Project_GitHub/voxelize: CMakeFiles/voxelize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable /home/lucky/Computer_Graphics/Project_GitHub/voxelize"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/voxelize.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/voxelize.dir/build: /home/lucky/Computer_Graphics/Project_GitHub/voxelize
.PHONY : CMakeFiles/voxelize.dir/build

CMakeFiles/voxelize.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/voxelize.dir/cmake_clean.cmake
.PHONY : CMakeFiles/voxelize.dir/clean

CMakeFiles/voxelize.dir/depend:
	cd /home/lucky/Computer_Graphics/Project_GitHub/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucky/Computer_Graphics/Project_GitHub /home/lucky/Computer_Graphics/Project_GitHub /home/lucky/Computer_Graphics/Project_GitHub/build /home/lucky/Computer_Graphics/Project_GitHub/build /home/lucky/Computer_Graphics/Project_GitHub/build/CMakeFiles/voxelize.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/voxelize.dir/depend

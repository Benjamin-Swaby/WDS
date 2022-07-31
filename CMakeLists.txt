# to check and find a Cuda compiler
include(CheckLanguage)
check_language(CUDA)

cmake_minimum_required(VERSION 3.20)

# Use cuda C
enable_language(CUDA)

IF (WIN32)
  set(GCC_COVERAGE_COMPILE_FLAGS "/MT")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
ELSE()
  set(GCC_COVERAGE_COMPILE_FLAGS "-static-libstdc++ -static-libgcc")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
ENDIF()


# Project Definition
project(Wave-Diffraction-Simulation
          VERSION 1.0
          LANGUAGES C CXX CUDA)

# Require OpenGL as a dependancy
find_package(OpenGL REQUIRED)


# Gtest dependancy
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



# set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Output directory for the binary
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# Don't build GLFW tests or DOCs or examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# enable testing
enable_testing()

# directory of glfw libary to build
# add_subdirectory(extern/glfw-3.3.7)


FetchContent_Declare(
	glfw
	URL https://github.com/glfw/glfw/archive/refs/tags/3.3.7.zip
)
FetchContent_MakeAvailable(glfw)

add_library(imgui STATIC
  extern/imgui/imgui_demo.cpp
  extern/imgui/imgui.cpp
  extern/imgui/imgui_draw.cpp
  extern/imgui/imgui_tables.cpp
  extern/imgui/imgui_widgets.cpp
  extern/imgui/backends/imgui_impl_glfw.cpp
  extern/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PRIVATE
  ${PROJECT_SOURCE_DIR}/extern/imgui
  ${PROJECT_SOURCE_DIR}/extern/imgui/backends
)
target_link_libraries(imgui glfw OpenGL::GL)

# main executable definition
add_executable(WDS
  lib/errors.cpp
  src/main.cpp
  src/glad.c
  )

# testing executable definition
add_executable(WDS_Test
  tests/main_test.cpp
  )

# build the testing executable with gtest
target_link_libraries(WDS_Test gtest_main glfw OpenGL::GL)

# build the main executable with glfw and opengl
target_link_libraries(WDS glfw)
target_link_libraries(WDS OpenGL::GL imgui)

# include the google test library
include(GoogleTest)
# find all the tests in the test project
gtest_discover_tests(WDS_Test)

# include directory for the main executable
target_include_directories(WDS
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/extern/imgui
	${PROJECT_SOURCE_DIR}/extern/imgui/backends
)

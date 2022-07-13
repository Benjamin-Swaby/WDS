# to check and find a Cuda compiler
include(CheckLanguage)
check_language(CUDA)

cmake_minimum_required(VERSION 3.10)

# Use cuda C
enable_language(CUDA)

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


# main executable definition
add_executable(WDS
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
target_link_libraries(WDS OpenGL::GL)

# include the google test library
include(GoogleTest)
# find all the tests in the test project
gtest_discover_tests(WDS_Test)

# include directory for the main executable
target_include_directories(WDS
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

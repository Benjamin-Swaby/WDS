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
# set flags
SET(CMAKE_CXX_FLAGS  "-static-libgcc -static-libstdc++")
# Output directory for the binary
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)


# enable testing
enable_testing()

# main executable definition
add_executable(WDS
  src/main.cpp
  )

# testing executable definition
add_executable(WDS_Test
  tests/main_test.cpp
  )


  # GTK stuff
find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})
target_link_libraries(WDS ${GTK4_LIBRARIES})
  
# build the testing executable with gtest
target_link_libraries(WDS_Test gtest_main)



# include the google test library
include(GoogleTest)
gtest_discover_tests(WDS_Test)

# include directory for the main executable
target_include_directories(WDS
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

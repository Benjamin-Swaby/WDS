# to check and find a Cuda compiler

cmake_minimum_required(VERSION 3.20)


IF (WIN32)
  set(GCC_COVERAGE_COMPILE_FLAGS "/MT")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
ELSE()
  set(GCC_COVERAGE_COMPILE_FLAGS "-static-libstdc++ -static-libgcc")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
ENDIF()


project(Wave-Diffraction-Simulation
          VERSION 1.0
          LANGUAGES C CXX)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


add_subdirectory(lib/AventraRenderEngine)


add_executable(WDS
  lib/errors.cpp
  src/main.cpp
  tests/main_test.cpp
)

target_include_directories(WDS
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        #${PROJECT_SOURCE_DIR}/extern/imgui
	    #${PROJECT_SOURCE_DIR}/extern/imgui/backends
        ${PROJECT_SOURCE_DIR}/lib/AventraRenderEngine/include        
)


target_link_libraries(WDS Aventra gtest_main)

enable_testing()
include(GoogleTest)
# gtest_discover_tests(WDS)


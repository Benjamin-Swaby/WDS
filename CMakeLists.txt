# to check and find a Cuda compiler

cmake_minimum_required(VERSION 3.20)


# enable with -Dtest=ON
option(test "Build all tests." OFF)

IF (WIN32)
  set(GCC_COVERAGE_COMPILE_FLAGS "/MT")
  set(CMAKE_CXX_FLAGS  "/MT")
  set(CMAKE_C_FLAGS "/MT")
ELSE()
  set(CMAKE_CXX_FLAGS  "-O2 -Wall -Wpedantic")
  set(CMAKE_C_FLAGS "-O2 -Wall -Wpedantic")
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
add_subdirectory(lib/WaveMath)

add_executable(WDS
  src/main.cpp
)

target_include_directories(WDS
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/lib/WaveMath/include
        ${PROJECT_SOURCE_DIR}/lib/AventraRenderEngine/include        
)


if (test)

  add_executable(WDS_test
    tests/main_test.cpp
  )

  target_include_directories(WDS_test
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/lib/WaveMath/include
        ${PROJECT_SOURCE_DIR}/lib/AventraRenderEngine/include        
      )
  
  enable_testing()
  include(GoogleTest)
  gtest_discover_tests(WDS_test)

  target_link_libraries(WDS_test Aventra waveMath gtest_main)
  
endif()

target_link_libraries(WDS Aventra waveMath)

install(TARGETS WDS
  RUNTIME DESTINATION /usr/local/bin)

cmake_minimum_required(VERSION 3.20)

option(test "Build all tests." OFF)

IF (WIN32)
  set(GCC_COVERAGE_COMPILE_FLAGS "/MT")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
ELSE()
  set(GCC_COVERAGE_COMPILE_FLAGS "-static-libstdc++ -static-libgcc  -O2")
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
  set(CMAKE_C_FLAGS "-static-libgcc -O2")
ENDIF()

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)


set(CMAKE_CXX_STANDARD 20)
FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


add_library(waveMath STATIC
 # src/waveCalculations.cpp
  src/waveMovement.cpp
)

target_include_directories(waveMath PRIVATE
  ./include
)

if (test)

  add_executable(waveMathTest
     tests/test_movement.cpp
    # tests/test_calculations.cpp
  )

  target_include_directories(waveMathTest PRIVATE
    ./include
  )

  enable_testing()
  include(GoogleTest)
  gtest_discover_tests(waveMathTest)

  target_link_libraries(waveMathTest waveMath gtest_main)

endif()


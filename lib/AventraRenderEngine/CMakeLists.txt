cmake_minimum_required(VERSION 3.20)

find_package(OpenGL REQUIRED)


include(FetchContent)

# enable with -Dcuda=ON
option(test "Build all tests." OFF)

# Gtest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)


FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/3.3.7.zip
)


FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)




# Build imgui
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
  extern/imgui
  extern/imgui/backends
)
target_link_libraries(imgui glfw OpenGL::GL)


# Build Aventra Library  

add_library(Aventra STATIC
  src/lib.cpp
  src/menus.cpp
  src/Aventra_line.cpp
  src/Aventra_rect.cpp
  src/glad.c
  src/errors.cpp
  src/Aventra_arc.cpp
)
  
target_include_directories(Aventra PRIVATE
  include
  include/glad
  extern/imgui
  extern/imgui/backends
)


target_link_libraries(Aventra glfw OpenGL::GL imgui)


if (test)

  add_executable(Aventra_test
    tests/test_rect.cpp
    tests/test_arc.cpp
    src/errors.cpp
  )

  target_include_directories(Aventra_test PRIVATE
    include
    include/glad
    extern/imgui
    extern/imgui/backends
  )



  enable_testing()
  include(GoogleTest)
  gtest_discover_tests(Aventra_test)

  target_link_libraries(Aventra_test Aventra gtest_main)
  
endif()

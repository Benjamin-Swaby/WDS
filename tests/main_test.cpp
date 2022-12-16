#include <gtest/gtest.h>

#include "Aventra.hpp"
#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"



TEST(Main, glfwImpl) {

  // version number should be this
  EXPECT_EQ(GLFW_VERSION_MAJOR, 3);
  EXPECT_EQ(GLFW_VERSION_MINOR, 3);
  EXPECT_EQ(GLFW_VERSION_REVISION,7);
}

TEST(Main, AventraImpl) {

  auto win = new Aventra::Window(20,20, "Test Window");

  if (!win) {
    EXPECT_EQ(1,2); // just throw an error
  }

  EXPECT_EQ(win->err, 0);
  
}

TEST(Main, RectGeneration) {


  auto win = new Aventra::Window(20,20, "Test Window");
  
  for (int i = 0; i < 1000; i++) {
    auto r = new Aventra::Rect(0.0f, 0.0f, 0.0f, 0.0f);
    win->RectQueue.push_back(r);
  }

  EXPECT_EQ(win->RectQueue.size(), 1000);
  EXPECT_EQ(win->err, 0);
  
}


TEST(Main, ArcGeneration) {

  auto win = new Aventra::Window(20,20, "Test Window");

  for (int i = 0; i < 1000; i++) {
    auto r = new Aventra::Arc(0.0f, 0.0f, 0);
    win->ArcQueue.push_back(r);
  }

  EXPECT_EQ(win->ArcQueue.size(), 1000);
  EXPECT_EQ(win->err, 0);
  
}

TEST(Main, ArcGenerationShaderProgramAttached) {

  auto win = new Aventra::Window(20,20, "Test Window");

  auto r = new Aventra::Arc(0.0f, 0.0f, 0);
  
  unsigned int sP = r->getShaderProgram();

  for (int i = 0; i < 1000; i++) {
    r = new Aventra::Arc(0.0f, 0.0f, 0, sP);
    win->ArcQueue.push_back(r);
  }

  EXPECT_EQ(win->ArcQueue.size(), 1000);
  EXPECT_EQ(win->err, 0);
}


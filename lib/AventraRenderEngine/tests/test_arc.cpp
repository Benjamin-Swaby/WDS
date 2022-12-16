#include <gtest/gtest.h>

#include "Aventra.hpp"
#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"

#include <iostream>

TEST(Aventra, ArcCreation) {

  auto win = new Aventra::Window(20, 20, "Test Window");

  
  // test for all plausable values of r
  for (float r = 0.0f; r < 3.0f; r+=0.1f) {
    for (float cx = -1.0f;  cx < 1.0f; cx+=0.1f) {
      for (float cy = -1.0f; cy < 1.0f; cy+=0.1f) {
        auto arc = new Aventra::Arc(r, cx, cy);
        EXPECT_EQ(arc->getR(),r);
        EXPECT_EQ(arc->getCx(),cx);
        EXPECT_EQ(arc->getCy(),cy);
      }
    }
  }

}

TEST(Aventra, ArcCreationCachedShaderProgram) {
  auto win = new Aventra::Window(20, 20, "Test Window");

  auto arc = new Aventra::Arc(0.0f, 0.0f, 0);
  unsigned int sp = arc->getShaderProgram();

  for (float r = 0.0f; r < 3.0f; r+=0.1f) {
    for (float cx = -1.0f;  cx < 1.0f; cx+=0.1f) {
      for (float cy = -1.0f; cy < 1.0f; cy+=0.1f) {
        auto arc = new Aventra::Arc(r, cx, cy, sp);
        EXPECT_EQ(arc->getR(),r);
        EXPECT_EQ(arc->getCx(),cx);
        EXPECT_EQ(arc->getCy(),cy);
      }
    }
  }
}

TEST(Aventra, ArcScale) {

  auto win = new Aventra::Window(200,200, "Test Window");

  auto arc = new Aventra::Arc(0.0f, 0.0f, 0);
  unsigned int sp = arc->getShaderProgram();

  for (float r = 0.0f; r < 3.0f; r+=0.1f) {
    for (float cx = -1.0f;  cx < 1.0f; cx+=0.1f) {
      for (float cy = -1.0f; cy < 1.0f; cy+=0.1f) {
        for (float t = 0.0f; t < 2.0f; t += 0.1f) {
          auto arc = new Aventra::Arc(r, cx, cy, sp);
          arc->Scale(t);
          EXPECT_EQ(arc->getR(), r + t);
          EXPECT_EQ(arc->getCx(),cx);
          EXPECT_EQ(arc->getCy(),cy);
        }
      }
    }
  }
  
}


TEST(Aventra, ArcMoveCX) {

  auto win = new Aventra::Window(200,200, "Test Window");

  auto arc = new Aventra::Arc(0.0f, 0.0f, 0);
  unsigned int sp = arc->getShaderProgram();

  for (float r = 0.0f; r < 3.0f; r+=0.1f) {
    for (float cx = -1.0f;  cx < 1.0f; cx+=0.1f) {
      for (float cy = -1.0f; cy < 1.0f; cy+=0.1f) {
        for (float t = -1.0f; t < 2.0f; t += 0.1f) {
          auto arc = new Aventra::Arc(r, cx, cy, sp);
          //arc->SetPos(t, 0.0f);
          EXPECT_EQ(arc->getR(), r);
          //EXPECT_EQ(arc->getCx(),t);
          EXPECT_EQ(arc->getCy(),cy);
        }
      }
    }
  }
  
  
}


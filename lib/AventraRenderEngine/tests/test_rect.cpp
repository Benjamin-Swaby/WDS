#include <gtest/gtest.h>

#include "Aventra.hpp"
#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"

#include <iostream>


inline Aventra::Window* genTestWindow() {
  auto win = new Aventra::Window(200, 200, "Test Window");
  return win;
}


TEST(Aventra, RectCreation) {
  auto win = genTestWindow();
  auto rect = new Aventra::Rect(0.0f,0.0f,0.0f,0.0f);
  
  for (float x = -2.0f; x < 2.0f; x += 0.5f) {
    for (float y = -2.0f; y < 2.0f; y += 0.5f) {
      for (float width = -2.0f; width < 2.0f; width += 0.5f) {
        for (float height = -2.0f; height < 2.0f; height += 0.5f) {
          rect = new Aventra::Rect(x, y, width, height);
          EXPECT_EQ(rect->x, x);
          EXPECT_EQ(rect->y, y);
          EXPECT_EQ(rect->width, width);
          EXPECT_EQ(rect->height, height);
        }
      }
    }
  }
}


TEST(Aventra, RectCreationCachedShaderProgram) {
  auto win = genTestWindow();
  auto rect = new Aventra::Rect(0.0f,0.0f,0.0f,0.0f);
  unsigned int sp = rect->getShaderProgram();
  
  for (float x = -2.0f; x < 2.0f; x += 0.5f) {
    for (float y = -2.0f; y < 2.0f; y += 0.5f) {
      for (float width = -2.0f; width < 2.0f; width += 0.5f) {
        for (float height = -2.0f; height < 2.0f; height += 0.5f) {
          rect = new Aventra::Rect(x, y, width, height, sp);
          EXPECT_EQ(rect->x, x);
          EXPECT_EQ(rect->y, y);
          EXPECT_EQ(rect->width, width);
          EXPECT_EQ(rect->height, height);
        }
      }
    }
  }
}


TEST (Aventra, RectTranslation) {
  auto win = genTestWindow();
  auto rect = new Aventra::Rect(0.0f,0.0f,0.0f,0.0f);
  
  for (float x = -2.0f; x < 2.0f; x += 0.5f) {
    for (float y = -2.0f; y < 2.0f; y += 0.5f) {
      for (float width = -2.0f; width < 2.0f; width += 0.5f) {
        for (float height = -2.0f; height < 2.0f; height += 0.5f) {
          rect = new Aventra::Rect(x, y, width, height);
          rect->Translate(10, -10);
          EXPECT_EQ(rect->x, x + 10);
          EXPECT_EQ(rect->y, y - 10);
          EXPECT_EQ(rect->width, width);
          EXPECT_EQ(rect->height, height);
        }
      }
    }
  }
}

TEST (Aventra, RectSetPos) {
  auto win = genTestWindow();
  auto rect = new Aventra::Rect(0.0f,0.0f,0.0f,0.0f);
  
  for (float x = -2.0f; x < 2.0f; x += 0.5f) {
    for (float y = -2.0f; y < 2.0f; y += 0.5f) {
      for (float width = -2.0f; width < 2.0f; width += 0.5f) {
        for (float height = -2.0f; height < 2.0f; height += 0.5f) {
          rect = new Aventra::Rect(x, y, width, height);
          rect->SetPos(y, x);
          EXPECT_EQ(rect->x, y);
          EXPECT_EQ(rect->y,  x);
          EXPECT_EQ(rect->width, width);
          EXPECT_EQ(rect->height, height);
        }
      }
    }
  }
}






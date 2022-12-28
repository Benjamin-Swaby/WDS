#pragma once
#include "./glad/glad.h"


namespace Aventra {

  class Line {

  private:
    float startx, starty, endx, endy;
    float r, g, b;
    
  public:
    Line(float startx, float starty, float endx, float endy);
    Line(float starty, float endy); // quick declare

    void setColour(float r, float g, float b);
    void Draw();
    
  };

}

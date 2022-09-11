#pragma once
#include "./glad/glad.h"
//#include "GL/gl.h"

namespace Aventra {
  class Rect {
  private:
    float x, y, width, height;
    unsigned int  VBO, VAO, EBO;
    unsigned int shaderProgram; 

  public:
    Rect(float x, float y, float width, float height);
    void Draw();
    void Destroy();
    ~Rect(){this->Destroy();}
  };
}

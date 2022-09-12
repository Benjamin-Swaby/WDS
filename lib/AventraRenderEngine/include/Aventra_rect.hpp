#pragma once
#include "./glad/glad.h"

//#include "GL/gl.h"

namespace Aventra {
  class Rect {
  private:
    
    unsigned int  VBO, VAO, EBO;
    unsigned int shaderProgram; 

  public:

    float x, y, width, height;
    
    Rect(float x, float y, float width, float height);
    void Draw();
    void Translate(float Mx, float My);
    void SetPos(float Mx, float My);
    void Destroy();
    ~Rect(){
      this->Destroy();
    }
  };
}

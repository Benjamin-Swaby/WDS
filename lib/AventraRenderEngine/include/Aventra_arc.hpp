#pragma once
#include "./glad/glad.h"

namespace Aventra {
  class Arc {
    
  private:
    
    unsigned int VBO, VAO, EBO;
    unsigned int shaderProgram;
    float r, cx;
    float red, green, blue;
    
  public:
    float cy;
    
    Arc(float r, float cx, float cy);
    Arc(float r, float cx, float cy, unsigned int shaderProgram);
    void Draw(int N, float slitWidth, float wavelength, float vertOffset);
    unsigned int getShaderProgram(){return this->shaderProgram;}
    float getR(){return this->r;}
    void setR(float r) {this->r = r;}
    void Scale(float x);
    void SetColour(float r, float g, float b);
    void SetPos(float cx, float cy);
    void Destroy();

    ~Arc() {
      this->Destroy();
    }
    
  };
}

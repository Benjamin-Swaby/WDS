#pragma once
#include "./glad/glad.h"

namespace Aventra {
  class Arc {
    
  private:
    
    unsigned int VBO, VAO, EBO;
    unsigned int shaderProgram;
    float r, cx, cy;
    
  public:
    
    Arc(float r, float cx, float cy);
    Arc(float r, float cx, float cy, unsigned int shaderProgram);
    void Draw(int N);
    unsigned int getShaderProgram(){return this->shaderProgram;}
    float getR(){return this->r;}
    void setR(float r) {this->r = r;}
    void Scale(float x);
    void SetPos(float cx, float cy);
    void Destroy();

    ~Arc() {
      this->Destroy();
    }
    
  };
}

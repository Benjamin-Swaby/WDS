#pragma once
#include "./glad/glad.h"

namespace Aventra {
  class Arc {
    
  private:
    
    unsigned int VBO, VAO, EBO, VBO_Cuda;
    unsigned int shaderProgram;
    float r, cx, cy;
    float red, green, blue;
    
  public:
   
    Arc(float r, float cx, float cy);
    Arc(float r, float cx, float cy, unsigned int shaderProgram);
    
    void Draw(int N, float slitWidth, float wavelength, float vertOffset);
    void Scale(float x);
    void Destroy();

    void setR(float r) {this->r = r;}
    void SetColour(float r, float g, float b);
    void SetPos(float cx, float cy);
    
    unsigned int getShaderProgram(){return this->shaderProgram;}
    float getR(){return this->r;}
    float getCx(){return this->cx;}
    float getCy(){return this->cy;}

    ~Arc() {
      this->Destroy();
    }
    
  };
}

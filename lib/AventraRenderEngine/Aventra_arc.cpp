#include "./include/Aventra_arc.hpp"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include "./glad/glad.h"
#include <math.h>


using namespace Aventra;

const char *vertexShaderSource2 = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
    "}\n\0";


inline unsigned int compileShaders() {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource2, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    //WDS::Error("Failed to compile Vertex shader", 30, false).Log();
   }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource2, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//WDS::Error("Failed to compile Fragment Shader", 31, false).Log();
  }

      // link the shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  } else {
    //std::cout << "Linked Shaders Sucessfully\n";
  }

  //clean up shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}


#define pi 3.141592653589793

void Arc::Draw(int N, float slitWidth, float wavelength, float vertOffset) {

  
  glUseProgram(this->shaderProgram);
  
  //glBindVertexArray(this->VAO);
  //glDrawArrays(GL_LINES, 0, 360);
  //glBindVertexArray(0);
  glLineWidth(5);


  
  glBegin(GL_LINES);
  glUseProgram(0);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  
  glColor3f(this->red, this->green, this->blue);
  const float halfPiByN = 0.5 * pi/N;
  const float quaterTurn = pi/2;
  float flatness = (wavelength < slitWidth) ? (wavelength / slitWidth) : 1.0f;
  float x,y;
  
  for (int i = 0; i < N; i++) {
    y = this->cy + this->r * cos((halfPiByN * i) + quaterTurn);
    x = this->cx + this->r * sin((halfPiByN * i * flatness) + quaterTurn) * flatness;
    glVertex2f(x,y+vertOffset);
  }   
  glEnd();

  glBegin(GL_LINES);
  glUseProgram(0);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glColor3f(this->red, this->green, this->blue);
  for (int i = 0; i < N; i++) {
    y = this->cy + this->r * cos((halfPiByN * i) + quaterTurn);
    x = this->cx + this->r * sin((halfPiByN * i * flatness) + quaterTurn) * flatness;
    glVertex2f(x,-y+vertOffset);
  }

  glEnd();
  
  glLineWidth(1);
  
}


Arc::Arc(float r, float cx, float cy, unsigned int shaderProgram) {
  this->shaderProgram = shaderProgram;
  this->r = r;
  this->cx = cx;
  this->cy = cy;
  
}


void Arc::Destroy() {
  glDeleteBuffers(1, &this->VAO);
  glDeleteBuffers(1, &this->VBO);
  glDeleteBuffers(1, &this->EBO);
  free(this);
}

Arc::Arc(float r, float cx, float cy) {
  this->shaderProgram = compileShaders();
  this->r = r;
  this->cx = cx;
  this->cy = cy;
    
}

void Arc::Scale(float x) {
  this->r += x;
}

void Arc::SetColour(float r, float g, float b) {
  this->red = r;
  this->green = g;
  this->blue = b;
}

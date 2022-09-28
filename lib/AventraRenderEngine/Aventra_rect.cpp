#include "./include/Aventra_rect.hpp"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include "./glad/glad.h"

using namespace Aventra;


const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
    "}\n\0";


inline unsigned int compileShaders() {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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


Rect::Rect(float x, float y, float width, float height) {

  this->shaderProgram = compileShaders();
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  
  float vertices[] = {
    x, y, 0.0f, // bl
    x+width, y, 0.0f, //br
    x+width, y + height, 0.0f, //tr
    x, y+height, 0.0f // tl
  };
  
  int indicies[] = {
    0, 1, 3,
    1, 2, 3
  };


  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  glGenBuffers(1, &this->EBO);

  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
}


void Rect::Draw() {
  glUseProgram(this->shaderProgram);
  glBindVertexArray(this->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  
}

void Rect::Destroy() {
  glDeleteBuffers(1, &this->VAO);
  glDeleteBuffers(1, &this->VBO);
  glDeleteBuffers(1, &this->EBO);
  free(this);
}


void Rect::Translate(float Mx, float My) {

  this->x += Mx;
  this->y += My;
  
  float vertices[] = {
    this->x, this->y, 0.0f, // bl
    this->x + this->width, this->y, 0.0f, //br
    this->x + this->width, this->y + this->height, 0.0f, //tr
    this->x, this->y + this->height, 0.0f // tl
  };

  int indicies[] = {
    0, 1, 3,
    1, 2, 3
  };
   
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
}


void Rect::SetPos(float Mx, float My) {

  this->x = Mx;
  this->y = My;
  
  float vertices[] = {
    this->x, this->y, 0.0f, // bl
    this->x + this->width, this->y, 0.0f, //br
    this->x + this->width, this->y + this->height, 0.0f, //tr
    this->x, this->y + this->height, 0.0f // tl
  };

  int indicies[] = {
    0, 1, 3,
    1, 2, 3
  };
   
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
}

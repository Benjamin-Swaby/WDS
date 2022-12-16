#include <../include/glad/glad.h>
#include <cuda_gl_interop.h>
#include <iostream>
#include <../include/Aventra_arc.hpp>
#define GL_GLEXT_PROTOTYPES


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



Arc::Arc(float r, float cx, float cy) {

  this->shaderProgram = compileShaders();
  this->r = r;
  this->cx = cx;
  this->cy = cy;

  // Allocate the VBO
  glGenBuffers(1, &this->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  unsigned int size = 90 * 4 * sizeof(float); // 90, 4 floats
  glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  cudaGraphicsResource_t VBO_Cuda;
  
  // register with CUDA
  cudaGraphicsGLRegisterBuffer(&VBO_Cuda, this->VBO, cudaGraphicsMapFlagsWriteDiscard);
  cudaGraphicsMapResources(1, &VBO_Cuda, 0);
  size_t numBytes;
  cudaGraphicsResourceGetMappedPointer((void **)&this->VBO, &numBytes, VBO_Cuda);
  
}

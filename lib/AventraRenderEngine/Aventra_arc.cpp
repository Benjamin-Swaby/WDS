#include "../include/Aventra_arc.hpp"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include "../include/glad/glad.h"
#include <math.h>

using namespace Aventra;


#define pi 3.141592653589793
void Arc::Draw(int N, float slitWidth, float wavelength, float vertOffset) {

  glLineWidth(5);
  glBegin(GL_LINES);
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
    glVertex2f(x,y - vertOffset);
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
    glVertex2f(x,-y + vertOffset);
  }

  glEnd();
  
  glLineWidth(1);
  
}

void Arc::Destroy() {
  glDeleteBuffers(1, &this->VAO);
  glDeleteBuffers(1, &this->VBO);
  glDeleteBuffers(1, &this->EBO);
  free(this);
}

void Arc::Scale(float x) {
  this->r += x;
}

void Arc::SetColour(float r, float g, float b) {
  this->red = r;
  this->green = g;
  this->blue = b;
}


void Arc::SetPos(float cx, float cy) {
  this->cx = cx;
  this->cy = cy;
}


Arc::Arc(float r, float cx, float cy) {
  this->r = r;
  this->cx = cx;
  this->cy = cy;  
}

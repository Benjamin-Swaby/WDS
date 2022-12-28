#include "Aventra_line.hpp"
#include "./glad/glad.h"

using namespace Aventra;


Line::Line(float startx, float starty, float endx, float endy) {

  this->startx = startx;
  this->starty = starty;
  this->endx = endx;
  this->endy = endy;

  // red by default
  this->r = 0.0f;
  this->g = 1.0f;
  this->b = 0.0f;
} 

Line::Line(float starty, float endy) {

  this->startx = 0.0f;
  this->starty = starty;
  this->endx = 1.0f;
  this->endy = endy;

  // red by default
  this->r = 0.0f;
  this->g = 1.0f;
  this->b = 0.0f;
}


void Line::setColour(float r, float g, float b) {
  this->r = r;
  this->g = g;
  this->b = b;
}


void Line::Draw() {

  glLineWidth(5);
  glShadeModel(GL_SMOOTH);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glMatrixMode(GL_MODELVIEW);
  glUseProgram(0);

  // draw a line between 2 points
  glBegin(GL_LINES);

  glColor3f(this->r, this->g, this->b);
  glVertex2f(this->startx, this->starty);
  glVertex2f(this->endx, this->endy);

  glEnd();
  
  glLineWidth(1);
}

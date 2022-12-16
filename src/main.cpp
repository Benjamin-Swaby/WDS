
#include <iostream>

#include "errors.hpp"    
#include "Aventra.hpp"
#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"


using namespace WDS;
using namespace Aventra;


const double distance = 0.03;
const int number = 400;

int main(void) {

  // window creation
  auto win = new Window(2000,2000, "WDS V0.1D");

  // generate input waves as rectangles
  for (int i = 0; i < number; i++) {
    auto r = new Rect(-0.99 + (i * distance), -0.90f, 0.005f, 1.80f);
    win->RectQueue.push_back(r);
  }

  // reference arc used to compile shaderProgram
  auto a = new Arc(0.0 + 0, 0.0, 0);
  unsigned int sP = a->getShaderProgram();

  // generation of arcs to arcqueue.
  for (int i = 0; i < number; i++) {
    auto a = new Arc(0.0 + (i * 0.1), 0.0, 0, sP);
    win->ArcQueue.push_back(a);
  }

  
  // main render loop
  while (!win->shouldClose() && !win->err) {
    win->update();
  }
  
}



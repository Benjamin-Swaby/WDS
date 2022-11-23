
#include <iostream>

#include "errors.hpp"    
#include "Aventra.hpp"
#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"
#include "chrono"


using namespace WDS;
using namespace Aventra;

static double simTime = -0.99;
const double scale = 0.03;
const int number = 400;

int main(void) {
  auto win = new Window(2000,2000, "WDS V0.1D");

  for (int i = 0; i < number; i++) {
    auto r = new Rect(simTime + (i * scale), -0.90f, 0.005f, 1.80f);
    win->RectQueue.push_back(r);
  }

  auto a = new Arc(0.0 + 0, 0.0, 0);
  
  unsigned int sP = a->getShaderProgram();
  
  for (int i = 0; i < number; i++) {
    auto a = new Arc(0.0 + (i * 0.1), 0.0, 0, sP);
    win->ArcQueue.push_back(a);
  }

  
  // main render loop
  while (!win->shouldClose() && !win->err) {
    win->update();
  }
  
}



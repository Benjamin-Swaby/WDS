
#include <iostream>

#include "errors.hpp"    
#include "Aventra.hpp"
#include "Aventra_rect.hpp"

using namespace WDS;
using namespace Aventra;

static double simTime = -0.99;
const double scale = 0.03;
const int number = 200;


void Step(float delta) {

}


int main(void) {
  auto win = new Window(1920,1080, "WDS V0.1D");


  // test initialisation of objects. Should be calculated using inputs.
  for (int i = 0; i < number; i++) {
    auto r = new Rect(simTime + (i * scale), -0.90f, 0.005f, 1.80f);
    win->RectQueue.push_back(r);
   }

  while (!win->shouldClose() && !win->err) {
    win->update(Step);
  }
  
}



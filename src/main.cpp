
#include <iostream>

#include "errors.hpp"    
#include "Aventra.hpp"
#include "Aventra_rect.hpp"

using namespace WDS;
using namespace Aventra;

static double simTime = -0.99;
const double scale = 0.001;
const int number = 20;

void Step(float delta) {
 
  auto  my_rect = new Rect(simTime, -0.90f, 0.05f, 1.8f);
  my_rect->Draw();


  simTime += scale;
  if (simTime > 1) {simTime = 0;}
}


int main(void) {
  auto win = new Window(1920,1080, "WDS V0.1D");
  
  while (!win->shouldClose() && !win->err) {
    win->update(Step);
  }

}




#include <iostream>
#include <vector>
#include <algorithm>

#include "errors.hpp"    
#include "Aventra.hpp"
#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"

#include "waveMovement.hpp"


using namespace WDS;
using namespace Aventra;


const double distance = 0.03;
const int number = 400;


void calculateDiffraction(Window* w) {
  Arc *master = w->ArcQueue.back();
  Arc *tail = w->ArcQueue.front();

  
  float flatness = (w->Wavelength < w->slitWidth) ? (w->Wavelength / w->slitWidth) : 1.0f;
    
  master->Scale((w->Wavelength * w->Frequency));
  if (master->getR() > 3.0f) {master->setR(tail->getR() - w->Wavelength);}

  float home = master->getR();
  for (int index = w->ArcQueue.size() - 2; index >=0; index--) {    
    w->ArcQueue[index]->setR((home - (index  * w->Wavelength)));
  }

  
  std::vector<float> offsets = waveMath::getOffsets(w->Slits);
  
  for (auto o : offsets) {
    for (auto a : w->ArcQueue) {
      if (a->getR() >= 0.0f) {
        a->Draw(180, w->slitWidth, w->Wavelength, o);
      }  
    }
  }
  
}

void moveIncidentWaves(Window* w) {

  // define a master wave.
  Rect *prev = w->RectQueue.back();
  // move the master wave
  prev->Translate((w->Wavelength * w->Frequency), 0.0f);

  // check bounds of master wave
  if (prev->x > -0.03f) {prev->x = w->RectQueue.front()->x - w->Wavelength;}

  // move the secondary waves behind a set distance
  for (int index = w->RectQueue.size() - 2; index >= 0; index--) {
    w->RectQueue[index]->SetPos((prev->x) - (index*(w->Wavelength)), w->RectQueue[index]->y);
  }
}


int main() {

  // window creation
  auto win = new Window(2000,2000, "WDS V0.1D");

  // generate input waves as rectangles
  for (int i = 0; i < number; i++) {
    auto r = new Rect(-0.99 + (i * distance), -0.90f, 0.005f, 1.80f);
    win->RectQueue.push_back(r);
  }

  // generation of arcs to arcqueue.
  for (int i = 0; i < number; i++) {
    auto a = new Arc(0.0 + (i * 0.1), 0.0, 0);
    win->ArcQueue.push_back(a);
  }


  for (int N = 0; N < 10; N++) {
    std::cout << N << " => ";
    auto vec = waveMath::getOffsets(N);
    std::sort(vec.begin(), vec.end());
    for (auto o : vec) {
      std::cout << o << ",";
    }
    std::cout << "\n";
  }
  

  
  // main render loop
  while (!win->shouldClose() && !win->err) {
    win->beginRender();
    moveIncidentWaves(win);
    calculateDiffraction(win);
    win->swap();
    
  }
  
}



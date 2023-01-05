
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "errors.hpp"

#include "Aventra.hpp"
#include "Aventra_line.hpp"
#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"

#include "waveMovement.hpp"
#include "waveCalculations.hpp"


using namespace WDS;
using namespace Aventra;


const double distance = 0.03;
const int number = 400;


void calculateDiffraction(Window* w) {
  Arc *master = w->ArcQueue.back();
  Arc *tail = w->ArcQueue.front();

  
  float flatness = (w->Wavelength < w->slitWidth) ? (w->Wavelength / w->slitWidth) : 1.0f;

  // scale the master wave - if it's too far bring it 1 wavelength behind the last wave in the queue
  master->Scale((w->Wavelength * w->Frequency));
  if (master->getR() > 3.0f) {master->setR(tail->getR() - w->Wavelength);}


  // move the other waves a distance behind the master wave
  float home = master->getR();
  for (int index = w->ArcQueue.size() - 2; index >=0; index--) {    
    w->ArcQueue[index]->setR((home - (index  * w->Wavelength)));
  }

  // calculate evenly spaced points along the grating
  std::vector<float> offsets = waveMath::getOffsets(w->Slits);

  // for each offset for each arc - render an arc.
  for (auto o : offsets) {
    for (auto a : w->ArcQueue) {
      if (a->getR() >= 0.0f) {
        a->Draw((7200/w->Slits), w->slitWidth, w->Wavelength, o); // Number of points scales with the number of slits to increase performance
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


void drawMinimaMaxima(Window* w) {

  if (w->Slits < 2) {
    // draw a line @ 0.0f and return
    w->numberOfMaxima = 1;
    return;
  }

  // calculate the maximum number of orders
  std::vector<float> offsets = waveMath::getOffsets(w->Slits);
  float d = offsets[1] - offsets[0];
  int maximumOrders = waveMath::getMaxOrders(d, w->Wavelength);
  w->numberOfMaxima = (maximumOrders * 2) - 1;

  if (w->showMaxima) {
    std::vector<float> orderAngles;
    for (int i = 0; i < maximumOrders; i++) {
      orderAngles.push_back(waveMath::getAngularSeperationRad(d, i, w->Wavelength));
    }
    
    std::vector<float> YposOfConstructiveInterference;
    // distance D (between grating and screen) is 1.0f 
    YposOfConstructiveInterference = waveMath::getPointsOfConstructiveInterference(1.0f, orderAngles);
    
    Line* line;
    for (auto order : YposOfConstructiveInterference) {
      line = new Line(0.0f, order);
      line->Draw();
      line = new Line(0.0f, order * -1);
      line->Draw();
    }
  }
}

int main(int argc, char** argv) {

  int res = 1000;
  if (argc > 1) {
    res = std::stoi(argv[1]);
  }
  
  // window creation
  auto win = new Window(res, res, "WDS V0.1D");

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

  
  // main render loop
  while (!win->shouldClose() && !win->err) {
    win->beginRender();
    moveIncidentWaves(win);
    calculateDiffraction(win);
    drawMinimaMaxima(win);
    win->swap();
    
  }
  
}



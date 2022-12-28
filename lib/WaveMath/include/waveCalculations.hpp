#pragma once

#include <vector>
#include <math.h>
#include <cstdlib>

namespace waveMath {

  float getAngularSeperationRad(float d, int n, float wavelength);
  float getOrderOfMaxima(float d, float theta, float wavelength);
  inline int getMaxOrders(float d, float wavelength) {return abs((int)floor(d/wavelength));}
  float lineGradFromAngularSeperation(float AngularSeperation);
  std::vector<float> getPointsOfConstructiveInterference(float D, std::vector<float> orderAngles);

}

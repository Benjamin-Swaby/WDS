#include "../include/waveCalculations.hpp"

#include <vector>
#include <cmath>

using std::vector;
using std::asin;
using std::sin;

float waveMath::getAngularSeperationRad(float d, int n, float wavelength) {
  return asin((n * wavelength) / d);
}


inline float waveMath::getOrderOfMaxima(float d, float theta, float wavelength) {
  return (d * sin(theta)) / wavelength;
}

float waveMath::lineGradFromAngularSeperation(float AngularSeperation) {
  return 0.1f;
}



vector<float> waveMath::getPointsOfConstructiveInterference(float D, vector<float> orderAngles) {

  vector<float> result;

  for (auto a : orderAngles) {
    result.push_back(tan(a) * D);
  }

  return result;
}



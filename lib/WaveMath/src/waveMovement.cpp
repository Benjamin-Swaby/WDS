#include <vector>

#include "../include/waveMovement.hpp"


using namespace waveMath;
using std::vector;

vector<float> waveMath::getOffsets(int slits) {
  
  vector<float> offsets;

  if (slits <= 0) {
    return offsets;
  }
  
  if (slits & 1) {

    slits += 2;
    offsets.push_back(0.0f);

    for (float i = 1.0f; i < slits / 2; i++) {
      offsets.push_back(i/slits);
    }
    
  } else {
    
    offsets.push_back(1.0f/(2 * slits));
    for (float i = 1.0f; i < (slits / 2); i++) {
      offsets.push_back((i / slits) + offsets[0]);
    }
    
  }

  for (int i = 0; i < (int)(slits / 2); i++) {
    if (offsets[i] != 0.0f) {
      offsets.push_back(offsets[i] * -1);
    }
  }

  // double all the values
  for (int i = 0; i < slits; i++) {
    offsets[i] = offsets[i] * 2;
  }

  
  return offsets;
}

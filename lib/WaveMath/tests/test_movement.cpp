#include <gtest/gtest.h>
#include <vector>
#include <iostream>

#include "../include/waveMovement.hpp"

using namespace waveMath;

TEST(waveMath, getOffsets) {

  for (int N = 0; N < 25; N++) {
    std::vector results = getOffsets(N);
    EXPECT_EQ(results.size(), N);
    
  }
  
}

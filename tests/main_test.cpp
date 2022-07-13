#include <gtest/gtest.h>
#include <GLFW/glfw3.h>


TEST(VersionTest, glfwImpl) {

  // version number should be this
  EXPECT_EQ(GLFW_VERSION_MAJOR, 3);
  EXPECT_EQ(GLFW_VERSION_MINOR, 3);
  EXPECT_EQ(GLFW_VERSION_REVISION,7);
}

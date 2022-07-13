
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <math.h>


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {

  printf("Compiled against GLFW %i.%i.%i\n",
       GLFW_VERSION_MAJOR,
       GLFW_VERSION_MINOR,
       GLFW_VERSION_REVISION);

  GLFWwindow* Win;


  if (!glfwInit()) {
    // TODO robust panic here
    std::cout << "Failed to initialise" << std::endl;
    return -1;
  }

  Win = glfwCreateWindow(640, 640, "WDS V0.1D",NULL,NULL);
  
  if (!Win) {
    std::cout << "Failed to Create Window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(Win);


  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialise GLAD" << std::endl;
  }

  
  // main render loop

  while (!glfwWindowShouldClose(Win)) {
    
    int width, height;
    glfwGetFramebufferSize(Win, &width, &height);
    processInput(Win);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwPollEvents();
    glfwSwapBuffers(Win);
  }
    
  glfwTerminate();
  return 0;
  
  
}

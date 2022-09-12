#pragma once

#include <math.h>
#include <stdio.h>
#include <vector>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "./glad/glad.h"

#include "Aventra_rect.hpp"

using std::vector;

namespace Aventra {

  //static GLFWwindow* window;
  
  class Window {
  private:
    GLFWwindow* window;
    int x,y;
    bool debug = false;
    bool changeBGcolour = false;
    bool MainMenu = false;    
    double now = 0.0f;
    double last = 0.0f;
    float delta = 1.0f;
        
  public:

    int err = 0;
    double time = 0.0f;
    float bgR = 0.25, bgG = 0.3, bgB = 0.3;
    float Wavelength;
    float Frequency;
    int Slits;
    bool play;

    vector<Rect*> RectQueue;
    //vector<Arc> ArcQueue;
    vector<Rect> SlitQueue;
    
    Window(int x, int y, char *title);
    void update(void (*update)(float));
    int shouldClose();
  

    void renderDebugMenu(bool &debug);
    void renderColours(bool &show);
    void renderMainMenu();

    GLFWwindow* getWindow() {
      //return this->window;
    }
                            
    
    ~Window() {
      glfwDestroyWindow(window);
      glfwTerminate();
    }
    
  };


  
  
}

#pragma once

#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "./glad/glad.h"

#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"

using std::vector;
using std::string;


namespace Aventra {
  
  class Window {
  private:
    GLFWwindow* window;
    int x,y;
    bool debug = false;
    bool changeBGcolour = false;
    bool MainMenu = false;
    vector<string> logVec;
    
  public:
    int err = 0;
    float bgR = 0.25, bgG = 0.3, bgB = 0.3;
    float Wavelength;
    float Frequency;
    int Slits;
    float slitWidth;

    vector<Rect*> RectQueue;
    vector<Rect*> SlitQueue;
    vector<Arc*> ArcQueue; 
    
    Window(int x, int y, char *title);
    void beginRender();
    void swap();
    int shouldClose();
    void renderDebugMenu(bool &debug);
    void renderColours(bool &show);
    void renderMainMenu();
    void log(std::string msg) {this->logVec.push_back(msg);}

    ~Window() {
      glfwDestroyWindow(window);
      glfwTerminate();
    }
    
  };


  
  
}

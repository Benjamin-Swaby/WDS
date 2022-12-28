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
#include "Aventra_line.hpp"

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
    
    
  public:
    int err = 0;
    float bgR = 0.25, bgG = 0.3, bgB = 0.3;
    float Wavelength;
    float Frequency;
    int Slits;
    float slitWidth;
    int numberOfMaxima;
    bool showMaxima = false;

    vector<Rect*> RectQueue;
    vector<Line*> MaximaQueue;
    vector<Arc*> ArcQueue; 
    
    Window(int x, int y, char *title);
    void beginRender();
    void swap();
    int shouldClose();
    void renderDebugMenu(bool &debug);
    void renderColours(bool &show);
    void renderMainMenu();
    

    ~Window() {
      glfwDestroyWindow(window);
      glfwTerminate();
    }
    
  };

}

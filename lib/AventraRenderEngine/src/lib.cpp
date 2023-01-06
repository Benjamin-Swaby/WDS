#include "Aventra.hpp"
#include "Aventra_rect.hpp"
#include "Aventra_arc.hpp"
#include <iostream>

#include "../../include/errors.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


using namespace Aventra;


Window::Window(int x, int y, char *title) {
  
#if defined(IMGUI_IMPL_OPENGL_ES2)
      const char* glsl_version = "#version 100";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
      const char* glsl_version = "#version 150";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
      const char* glsl_version = "#version 130";
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
      

      // initialisation of class attributes:
      this->Wavelength = 0.003f; // make sure the wavelength is > 0!
      this->Frequency = 0.0f;
      this->Slits = 1;
      
      this->x = x;
      this->y = y;

      // initialse GLFW
      if (!glfwInit()) {
        WDS::Error("Failed to Init GLFW", -12, true);
        this->err = 1;
      }

      // generate window object
      glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
      this->window = glfwCreateWindow(x,y, title, NULL, NULL);


      // Create a window
      if (!this->window) {
        glfwTerminate();
        WDS::Error("Failed to Create Window", -12, true);
        this->err = 1;
      }

      glfwMakeContextCurrent(this->window);
      glfwSwapInterval(1); // enable Vsync

      // set window size limits and lock aspect ration to 1:1
      // min = 200x200 , max = NULL
      glfwSetWindowSizeLimits(this->window, 200, 200,GLFW_DONT_CARE, GLFW_DONT_CARE);

      // lock aspect Ratio
      glfwSetWindowAspectRatio(this->window, 1, 1);
      
      //  using the Glad OpenGL loader to set some sane defaults for OpenGL
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      // ~~Chosen not to panic here as the program still may run.~~ //Unlikely! 
           WDS::Error("Failed to load GLAD configuration", 14, true);
           this->err = 1;
       }

      // -- IMGUI Attachment -- //
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      ImGui::StyleColorsLight();
      ImGui_ImplGlfw_InitForOpenGL(this->window, true);
      ImGui_ImplOpenGL3_Init(glsl_version);
}



void Window::beginRender() {

  glfwGetWindowSize(this->window, &this->x, &this->y);
  
  glViewport(0, 0, this->x, this->y);
  glClearColor(this->bgR, this->bgG, this->bgB, 1);
  glClear(GL_COLOR_BUFFER_BIT);
   
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  
  if (this->debug) {this->renderDebugMenu(this->debug);}
  if (this->changeBGcolour) {this->renderColours(this->changeBGcolour);}
  

  renderMainMenu();  

  // Draw all wavefronts
  for (auto r : this->RectQueue) {
    r->Draw();
  }
  
}

void Window::swap() {

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  
  glfwSwapBuffers(this->window);
  glfwPollEvents();
  
}

int Window::shouldClose() {
  return glfwWindowShouldClose(this->window);
}



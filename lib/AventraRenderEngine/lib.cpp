#include "Aventra.hpp"
#include "Aventra_rect.hpp"
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
      

      this->x = x;
      this->y = y;
      
      if (!glfwInit()) {
        WDS::Error("Failed to Init GLFW", -12, true);
        this->err = 1;
      }

      // generate window object
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
      this->window = glfwCreateWindow(x,y, title, NULL, NULL);

      if (!this->window) {
        glfwTerminate();
        WDS::Error("Failed to Create Window", -12, true);
        this->err = 1;
      }

      glfwMakeContextCurrent(this->window);
      glfwSwapInterval(1); // enable Vsync

      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      // Chosen not to panic here as the program still may run. 
           WDS::Error("Failed to load GLAD configuration", 14, false); 
       }

      // -- IMGUI Attachment -- //
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      ImGui::StyleColorsLight();
      ImGui_ImplGlfw_InitForOpenGL(this->window, true);
      ImGui_ImplOpenGL3_Init(glsl_version);
}



void Window::update(void (*update)(float)) {
  last = glfwGetTime();

  glViewport(0, 0, this->x, this->y);
  glClearColor(this->bgR, this->bgG, this->bgB, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  
  (*update)(delta);

  
  

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  
  if (this->debug) {this->renderDebugMenu(this->debug);}
  if (this->changeBGcolour) {this->renderColours(this->changeBGcolour);}
  

  renderMainMenu();  
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // define a master wave.
  Rect *prev = this->RectQueue.back();
  // move the master wave
  prev->Translate((this->Wavelength * this->Frequency), 0.0f);

  // check bounds of master wave
  if (prev->x > 0.0f) {prev->x = this->RectQueue.front()->x - this->Wavelength;}

  // move the slave waves behind a set distance
  for (int index = this->RectQueue.size() - 2; index >= 0; index--) {
    this->RectQueue[index]->SetPos((prev->x) - (index*(this->Wavelength)), this->RectQueue[index]->y);
  }

  // Draw all wavefronts
  for (auto r : this->RectQueue) {
    r->Draw();
  }
  
  glfwSwapBuffers(this->window);
  glfwPollEvents();
  

   
  now = glfwGetTime();
  delta = (float)(now - last) * 10.0f;
}

int Window::shouldClose() {
  return glfwWindowShouldClose(this->window);
}




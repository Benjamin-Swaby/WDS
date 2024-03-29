#include "Aventra.hpp"

#include "../../include/errors.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace Aventra;


void Window::renderDebugMenu(bool &debug) {
   // begin window definition.
  ImGui::Begin("Debug Options",&debug);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    
  if (ImGui::Button("Crash")) {
    WDS::Error("Forcefully crashed by dev", 99, true);
  }

  if (ImGui::Button("Soft Error")) {
    WDS::Error("Soft Error created by dev",98, false).ToStdOut();
  }

  if (ImGui::Button("Close")) {
    debug = false;
  }

 
  ImGui::End();
}

void Window::renderColours(bool &show) {
  ImGui::Begin("Background Colour", &show);
  ImGui::SliderFloat("Red", &this->bgR, 0.0f, 1.0f);
  ImGui::SliderFloat("Green", &this->bgG, 0.0f, 1.0f);
  ImGui::SliderFloat("Blue", &this->bgB, 0.0f, 1.0f);
  ImGui::End();
}


void Window::renderMainMenu() {
  ImGui::Begin("WDS");
  
  ImGui::SliderFloat("Wavelength", &this->Wavelength, 0.03f, 0.75f); 
  ImGui::SliderFloat("Frequency", &this->Frequency, 0.0f, 0.5f);
  ImGui::SliderInt("Slits", &this->Slits, 1, 12);
  
  // calculate max slit width and reset bounds automatically
  float maxSlitWidth;
  if (this->Slits > 0.0f){

    maxSlitWidth = this->y / this->Slits;

  } else{maxSlitWidth = 0.0f;}

  
  if (this->slitWidth >= maxSlitWidth) {this->slitWidth = maxSlitWidth;}
  
  ImGui::SliderFloat("Slit Width", &this->slitWidth, 0.0f, maxSlitWidth / this->y);

  ImGui::Text("Wave Speed: %.3f cm/s", (this->Wavelength * this->Frequency) * 100);
  ImGui::Text("Number of Maxima: %d", this->numberOfMaxima);

  if (ImGui::Button("Show Maxima")) {
    this->showMaxima = !this->showMaxima;
  }
  
  if (ImGui::Button("Change Background Colour")) {
    this->changeBGcolour = !this->changeBGcolour;
  }
      
  if (ImGui::Button("Debug Mode")) {
    this->debug = !this->debug;
  }

  
  ImGui::End();

}

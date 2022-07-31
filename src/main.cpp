
#include <iostream>

#include "../include/errors.hpp"    

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <math.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
    "}\n\0";


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void RenderColours(float &r, float &g, float &b, bool &show) {

  ImGui::Begin("Background Colour", &show);
  ImGui::SliderFloat("Red", &r, 0.0f, 1.0f);
  ImGui::SliderFloat("Green", &g, 0.0f, 1.0f);
  ImGui::SliderFloat("Blue", &b, 0.0f, 1.0f);
  ImGui::End();
  
}


void TranslateMenu(bool &show, float &offset) {
  ImGui::Begin("Translate", &show);
  ImGui::SliderFloat("Amount", &offset, -0.02f, 0.02f);
  ImGui::End();
}

void RenderMainMenu(float &wavelength, float &frequency, bool &debug, bool &play, int &slits, bool &bg_colour) {

  ImGui::Begin("WDS");
  
  ImGui::SliderFloat("Wavelength", &wavelength, 0.0f, 100.0f); 
  ImGui::SliderFloat("Frequency", &frequency, 0.0f, 100.0f);
  ImGui::SliderInt("Slits", &slits, 0, 100);
 
 
  if (ImGui::Button("Play/Pause")) {
    play = !play;
  }

  ImGui::SameLine();
  if (ImGui::Button("Change Background Colour")) {
    bg_colour = !bg_colour;
  }
  
  if (ImGui::Button("Debug Mode")) {
    debug = true;
  }

  
  ImGui::End();
  
}


void RenderDebugMenu(bool &debug) {
    
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


int main(void) {

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

    // useful message to user about which version of GLFW is linked
    printf("Compiled against GLFW %i.%i.%i\n",
          GLFW_VERSION_MAJOR,
          GLFW_VERSION_MINOR,
          GLFW_VERSION_REVISION);

    // window definition
    GLFWwindow* Win;


    if (!glfwInit()) {
        WDS::Error("Failed to Initialise GLFW", 12, true);
        return -1;
    }

    Win = glfwCreateWindow(1920, 1080, "WDS V0.1D",NULL,NULL);    

    if (!Win) {
        WDS::Error("Failed to create GLFW context", 13, false);
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(Win);
    glfwSwapInterval(1); // enable vsync  

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      // Chosen not to panic here as the program still may run. 
      WDS::Error("Failed to load GLAD configuration", 14, false); 
    }

    //imgui setup:
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(Win, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // shader setup:
    // compile the vertexShader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	WDS::Error("Failed to compile Vertex shader", 30, false).Log();
    }

    // compile the fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	WDS::Error("Failed to compile Fragment Shader", 31, false).Log();
    }
    

    // link the shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	WDS::Error("Failed to Link Vertex and Fragment shaders", 32, false).Log();
    }

    //clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // define vertices (temp)
    

    
    // -- USER INPUT VARIABLES -- //
    int slits = 0;
    float wavelength, frequency = 0.0f;

    float b_red = 0.2f;
    float b_green = 0.3f;
    float b_blue = 0.3f;
    
    bool debug, play, bg_colour_change, translate = false;
    float offset = 0.0f;

    float vertices[] = {
	  -0.5f, -0.5f, 0.0f, // left  
	  0.5f, -0.5f, 0.0f, // right 
	  0.0f,  0.5f, 0.0f  // top   
    };
    
    // main render loop
    while (!glfwWindowShouldClose(Win)) {
    
        int width, height;
        glfwGetFramebufferSize(Win, &width, &height);
	glViewport(0, 0, width, height);
        processInput(Win);
	

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

	

	// bind to a VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
    
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
    
	glBindVertexArray(0); 


	// menu rendering
	RenderMainMenu(wavelength,frequency,debug,play,slits,bg_colour_change);
	TranslateMenu(translate,offset);

	for (int i = 0; i < 8; i+=3) {
	  vertices[i] += offset;
	}
	
	if (debug) {
	  RenderDebugMenu(debug);
	}

	if (bg_colour_change) {
	  RenderColours(b_red, b_green, b_blue, bg_colour_change);
	}
	
        glClearColor(b_red, b_green, b_blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


	
	
	// render stuff here!
        ImGui::Render();
	glUseProgram(shaderProgram);
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3);
      
        glfwPollEvents();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(Win);
    }
    
    glfwTerminate();
    return 0;
  
}



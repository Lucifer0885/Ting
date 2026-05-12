#include "Application.hpp"
#include "Logger/Logger.hpp"
#include "GLFW/glfw3.h"
#include <gl/gl.h>


Application::Application() { 
  Logger::getInstance().info("Application created");
  if(!glfwInit()){
    Logger::getInstance().error("Could not Initialize GLFW!");
  }

  this->window = glfwCreateWindow(800, 600, "Ting TnL", NULL, NULL);
}
Application::~Application() {
  Logger::getInstance().info("Application destroyed");
}
int Application::run() { 
  Logger::getInstance().info("Application running");

  if(!this->window){
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(this->window);

  while (!glfwWindowShouldClose(this->window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(this->window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

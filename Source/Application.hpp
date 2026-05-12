#pragma once

#include "../Dependancies/GLFW/include/GLFW/glfw3.h"

class Application {
  public:
  GLFWwindow* window;

  public:
    Application();
    ~Application();
    int run();
};
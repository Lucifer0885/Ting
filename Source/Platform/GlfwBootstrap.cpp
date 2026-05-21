#include "Platform/GlfwBootstrap.hpp"

#include "GLFW/glfw3.h"

GlfwBootstrap::GlfwBootstrap() : m_ok(glfwInit() == GLFW_TRUE) {
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
  glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
}

GlfwBootstrap::~GlfwBootstrap() {
  if (this->m_ok) {
    glfwTerminate();
  }
}

#include "Platform/GlfwBootstrap.hpp"

#include "GLFW/glfw3.h"

GlfwBootstrap::GlfwBootstrap() : m_ok(glfwInit() == GLFW_TRUE) {}

GlfwBootstrap::~GlfwBootstrap() {
  if (this->m_ok) {
    glfwTerminate();
  }
}

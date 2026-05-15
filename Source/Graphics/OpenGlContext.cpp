#include "Graphics/OpenGlContext.hpp"

#include "Logger/Logger.hpp"
#include "Platform/GlfwWindow.hpp"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace OpenGlContext {

bool attach(GlfwWindow& window) {
  if (!window.valid()) {
    Logger::getInstance().error("OpenGlContext::attach: window is not valid");
    return false;
  }

  window.makeContextCurrent();

  if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
    Logger::getInstance().error("Could not initialize GLAD");
    return false;
  }

  const auto* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  if (version != nullptr) {
    Logger::getInstance().info(std::string {"OpenGL version: "} + version);
  }

  return true;
}

void setClearColor(float red, float green, float blue, float alpha) {
  glClearColor(red, green, blue, alpha);
}

}

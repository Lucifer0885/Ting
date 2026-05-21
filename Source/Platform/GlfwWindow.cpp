#include "Platform/GlfwWindow.hpp"

#include "Logger/Logger.hpp"

#include "GLFW/glfw3.h"

GlfwWindow::GlfwWindow() = default;

GlfwWindow::~GlfwWindow() {
  this->destroy();
}

bool GlfwWindow::create(int width, int height, const char* title, int contextMajor,
    int contextMinor) {
  if (this->m_window != nullptr) {
    Logger::getInstance().error("GLFW window already created");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextMinor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (this->m_window == nullptr) {
    Logger::getInstance().error("glfwCreateWindow failed");
    return false;
  }

  glfwSetWindowUserPointer(this->m_window, this);
  return true;
}

void GlfwWindow::destroy() {
  if (this->m_window == nullptr) {
    return;
  }
  glfwDestroyWindow(this->m_window);
  this->m_window = nullptr;
  this->m_onCloseRequest = nullptr;
  Logger::getInstance().info("GLFW window destroyed");
}

void GlfwWindow::pollEvents() const {
  glfwPollEvents();
}

bool GlfwWindow::shouldClose() const {
  return this->m_window != nullptr && glfwWindowShouldClose(this->m_window) != 0;
}

void GlfwWindow::swapBuffers() const {
  if (this->m_window != nullptr) {
    glfwSwapBuffers(this->m_window);
  }
}

void GlfwWindow::makeContextCurrent() const {
  if (this->m_window != nullptr) {
    glfwMakeContextCurrent(this->m_window);
  }
}

void GlfwWindow::setSwapInterval(int interval) const {
  if (this->m_window != nullptr) {
    glfwSwapInterval(interval);
  }
}

void GlfwWindow::setOnCloseRequest(std::function<void()> callback) {
  this->m_onCloseRequest = std::move(callback);
  if (this->m_window == nullptr) {
    return;
  }
  glfwSetWindowCloseCallback(this->m_window, &GlfwWindow::closeCallback);
}

void GlfwWindow::requestClose() {
  if (this->m_window != nullptr) {
    glfwSetWindowShouldClose(this->m_window, GLFW_TRUE);
  }
}

void GlfwWindow::closeCallback(GLFWwindow* window) {
  Logger::getInstance().info("User requested window close...");
  auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
  if (self != nullptr && self->m_onCloseRequest) {
    self->m_onCloseRequest();
  }
}

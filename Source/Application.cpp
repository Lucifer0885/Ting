#include "Application.hpp"

#include "Graphics/OpenGlContext.hpp"
#include "Logger/Logger.hpp"

int Application::run() {

  if (!this->m_glfw.ok()) {
    Logger::getInstance().error("Could not initialize GLFW");
    return -1;
  }

  if (!this->m_window.create(800, 600, "Ting TnL", 4, 6)) {
    Logger::getInstance().error("Could not create GLFW window");
    return -1;
  }

  this->m_window.setOnCloseRequest([this]() { this->m_settingsManager.saveSettings(); });

  if (!OpenGlContext::attach(this->m_window)) {
    Logger::getInstance().error("Could not initialize OpenGL");
    return -1;
  }

  this->m_window.setSwapInterval(this->m_settingsManager.getVsync() ? 1 : 0);
  OpenGlContext::setClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  if (!this->m_imgui.init(this->m_window, "#version 460")) {
    Logger::getInstance().error("Could not initialize ImGui");
    return -1;
  }

  this->m_macroManager.initialize();

  this->runMainLoop();
  return 0;
}

void Application::runMainLoop() {
  while (!this->m_window.shouldClose()) {
    this->m_window.pollEvents();
    this->m_macroManager.poll();

    this->m_imgui.newFrame();
    this->m_appUi.draw(this->m_settingsManager, this->m_window, [this]() { this->m_settingsManager.saveSettings(); });
    this->m_imgui.render();

    this->m_window.swapBuffers();
  }
}

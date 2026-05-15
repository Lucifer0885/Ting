#pragma once

#include "MacroManager/MacroManager.hpp"
#include "Platform/GlfwBootstrap.hpp"
#include "Platform/GlfwWindow.hpp"
#include "Ui/AppUi.hpp"
#include "Ui/ImGuiLayer.hpp"

class Application {
private:
  GlfwBootstrap m_glfw;
  GlfwWindow m_window;
  MacroManager m_macroManager;
  ImGuiLayer m_imgui;
  AppUi m_appUi;
  bool m_vsync = true;

  void saveSettings();
  void runMainLoop();

public:
  Application() = default;
  ~Application() = default;

  int run();
};

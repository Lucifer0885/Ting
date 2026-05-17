#pragma once

#include "Macro/MacroManager/MacroManager.hpp"
#include "SettingsManager/SettingsManager.hpp"
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
  SettingsManager m_settingsManager;

  void runMainLoop();

public:
  Application() = default;
  ~Application() = default;

  int run();
};

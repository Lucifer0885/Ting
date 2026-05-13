#pragma once

#include "MacroManager/MacroManager.hpp"

struct GLFWwindow;

class Application {
  private:
  MacroManager m_macroManager;
  GLFWwindow* m_window = nullptr;
  bool m_vsync = true;
  bool m_imguiInitialized = false;

  void saveSettings();
  bool initializeWindow();
  bool initializeOpenGL();
  bool initializeImGui();
  void renderUI();
  void runMainLoop();
  void destroyImGui();
  void destroyWindow();

  public:
    Application();
    ~Application();
    int run();
};
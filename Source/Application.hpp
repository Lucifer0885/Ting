#pragma once

struct GLFWwindow;

class Application {
  private:
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
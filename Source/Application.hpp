#pragma once

struct GLFWwindow;

class Application {
  private:
  GLFWwindow* m_window = nullptr;

  public:
    Application();
    ~Application();
    void saveSettings();
    int run();
};
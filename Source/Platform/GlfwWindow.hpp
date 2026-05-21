#pragma once

#include <functional>

struct GLFWwindow;

class GlfwWindow {
public:
  GlfwWindow();
  ~GlfwWindow();

  GlfwWindow(const GlfwWindow&) = delete;
  GlfwWindow& operator=(const GlfwWindow&) = delete;
  GlfwWindow(GlfwWindow&&) = delete;
  GlfwWindow& operator=(GlfwWindow&&) = delete;

  [[nodiscard]] bool create(int width, int height, const char* title, int contextMajor,
      int contextMinor);
  void destroy();

  [[nodiscard]] bool valid() const { return this->m_window != nullptr; }
  [[nodiscard]] GLFWwindow* native() const { return this->m_window; }

  void pollEvents() const;
  [[nodiscard]] bool shouldClose() const;
  void swapBuffers() const;
  void makeContextCurrent() const;
  void setSwapInterval(int interval) const;
  void setOnCloseRequest(std::function<void()> callback);

  void requestClose();
  void restore();
  void iconify();
  void maximize();

private:
  GLFWwindow* m_window = nullptr;
  std::function<void()> m_onCloseRequest;
  int m_isMaximized = 1;
  int m_isIconified = 0;
  int m_isRestored = 0;

  static void closeCallback(GLFWwindow* window);
};

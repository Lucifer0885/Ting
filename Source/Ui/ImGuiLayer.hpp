#pragma once

class GlfwWindow;

class ImGuiLayer {
public:
  ImGuiLayer() = default;
  ~ImGuiLayer();

  ImGuiLayer(const ImGuiLayer&) = delete;
  ImGuiLayer& operator=(const ImGuiLayer&) = delete;
  ImGuiLayer(ImGuiLayer&&) = delete;
  ImGuiLayer& operator=(ImGuiLayer&&) = delete;

  [[nodiscard]] bool init(const GlfwWindow& window, const char* glslVersion);
  void shutdown();
  void newFrame();
  void render();

  [[nodiscard]] bool initialized() const { return this->m_initialized; }

private:
  bool m_initialized = false;
};

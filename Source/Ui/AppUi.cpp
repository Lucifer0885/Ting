#include "Ui/AppUi.hpp"

#include "GLFW/glfw3.h"
#include "imgui.h"

void AppUi::draw(bool& vsync, const std::function<void()>& onSaveSettings) const {
  ImGuiIO& io = ImGui::GetIO();

  ImGui::Begin("Ting TnL");
  ImGui::Text("(%d FPS)", static_cast<int>(io.Framerate));
  ImGui::End();

  ImGui::Begin("Settings");
  ImGui::Separator();
  if (ImGui::Checkbox("VSync", &vsync)) {
    glfwSwapInterval(vsync ? 1 : 0);
  }
  ImGui::Separator();
  if (ImGui::Button("Save Settings")) {
    onSaveSettings();
  }
  ImGui::End();
}

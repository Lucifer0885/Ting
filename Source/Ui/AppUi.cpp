#include "Ui/AppUi.hpp"

#include "SettingsManager/SettingsManager.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"

void AppUi::draw(SettingsManager& settingsManager, GlfwWindow& window, const std::function<void()>& onSaveSettings) const {
  this->m_header.draw(window, "Ting TnL");

  bool* vsync = settingsManager.vsyncMutable();

  ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoTitleBar  | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Settings");
  ImGui::Separator();
  if (ImGui::Checkbox("VSync", vsync)) {
    glfwSwapInterval(*vsync ? 1 : 0);
  }
  ImGui::Separator();

  const float buttonRowHeight = ImGui::GetFrameHeightWithSpacing();
  const float spaceAboveButton = ImGui::GetContentRegionAvail().y - buttonRowHeight;
  if (spaceAboveButton > 0.0f) {
    ImGui::Dummy(ImVec2(0.0f, spaceAboveButton));
  }

  const float buttonWidth = ImGui::GetContentRegionAvail().x;
  if (ImGui::Button("Save Settings", ImVec2(buttonWidth, 0.0f))) {
    onSaveSettings();
  }
  ImGui::End();

  ImGui::Begin("Macros");
  ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Macros");

  ImGui::End();
}

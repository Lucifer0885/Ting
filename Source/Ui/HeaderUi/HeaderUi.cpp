#include "HeaderUi.hpp"

#include "Platform/GlfwWindow.hpp"
#include "imgui.h"

void HeaderUi::draw(GlfwWindow& window, const std::string_view& title) const {
  ImGuiIO& io = ImGui::GetIO();

  ImGui::Begin("Header", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

  const float contentMinX = ImGui::GetWindowContentRegionMin().x;
  const float contentMaxX = ImGui::GetWindowContentRegionMax().x;
  const float contentWidth = contentMaxX - contentMinX;
  const float rowY = ImGui::GetCursorPosY();

  const ImVec4 textColor(1.0f, 1.0f, 1.0f, 1.0f);

  // Left: FPS
  ImGui::SetCursorPos(ImVec2(contentMinX, rowY));
  ImGui::TextColored(textColor, "(%d FPS)", static_cast<int>(io.Framerate));

  // Center: title (middle of the full header width)
  const ImVec2 titleSize =
      ImGui::CalcTextSize(title.data(), title.data() + static_cast<int>(title.size()));
  ImGui::SetCursorPos(ImVec2(contentMinX + (contentWidth - titleSize.x) * 0.5f, rowY));
  ImGui::TextColored(textColor, "%.*s", static_cast<int>(title.size()), title.data());

  // Right: window controls
  const float buttonSize = ImGui::GetFrameHeight();
  const float spacing = ImGui::GetStyle().ItemSpacing.x;
  const float buttonsWidth = buttonSize * 3.0f + spacing * 2.0f;
  ImGui::SetCursorPos(ImVec2(contentMaxX - buttonsWidth, rowY));

  ImGui::Button("-", ImVec2(buttonSize, buttonSize));
  ImGui::SameLine(0.0f, spacing);
  if (ImGui::Button("*", ImVec2(buttonSize, buttonSize))) {
    window.maximize();
  }
  ImGui::SameLine(0.0f, spacing);
  if (ImGui::Button("X", ImVec2(buttonSize, buttonSize))) {
    window.requestClose();
  }

  ImGui::End();
}

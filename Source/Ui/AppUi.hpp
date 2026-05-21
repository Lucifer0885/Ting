#pragma once

#include "SettingsManager/SettingsManager.hpp"
#include <functional>
#include "HeaderUi/HeaderUi.hpp"
#include "Platform/GlfwWindow.hpp"

class AppUi {
private:
  HeaderUi m_header;
public:
  void draw(SettingsManager& settingsManager, GlfwWindow& window, const std::function<void()>& onSaveSettings) const;
};

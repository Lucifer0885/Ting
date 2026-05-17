#pragma once

#include "SettingsManager/SettingsManager.hpp"
#include <functional>

class AppUi {
public:
  void draw(SettingsManager& settingsManager, const std::function<void()>& onSaveSettings) const;
};

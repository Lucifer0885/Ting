#pragma once

#include <filesystem>
#include "json.hpp"

class SettingsManager {
private:
  std::filesystem::path m_settingsFilePath;
  nlohmann::json m_settings;
  bool m_vsync = true;

public:
  SettingsManager();
  ~SettingsManager();
  
  [[nodiscard]] bool getVsync() const;
  bool* vsyncMutable();
  void setVsync(bool vsync);
  void loadSettings();
  void saveSettings();
};
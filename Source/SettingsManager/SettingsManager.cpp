#include "Logger/Logger.hpp"
#include <filesystem>
#include <fstream>

#include "SettingsManager.hpp"

SettingsManager::SettingsManager() {
  this->m_settingsFilePath = std::filesystem::path(std::getenv("USERPROFILE")) / "TingTnL" / "settings.json";
  if (!std::filesystem::exists(this->m_settingsFilePath)) {
    Logger::getInstance().error("Settings file not found: " + this->m_settingsFilePath.string());
    std::filesystem::create_directories(this->m_settingsFilePath.parent_path());
    std::ofstream(this->m_settingsFilePath) << "{}";
    return;
  }
  this->loadSettings();
}

SettingsManager::~SettingsManager() {
  this->saveSettings();
}

void SettingsManager::loadSettings() {
  Logger::getInstance().info("Loading Settings...");
}

void SettingsManager::saveSettings() {
  Logger::getInstance().info("Saving Settings...");
}

void SettingsManager::setVsync(bool vsync) {
  this->m_vsync = vsync;
}

bool* SettingsManager::vsyncMutable() {
  return &this->m_vsync;
}

[[nodiscard]] bool SettingsManager::getVsync() const {
  return this->m_vsync;
}

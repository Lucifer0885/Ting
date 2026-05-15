#pragma once

#include <functional>

class AppUi {
public:
  void draw(bool& vsync, const std::function<void()>& onSaveSettings) const;
};

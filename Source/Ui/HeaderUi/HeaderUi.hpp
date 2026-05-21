#pragma once

#include <string_view>
#include "Platform/GlfwWindow.hpp"

class HeaderUi {
public:
  void draw(GlfwWindow& window, const std::string_view& title) const;
};
#pragma once

class GlfwWindow;

namespace OpenGlContext {

[[nodiscard]] bool attach(GlfwWindow& window);

void setClearColor(float red, float green, float blue, float alpha);

}

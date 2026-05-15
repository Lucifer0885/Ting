#include "Ui/ImGuiLayer.hpp"

#include "Logger/Logger.hpp"
#include "Platform/GlfwWindow.hpp"

#include "glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ImGuiLayer::~ImGuiLayer() {
  this->shutdown();
}

bool ImGuiLayer::init(const GlfwWindow& window, const char* glslVersion) {
  if (this->m_initialized) {
    Logger::getInstance().error("ImGui already initialized");
    return false;
  }
  if (!window.valid()) {
    Logger::getInstance().error("ImGui init: GLFW window is not valid");
    return false;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  if (ImGui::GetCurrentContext() == nullptr) {
    Logger::getInstance().error("Could not create ImGui context");
    return false;
  }
  Logger::getInstance().info(std::string {"ImGui context created with version: "} + ImGui::GetVersion());

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark();

  if (!ImGui_ImplGlfw_InitForOpenGL(window.native(), true)) {
    Logger::getInstance().error("Could not initialize ImGui GLFW backend");
    ImGui::DestroyContext();
    return false;
  }
  if (!ImGui_ImplOpenGL3_Init(glslVersion)) {
    Logger::getInstance().error("Could not initialize ImGui OpenGL backend");
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return false;
  }
  Logger::getInstance().info("ImGui initialized");
  this->m_initialized = true;
  return true;
}

void ImGuiLayer::shutdown() {
  if (!this->m_initialized) {
    return;
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  this->m_initialized = false;
  Logger::getInstance().info("ImGui destroyed");
}

void ImGuiLayer::newFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiLayer::render() {
  ImGui::Render();
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

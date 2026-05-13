#include "Application.hpp"
#include "Logger/Logger.hpp"

#include "glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Application::Application() {}

Application::~Application() {
  if (this->m_imguiInitialized) {
    this->destroyImGui();
  }
  this->m_macroManager.destroy();
  if (this->m_window != nullptr){
    this->destroyWindow();
  }
  glfwTerminate();
  Logger::getInstance().info("Application destroyed");
}

void Application::saveSettings() {
  Logger::getInstance().info("Saving Settings...");
}

bool Application::initializeWindow() {
  if (this->m_window != nullptr) {
    Logger::getInstance().error("Window already initialized");
    return false;
  }

  if (!glfwInit()) {
    Logger::getInstance().error("Could not initialize GLFW!");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  this->m_window = glfwCreateWindow(800, 600, "Ting TnL", nullptr, nullptr);

  return true;
}

bool Application::initializeImGui() {

  if (this->m_imguiInitialized) {
    Logger::getInstance().error("ImGui already initialized");
    return false;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  if (ImGui::GetCurrentContext() == nullptr) {
    this->m_imguiInitialized = false;
    Logger::getInstance().error("Could not create ImGui context");
    return false;
  }
  Logger::getInstance().info(std::string {"ImGui context created with version: "} + ImGui::GetVersion());

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark();

  if (!ImGui_ImplGlfw_InitForOpenGL(this->m_window, true)) {
    Logger::getInstance().error("Could not initialize ImGui GLFW backend");
    ImGui::DestroyContext();
    return false;
  }
  if (!ImGui_ImplOpenGL3_Init("#version 460")) {
    Logger::getInstance().error("Could not initialize ImGui OpenGL backend");
    ImGui::DestroyContext();
    return false;
  }
  Logger::getInstance().info("ImGui initialized");
  this->m_imguiInitialized = true;
  return true;
}

bool Application::initializeOpenGL() {
  if (this->m_window == nullptr) {
    Logger::getInstance().error("GLFW window is null");
    return false;
  }

  glfwSetWindowUserPointer(this->m_window, this);

  glfwSetWindowCloseCallback(this->m_window, [](GLFWwindow* window){
    Logger::getInstance().info("User Requested window close...");
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    (void)app->saveSettings();
  });
  
  glfwMakeContextCurrent(this->m_window);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    Logger::getInstance().error("Could not initialize GLAD!");
    return false;
  }

  const auto* openGlVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  if (openGlVersion) {
    Logger::getInstance().info(std::string {"OpenGL version: "} + openGlVersion);
  }

  glfwSwapInterval(this->m_vsync ? 1 : 0);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  return true;
}

void Application::renderUI() {
  ImGuiIO& io = ImGui::GetIO();

  ImGui::Begin("Ting TnL");
  ImGui::Text("(%d FPS)", static_cast<int>(io.Framerate));
  ImGui::End();

  ImGui::Begin("Settings");
  ImGui::Separator();
  if (ImGui::Checkbox("VSync", &this->m_vsync)) {
    glfwSwapInterval(this->m_vsync ? 1 : 0);
  }
  ImGui::Separator();
  if (ImGui::Button("Save Settings")) {
    this->saveSettings();
  }
  ImGui::End();

}

void Application::runMainLoop() {
  while (!glfwWindowShouldClose(this->m_window)) {
    glfwPollEvents();
    this->m_macroManager.poll();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    this->renderUI();

    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(this->m_window);
  }
}

void Application::destroyImGui() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  this->m_imguiInitialized = false;
  Logger::getInstance().info("ImGui destroyed");
}

void Application::destroyWindow() {
  glfwDestroyWindow(this->m_window);
  this->m_window = nullptr;
  Logger::getInstance().info("Window destroyed");
}

int Application::run() { 
  Logger::getInstance().info("Application running");

  if(!this->initializeWindow()) {
    Logger::getInstance().error("Could not create Window");
    return -1;
  }

  if(!this->initializeOpenGL()) {
    Logger::getInstance().error("Could not initialize OpenGL");
    return -1;
  }

  if(!this->initializeImGui()) {
    Logger::getInstance().error("Could not initialize ImGui");
    return -1;
  }

  this->m_macroManager.initialize();

  this->runMainLoop();
  return 0;
}

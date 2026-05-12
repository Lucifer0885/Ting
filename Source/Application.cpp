#include "Application.hpp"
#include "Logger/Logger.hpp"

#include "glad.h"
#include "GLFW/glfw3.h"

Application::Application() {

  if(!glfwInit()){
    Logger::getInstance().error("Could not Initialize GLFW!");
  } else {
    Logger::getInstance().info("Application created");
    
    this->m_window = glfwCreateWindow(800, 600, "Ting TnL", NULL, NULL);
  }
}

Application::~Application() {
  if (this->m_window){
    glfwDestroyWindow(this->m_window);
  }
  glfwTerminate();
  Logger::getInstance().info("Application destroyed");
}

void Application::saveSettings() {
  Logger::getInstance().info("Saving Settings...");
}

int Application::run() { 
  Logger::getInstance().info("Application running");

  if(!this->m_window){
    Logger::getInstance().error("GLFW window is null");
    return -1;
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
    return -1;
  }

  const auto* openGlVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  if (openGlVersion) {
    Logger::getInstance().info(std::string {"OpenGL version: "} + openGlVersion);
  }

  glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(this->m_window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(this->m_window);
    glfwPollEvents();
  }
  return 0;
}

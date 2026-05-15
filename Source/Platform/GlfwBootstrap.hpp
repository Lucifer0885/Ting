#pragma once

class GlfwBootstrap {
public:
  GlfwBootstrap();
  ~GlfwBootstrap();

  GlfwBootstrap(const GlfwBootstrap&) = delete;
  GlfwBootstrap& operator=(const GlfwBootstrap&) = delete;
  GlfwBootstrap(GlfwBootstrap&&) = delete;
  GlfwBootstrap& operator=(GlfwBootstrap&&) = delete;

  [[nodiscard]] bool ok() const { return m_ok; }

private:
  bool m_ok = false;
};

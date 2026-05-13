#include <string>
#include "Logger/Logger.hpp"
#include "MacroManager.hpp"

namespace {

  constexpr UINT kHotkeyId = 1;
  constexpr wchar_t kWindowClassName[] = L"TingMacroHotkeyHost";

}

LRESULT CALLBACK tingMacroHotkeyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  MacroManager* self = reinterpret_cast<MacroManager*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

  if (msg == WM_NCCREATE) {
    const auto* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
    self = static_cast<MacroManager*>(create->lpCreateParams);
    SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    return DefWindowProcW(hwnd, msg, wParam, lParam);
  }

  if (self == nullptr) {
    return DefWindowProcW(hwnd, msg, wParam, lParam);
  }

  switch (msg) {
  case WM_HOTKEY:
    self->onHotkey(static_cast<int>(wParam));
    return 0;
  default:
    return DefWindowProcW(hwnd, msg, wParam, lParam);
  }
}

MacroManager::MacroManager() {
  Logger::getInstance().info("MacroManager created");
}

MacroManager::~MacroManager() {
  this->destroy();
}

void MacroManager::onHotkey(int hotkeyId) {
  if (hotkeyId == static_cast<int>(kHotkeyId)) {
    this->m_enabled = !this->m_enabled;
    Logger::getInstance().info(std::string {"Global F9 hotkey - logging mode now "}
        + (this->m_enabled ? "ON" : "OFF"));
  }
}

void MacroManager::initialize() {
  if (this->m_initialized) {
    Logger::getInstance().warning("MacroManager already initialized");
    return;
  }

  this->m_instance = GetModuleHandleW(nullptr);
  if (this->m_instance == nullptr) {
    Logger::getInstance().error("GetModuleHandleW failed");
    return;
  }

  WNDCLASSEXW wc{};
  wc.cbSize = sizeof(wc);
  wc.lpfnWndProc = tingMacroHotkeyWndProc;
  wc.hInstance = this->m_instance;
  wc.lpszClassName = kWindowClassName;

  ATOM atom = RegisterClassExW(&wc);
  if (atom == 0) {
    const DWORD err = GetLastError();
    if (err != ERROR_CLASS_ALREADY_EXISTS) {
      Logger::getInstance().error("RegisterClassExW failed: " + std::to_string(err));
      return;
    }
  }
  this->m_classRegistered = true;

  this->m_messageWindow =
      CreateWindowExW(0, kWindowClassName, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, this->m_instance, this);

  if (this->m_messageWindow == nullptr) {
    const DWORD err = GetLastError();
    Logger::getInstance().error("CreateWindowExW failed: " + std::to_string(err));
    if (this->m_classRegistered) {
      UnregisterClassW(kWindowClassName, this->m_instance);
      this->m_classRegistered = false;
    }
    return;
  }

  if (!RegisterHotKey(this->m_messageWindow, kHotkeyId, MOD_NOREPEAT, VK_F9)) {
    const DWORD err = GetLastError();
    Logger::getInstance().error("RegisterHotKey failed: " + std::to_string(err));
    DestroyWindow(this->m_messageWindow);
    this->m_messageWindow = nullptr;
    UnregisterClassW(kWindowClassName, this->m_instance);
    this->m_classRegistered = false;
    return;
  }
  this->m_hotkeyRegistered = true;

  this->m_initialized = true;
  Logger::getInstance().info("MacroManager initialized - global F9 toggles logging mode");
}

void MacroManager::destroy() {
  if (!this->m_initialized) {
    return;
  }

  if (this->m_hotkeyRegistered) {
    UnregisterHotKey(this->m_messageWindow, kHotkeyId);
    this->m_hotkeyRegistered = false;
  }

  if (this->m_messageWindow != nullptr) {
    DestroyWindow(this->m_messageWindow);
    this->m_messageWindow = nullptr;
  }

  if (this->m_classRegistered && this->m_instance != nullptr) {
    UnregisterClassW(kWindowClassName, this->m_instance);
    this->m_classRegistered = false;
  }

  this->m_initialized = false;
  Logger::getInstance().info("MacroManager shut down (hotkey + host window released)");
}

void MacroManager::poll() {
  if (!this->m_initialized || this->m_messageWindow == nullptr) {
    return;
  }

  MSG msg{};
  while (PeekMessageW(&msg, this->m_messageWindow, 0, 0, PM_REMOVE) != 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
}

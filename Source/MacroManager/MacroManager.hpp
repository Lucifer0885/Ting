#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

class MacroManager {
private:
  bool m_initialized = false;
  bool m_hotkeyRegistered = false;
  bool m_classRegistered = false;
  HWND m_messageWindow = nullptr;
  HINSTANCE m_instance = nullptr;

  bool m_isRunning = false;
  bool m_enabled = false;

public:
  MacroManager();
  ~MacroManager();

  void initialize();
  void destroy();
  void poll();

  // Called from the Win32 window procedure when WM_HOTKEY arrives. Kept on the
  // public surface so we do not need `friend` declarations in this header.
  void onHotkey(int hotkeyId);
};

// Window procedure must be declared at namespace scope for Win32 registration.
LRESULT CALLBACK tingMacroHotkeyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

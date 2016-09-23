#include "WindowDisplay.h"
#include "Windows.h"

HWND CreateDisplayWindow(HINSTANCE app);

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance,
    LPSTR cmdLine, int show) {
  HWND const window = CreateDisplayWindow(instance);
  ::ShowWindow(window, show);
  WindowDisplay display(window);
  MSG msg = { };
  while (::GetMessage(&msg, 0, 0, 0)) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
    display.processRequest();
  }
  return 0;
}
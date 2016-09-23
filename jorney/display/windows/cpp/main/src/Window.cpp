#include <windows.h>

LRESULT CALLBACK DisplayWindowProcedure(HWND wnd, UINT msg, WPARAM wParam,
    LPARAM lParam) {
  switch(msg) {
    case WM_CLOSE:
      ::DestroyWindow(wnd);
      break;

    case WM_DESTROY:
      ::PostQuitMessage(0);
      break;

    case WM_PAINT:
      PAINTSTRUCT ps;
      HDC const hdc = ::BeginPaint(wnd, &ps);
      ::FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
      ::EndPaint(wnd, &ps);
      break;
  }
  return ::DefWindowProc(wnd, msg, wParam, lParam);
}

HWND CreateDisplayWindow(HINSTANCE app) {
  WNDCLASS wc = { };
  wc.lpfnWndProc = DisplayWindowProcedure;
  wc.hInstance = app;
  wc.lpszClassName = "jorney.display";
  ::RegisterClass(&wc);
  return ::CreateWindowEx(0, "jorney.display", "Display", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, app, 0);
  return 0;
}
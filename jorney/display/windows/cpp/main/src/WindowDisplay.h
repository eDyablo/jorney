#pragma once

#include "DisplayService.h"
#include "Windows.h"

class WindowDisplay : public DisplayService {
public:
	WindowDisplay(HWND window):
		window(window) {
	}

private:
	HWND window;
};
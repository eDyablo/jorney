#include <Windows.h>

namespace basics {
	void sleep(unsigned int seconds) {
		::Sleep(seconds * 1000);
	}

	void msleep(unsigned int milliSeconds) {
		::Sleep(milliSeconds);
	}
}
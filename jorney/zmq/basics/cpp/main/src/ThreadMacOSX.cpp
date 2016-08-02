#include <unistd.h>

namespace basics {
	void sleep(size_t seconds) {
		::sleep(seconds);
	}

	void msleep(size_t milliSeconds) {
		::usleep(milliSeconds * 1000);
	}
}
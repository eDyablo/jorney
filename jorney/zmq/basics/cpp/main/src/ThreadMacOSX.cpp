#include <unistd.h>

namespace basics {
	void sleep(unsigned int seconds) {
		::sleep(seconds);
	}

	void msleep(unsigned int milliSeconds) {
		::usleep(milliSeconds * 1000);
	}
}
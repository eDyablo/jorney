namespace basics {
	void sleep(size_t seconds) {
		::Sleep(seconds * 1000);
	}

	void msleep(size_t milliSeconds) {
		::Sleep(milliSeconds);
	}
}
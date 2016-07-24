#include "tennis/Score.h"

namespace tennis {
	Score::Score(const std::string& first, const std::string& second):
		firstPlayerScore(first),
		secondPlayerScore(second) {
	}

	std::string Score::firstPlayer() const {
		return firstPlayerScore;
	}

	std::string Score::secondPlayer() const {
		return secondPlayerScore;
	}
}
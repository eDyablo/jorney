#pragma once

#include <string>

namespace tennis {
	class Score {
		std::string firstPlayerScore;
		std::string secondPlayerScore;

	public:
		Score(const std::string& first, const std::string& second);

		std::string firstPlayer() const;

		std::string secondPlayer() const;
	};
}
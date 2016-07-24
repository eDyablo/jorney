#pragma once

#include "Score.h"

#include <string>

namespace tennis {
	class Game {
		size_t firstPlayerPoints;
		size_t secondPlayerPoints;

	public:
		Game();
		
		Score score() const;

		void firstWon();

		void secondWon();
	private:
		std::string pointsToScore(size_t points) const;
	};
}
#include "tennis/Game.h"

namespace tennis {
	Game::Game():
		firstPlayerPoints(0),
		secondPlayerPoints(0) {
	}

	Score Game::score() const {
		return Score(pointsToScore(firstPlayerPoints),
				pointsToScore(secondPlayerPoints));
	}

	std::string Game::pointsToScore(size_t points) const {
		if (points == 1)
			return "fifteen";
		if (points == 2)
			return "thirty";
		if (points > 2)
			return "forty";
		return "love";
	}

	void Game::firstWon() {
		++firstPlayerPoints;
	}

	void Game::secondWon() {
		++secondPlayerPoints;
	}
}
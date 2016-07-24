#include "gmock/gmock.h"
#include "tennis/Game.h"

using namespace ::testing;
using namespace ::tennis;

MATCHER_P(ScoredAs, expected, "") {
	auto score = arg.score();
	return score.firstPlayer() == expected.firstPlayer()
		&& score.secondPlayer() == expected.secondPlayer();
}

class AGame : public Test {
public:
	Game game;
};

TEST_F(AGame, ScoresLoveForBothPlayersWhenNoOneWonPoints) {
	ASSERT_THAT(game, ScoredAs(Score("love", "love")));
}

TEST_F(AGame, ScoresFifteenForBothPlayerWhenEachWonOnePoint) {
	game.firstWon();
	game.secondWon();
	ASSERT_THAT(game, ScoredAs(Score("fifteen", "fifteen")));
}

TEST_F(AGame, ScoresThirtyForBothPlayerWhenEachWonTwoPoints) {
	game.firstWon(), game.firstWon();
	game.secondWon(), game.secondWon();
	ASSERT_THAT(game, ScoredAs(Score("thirty", "thirty")));
}

TEST_F(AGame, ScoresFortyForFirstPlayerWhenSheWonThreePoints) {
	game.firstWon();
	game.firstWon();
	game.firstWon();
	ASSERT_THAT(game, ScoredAs(Score("forty", "love")));
}

TEST_F(AGame, ScoresFortyForSecondPlayerWhenSheWonThreePoints) {
	game.secondWon();
	game.secondWon();
	game.secondWon();
	ASSERT_THAT(game, ScoredAs(Score("love", "forty")));
}
#ifndef __GAMEIMPL_H__
#define __GAMEIMPL_H__
#include <vector>

// Reference for each player
enum Player { n, X, O };

// Exceptions
class GameOver{};
class OutOfBounds {};
class NonEmpty {};

// Data members of Game
struct GameImpl {
	const int SIZE;								// Dimensions of the game's board
	int t;										// Number of turns remaining
	Player pturn;								// Current player's turn
	std::vector<std::vector<Player>> board;		// Board's matrix representation

	GameImpl(int s, int t, Player p, std::vector<std::vector<Player>> b);
	Player &pos(int r, int c);
};

#endif

#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <memory>
#include "gameimpl.h"

class Game {
	std::unique_ptr<GameImpl> impl;		// Abstracted implementation of the game
  public:
	Game(int s = 3);
	void play(int r, int c);
	Player getCurrentPlayer();
	Player getWinner();

	friend std::ostream &operator<<(std::ostream &out, Game &game);
};

std::ostream &operator<<(std::ostream &out, Game &game);

#endif

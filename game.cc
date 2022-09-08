#include "game.h"
using namespace std;

Game::Game(int s) :
	impl{make_unique<GameImpl>(s, s*s, Player::X, vector<vector<Player>>(s, vector<Player>(s, Player::n)))} {}

void Game::play(int r, int c) {

	// Check if game is still running
	// Just a note - this exn should not be thrown, given
	// the proper and inteded implementation
	if (impl->t == 0) {
		throw GameOver{};

	// Check if position stays in boundary
	} else if (r < 0 || r >= impl->SIZE || c < 0 || c >= impl->SIZE) {
		throw OutOfBounds{};

	// Check if position is open
	} else if (impl->pos(r,c) != Player::n) {
		throw NonEmpty{};

	// Otherwise, commit move
	} else {
		impl->pos(r,c) = impl->pturn;
		impl->pturn = (impl->pturn == Player::X) ? Player::O : Player::X;
		--(impl->t);
	}
}

Player Game::getCurrentPlayer() {
	return impl->pturn;
}

Player Game::getWinner() {
	bool boolean = false;
	if (impl->t == 0) boolean = true;

	// Checking each row from the top
	if (!boolean) {
		for (int r = 0; r < impl->SIZE; ++r) {
			bool b = (impl->pos(r,0) != Player::n);
			if (b) {
				for (int c = 0; c < impl->SIZE-1; ++c) {
					b = b && (impl->pos(r,c) == impl->pos(r,c+1));
				}
				if (b) boolean = true;
			}
		}
	}

	// Checking each column from the left
	if (!boolean) {
		for (int c = 0; c < impl->SIZE; ++c) {
			bool b = (impl->pos(0,c) != Player::n);
			if (b) {
				for (int r = 0; r < impl->SIZE-1; ++r) {
					b = b && (impl->pos(r,c) == impl->pos(r+1,c));
				}
				if (b) boolean = true;
			}
		}
	}

	// Check diagonal from top-left
	if (!boolean) {
		bool b = (impl->pos(0,0) != Player::n);
		for (int i = 0; i < impl->SIZE-1; ++i) {
			b = b && (impl->pos(i,i) == impl->pos(i+1,i+1));
		}
		if (b) boolean = true;
	}

	// Check diagonal from top-right
	if (!boolean) {
		bool b = (impl->pos(0,impl->SIZE-1) != Player::n);
		for (int i = 0; i < impl->SIZE-1; ++i) {
			b = b && (impl->pos(i,impl->SIZE-1-i) == impl->pos(i+1,impl->SIZE-2-i));
		}
		if (b) boolean = true;
	}

	// Empty case already tested for (at each of the tests above already)
	// Finish by switching current player turn and by returning false
	if (!boolean) return Player::n;
	if (impl->t != 0) {
		impl->t = 0;
		impl->pturn = (impl->pturn == Player::X) ? Player::O : Player::X;
	}
	return impl->pturn;
}

ostream &operator<<(ostream &out, Game &game) {
	// Print column numbers
	out << "___";
	for (int r = 0; r < game.impl->SIZE; ++r) {
		out << r << "_";
	}
	out << endl;

	// Print each row, column by column
	for (int c = 0; c < game.impl->SIZE; ++c) {
		// Include the row numbers at the beginning
		out << c << "| ";
		for (int r = 0; r < game.impl->SIZE; ++r) {
			switch ((game.impl)->pos(r,c)) {
				case Player::X: out << 'X'; break;
				case Player::O: out << 'O'; break;
				default:		out << '_'; break;
			}
			out << ' ';
		}
		out << endl;
	}
	return out;
}

#include <iostream>
#include "game.h"
using namespace std;

int main(int argc, char **argv) {
	bool repeat = false;	// whether this game is a repeated instance
	char c;					// input char
	int x, y;				// input coodinates

	while (true) {

		// Introductory Prompt
		cout << "Do you want to play TicTacToe" << ((repeat) ? " again" : "") << "? [y/n]: ";
		while (cin >> c) {
			if (c == 'y' || c == 'Y' || c == 'n' || c == 'N')
				break;
		}
		if (!cin || c == 'n' || c == 'N') {
			cout << endl;
			break;
		}
		repeat = true;

		// Start the game
		Game game{};
		Player winner;
		while ((winner = game.getWinner()) == Player::n) {

			// Print prompts and request for input
			cout << endl << game;
			cout << "Player " << ((game.getCurrentPlayer() == Player::X) ? 'X' : 'O')
			     << "'s turn (enter position as \"x y\"): ";
			if (!(cin >> x >> y)) {
				cout << endl;
				return 0;
			}

			// Play and process move
			try {
				game.play(x, y);
				cout << "Move placed successfully on (" << x << "," << y << ")." << endl;
			} catch (OutOfBounds &e) {
				cout << "Position (" << x << "," << y << ") is out of bounds! Play again..." << endl;
			} catch (NonEmpty &e) {
				cout << "Position (" << x << "," << y << ") is already taken! Play again..." << endl;
			} catch (...) {
				cout << "Something went wrong ... please report this to the owner (you can keep playing)." << endl;
			}
		}

		// Determine the winner precedence to player O for forcing a draw
		cout << endl << game;
		cout << "Player " << ((winner == Player::X) ? 'X' : 'O') << " wins!" << endl;
	}
}

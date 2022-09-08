#include "gameimpl.h"
using namespace std;

GameImpl::GameImpl(int s, int t, Player p, std::vector<std::vector<Player>> b) :
	SIZE{s}, t{t}, pturn{p}, board{b} {}

Player &GameImpl::pos(int r, int c) { return board.at(r).at(c); }

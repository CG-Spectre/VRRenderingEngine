#include "Player.h"
Player::Player(Pos* pos, const char* name) : pos(*pos), name(name) {
	
}

Pos* Player::getPos() {
	return &this->pos;
}
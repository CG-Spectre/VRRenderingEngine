#pragma once
#include "Pos.h"
class Player
{
	public:
		Player(Pos* pos, const char* name);
		Pos* pos;
	private:
		const char* name;
};


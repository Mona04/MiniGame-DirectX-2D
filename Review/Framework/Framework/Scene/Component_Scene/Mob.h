#pragma once
#include "../Actor.h"

class Mob : public Actor
{
public:
	Mob(class Context* context);
	~Mob();

	std::vector<class Animator*> GetMotions() { return motions; }

private:
	int status;
	std::vector<class Animator*> motions;
};
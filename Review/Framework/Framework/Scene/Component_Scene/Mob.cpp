#include "Framework.h"
#include "Mob.h"

Mob::Mob(Context* context)
	: Actor(context)
{
}

Mob::~Mob()
{
	for (auto motion : motions)
		SAFE_DELETE(motion);
}

class Mob_Normal
{
	Actor@ actor;
	Controller@ controller;

	Mob_Normal(Actor @in_actor)
	{
		@actor = in_actor;
		@controller = actor.GetController();
	}

	void Start()
	{
	}

	void Update()
	{
		bool isAttacked = controller.IsHostile();
		if(isAttacked)
		{
			controller.RandomAttack(5000.0f, 0.15f, 0.15f, 0.15f);
		}
		else
		{
			controller.RandomWalk(3000.0f);
		}
	}
}
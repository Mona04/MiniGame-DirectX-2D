class NPCBlony
{
	Actor@ actor;
	Controller@ controller;

	NPCBlony(Actor @in_actor)
	{
		@actor = in_actor;
		@controller = actor.GetController();
	}

	void Start()
	{
		controller.Walk(0);
	}

	void Update()
	{
		bool isKeyPressed = false;
		controller.Stand();
	}
}
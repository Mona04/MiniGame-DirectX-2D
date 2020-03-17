class Portal
{
	Actor@ actor;
	Controller@ controller;

	Portal(Actor @in_actor)
	{
		@actor = in_actor;
		@controller = actor.GetController();
	}

	void Start()
	{
	}

	void Update()
	{
		bool isKeyPressed = false;
		if(input.KeyPress(KeyCode::KEY_A))
		{
			controller.Walk(0);
			isKeyPressed = true;
		}
		if(input.KeyPress(KeyCode::KEY_D))
		{
			controller.Walk(1);
			isKeyPressed = true;
		}
		if(input.KeyPress(KeyCode::KEY_W))
		{
			controller.Jump();
			isKeyPressed = true;
		}
		if(input.KeyDown(KeyCode::KEY_K))
		{
			controller.Attack1();
		}
		if(!isKeyPressed)
		{
			controller.Stand();
			isKeyPressed = true;
		}
	}
}
class Protagonist
{
	Actor@ actor;
	Controller@ controller;
	bool bRun = false;


	Protagonist(Actor @in_actor)
	{
		@actor = in_actor;
		@controller = actor.GetController();
	}
	
	void Start()
	{
	}
	
	void Update()
	{
		bool bKeyPressed = false;
		if( input.KeyDoubleDown(KeyCode::KEY_LEFT))
		{
			controller.Run(0);
			bRun = true;
			bKeyPressed = true;	
		}
		else if(input.KeyPress(KeyCode::KEY_LEFT))
		{
			bRun ? controller.Run(0) : controller.Walk(0);
			bKeyPressed = true;	
		}
		if( input.KeyDoubleDown(KeyCode::KEY_RIGHT))
		{
			controller.Run(1);
			bRun = true;
			bKeyPressed = true;	
		}
		else if(input.KeyPress(KeyCode::KEY_RIGHT))
		{
			bRun ? controller.Run(1) : controller.Walk(1);
			bKeyPressed = true;	
		}
		if(input.KeyPress(KeyCode::KEY_UP))
		{
			controller.Jump();
			bKeyPressed = true;
		}
		if(!bKeyPressed)
		{
			controller.Stand();
			bRun = false;			
		}
		
		if(input.KeyDown(KeyCode::KEY_UP))
		{
			controller.Portal();
			controller.Dialog();
		}	
		if(input.KeyDown(KeyCode::KEY_Z))
		{
			controller.Attack2();
		}
		if(input.KeyDown(KeyCode::KEY_X))
		{
			controller.Attack1();
		}
		if(input.KeyDown(KeyCode::KEY_C))
		{
			controller.Gaurd();
		}
		if(input.KeyPress(KeyCode::KEY_V))
		{
		    controller.ItemPick();
		}
		if(input.KeyDown(KeyCode::KEY_H))
		{
			inventoryManager.UseItem("RedPotion_Small", 1);
		}
		if(input.KeyDown(KeyCode::KEY_SPACE))
		{
			controller.SuperJump(3.0f);
		}
		
		if(input.KeyDown(KeyCode::KEY_I))
			inventoryManager.ToggleInventory();
		if(input.KeyDown(KeyCode::KEY_K))
			monsterManager.ToggleEvolution();
		
	}
}
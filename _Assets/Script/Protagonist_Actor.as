class Protagonist
{
	Actor@ actor;
	Controller@ controller;

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
		bool isKeyPressed = false;
		if(input.KeyPress(KeyCode::KEY_LEFT))
		{
			controller.Walk(0);
			isKeyPressed = true;
		}
		if(input.KeyDoubleDown(KeyCode::KEY_LEFT))
		{
			controller.Run(0);
			isKeyPressed = true;
		}
		if(input.KeyPress(KeyCode::KEY_RIGHT))
		{
			controller.Walk(1);
			isKeyPressed = true;
		}
		if(input.KeyDoubleDown(KeyCode::KEY_RIGHT))
		{
			controller.Run(1);
			isKeyPressed = true;
		}
		if(input.KeyPress(KeyCode::KEY_UP))
		{
			controller.Jump();
			isKeyPressed = true;
		}
		if(input.KeyDown(KeyCode::KEY_UP))
		{
			controller.Portal();
			controller.Dialog();
		}	
		if(input.KeyDown(KeyCode::KEY_DOWN))
		{
			//controller.Attack1();
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
		//if(input.KeyDown(KeyCode::KEY_V))
		//{
		//    Physics Manager 에 있는데, 아이템 줍기
		//}
		if(input.KeyDown(KeyCode::KEY_H))
		{
			if(inventoryManager.GetItemStock("RedPotion_Small") > 0)
			{
				inventoryManager.DeleteItemAuto("RedPotion_Small", 1);
				gameManager.GetProtagonist().Heal(99999, 99999, 99999);
			}
		}
		if(input.KeyDown(KeyCode::KEY_SPACE))
		{
			controller.SuperJump(3.0f);
		}
		if(!isKeyPressed)
		{
			controller.Stand();
			isKeyPressed = true;
		}
		
		if(input.KeyDown(KeyCode::KEY_I))
			inventoryManager.ToggleInventory();
		if(input.KeyDown(KeyCode::KEY_K))
			monsterManager.ToggleEvolution();
		
	}
}
class InventoryItemUse
{
	Frame@ frame;
	Controller@ protagonist;
	InventoryItemUse(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		@protagonist = gameManager.GetProtagonist();
	}

	void Update()
	{
		int code = inventoryManager.GetUsedItem();
		switch(code)
		{
		case 1:
		{
			dialogManager.DialogSetState(2);
			gameManager.GetProtagonist().Evolution("snail");
			break;
		}
		case 11:
		case 12:
		case 13:
		case 14:
		{
			inventoryManager.InsertItemAuto("Powder_Magic", 5);
			break;
		}
		case 20: gameManager.GetProtagonist().Heal(99999, 99999, 99999); break;
		case 21: inventoryManager.InsertItemAuto("Herb_Blue", 7); break;
		case 22: inventoryManager.InsertItemAuto("Herb_Red", 7); break;
		case 23: inventoryManager.InsertItemAuto("Herb_Light", 7); break;
		case 24: inventoryManager.InsertItemAuto("Herb_Dark", 7); break;
		case 30: gameManager.EnforceProtagonistSpeed(); break;
		case 31: inventoryManager.InsertItemAuto("Herb_Blue", 20); break;
		case 32: inventoryManager.InsertItemAuto("Herb_Red", 20); break;
		case 33: inventoryManager.InsertItemAuto("Herb_Light", 20); break;
		case 34: inventoryManager.InsertItemAuto("Herb_Dark", 20); break;
		case 41: gameManager.GetProtagonist().RandomSkillChange(); break;
		case 42: inventoryManager.InsertItemAuto("TrainingPortion", 1); break;
		case 43: 
		{	
			gameManager.EnforceProtagonistSpeed();
			gameManager.EnforceProtagonistSpeed(); 
			gameManager.EnforceProtagonistSpeed();
			gameManager.EnforceProtagonistJump();
			break;
		}
		case 44: monsterManager.SpawnAuto("tauromasis", 0, false); break;
		case 46: 
			for(int i = 0 ; i < 10; i++)
				gameManager.EnforceProtagonistSpeed(); 
			break;
		case 47: gameManager.GetProtagonist().RandomRGBChange(); break;

		case 49: monsterManager.SpawnAuto("teddy_soul", 0, false); break;
		case 50: gameManager.GetProtagonist().Heal(99999, 99999, 99999); break;
		case 51: gameManager.GetProtagonist().ObtainExp(10000); break;
		case 52: inventoryManager.InsertItemAuto("FireFeather", 1); break;
		case 53: gameManager.SetGradiateTime(30000.0f); gameManager.TrueEnding(); break;
		case 54: inventoryManager.InsertItemAuto("mindCichol", 1); break;
		case 55: inventoryManager.InsertItemAuto("Kit", 500); break;
			
		default:
		{
			break;
		}
		}
	}
}
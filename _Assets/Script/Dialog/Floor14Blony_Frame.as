class Floor14Blony
{
	Frame@ frame;
	int _cur;

	Floor14Blony(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		_cur = 0;
	}

	void Update()
	{
		int _state = dialogManager.DialogGetState();

		if(_state == 0)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("�ȳ� �з��þ�?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				dialogManager.DialogSetButton(1, " �����Ѵ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				else if(dialogManager.IsDialogButtonClicked(1))
				{
					_cur = 200;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�ȳ� ��δ�. \n������ �ٷ�?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 3:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 4:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("��... �׷�!!");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 5:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}
 		
			case 100:
			{
				inventoryManager.InsertItemAuto("RedPotion_Small", 60);
				dialogManager.DialogSetState(1);
				dialogManager.DialogEnd();
				_cur += 1;
				break;
			}
			case 200:
			{
				dialogManager.DialogEnd();
				_cur += 1;
				break;
			}
			}
		}

		else
		{
		switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("���� ����� ���� �ٰ�����...");
				dialogManager.DialogSetButton(0, " ������");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogSetState(1);
				dialogManager.DialogEnd();
				break;
			}
			}
		}


	}
}
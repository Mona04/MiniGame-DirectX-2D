class Floor15Blony
{
	Frame@ frame;
	int _cur;

	Floor15Blony(Frame @in_frame)
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
				dialogManager.DialogSetText("�з��þ�..");
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
				dialogManager.DialogSetText("�׷�..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 5:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
 			case 6:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("�з��þ�.. �Ҹ��� �־�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 7:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 8:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�������ε�..?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 9:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 10:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("��δϴ� �������� ���� �ö� �� ����.\n�׷��� ���Ⱑ �������̾�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 11:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 12:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("�з��þ��� ��δϸ� ��� �峭ģ�� �˰��־�.\n������ �����־� ��°�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 13:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 14:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("�ٽ� �з��þ�, �� �������� ���ڴ�..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 15:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 16:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("������ ��������... �ԼӰ�� ��������..\n��δϴ� �з��þ��� ��û �����ϴϱ�..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 17:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 18:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("�츰 ���� ģ�� ģ���ϱ�... ��½..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 19:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 20:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("��.. �ȿ��� �ߴµ�... \n�̾��� �з��þ�.. ���ڱ� ��������...");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 21:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 22:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("����.. �ʸ� ���� �غ��� �ۺ� �����̾�..\n�ٽ� �������� �𸣰�����... ����");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 23:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}




			case 100:
			{
				inventoryManager.InsertItemAuto("MindBlony", 1);
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
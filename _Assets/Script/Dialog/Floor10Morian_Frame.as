class Floor10Morian
{
	Frame@ frame;
	int _cur;

	Floor10Morian(Frame @in_frame)
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�鸮����?\n");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				dialogManager.DialogSetButton(1, " ��ŵ�ϱ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				if(dialogManager.IsDialogButtonClicked(1))
				{
					_cur = 100;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("10���̿���. ���� ���ڸ� �� �Դϴ�!");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���ݺ��� �߿��� ����Ʈ�� �ֽ��ϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("Ư�� �������� Ư�� �ι����Լ� ���� �� �ִµ�\n���� ������ ������ ���ϸ� ������ �����ϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��.. ��?");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�׷��ϱ� ������������ Ŭ�������ּ���.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 13:
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
				_cur += 1;
			}
			}
		}
		else if(_state == 1)
		{
		switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("...");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				dialogManager.DialogSetButton(1, " ��ŵ�ϱ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				if(dialogManager.IsDialogButtonClicked(1))
				{
					_cur = 100;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�з��þ�.\n����� �հ����� ���� �����̴� �����̶� ������ �� �ֳ���?");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�翬�� �� �ƴմϱ�?");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�׷�������...");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�׷� ������ ������ �̴ϱ�?");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("���� ���� �Ϸ���Ʈ�� �������� ������ ���� ����\n������� ���� �����̾����ϴ�.!!");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("����� ������ ���׸��� ������,\n���� �װ��� �������� ��� Ű��� ���������� �𸨴ϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�׷��� ������� ������ ������ �������� �ٸ��̴ϴ�.\n�ֳ��ϸ� �̹� ����� ������ �������� Ű���� ���̴ϱ��.");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("������ �׷��� ������ ����� ���ϴ� �׷� ������ �� ���� ���� �ſ���.");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�װ��� �����ϴٸ� ���� ����� ���ڽ��ϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("������. \n�׷��ٸ� ���ʸ� ���ش� �ֽðھ��?");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�� ���ʸ� 10���� ���ش��ּ���.\n�׷��� �� ���׸��� ��Ƽ� ��ſ��� �帮�ڽ��ϴ�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 23:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 24:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�װ��� ������ â���ϴµ� �˸����� �� �ſ���.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 25:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 26:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��ڽ��ϴ�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 27:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}
	
			case 100:
			{
				dialogManager.DialogSetState(2);
				dialogManager.DialogEnd();
				break;
			}
			}
		}
		else if(_state == 2)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�÷�Ÿ");
				dialogManager.DialogSetText("���ʴ� �������̳���?");
				dialogManager.DialogSetButton(0, " ��");
				dialogManager.DialogSetButton(1, " �ƴϿ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0) &&
					inventoryManager.GetItemStock("Herb_Blue") >= 10 && inventoryManager.GetItemStock("Herb_Red") >= 10 &&
					inventoryManager.GetItemStock("Herb_Dark") >= 10 &&  inventoryManager.GetItemStock("Herb_Light") >= 10 )
				{
					_cur += 1;
					inventoryManager.DeleteItemAuto("Herb_Blue", 10);
					inventoryManager.DeleteItemAuto("Herb_Dark", 10);
					inventoryManager.DeleteItemAuto("Herb_Red", 10);
					inventoryManager.DeleteItemAuto("Herb_Light", 10);
				}
				if(dialogManager.IsDialogButtonClicked(1))
				{
					_cur = 200;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�����մϴ�. �̰� ���ϰ� �־� �ּ���.");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�Ҿ�����ų�, ������ �ְų� �Ͻø� �ȵ˴ϴ�.\n�ƽð���?");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��. �˰ڽ��ϴ�.");
				dialogManager.DialogSetButton(0, " ������");
				_cur += 1;
				break;
			}
			case 7:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
					inventoryManager.InsertItemAuto("FireFeather", 1);
				}
				break;
			}

			case 100:
			{
				dialogManager.DialogSetState(3);
				dialogManager.DialogEnd();
				break;
			}
			case 200:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���� ������ �ּ���.");
				dialogManager.DialogSetButton(0, " ������");
				_cur += 1;
				break;
			}
			case 201:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					dialogManager.DialogEnd();
					_cur += 1;
				}
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("...");
				dialogManager.DialogSetButton(0, "������");
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
				dialogManager.DialogSetState(2);
				dialogManager.DialogEnd();
				break;
			}
			}
		}
	}
}
class NaoZoneMorian
{
	Frame@ frame;
	int _cur;

	NaoZoneMorian(Frame @in_frame)
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
		if(_state == 3 && gameManager.GetProtagonistLv() == "2")
			_state = 4;
		else if(_state == 5 && gameManager.GetProtagonistMobName() == "snail_blue")
			_state = 6;

		if(_state == 0)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���ϼ̾��. \nž�� ������ �����ϱ� ���� ���ݺ��� ������ ������ �˷��帱���� �ؿ�.\n��ŵ�Ͻðھ��?");
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
					_cur = 0;
					dialogManager.DialogSetState(6);
					inventoryManager.InsertItemAuto("Powder_Magic",10);
					inventoryManager.InsertItemAuto("Herb_Red", 10);
					inventoryManager.InsertItemAuto("Herb_Blue", 10);
					inventoryManager.InsertItemAuto("Herb_Dark", 10);
					inventoryManager.InsertItemAuto("Herb_Light", 10);

					 gameManager.GetProtagonist().Evolution("snail_blue");
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�׷� �κ��丮�� ���� ����Կ�.\n I Ű�� ������ �κ��丮�� �� �� �ֽ��ϴ�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 3:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
					if(inventoryManager.InsertItemAuto("NaoBread", 1) == false)
					{
						_cur = 200;
						dialogManager.DialogSetState(0);
					}
					else
						dialogManager.DialogSetState(1);
				}
				break;
			}
			case 200:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("������ â�� ����� �ִ��� Ȯ�����ּ���.");
				dialogManager.DialogSetButton(0, "������");
				_cur += 1;
				break;
			}
			case 201:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur = 100;
				break;
			}
			case 100:
			{
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�κ��丮�� ���� ���� �ʳ���? ���� ��Ƚ��ϴ�.\n�̹��� ������ ������ �������ô�!. \n����Ŭ������ �������� ����� �� �ֽ��ϴ�. ����غ�����.");
				dialogManager.DialogSetButton(0, "������");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur = 100;
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�� ����� ���� ������ ����Ͻ� ����̱���?");
				dialogManager.DialogSetButton(0, "����ϱ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("����� �� ���� �Ծ��µ� �� ���� ���ڱ� �����̰� �Ȱ���?");
				dialogManager.DialogSetButton(0, "����ϱ�");
				_cur += 1;
				break;
			}
			case 3:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				break;
			}
			case 4:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�Ʊ� ������ȵ��� ����� �����̺���...");
				dialogManager.DialogSetButton(0, "����ϱ�");
				_cur += 1;
				break;
			}
			case 5:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				break;
			}
			case 6:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�𸮾�.. �����... ����� �̷���...!!");
				dialogManager.DialogSetButton(0, "����ϱ�");
				_cur += 1;
				break;
			}
			case 7:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				break;
			}
			case 8:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("(��Ȳ�ϴ� ���� �������� �ϰ� �ִ�.)\n�̹��� ���� �ý����� �˷��帱�Կ�!\nZ ����, X ���, C ��� �Դϴ�.");
				dialogManager.DialogSetButton(0, "����ϱ�");
				_cur += 1;
				break;
			}
			case 9:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				break;
			}
			case 10:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("����� ������ ������� �ʾƿ�. ��� ���� ���� �� �ֽ��ϴ�. \n������ ������ ����ؿ�. ��� �� ���� �� �ֽ��ϴ�. \n�������� ����Ű�� ������ �뽬�� �� �� �ֽ��ϴ�.\n�����̸� ��ȯ���״� �ο�������!");
				dialogManager.DialogSetButton(0, "������");
				_cur += 1;
				break;
			}
			case 11:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					dialogManager.DialogSetState(3);
					monsterManager.SpawnAuto("snail", 1, false);
					_cur = 100;
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
			}
			}
		}
		else if(_state == 3)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���Ͱ� ����������?. \n�� ��ȯ�� �帱�Կ�?.");
				dialogManager.DialogSetButton(0, "������");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
					monsterManager.SpawnAuto("snail", 1, false);
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
			}
			}
		}
		else if(_state == 4)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�� �ϼ̾��.\n���װ� �ڽŰ� ������ �����̸� �̱�ôٴ� ����ϼ���.");
				dialogManager.DialogSetButton(0, "����ϱ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�� ���ϼ��Դϱ�?\n���� �������ߴٱ���!!");
				dialogManager.DialogSetButton(0, "����ϱ�");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("(������ �̼Ҹ� ���� �ִ�.)\n�����ƿ�.\n���� ��ȭ�� �غ��ô�.\n����� ���Ѹ�ŭ ���� ���迡�� ��� �� �����ſ���.");
				dialogManager.DialogSetButton(0, "����ϱ�");
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
				dialogManager.DialogSetText("\"K\"Ű�� ������ ��ȭâ�� ��ſ���. \n�ű⿡ �����ִ� ���׸��� �縸ŭ �������� ������ ��ȭ�� �� ���� �ſ���. ");
				dialogManager.DialogSetButton(0, "����ϱ�");
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
				dialogManager.DialogSetText("���� �� �Ӽ��� �´� ���׸� �ϳ� ���� �ؿ�.\n��ȭ�� ���ؼ� �� ������ ��긦 ������ �帱�Կ�. \n Ȥ�� �帰 ��갡 ���ڶ��� �ʰ���?");
				dialogManager.DialogSetButton(0, "����ϱ�");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("������ �ٽ� ������ ���� �ɾ��ּ���. \n���� �� �ֵ��� �ص帱�Կ�.");
				dialogManager.DialogSetButton(0, "������");
				_cur += 1;
				break;
			}
			case 11:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					if(inventoryManager.InsertItemAuto("Herb_Red", 10) == true)
					{
						if(inventoryManager.InsertItemAuto("Herb_Blue", 10) == true)
						{
							if(inventoryManager.InsertItemAuto("Herb_Light", 10) == true)
							{
								if(inventoryManager.InsertItemAuto("Herb_Dark", 10) == true)
								{
									_cur = 100;
									dialogManager.DialogSetState(5);
								}
								else
								{
									inventoryManager.DeleteItemAuto("Herb_Red", 10);
									inventoryManager.DeleteItemAuto("Herb_Blue", 10);
									inventoryManager.DeleteItemAuto("Herb_Light", 10);
									_cur = 200;
									dialogManager.DialogSetState(4);
								}
							}
							else
							{
								inventoryManager.DeleteItemAuto("Herb_Red", 10);
								inventoryManager.DeleteItemAuto("Herb_Blue", 10);
								_cur = 200;
								dialogManager.DialogSetState(4);
							}
						}
						else
						{
							inventoryManager.DeleteItemAuto("Herb_Red", 10);
							_cur = 200;
							dialogManager.DialogSetState(4);
						}

					}
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
			}
			case 200:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("������ â�� ����� �ִ��� Ȯ�����ּ���.");
				dialogManager.DialogSetButton(0, "������");
				_cur += 1;
				break;
			}
			case 201:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}
			}
		}
		else if(_state == 5)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�ٽ� ��ȯ�� �帱�Կ�.\n \"V\"Ű�� ������ �Ա⿡��.");
				dialogManager.DialogSetButton(0, "������");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
					monsterManager.SpawnAuto("snail", 1, false);
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
			}
			}
		}

		else if(_state == 6)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("��ȭ�� ������ �����ϼ̳׿�. �����̿���.");
				dialogManager.DialogSetButton(0, "����ϱ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��.. �������� ����ϸ� �Ǵ°���?\n�����̶�� ���� ���� ������ ���ư��� �ͽ��ϴ�");
				dialogManager.DialogSetButton(0, "����ϱ�");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("(��� ������)�׷� ���ݺ��� ž 1���� �����帮�ڽ��ϴ�.\n������ ž �ֻ����� �������ּ���.");
				dialogManager.DialogSetButton(0, "������");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("���� ��񸸿�! ���ڱ� ���� ������....");
				dialogManager.DialogSetButton(0, "������");
				_cur += 1;
				break;
			}
			case 7:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}
			case 100:
			{
				monsterManager.Teleport("Floor1", "Protagonist", Vector3(0.0f, -5000.0f, 0.0f));
				dialogManager.DialogEnd();
				_cur += 1;
			}
			}
		}

	}
}
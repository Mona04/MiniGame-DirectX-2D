class Floor7Morian
{
	Frame@ frame;
	int _cur;

	Floor7Morian(Frame @in_frame)
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
				dialogManager.DialogSetText("7���̿���.\n");
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
				dialogManager.DialogSetText("������ �����ε�, ���� ������ ����� �����ϱ�?");
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
				dialogManager.DialogSetText("�� �ʿ��� ����ΰ���?");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�׷� �ϳ��ϳ� �Űܶ� ���Դϱ�? \n�鰳�� ������ �ִ� ����������?");
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
				dialogManager.DialogSetText("�׳� �����Ͻø� ������ ���մϴ�.. \n������ �¿� �ҵ� �����ϱ��.");
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
				dialogManager.DialogSetText("Ȥ��..\n������ ������ �������� ���� ���� ���°� �ƴ���?");
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
				dialogManager.DialogSetText("�����̿���.\n�׷��ϱ� 3x3ĭ�� ������ Ȥ�� �𸣴ϱ� �׻� ����ּ���.");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�������� ����ּ��� ��� ���� �׻� �ֱⰡ �����ŵ��.");
				dialogManager.DialogSetButton(0, " ������");
				_cur += 1;
				break;
			}
			case 15:
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
		else
		{
		switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�𸮾�. ����� ������ �־��.");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("���� ����� ŰƮ�� ����� �ƴѰ� �ǽ��ϰ� �ֽ��ϴ�.");
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
				dialogManager.DialogSetText("�����ϰ� �˷��ּ���.");
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
				dialogManager.DialogSetText("...");
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
				dialogManager.DialogSetText("��, ������ ���� ����, \n�˷����� ����� ���ھ��.");
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
				dialogManager.DialogSetText("�����Ѵٴ� ���Դϱ�?");
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
				dialogManager.DialogSetText("�׷����ϴ�. \n������ �з��þ��� �θ��� ���ؼ� ��¿ �� ���� ���̾����.");
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
				dialogManager.DialogSetText("�з��þ��� �������� �׻� ���ڴٸ� ��ε� �ҵ常 �ֵѷ����Ѵٸ� \n� �з��þ��� ������ �ӹ��ھ��?\n����� �з��þ��� ������ ���� �������� �;��߾��.");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�װ͵��� ������ ��ġ�� ���⵵ ����� �����̾�����?\n���� �� �Ҹ��� �ƴ�����, �װ͵��� ������ �ı����״ٰ� ������ϴ�.\n��ſ��Ե� ���Դϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�˰� �־����ϴ�.\n������ ��¿ �� �������. \n��� ��ƾ��ϴµ� ������ �ѹ濡 ������ �ҿ��� �����ϱ��.");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���� �߸��ߴٰ� �����Ͻó���?\n������ �װ͵� ���п� ������ ����� �ڷ� �̷���ϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("ŰȦ�� �̻��� ������ ���� ���\n�������� ���ڸ� ���÷� �ٴϰ�,\n���� ������ ������ ��Ű�� ���ؼ� ���� ����.");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�̷� ���� �ൿ�� ������ ������� ���������,\n�̰͸��� ������ ��ų �� �ִ� �ൿ�̾����.");
				dialogManager.DialogSetButton(0, " ������");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�з��þ�, ������ �ܼ������� �ʾƿ�.");
				dialogManager.DialogSetButton(0, " ������");
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
				dialogManager.DialogSetState(1);
				dialogManager.DialogEnd();
				break;
			}
			}
		}

	}
}
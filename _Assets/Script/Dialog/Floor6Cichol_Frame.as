class Floor6Cichol
{
	Frame@ frame;
	int _cur;

	Floor6Cichol(Frame @in_frame)
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
				dialogManager.DialogSetIllust("UI/NPC/cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("...");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				dialogManager.DialogSetButton(1, " �����Ѵ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				if(dialogManager.IsDialogButtonClicked(1))
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
				dialogManager.DialogSetText("�� ŰƮ�� ����غý��ϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�׷� ���� �˰ڱ�");
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
				dialogManager.DialogSetText("�װ� Ȯ���� ŰƮ�����ϴ�. \nŰ���� Ƣ����� �ͱ��� �Ϻ��� ������... ŰƮ�����ϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�׷��ٸ� �������� ���� �ְ���?");
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
				dialogManager.DialogSetText("���� ������ �з��þȵ��� ���ϰ� ����� �ǵ��� ���̿�����...\n�Ƹ��� �� ���� ���� �����ϴ� �͵� ��������...");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("���� ������ ���״ٰ� ���������� ��� ��������Ʈ�������� �𸣰ڽ��ϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�װ� �ƴϴ�.\n����� ������ ���� ����� �� ������ ���� ����.");
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
				dialogManager.DialogSetText("�װ� ��� Ȯ���� �� �ֽ��ϴ�. \nŰƮ��, �巡�ﵵ ���� �� �ִٸ� ���������� ���� �� ���� �ʽ��ϱ�?");
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
				dialogManager.DialogSetIllust("UI/NPC/cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�ƽ��Ե� �׷� ���ɼ��� ����.");
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
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�𸮾��� ����, ���� ���� ¡�׷���� �Ⱦ��ϱ� �����̴�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("?!?!");
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
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�𸮾��� ������ ��Ű������ ����鿡�� ���� ������ ������� ����� ���� ŰƮ���� ���̴�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("������ �׷��� ���������� ������ ���׸��� �з��þȿ��� �� ���... \n�̷��� ������ ����� ������.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 27:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 28:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�׷� ���ΰ���..?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 29:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 30:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�ű��ġ�� �����̶�� �� ���� ������...\n�ٸ� ���ɼ��� ������ �� ����.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 31:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 32:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�׷�����..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 33:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 34:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�� ���� ��Ͱ� �ҿ� ��Ʈ���� ���� �ʾұ� �����̴�.\n���� �׳�� �뼭���� �� ����..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 35:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 36:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�ʿ��� ��Ź �ϳ�����. \n������ ���׸��� ��� �� ������ ���ʸ� 20���� ���ؿͶ�.");
				dialogManager.DialogSetButton(0, " ������");
				_cur += 1;
				break;
			}
			case 37:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 38:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�� ���ʷ� ������ �� �����̽Ű���?");
				dialogManager.DialogSetButton(0, " ���");
				_cur += 1;
				break;
			}
			case 39:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 40:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("������ ��ã�� ����� ã�� ���� ���� ���̴�. \n���� ������ ��ٸ����� ����.");
				dialogManager.DialogSetButton(0, " ������");
				_cur += 1;
				break;
			}
			case 41:
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
			case 200:
			{
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
				dialogManager.DialogSetIllust("UI/NPC/cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("...");
				dialogManager.DialogSetButton(0, " ����ϱ�");
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
				break;
			}
			}
		}

	}
}
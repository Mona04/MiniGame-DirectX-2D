class Floor3Morian
{
	Frame@ frame;
	int _cur;

	Floor3Morian(Frame @in_frame)
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
				dialogManager.DialogSetText("���� 3���̿���.\n");
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
				dialogManager.DialogSetText("�ٵ� �� �����ΰ���?");
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
				dialogManager.DialogSetText("���� �÷��� ���������̳���?");
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
				dialogManager.DialogSetText("���͸� ��� ����Ʈ�� ���� �������� �ؼ� ȯ�����ϴ�,\n �̰��� �ݺ��ε� ���� ����ְھ��?");
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
				dialogManager.DialogSetText("�˼��ؿ�.���� ��վ��� �׸�...\n���� �÷��� �޴� ���忡�� ���� ����������� ������.");
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
				dialogManager.DialogSetText("�� ��� �̴ϱ�?");
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
				dialogManager.DialogSetText("���� ���� �Ǿ�帮�� ���ؼ� �˼��ؿ�.");
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
				dialogManager.DialogSetText("�׷� ž�� ������ ������ �÷��� �̰ܳ� ����� ��ٸ��� �ְڽ��ϴ�. \n��������!");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���� ���ΰ���?");
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
				dialogManager.DialogSetText("���� ������ ���� �ʾҴ� ���� ���.. \n������ �־� �� ���Ҵ� ���� �ƴұ� ������ ����.");
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
				dialogManager.DialogSetText("����� ������ ��Ų �����Դϴ�.\n����� �ҿｺƮ������ �������� ���̱� ������ ���� ����ϴ�... \n������ ������ �� �־����ϴ�.");
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
				dialogManager.DialogSetText("�ڶ������� �����ص� ���� ���Դϴ�. \n��ü ������ ����� �׷� ������ �鵵�� ���� �ǰ���?\nȤ�� ŰƮ�� ���ؼ� ��å���� ������ ��Űǰ���?");
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
				dialogManager.DialogSetText("�ƴϿ�. \n�װ� ��¿ �� ���� ���̶�� �����ϰ� �ֽ��ϴ�.\n������ �׷� ������ �� ���� �����ٸ� ������ �� �� ���� �� ����� ������ ���� �ʾ�����. \n");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("ŰƮ�� ���� ������ ����, �ڱ� �������� ���Կ� ������ �ô�.\n���� �л��ڷμ��� �з��þ��� �ƴ� ������ �����ڷμ��� �з��þ�. \n�׷� �Ҽ��� �� �ô븦 �� �� ���� ������ �� ���� �ʾ�����.");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�׳� �̷� ������ ����� ���Դϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�׷���... ���� ���� ������ �ʴٴ°� �𸣽ó���?");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�׷�����...");
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
				dialogManager.DialogSetText("������ ���ϴ°� �翬�Ѱ̴ϴ�. \n������ �������� �߾������� ������� �ű⿡ �Ŵ޸��°� ���� ������ �ƴ϶�� �����ؿ�");
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
				dialogManager.DialogSetText("�ҿｺƮ���� �����̴� ���, �з��þ��� �����ٸ� ������..\n����ó�� ���׸��� ���Ѱ� ������� �� �̻����� �� ���� ������� �̴ϴ�.");
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
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���׸��� ��ü�Ǿ� ������ ������������ ������ �з��þ��� �ٽ� �����ϰ� ����������ϱ��.");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���, �з��þ��� �� ��� ������ �����Ű�⵵ ������, \n�� ���縸���� �������Դϴ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���������ּ���");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 29:
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
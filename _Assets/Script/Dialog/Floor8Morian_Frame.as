class Floor8Morian
{
	Frame@ frame;
	int _cur;

	Floor8Morian(Frame @in_frame)
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
				dialogManager.DialogSetText("8���Դϴ�.\n���� �����̿���!!.\n");
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
				dialogManager.DialogSetText("�̵��ӵ��� �ø��� �������� ����ϸ�\n�� ���� �¾��� �� �˹��� Ŀ���� ���� ����� ��ϴ�.");
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
				dialogManager.DialogSetText("���� �з��þ�.\n�������� ���ٸ��׿�.");
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
				dialogManager.DialogSetText("�����̾����ϱ�?");
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
				dialogManager.DialogSetText("������ �翬���� �ʳ���?\n�˹鵵 �̵��̴ϱ��.");
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
				dialogManager.DialogSetText("�˹鵵 �̵��̶��..");
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
				dialogManager.DialogSetText("�׸��� ���� �Ӹ��� ������ ���� �� ������\n������ �׷� �������� ���°� ���ƿ�.");
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
				dialogManager.DialogSetText("�˰���?");
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
				dialogManager.DialogSetText("����� ŰȦ�� ���� ���� �ٹ̰� �ִ��� �˰� ��ó���?");
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
				dialogManager.DialogSetText("ŰȦ�� ���Դϱ�?");
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
				dialogManager.DialogSetText("�װ� ������ ������� ��ģ�� �˰� ��ó���?\nŰƮ, ����, �巡��... �ڵ��� ����� ���� �ű⿡ �־��.");
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
				dialogManager.DialogSetText("ŰȦ�� �ܿ� �̷��� �����ڴٰ� �� ������� ���ƴٰ�� �������� �ʾƿ�.\n�Ƹ� ������ ���׸��� ���� �����ϴ� ���� �˾Ƴ��� ���� �Ŷ� �����ؿ�.");
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
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���� ������ ���׸��� ��Ƽ� �ٽ� ������ ������� ������ �ƴ���...");
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
				dialogManager.DialogSetText("�з��þ�, ����� ŰȦ���� �̷����� �̾߱⸦ ��� �ִٴ°� �˰� �־��.\n���� ��ȹ�� �˷��ֽðھ��?");
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
				dialogManager.DialogSetText("�װ� �Ϸ��� ���� �ſ� �����ҰŰ��� ������ ����.");
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
				dialogManager.DialogSetText("���� �ڼ����� �𸣰ڽ��ϴ�.\n������ �װ� ������ ���׸��� �����ϴ� ���� �����Ѵٴ� �� �½��ϴ�.");
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
				dialogManager.DialogSetText("���� ���� �巡���� ������ ���ߴٴ� �� �˰� �ֳ���? �з��þ�.");
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
				dialogManager.DialogSetText("���̾�巡��, ����巡��, ���̽��巡��, �ϵ���..\n��� ŰȦ�� �غ��ߴ� �۶󽺱��ٿ��� �� ����Ƽ�� ������̿���. ");
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
				dialogManager.DialogSetText("���� �Ϻη� �װ͵��� ���ϰ� ����� �ƴϿ���.\n���ϰ� ���� �� ������ �ſ���.");
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
				dialogManager.DialogSetText("������ ���׸��� ��ó�� ���������� ������� �����ϸ�,\n�� ���� Ŭ���� �����ڿ��� �δ��� Ŀ���� �����̿���.");
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
				dialogManager.DialogSetText("ŰȦ�� �����˴ϴ�. \n�״� �������� �ڱ� �ڴ�ο����ϱ��.");
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
class Floor16Cichol
{
	Frame@ frame;
	int _cur;

	Floor16Cichol(Frame @in_frame)
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
				dialogManager.DialogSetText("(��ȣ�� ������ 2�� �̻� ��� ������, �ƴϸ� ��忣��(��������))");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				dialogManager.DialogSetButton(1, " �����Ѵ�");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					 if(inventoryManager.GetItemStock("mindCichol") >= 2) //true ending
						_cur = 300;
				}
				if(dialogManager.IsDialogButtonClicked(1))
				{
					_cur = 200;
				}
				break;
			}
			case 300:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("���� ���ο� ������ â���� �����Դϴ�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 301:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 302:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�ƴ�.. �װ� ������.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 303:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 304:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("ŰȦ... ���� ����� �з��þ��� �Ӱ��ΰ���?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 305:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 306:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("��� ���� ������ ������� �ʳ���?\n�� ������ â���ϴ� ���� �����ϴ� ���ΰ���?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 307:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 308:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�ʴ� ������ ���ο� ���� �ٷ���.\n�ʰ� ������� �ϴ� ���� ���� �����ΰ�?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 309:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 310:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�ǻ� �׷��ȿ� ����� ������, ���ǿ� ����� ��������, \n�ʰ� �ϴ� ������ �̹� ���ϴ�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 311:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 312:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("�װ��� ��·�� ���ΰ���!.\n�� �𸮾��� �ִ� ����� �𸮾��� �ִ� �� �����Դϴ�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 313:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 314:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("���̻� �ΰ� �� �� ���ڱ�..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 315:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 316:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�з��þ��� ���� ���� ����Ѵ�.\n���� �ٽ� ������ ������.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 317:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 318:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("�𸮾�");
				dialogManager.DialogSetText("ŰȦ.. ���� �����ΰ���?\n���� �غ� ���� �ٷ� �׷��� ū ���׸��� �����Ѵٴ�... �����մϴ�!!");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 319:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 320:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�������.\n������ ������ ������ �̻� ���� ���� ���� ������...");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 321:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 322:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�з��þ�, �� â�� �ְڴ�..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 323:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 324:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�� â�� ����ϸ� �� ž�� �ν�����.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 325:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 326:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("���� �ʿ��� �� ��ȣ�� ������ �� ������ ���̴�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 327:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 328:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�ʴ� �ٽ� ���� 1�� ���� �ǰ�����.. \n�� ���� ������ �����ϴ� �װɷ� �ȰŰ���..");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 329:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 330:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Cichol.png");
				dialogManager.DialogSetName("ŰȦ");
				dialogManager.DialogSetText("�߰���...");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 331:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					inventoryManager.DeleteItemAuto("mindCichol", 5);

					if(inventoryManager.InsertItemAuto("brionac", 1)==true)
						_cur = 100;
					else
						_cur = 101;
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogSetState(1);
				dialogManager.DialogEnd();
				_cur += 1;
			}
			case 101:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("(������ ���� ������)");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 102:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					dialogManager.DialogEnd();
				}
				break;
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
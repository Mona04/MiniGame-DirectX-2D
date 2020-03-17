class Floor5Blony
{
	Frame@ frame;
	int _cur;

	Floor5Blony(Frame @in_frame)
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
				dialogManager.DialogSetText("�ҷ��ҷ�~");
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
				dialogManager.DialogSetText("�ȳ��ϼ���. ��δ�.");
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
				dialogManager.DialogSetText("�з��þ�~ �ٵ� ���� �������� �ʾ�?");
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
				dialogManager.DialogSetText("��ҿ� �̷��� �Ἥ... ������ �����Ͻó���?");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("�츰 ģ���ݾ�. \n�ʰ� �ȴٸ� ��¿ �� ������...\n��δϿ��� ���ϰ� ���ص� ��!!");
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
				dialogManager.DialogSetText("������ �׷��� ����� ���� ���Ƽ�...");
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
				dialogManager.DialogSetText("����.... \n��½....");
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
				dialogManager.DialogSetText("��δϸ�... ��½... �츮�� .... ����� ���̶�� ... \n ��½... �����ϰ� �־�... ��... ����");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��.. \n���� ������ ��δ�.");
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
				dialogManager.DialogSetText("���ƾƾƾƾ�");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��... \n��δ� ... \n��.. ��... ������.");
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
				dialogManager.DialogSetText("��½.. \n��δϿ��� �ݸ� ���ذž�?");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��.. .��..");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("�츮 ģ�� ģ������ ����?\n��δϸ� �׷��� �����Ѱ� �ƴ���?");
				dialogManager.DialogSetButton(0, " ����");
				dialogManager.DialogSetButton(1, " �ƴ�");
				_cur += 1;
				break;
			}
			case 27:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				if(dialogManager.IsDialogButtonClicked(1))
				{
					_cur = 60;
				}
				break;
			}
			case 28:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��.. �׷�..");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�ʴ� ģ���� ���ݾ�.\n�׷� ģ�� ģ�������ΰ� �翬����.");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("��.. ��ġ?");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("��. ģ���� �ٰ���?");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("�����̾�. \n�ʸ� ���ؼ� ���ο� ������ �����þ�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
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
				dialogManager.DialogSetText("���� �����ε�?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("����ȸ��ǥ���̾�!!\n");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 41:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 42:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("���� �� �����̶� ���� �ٸ��ž�>\n�װ͵� ������ ȸ�����������ʾ�?");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 43:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 44:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("���� �ٸ�����~ \n���������� ����Ű�� ���� �� ������ �̰� ����Ű�� ���� �� ����.\n");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 45:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 46:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("...\n");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 47:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 48:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�Ź� ����?\n");
				dialogManager.DialogSetButton(0, " ������");
				_cur += 1;
				break;
			}
			case 49:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}

			case 60:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("�׷��� ģ�ѻ��̴� �ƴ��� �ʾ�?\n");
				dialogManager.DialogSetButton(0, " ������");
				_cur += 1;
				break;
			}
			case 61:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 62:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("���ƾƾƾƾƾƾ�\n");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 63:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 64:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("���");
				dialogManager.DialogSetText("������ �ʴ� ģ���� ���ݾ�?\n�׷��ϱ� ������ �� ģ�ϰ� ���� �� �����ž�.");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 65:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 66:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("��δ�");
				dialogManager.DialogSetText("��.. �׷��ž�?\n");
				dialogManager.DialogSetButton(0, " ����ϱ�");
				_cur += 1;
				break;
			}
			case 67:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 34;
				}
				break;
			}


			case 100:
			{
				inventoryManager.InsertItemAuto("PerfectPortion", 50); 
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
				dialogManager.DialogSetText("����ȸ�������� ���� �ȵ�����ɱ�?\n������ �Ͱ� ����ϰ� ������µ�...");
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
				dialogManager.DialogSetState(1);
				dialogManager.DialogEnd();
				break;
			}
			}
		}


	}
}
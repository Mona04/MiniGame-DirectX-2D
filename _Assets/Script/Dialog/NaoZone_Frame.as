class NaoZone
{
	Frame@ frame;
	int _cur;

	NaoZone(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		_cur = 0;
	}

	void Update()
	{
		switch(_cur)
		{
		case 0:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/morian.png");
			dialogManager.DialogSetName("�𸮾�");
			dialogManager.DialogSetText("�鸮����?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
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
			dialogManager.DialogSetIllust("UI/NPC/morian.png");
			dialogManager.DialogSetName("�𸮾�");
			dialogManager.DialogSetText("�ٷ� �տ� �ִµ� �翬�� �鸮����?\nũ.. ũ��.\n�ȳ��ϼ��� �з��þ�. �ٽ��ѹ� �Ұ��ҰԿ�. ");
			dialogManager.DialogSetButton(0, " ����ϱ�");
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
			dialogManager.DialogSetText("���� �𸮾�. ����� �����̿���.\n��ŵ�ҷ���?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			dialogManager.DialogSetButton(1, " ��ŵ�ϱ�");
			_cur += 1;
			break;
		}
		case 5:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			if(dialogManager.IsDialogButtonClicked(1))
				_cur = 90;
			break;
		}
		case 6:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("���� ��ݱ��� ���ɺ�ȭ���� �����ϰ� �־��µ�...\n����� ��ü �����?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 7:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			if(dialogManager.IsDialogButtonClicked(1))
				_cur = 100;
			break;
		}
		case 8:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/morian.png");
			dialogManager.DialogSetName("�𸮾�");
			dialogManager.DialogSetText("�׷��׿�... ���� ����� �ؾ��� �� �����ϴ�.\n�˼��մϴ�.");
			dialogManager.DialogSetButton(0, " ����ϱ�");
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
			dialogManager.DialogSetText("...");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 11:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 12:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/morian.png");
			dialogManager.DialogSetName("�𸮾�");
			dialogManager.DialogSetText("������� ����� ������ ��ǿ� �ָ����� �Ǿ����ϴ�.\n�� ����� ����� �� �� \"ž\"�� ������ �Ǿ���.");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 13:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 14:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("��ü... ����..?\n���.. �� ���� ���� �ٹ̰� �ִ°̴ϱ�?\n�ƾƾ�..\n�� ������� ����� �ձ��� ������ ����ϰ� �ֽ��ϴ�... ");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 15:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 16:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/morian.png");
			dialogManager.DialogSetName("�𸮾�");
			dialogManager.DialogSetText(" (��Ȳ�ߴ��� ��� �������� ���߾���) \n ...");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 17:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 18:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/morian.png");
			dialogManager.DialogSetName("�𸮾�");
			dialogManager.DialogSetText("�� ������ ��Ӵ�, �����Ͻ� ��ư �ù̴ϴԲ����� �Ѹ��� �����μ��� ����� �����Ͻ÷��� �Ͻʴϴ�.\n�ٷ� �� \"ž\" ���� ���̿���.");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 19:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 20:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("�� ���� �ƴմϴ�!");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 21:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 22:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/cichol.png");
			dialogManager.DialogSetName("ŰȦ");
			dialogManager.DialogSetText("�ʴ� ���� �ƴ���.\n������ �ݽ����� �ʳ�.?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 23:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 24:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("?!?!?!?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 25:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 26:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/cichol.png");
			dialogManager.DialogSetName("ŰȦ");
			dialogManager.DialogSetText("��ư �ù̴ϴԲ��� ���迡 ȥ���� �������ִ� �з��þ��� ������ ��ġ�� �ִ��� �����Ͻ÷��� �ϴ� ���̴�.");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 27:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 28:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/blony.png");
			dialogManager.DialogSetName("��δ�");
			dialogManager.DialogSetText("�̾��ϰ� �Ǿ���Ⱦ��. \n������ ��ſ��� ������ ���� �̾߱����� �����.\n�Ǵ��� �̾߱⸦ �� ��� ���� �ϱ��... ���?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 29:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 30:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("...");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 31:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 32:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("�׷� �� ������ �������� �˷��ֽʽÿ�.");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 33:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 34:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/cichol.png");
			dialogManager.DialogSetName("ŰȦ");
			dialogManager.DialogSetText("��ư �ù̴ϴԲ��� �ʿ��� ���� �÷�.. \n�ʴ� ���ݺ��� �����̰� �ȴ�. �׸��� ��ȭ�� �ŵ��ؼ� �� ž�� �������� ������ ���̴�.\n�츮���� ������ ���� �÷��� ���Ѻ��� �ʿ��ϴٸ� ���Ե� �ϴ� ��... ");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 35:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 36:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("�����̰� �ȴٴ�... �׳� ���� �̾߱��� �ʽ��ϱ�!");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 37:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 38:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/blony.png");
			dialogManager.DialogSetName("��δ�");
			dialogManager.DialogSetText("������ ���� �������� �̹�... ������ ������°�...");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 39:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 40:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("������ٴ�.. ����..");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 41:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 42:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
			dialogManager.DialogSetName("�÷�Ÿ");
			dialogManager.DialogSetText("������ ���� ����. \n�ʰ� �ı������ݾ�");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 43:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 44:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("����..?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 45:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 46:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/Manannan.png");
			dialogManager.DialogSetName("������");
			dialogManager.DialogSetText("ŰƮ�� ������ ���׸��� ��������°� �˾�?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 47:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 48:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/pepe.png");
			dialogManager.DialogSetName("���");
			dialogManager.DialogSetText("ŰƮ�� ������ ���׸����..?");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 49:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 50:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/Manannan.png");
			dialogManager.DialogSetName("������");
			dialogManager.DialogSetText("�ʰ� ���� ŰƮ�� ������ ���׸��� �Ҹ���׾�. �׷��� ������ �ر��Ѱž�. \n�׷����� �� ���� ���̴ϱ� Ư���� ��ȸ�� ���� ����.\n�� ó���� �˾����� ���ڱ�.");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 51:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 52:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/cichol.png");
			dialogManager.DialogSetName("ŰȦ");
			dialogManager.DialogSetText("��� �����̶� �̾߱Ⱑ �ƴϴ�. \n�ʴ� �� ž���� �����θ� ã�ư��� ���� ����� �ٲٱ⵵, �ɷ��� �ٲٱ⵵ �ϰ���...");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 53:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur += 1;
			break;
		}
		case 54:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/morian.png");
			dialogManager.DialogSetName("�𸮾�");
			dialogManager.DialogSetText("�з��þ�.\n���� ���������� ����� ����� ������ ��� ���� ���κ��� ���۵� ��...\n�켱 �����Է� �ͼ� ����Ű ��Ű�� ���������� �ʰھ��? ����Ű�� �����̴� �Ŷ��ϴ�.");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 55:
		{
			if(dialogManager.IsDialogButtonClicked(0))
				_cur = 100;
			break;
		}
		case 90:
		{
			dialogManager.DialogDefaultUpdate();
			dialogManager.DialogSetIllust("UI/NPC/morian.png");
			dialogManager.DialogSetName("�𸮾�");
			dialogManager.DialogSetText("�з��þ�.\n�׷� Ʃ�丮���̶� �޾ƺ�����.\n�����Է� �ͼ� ����Ű ��Ű�� ���������� �ʰھ��? ����Ű�� �����̴� �Ŷ��ϴ�.");
			dialogManager.DialogSetButton(0, " ����ϱ�");
			_cur += 1;
			break;
		}
		case 91:
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
}
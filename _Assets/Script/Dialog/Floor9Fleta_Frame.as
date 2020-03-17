class Floor9Fleta
{
	Frame@ frame;
	int _cur;

	Floor9Fleta(Frame @in_frame)
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("안녕 밀레시안.");
				dialogManager.DialogSetButton(0, " 계속하기");
				dialogManager.DialogSetButton(1, " 무시하기");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("밀레시안.\n꼴에... 제법 강해보이네");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("그런가요?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("성실히 시련을 받고 있나봐.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("물롭입니다.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("왜?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("제가 할 수 있는 에린을 되돌릴 수 있는 유일한 방법이니까요.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("그래?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("그럼 너한테 이걸 줄게.\n시련을 이겨내는데 도움이 될거야.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("키홀이 필요없다고 줬는데, \n플레타도 필요없거든.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("잘 쓰길 바라");
				dialogManager.DialogSetButton(0, " 계속하기");
				_cur += 1;
				break;
			}
			case 21:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}

			case 100:
			{
				inventoryManager.InsertItemAuto("Sheet_Blue", 8);
				inventoryManager.InsertItemAuto("FireWood", 8);
				inventoryManager.InsertItemAuto("thread", 8);
				inventoryManager.InsertItemAuto("Knife", 8);
				inventoryManager.InsertItemAuto("HandWork", 30);
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("삐슝 빠슝");
				dialogManager.DialogSetButton(0, "끝내기");
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
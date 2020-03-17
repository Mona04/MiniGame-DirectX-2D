class Floor13Blony
{
	Frame@ frame;
	int _cur;

	Floor13Blony(Frame @in_frame)
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("안녕 밀레시안!!");
				dialogManager.DialogSetButton(0, " 계속하기");
				dialogManager.DialogSetButton(1, " 무시한다");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				else if(dialogManager.IsDialogButtonClicked(1))
				{
					_cur = 200;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("안녕 블로니. \n기분이 좋아보이네?");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("응!! 여기의 배경음악이 정말 마음에 들어!!");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("몬스터는 무섭지만...");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("블로니는 앞으로 커서 밀레시안처럼 멋있는 모험가가 될래.");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("너 성인 아니었어?");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("여자의 나이를 묻는건 실례야~ 밀레시안.");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("헤헤. \n친구랑 같이 이렇게 이쁜 숲에 있으니까 좋다.");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("너가 마지막까지 시련을 이겨낼 수 있게,\n블로니 특제 포션을 줄게.");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("아, 아니야.\n나는 그냥 포션이 더 좋아.");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("그래? 알겠어~");
				dialogManager.DialogSetButton(0, " 끝내기");
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
				inventoryManager.InsertItemAuto("RedPotion_Small", 40);
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("근데 하늘은 이쁘다.");
				dialogManager.DialogSetButton(0, " 끝내기");
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
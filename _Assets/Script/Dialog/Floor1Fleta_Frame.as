class Floor1Fleta
{
	Frame@ frame;
	int _cur;

	Floor1Fleta(Frame @in_frame)
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
				dialogManager.DialogSetText("이봐 밀레시안.");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("당신.. 센마이 평원에 출장다니는 플레타맞죠?");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("맞아. 플레타야. \n너에게 부탁이 있어");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("부탁? 저에게? \n당신도 시련을 받고 있는겁니까?");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("아니. 나는 센마이 평원의 신인걸.\n그게 아니라 라브가 약초가 필요한데 마침 너가 와서 부른거 뿐이야.");
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
				dialogManager.DialogSetText("라브...라면 당신의 개?\n");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("맞아, 내 친구야.\n얘가 너무 배가 고프다고 하잖아.\n여기 약초는 에테르가 담겨서 라브가 기운차리게 도와줄거야.\n파란허브 5개만 구해줘.");
				dialogManager.DialogSetButton(0, " 계속하기");
				_cur += 1;
				break;
			}
			case 13:
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
		else if(_state == 1)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("약초는 가져왔어?");
				dialogManager.DialogSetButton(0, " 예");
				dialogManager.DialogSetButton(1, " 아니오");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0) && inventoryManager.GetItemStock("Herb_Blue") >= 2)
				{
					_cur += 1;
					inventoryManager.DeleteItemAuto("Herb_Blue", 3);
				}
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
				dialogManager.DialogSetText("고마워. 답례로 이걸 줄게.");
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("최근에 날 찾는 사람이 줄었어..\n그래서 남은 재고야.\n쓰면 이동속도를 올려줄거야. 잘 쓰도록 해");
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
				dialogManager.DialogSetText("그리고 왼쪽에 블로니가 포션을 만들고 있던데\n가보는게 어때?");
				dialogManager.DialogSetButton(0, " 계속하기");
				_cur += 1;
				break;
			}
			case 7:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
					inventoryManager.InsertItemAuto("FletaRobe", 10);
				}
				break;
			}

			case 100:
			{
				dialogManager.DialogSetState(2);
				dialogManager.DialogEnd();
				break;
			}
			case 200:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("쓸모없네. 빨리 가져다줘");
				dialogManager.DialogSetButton(0, " 끝내기");
				_cur += 1;
				break;
			}
			case 201:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					dialogManager.DialogEnd();
					_cur += 1;
				}
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
				dialogManager.DialogSetIllust("UI/NPC/Fleta.png");
				dialogManager.DialogSetName("플레타");
				dialogManager.DialogSetText("이 층 어딘가에 윗층으로 올라가는 길이 있어.\n행운을 빌게 밀레시안.");
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
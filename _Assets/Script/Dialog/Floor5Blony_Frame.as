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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("할로할로~");
				dialogManager.DialogSetButton(0, " 계속하기");
				dialogManager.DialogSetButton(1, " 무시한다");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("안녕하세요. 블로니.");
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
				dialogManager.DialogSetText("밀레시안~ 근데 존댓말 불편하지 않아?");
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
				dialogManager.DialogSetText("평소에 이렇게 써서... 존댓말이 불편하시나요?");
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
				dialogManager.DialogSetText("우린 친구잖아. \n너가 싫다면 어쩔 수 없지만...\n블로니에게 편하게 말해도 돼!!");
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
				dialogManager.DialogSetText("하지만 그러면 가까운 사이 같아서...");
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
				dialogManager.DialogSetText("에에.... \n훌쩍....");
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
				dialogManager.DialogSetText("블로니만... 훌쩍... 우리가 .... 가까운 사이라고 ... \n 훌쩍... 생각하고 있었... 으... 으앙");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("어.. \n울지 마세요 블로니.");
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
				dialogManager.DialogSetIllust("UI/NPC/Blony.png");
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("으아아아아앙");
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
				dialogManager.DialogSetIllust("UI/NPC/Pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("어... \n블로니 ... \n어.. 그... 울지마.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("훌쩍.. \n블로니에게 반말 써준거야?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("어.. .어..");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("우리 친한 친구사이 맞지?\n블로니만 그렇게 생각한거 아니지?");
				dialogManager.DialogSetButton(0, " 맞음");
				dialogManager.DialogSetButton(1, " 아님");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("그.. 그럼..");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("너는 친구비를 주잖아.\n그럼 친한 친구사이인게 당연하지.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("그.. 그치?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("응. 친구비 줄거지?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("물론이야. \n너를 위해서 새로운 포션을 만들어봤어.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("무슨 포션인데?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("완전회복표션이야!!\n");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("전에 준 포션이랑 뭐가 다른거야>\n그것도 완전히 회복시켜줬지않아?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("뭐가 다르나면~ \n빨간포션은 단축키로 먹을 수 있지만 이건 단축키로 먹을 수 없어.\n");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("...\n");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("매번 고마워?\n");
				dialogManager.DialogSetButton(0, " 끝내기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("그렇게 친한사이는 아니지 않아?\n");
				dialogManager.DialogSetButton(0, " 끝내기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("으아아아아아아앙\n");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("하지만 너는 친구비를 주잖아?\n그러니까 앞으로 더 친하게 지낼 수 있을거야.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("그.. 그런거야?\n");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("블로니");
				dialogManager.DialogSetText("완전회복포션이 맘에 안들었던걸까?\n에린의 것과 비슷하게 만들었는데...");
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
				dialogManager.DialogSetState(1);
				dialogManager.DialogEnd();
				break;
			}
			}
		}


	}
}
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("(수호의 반지가 2개 이상 경우 진엔딩, 아니면 배드엔딩(엔딩없음))");
				dialogManager.DialogSetButton(0, " 계속하기");
				dialogManager.DialogSetButton(1, " 무시한다");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("이제 새로운 에린을 창조할 차례입니다.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("아니.. 그건 무리다.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("키홀... 설마 당신이 밀레시안을 꾄것인가요?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("당신 역시 에린을 사랑하지 않나요?\n왜 에린을 창조하는 것을 방해하는 것인가요?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("너는 언제나 새로운 것을 바랬지.\n너가 만들려고 하는 것은 진정 에린인가?");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("실사 그래픽에 가까운 외형에, 현실에 가까운 물리엔진, \n너가 하는 생각은 이미 훤하다.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("그것이 어쨌단 말인가요!.\n저 모리안이 있는 세계는 모리안이 있는 한 에린입니다.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("더이상 두고 볼 수 없겠군..");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("밀레시안의 힘은 내가 사용한다.\n내가 다시 에린을 만들지.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("키홀.. 죽을 생각인가요?\n사전 준비도 없이 바로 그렇게 큰 에테르를 조작한다니... 무모합니다!!");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("상관없다.\n어차피 에린이 없어진 이상 내가 있을 곳은 없으니...");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("밀레시안, 이 창을 주겠다..");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("이 창을 사용하면 이 탑은 부숴진다.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("내가 너에게 준 수호의 반지는 널 지켜줄 것이다.");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("너는 다시 누렙 1의 뉴비가 되겠지만.. \n너 역시 에린을 좋아하니 그걸로 된거겠지..");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("잘가라...");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("(가방을 비우고 오세요)");
				dialogManager.DialogSetButton(0, " 계속하기");
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
				dialogManager.DialogSetName("키홀");
				dialogManager.DialogSetText("...");
				dialogManager.DialogSetButton(0, " 계속하기");
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
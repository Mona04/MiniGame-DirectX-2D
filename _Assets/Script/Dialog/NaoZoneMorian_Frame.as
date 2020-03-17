class NaoZoneMorian
{
	Frame@ frame;
	int _cur;

	NaoZoneMorian(Frame @in_frame)
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
		if(_state == 3 && gameManager.GetProtagonistLv() == "2")
			_state = 4;
		else if(_state == 5 && gameManager.GetProtagonistMobName() == "snail_blue")
			_state = 6;

		if(_state == 0)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("잘하셨어요. \n탑의 내부의 입장하기 전에 지금부터 간략한 지식을 알려드릴려고 해요.\n스킵하시겠어요?");
				dialogManager.DialogSetButton(0, " 계속하기");
				dialogManager.DialogSetButton(1, " 스킵하기");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				if(dialogManager.IsDialogButtonClicked(1))
				{
					_cur = 0;
					dialogManager.DialogSetState(6);
					inventoryManager.InsertItemAuto("Powder_Magic",10);
					inventoryManager.InsertItemAuto("Herb_Red", 10);
					inventoryManager.InsertItemAuto("Herb_Blue", 10);
					inventoryManager.InsertItemAuto("Herb_Dark", 10);
					inventoryManager.InsertItemAuto("Herb_Light", 10);

					 gameManager.GetProtagonist().Evolution("snail_blue");
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("그럼 인벤토리를 먼저 열어볼게요.\n I 키를 누르면 인벤토리를 열 수 있습니다.");
				dialogManager.DialogSetButton(0, " 계속하기");
				_cur += 1;
				break;
			}
			case 3:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
					if(inventoryManager.InsertItemAuto("NaoBread", 1) == false)
					{
						_cur = 200;
						dialogManager.DialogSetState(0);
					}
					else
						dialogManager.DialogSetState(1);
				}
				break;
			}
			case 200:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("아이템 창이 비워져 있는지 확인해주세요.");
				dialogManager.DialogSetButton(0, "끝내기");
				_cur += 1;
				break;
			}
			case 201:
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
		else if(_state == 1)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("인벤토리에 빵이 있지 않나요? 제가 드렸습니다.\n이번엔 아이템 사용법을 익혀봅시다!. \n더블클릭으로 아이템을 사용할 수 있습니다. 사용해보세요.");
				dialogManager.DialogSetButton(0, "끝내기");
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
				_cur += 1;
			}
			}
		}
		else if(_state == 2)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("그 모습을 보니 무사히 사용하신 모양이군요?");
				dialogManager.DialogSetButton(0, "계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("당신이 준 빵을 먹었는데 왜 내가 갑자기 달팽이가 된거죠?");
				dialogManager.DialogSetButton(0, "계속하기");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("아까 말씀드렸듯이 당신은 달팽이부터...");
				dialogManager.DialogSetButton(0, "계속하기");
				_cur += 1;
				break;
			}
			case 5:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				break;
			}
			case 6:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("모리안.. 당신은... 사람을 이렇게...!!");
				dialogManager.DialogSetButton(0, "계속하기");
				_cur += 1;
				break;
			}
			case 7:
			{
				if(dialogManager.IsDialogButtonClicked(0))
					_cur += 1;
				break;
			}
			case 8:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("(당황하는 듯한 움직임을 하고 있다.)\n이번엔 전투 시스템을 알려드릴게요!\nZ 강공, X 약공, C 방어 입니다.");
				dialogManager.DialogSetButton(0, "계속하기");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("약공은 마나를 사용하지 않아요. 대신 방어로 막을 수 있습니다. \n강공은 마나를 사용해요. 대신 방어를 뚫을 수 있습니다. \n연속으로 방향키를 누르면 대쉬를 할 수 있습니다.\n달팽이를 소환할테니 싸워보세요!");
				dialogManager.DialogSetButton(0, "끝내기");
				_cur += 1;
				break;
			}
			case 11:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					dialogManager.DialogSetState(3);
					monsterManager.SpawnAuto("snail", 1, false);
					_cur = 100;
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
			}
			}
		}
		else if(_state == 3)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("몬스터가 없어졌나요?. \n또 소환해 드릴게요?.");
				dialogManager.DialogSetButton(0, "끝내기");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
					monsterManager.SpawnAuto("snail", 1, false);
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
			}
			}
		}
		else if(_state == 4)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("잘 하셨어요.\n안죽고 자신과 동급인 달팽이를 이기시다니 대단하세요.");
				dialogManager.DialogSetButton(0, "계속하기");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("날 죽일셈입니까?\n거의 죽을뻔했다구요!!");
				dialogManager.DialogSetButton(0, "계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("(잔잔한 미소를 짓고 있다.)\n괜찮아요.\n이제 진화를 해봅시다.\n당신이 강한만큼 죽을 위험에서 벗어날 수 있을거에요.");
				dialogManager.DialogSetButton(0, "계속하기");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("\"K\"키를 누르면 진화창이 뜰거에요. \n거기에 나와있는 에테르의 양만큼 아이템이 있으면 진화할 수 있을 거에요. ");
				dialogManager.DialogSetButton(0, "계속하기");
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
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("허브는 각 속성에 맞는 에테르 하나 몫을 해요.\n진화를 위해서 각 종류별 허브를 열개씩 드릴게요. \n 혹시 드린 허브가 모자라진 않겠죠?");
				dialogManager.DialogSetButton(0, "계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("없으면 다시 저에게 말을 걸어주세요. \n얻을 수 있도록 해드릴게요.");
				dialogManager.DialogSetButton(0, "끝내기");
				_cur += 1;
				break;
			}
			case 11:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					if(inventoryManager.InsertItemAuto("Herb_Red", 10) == true)
					{
						if(inventoryManager.InsertItemAuto("Herb_Blue", 10) == true)
						{
							if(inventoryManager.InsertItemAuto("Herb_Light", 10) == true)
							{
								if(inventoryManager.InsertItemAuto("Herb_Dark", 10) == true)
								{
									_cur = 100;
									dialogManager.DialogSetState(5);
								}
								else
								{
									inventoryManager.DeleteItemAuto("Herb_Red", 10);
									inventoryManager.DeleteItemAuto("Herb_Blue", 10);
									inventoryManager.DeleteItemAuto("Herb_Light", 10);
									_cur = 200;
									dialogManager.DialogSetState(4);
								}
							}
							else
							{
								inventoryManager.DeleteItemAuto("Herb_Red", 10);
								inventoryManager.DeleteItemAuto("Herb_Blue", 10);
								_cur = 200;
								dialogManager.DialogSetState(4);
							}
						}
						else
						{
							inventoryManager.DeleteItemAuto("Herb_Red", 10);
							_cur = 200;
							dialogManager.DialogSetState(4);
						}

					}
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
			}
			case 200:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/Morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("아이템 창이 비워져 있는지 확인해주세요.");
				dialogManager.DialogSetButton(0, "끝내기");
				_cur += 1;
				break;
			}
			case 201:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}
			}
		}
		else if(_state == 5)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("다시 소환해 드릴게요.\n \"V\"키가 아이템 먹기에요.");
				dialogManager.DialogSetButton(0, "끝내기");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
					monsterManager.SpawnAuto("snail", 1, false);
				}
				break;
			}
			case 100:
			{
				dialogManager.DialogEnd();
				_cur += 1;
			}
			}
		}

		else if(_state == 6)
		{
			switch(_cur)
			{
			case 0:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("진화에 무사히 성공하셨네요. 다행이에요.");
				dialogManager.DialogSetButton(0, "계속하기");
				_cur += 1;
				break;
			}
			case 1:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur += 1;
				}
				break;
			}
			case 2:
			{
				dialogManager.DialogDefaultUpdate();
				dialogManager.DialogSetIllust("UI/NPC/pepe.png");
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("후.. 이제부터 어떻게하면 되는거죠?\n달팽이라니 빨리 원래 몸으로 돌아가고 싶습니다");
				dialogManager.DialogSetButton(0, "계속하기");
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
				dialogManager.DialogSetIllust("UI/NPC/morian.png");
				dialogManager.DialogSetName("모리안");
				dialogManager.DialogSetText("(방긋 웃으며)그럼 지금부터 탑 1층에 보내드리겠습니다.\n무사히 탑 최상층에 도달해주세요.");
				dialogManager.DialogSetButton(0, "끝내기");
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
				dialogManager.DialogSetName("당신");
				dialogManager.DialogSetText("저기 잠깐만요! 갑자기 어디로 보낸단....");
				dialogManager.DialogSetButton(0, "끝내기");
				_cur += 1;
				break;
			}
			case 7:
			{
				if(dialogManager.IsDialogButtonClicked(0))
				{
					_cur = 100;
				}
				break;
			}
			case 100:
			{
				monsterManager.Teleport("Floor1", "Protagonist", Vector3(0.0f, -5000.0f, 0.0f));
				dialogManager.DialogEnd();
				_cur += 1;
			}
			}
		}

	}
}
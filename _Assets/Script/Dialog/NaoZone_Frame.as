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
			dialogManager.DialogSetName("모리안");
			dialogManager.DialogSetText("들리나요?");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("모리안");
			dialogManager.DialogSetText("바로 앞에 있는데 당연히 들리겠죠?\n크.. 크흠.\n안녕하세요 밀레시안. 다시한번 소개할게요. ");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetText("저는 모리안. 까마귀의 여신이에요.\n스킵할래요?");
			dialogManager.DialogSetButton(0, " 계속하기");
			dialogManager.DialogSetButton(1, " 스킵하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("저는 방금까지 벚꽃비화술을 수련하고 있었는데...\n여기는 대체 어디죠?");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("모리안");
			dialogManager.DialogSetText("그렇네요... 먼저 사과를 해야할 것 같습니다.\n죄송합니다.");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetText("...");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("모리안");
			dialogManager.DialogSetText("저희들은 상당히 복잡한 사건에 휘말리게 되었습니다.\n그 결과로 당신은 이 곳 \"탑\"에 들어오게 되었죠.");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("대체... 무슨..?\n당신.. 또 무슨 일을 꾸미고 있는겁니까?\n아아아..\n제 뒷통수는 당신의 손길을 아직도 기억하고 있습니다... ");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("모리안");
			dialogManager.DialogSetText(" (당황했는지 잠깐 움직임이 멈추었다) \n ...");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("모리안");
			dialogManager.DialogSetText("이 세계의 어머니, 위대하신 아튼 시미니님께서는 한명의 신으로서의 당신을 시험하시려고 하십니다.\n바로 이 \"탑\" 에서 말이에요.");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("전 신이 아닙니다!");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("키홀");
			dialogManager.DialogSetText("너는 신은 아니지.\n하지만 반신이지 않나.?");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("?!?!?!?");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("키홀");
			dialogManager.DialogSetText("아튼 시미니님께선 세계에 혼돈을 가져다주는 밀레시안이 존재할 가치가 있는지 시험하시려고 하는 것이다.");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("블로니");
			dialogManager.DialogSetText("미안하게 되어버렸어요. \n하지만 당신에게 나쁘지 않은 이야기일지 몰라요.\n판단은 이야기를 다 듣고 나서 하기로... 어때요?");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("...");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("그럼 그 시험이 무엇인지 알려주십시오.");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("키홀");
			dialogManager.DialogSetText("아튼 시미니님께서 너에게 내린 시련.. \n너는 지금부터 달팽이가 된다. 그리고 진화를 거듭해서 이 탑의 꼭대기까지 오르는 것이다.\n우리들의 역할은 너의 시련을 지켜보고 필요하다면 개입도 하는 것... ");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("달팽이가 된다니... 그냥 나쁜 이야기지 않습니까!");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("블로니");
			dialogManager.DialogSetText("하지만 너의 영향으로 이미... 에린은 사라졌는걸...");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("사라졌다니.. 무슨..");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("플레타");
			dialogManager.DialogSetText("에린은 이제 없어. \n너가 파괴시켰잖아");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("내가..?");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("마나난");
			dialogManager.DialogSetText("키트가 에린의 에테르로 만들어지는건 알아?");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("당신");
			dialogManager.DialogSetText("키트가 에린의 에테르라고..?");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("마나난");
			dialogManager.DialogSetText("너가 만들어낸 키트가 에린의 에테르를 소모시켰어. 그래서 에린이 붕괴한거야. \n그럼에도 넌 반은 신이니까 특별히 기회를 받은 거지.\n네 처지를 알았으면 좋겠군.");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("키홀");
			dialogManager.DialogSetText("평생 달팽이란 이야기가 아니다. \n너는 그 탑에서 스스로를 찾아감에 따라 모습을 바꾸기도, 능력을 바꾸기도 하겠지...");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("모리안");
			dialogManager.DialogSetText("밀레시안.\n저는 직접적으로 당신을 도울순 없지만 모든 것은 저로부터 시작된 것...\n우선 저에게로 와서 방향키 위키를 눌러보시지 않겠어요? 방향키가 움직이는 거랍니다.");
			dialogManager.DialogSetButton(0, " 계속하기");
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
			dialogManager.DialogSetName("모리안");
			dialogManager.DialogSetText("밀레시안.\n그럼 튜토리얼이라도 받아보세요.\n저에게로 와서 방향키 위키를 눌러보시지 않겠어요? 방향키가 움직이는 거랍니다.");
			dialogManager.DialogSetButton(0, " 계속하기");
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
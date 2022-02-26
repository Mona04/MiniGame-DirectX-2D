class MainGame
{
	Frame@ frame;
	ProgressBar@ _hpBar;
	ProgressBar@ _mpBar;
	ProgressBar@ _spBar;

	MainGame(Frame @in_frame)
	{
		@frame = in_frame;
	}
	
	void Start()
	{
		@_hpBar = uiManager.GetUIComponent_ProgressBar("HP_Bar");
		@_mpBar = uiManager.GetUIComponent_ProgressBar("MP_Bar");
		@_spBar = uiManager.GetUIComponent_ProgressBar("SP_Bar");
	}
	
	void Update()
	{
	}
}
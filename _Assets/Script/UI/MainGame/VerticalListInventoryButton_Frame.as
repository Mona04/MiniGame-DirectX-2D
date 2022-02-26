class VerticalListInventoryButton
{
	Frame@ frame;
	VerticalListInventoryButton(Frame @in_frame)
	{
		@frame = in_frame;
	}

	void Start()
	{
		frame.SetText("Inven");
	}
	
	void Update()
	{
		if(frame.IsClicked())
			inventoryManager.ToggleInventory();
	}
}
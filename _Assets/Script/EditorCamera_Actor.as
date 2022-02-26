class EditorCamera
{
	Actor@ actor;
	Transform@ transform;

	EditorCamera(Actor @in_actor)
	{
		@actor = in_actor;
		@transform = in_actor.GetTransform();
	}
	
	void Start()
	{
	}
	
	void Update()
	{
		bool bPressed = false;
		Vector3 pos = transform.GetPosition();
		float delta = timer.GetDeltaTime() * 500;
		
		if(input.KeyPress(KeyCode::KEY_A))
		{	
			pos = pos + delta * Vector3(-1, 0, 0);
			bPressed = true;
		}
		if(input.KeyPress(KeyCode::KEY_D))
		{
			pos = pos + delta * Vector3(+1, 0, 0);
			bPressed = true;		
		}
		if(input.KeyPress(KeyCode::KEY_W))
		{
			pos = pos + delta * Vector3(0, +1, 0);
			bPressed = true;		
		}
		if(input.KeyPress(KeyCode::KEY_S))
		{
			pos = pos + delta * Vector3(0, -1, 0);
			bPressed = true;		
		}
		
		if(bPressed)
		{
			transform.SetPosition(pos);	
		}
	}
}
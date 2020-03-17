#include "Framework.h"
#include "Box.h"

Box::Box(Context* context)
	: IUIComponent(context)
{
	type = UIComponentType::Box;
}

void Box::Init_Default()
{
	auto frame = AddFrame("frame");
	frame->Init_Default();
	frame->GetTransform()->SetScale(Vector3(10, 10, 10));
};

void Box::Update()
{
	for (const auto& frame : frames)
		frame->Update();
}

void Box::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		std::string frameName;

		stream.Read(frameName);

		UI_Component_Frame* frame = AddFrame(frameName);
		frame->LoadFromFile(stream);
	}
	stream.Close();
}

void Box::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		for (auto& frame : frames)
		{
			stream.Write(frame->GetName()); // frameName
			frame->SaveToFile(stream);
		}
	}
	stream.Close();
}

#include "Framework.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(Context* context)
	: IUIComponent(context)
{
	type = UIComponentType::ProgressBar;
}

void ProgressBar::Init_Default()
{
	{
		auto frame = AddFrame("Gauge");
		frame->Init_Default();
		frame->GetTransform()->SetScale(scale);
	}
	{
		auto frame = AddFrame("Frame");
		frame->Init_Default();
		frame->GetTransform()->SetScale(scale);
	}	
}

void ProgressBar::Update()
{
	for (auto& frame : frames)
		frame->Update();
}

// 애는 Frame, Gauge 로 고정시킬 생각임
void ProgressBar::LoadFromFile(const std::string& path)
{
	IUIComponent::Clear();

	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		stream.Read(pos); // pos
		stream.Read(scale); // scale

		std::string frameName;

		stream.Read(frameName);

		UI_Component_Frame* frame = AddFrame(frameName);
		frame->LoadFromFile(stream);
		
		stream.Read(frameName);
		
		frame = AddFrame(frameName);
		frame->LoadFromFile(stream);
	}
	stream.Close();

	_gaugeScale = GetFrame("Gauge")->GetScale();
	Update();
}

void ProgressBar::SaveToFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(pos); // pos
		stream.Write(scale); // scale
		
		for (auto& frame : frames)
		{
			stream.Write(frame->GetName()); // frameName
			frame->SaveToFile(stream);
		}
	}
	stream.Close();
}

void ProgressBar::SetProgress(const int& numerator, const int& denominator)
{
	float percentage = static_cast<float>(numerator) / static_cast<float>(denominator);
	percentage = percentage >= 1.0f ? 1.0f : percentage < 0.0f ? 0.0f : percentage;

	GetFrame("Gauge")->GetTransform()->SetScale(Vector3(percentage * _gaugeScale.x, _gaugeScale.y, 0.0f));
}

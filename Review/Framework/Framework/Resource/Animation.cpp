#include "Framework.h"
#include "Animation.h"
#include "Texture.h"

#undef BINARYMODE

Animation::Animation(Context * context)
	: IResource(context)
	, repeatType(RepeatType::Once)
{
	
}

Animation::~Animation()
{
}

void Animation::SaveToFile(const std::string & path)
{
#ifdef BINARYMODE
    Xml::XMLDocument doc;
    Xml::XMLDeclaration* decl = doc.NewDeclaration();
    doc.LinkEndChild(decl);

    Xml::XMLElement* root = doc.NewElement("Animation");
    doc.LinkEndChild(root);

    root->SetAttribute("AnimationName", resourceName.c_str());
    root->SetAttribute("TexturePath", texturePath.c_str());
    root->SetAttribute("RepeatType", static_cast<uint>(repeatType));

    for (const auto& keyframe : keyframes)
    {
        Xml::XMLElement* firstElem = doc.NewElement("Keyframe");
        root->LinkEndChild(firstElem);

        firstElem->SetAttribute("OffsetX", keyframe.offset.x);
        firstElem->SetAttribute("OffsetY", keyframe.offset.y);
        firstElem->SetAttribute("SizeX", keyframe.size.x);
        firstElem->SetAttribute("SizeY", keyframe.size.y);
        firstElem->SetAttribute("Time", keyframe.time);
    }
    doc.SaveFile(path.c_str());
#else
    FileStream w;
    w.Open(path, StreamMode::Write);
    {
        w.Write(resourceName);
        w.Write(texturePath);
        w.Write(static_cast<uint>(repeatType));
        w.Write(keyframes.size());
        for (const auto& keyframe : keyframes)
        {
            w.Write(keyframe.offset);
            w.Write(keyframe.size);
            w.Write(keyframe.time);
        }
    }
    w.Close();
#endif
}

void Animation::LoadFromFile(const std::string & path)
{
#ifdef BINARYMODE
    Xml::XMLDocument doc;
    Xml::XMLError error = doc.LoadFile(path.c_str());
    assert(error == Xml::XMLError::XML_SUCCESS);

    Xml::XMLElement* root = doc.FirstChildElement();
    resourceName = root->Attribute("AnimationName");
    std::string texturePath = root->Attribute("TexturePath");
    repeatType = static_cast<RepeatType>(root->IntAttribute("RepeatType"));

    SetSprite(texturePath);

    Xml::XMLElement* firstElem = root->FirstChildElement();
    for (; firstElem != nullptr; firstElem = firstElem->NextSiblingElement())
    {
        float offsetX = firstElem->FloatAttribute("OffsetX");
        float offsetY = firstElem->FloatAttribute("OffsetY");
        float sizeX = firstElem->FloatAttribute("SizeX");
        float sizeY = firstElem->FloatAttribute("SizeY");
        float time = firstElem->FloatAttribute("Time");

        AddKeyframe({ offsetX, offsetY }, { sizeX, sizeY }, time);
    }
#else
    FileStream r;
    r.Open(path, StreamMode::Read);
    {
        uint repeat = 0;

        r.Read(resourceName);
        r.Read(texturePath);
        r.Read(repeat);

        repeatType = static_cast<RepeatType>(repeat);

        uint count = r.ReadUInt();
        for (uint i = 0; i < count; i++)
        {
            Vector2 offset;
            Vector2 size;
            float time;

            r.Read(offset);
            r.Read(size);
            r.Read(time);

            AddKeyframe(offset, size, time);
        }
    }
    r.Close();
#endif
}

Keyframe * Animation::GetKeyframeFromIndex(const uint & index)
{
	if (keyframes.size() <= index)
		return nullptr;

	return &keyframes[index];
}

void Animation::AddKeyframe(const Keyframe & keyframe)
{
	keyframes.emplace_back(keyframe);
}

void Animation::AddKeyframe(const Vector2 & offset, const Vector2 & size, const float & time)
{
	keyframes.emplace_back(offset, size, time);
}
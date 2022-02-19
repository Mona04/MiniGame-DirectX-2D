#pragma once
#include "ISubsystem.h"

class ResourceManager : public ISubsystem
{
public:
	ResourceManager(class Context* context);
	~ResourceManager();

	const bool Initialize() override;

	class ImageImporter* GetImageImporter() { return imageImporter; }

private:
	class ImageImporter* imageImporter;
};
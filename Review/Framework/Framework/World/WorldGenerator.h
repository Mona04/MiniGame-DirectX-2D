#pragma once

class WorldGenerator
{
public:
	WorldGenerator(class Context* context);
	~WorldGenerator();

	void CreateTown();

private:
	Context* context;
	SceneManager* sceneManager;

};
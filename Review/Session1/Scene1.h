#pragma once
#include "Framework/Scene/Scene.h"

class Scene1 : public Scene
{
public:
	Scene1(class Context* context);
	~Scene1();

	void Create();
	void Update();

private:
	class Graphics* graphics;
	class Input* input;
	class Timer* timer;
	class AudioSource* bgm;
};
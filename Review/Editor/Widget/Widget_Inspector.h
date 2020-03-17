#pragma once
#include "IWidget.h"

class Widget_Inspector final : public IWidget
{
public:
	Widget_Inspector(class Context* context);
	~Widget_Inspector();

	Widget_Inspector(const Widget_Inspector&) = delete;
	Widget_Inspector& operator=(const Widget_Inspector&) = delete;

	void Render() override;
	
private:
	void ShowRenderer(class Renderer* renderer);
	void ShowScene(class Scene* scene);
	void ShowActor(class Actor* actor);

	void ShowTransform(class Transform* transform);
	void ShowRenderable(class Renderable* renderable);
	void ShowAnimator(class std::vector<Animator*> animator, class Actor* actor);
	void ShowRigidBody(class RigidBody* rigidBody);
	void ShowScripter(class Scripter* scripter, class Actor* actor);
	void ShowController(class Controller* controller);

	void ShowMaterialInRenderable(class Material* material);
	void ShowRenderableTextureSlot(class Renderable* renderable, const class Texture* texture, const char* name, const TextureType& type);

private:
	std::vector<std::string> stringsForSamplerCombobox;
	std::vector<std::string> stringsForRigidBodyType;
};
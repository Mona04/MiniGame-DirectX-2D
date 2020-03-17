#pragma once
#include "stdafx.h"

class EditorHelper final
{
public:
	static inline ImVec2 ToImVec(const Vector2& vec) { return ImVec2(vec.x, vec.y); }
	static inline ImVec4 ToImVec(const Vector4& vec) { return ImVec4(vec.x, vec.y, vec.z, vec.w); }

	static inline Vector2 ToD3DVec2(const ImVec2& vec) { return Vector2(vec.x, vec.y); }
	static inline Vector3 ToD3DVec3(const ImVec4& vec) { return Vector3(vec.x, vec.y, vec.z); }
	static inline Vector4 ToD3DVec4(const ImVec4& vec) { return Vector4(vec.x, vec.y, vec.z, vec.w); }


public:
	static EditorHelper* Get() { static EditorHelper a; return &a; }

	class Scene* GetSelectedScene() { return scene; }
	void SelectScene(class Scene* var) { scene = var; }

	class Actor* GetSelectedActor() { return actor; }
	void SelectActor(class Actor* var) { actor = var; }

	class IUIComponent* GetSelectedUIComponent() { return uiComponent; }
	void SelectUIComponent(class IUIComponent* var) { uiComponent = var; }

private:
	EditorHelper(): actor(nullptr), scene(nullptr), uiComponent(nullptr) {}
	~EditorHelper() = default;

	class Scene* scene = nullptr;
	class Actor* actor = nullptr;
	class IUIComponent* uiComponent;
};
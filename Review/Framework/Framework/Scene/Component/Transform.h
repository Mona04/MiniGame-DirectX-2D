#pragma once
#include "IComponent.h"

class Transform final : public IComponent
{
public:
	Transform(class Context* context);
	~Transform() = default;

	void Update() override;
	void Render() override;

	//=============================================
	//Local
	const Vector3& GetLocalScale() const { return localScale; }
	const Quaternion& GetLocalRotation() const { return localRotation; }
	const Vector3& GetLocalPosition() const { return localPosition; }
	const Matrix& GetLocalMatrix() const { return local; }

	void SetLocalScale(const Vector3& vec);
	void SetLocalRotation(const Quaternion& vec);
	void SetLocalPosition(const Vector3& vec);
	//=============================================

	//=============================================
	//World
	const Vector3 GetScale() const;
	const Quaternion GetRotation() const;
	const Vector3 GetPosition() const;
	const Matrix& GetWorldMatrix() const { return world; }

	void SetScale(const Vector3& vec);
	void SetRotation(const Quaternion& quart);
	void SetPosition(const Vector3& vec);
	//=============================================

	//=============================================
	//Transform
	Transform* GetRoot() { return HasParent() ? GetParent()->GetRoot() : this; }
	Transform* GetParent() const { return parent; }
	const std::vector<Transform*>& GetChilds() const { return childs; }
	const uint GetChildCount() const { return childs.size(); }

	void SetParent(Transform* newParent);
	void AddChild(Transform* child);

	const bool HasParent() const { return parent ? true : false; }
	const bool HasChilds() const { return !childs.empty(); }
	//=============================================

	void Translate(const Vector3& var) { SetPosition(GetPosition() + var); }
	void ScaleTranslate(const Vector3& var) { SetScale(GetScale() + var); }

	void UpdateTransform();
	void UpdateBuffer();
	
	ConstantBuffer* GetTransformBuffer() { return transformBuffer; }

private:
	ConstantBuffer* transformBuffer;

	Vector3 localScale;
	Quaternion localRotation;
	Vector3 localPosition;

	Matrix local;
	Matrix world;

	Transform* parent;
	std::vector<Transform*> childs;
};
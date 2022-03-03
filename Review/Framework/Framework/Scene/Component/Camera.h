#pragma once
#include "IComponent.h"

class Camera : public IComponent
{
public:
	Camera(class Context* context);
	~Camera();
	
	virtual void Update();
	virtual void Render() {};

	const Matrix& GetViewMatrix() const { return view; }
	const Matrix& GetProjectionMatrix() const { return proj; }
	const Vector3& GetPosition() const { return position; }

	const float& GetNearPlane() const { return nearPlane; }
	const float& GetFarPlane() const { return farPlane; }

	void SetNearPlane(const float& nearPlane) { this->nearPlane = nearPlane; }
	void SetFarPlane(const float& farPlane) { this->farPlane = farPlane; }

	Vector3 GetWorldRay(const Vector2& in);

	ConstantBuffer* GetCameraBuffer() { return cameraBuffer; }
	const Vector2 GetResolution() { return resolution; }
	const float& GetMagFactor() { return mag_factor; }

	void SetTransform(class Transform* transform) { this->transform = transform; if(this->transform) this->owner = transform->GetOwner(); }
	Transform* GetTransform() { return transform; }

	void SetFieldData(Data_Field* data) { this->fieldData = data; }

private:
	void RestrictCameraPosition();
	void UpdateMatrix();
	void UpdateBuffer();

private:
	class Renderer* renderer;
	class Input* input;
	class Timer* timer;

	class ConstantBuffer* cameraBuffer;
	Vector2 resolution;
	Vector2 limitMax;
	Vector2 limitMin;

	class Transform* transform;
	class Data_Field* fieldData;


	Matrix view;
	Matrix proj;

	Vector3 position;
	float nearPlane;
	float farPlane;

	float mag_factor;   // screen magnificant
};
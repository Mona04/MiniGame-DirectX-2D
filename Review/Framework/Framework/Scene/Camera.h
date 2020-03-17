#pragma once

class Camera final
{
public:
	Camera(class Context* context);
	~Camera();

	const Matrix& GetViewMatrix() const { return view; }
	const Matrix& GetProjectionMatrix() const { return proj; }
	const Vector3& GetPosition() const { return position; }

	const float& GetNearPlane() const { return nearPlane; }
	const float& GetFarPlane() const { return farPlane; }

	void SetNearPlane(const float& nearPlane) { this->nearPlane = nearPlane; }
	void SetFarPlane(const float& farPlane) { this->farPlane = farPlane; }

	const Vector3 GetWorldRay() { return worldRay; }

	ConstantBuffer* GetCameraBuffer() { return cameraBuffer; }
	const Vector2 GetOffset() { return offset * mag_factor; }
	const Vector2& GetMagResolution() { return mag_resolution; }
	const float& GetMagFactor() { return mag_factor; }

	void SetTransform(class Transform* transform) { this->transform = transform; }
	void SetFieldData(Data_Field* data) { this->fieldData = data; }

	void Update();
	void UpdateBuffer();
	void UpdateWorldRay();

private:
	void RestrictCameraPosition();
	void UpdateMatrix();

private:
	class Context* context;
	class Renderer* renderer;
	class Input* input;

	class ConstantBuffer* cameraBuffer;
	Vector2 mag_resolution;
	Vector2 resolution;
	Vector2 offset;
	Vector2 limitMax;
	Vector2 limitMin;

	class Transform* transform;
	class Data_Field* fieldData;


	Matrix view;
	Matrix proj;

	Vector3 position;
	float nearPlane;
	float farPlane;

	float mag_factor = 1.1f;

	Vector3 worldRay;
};
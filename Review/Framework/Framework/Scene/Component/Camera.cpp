#include "Framework.h"
#include "Camera.h"

Camera::Camera(Context * context)
	: IComponent(context)
	, transform(nullptr)
	, position(0, 0, 0)
	, nearPlane(1.0f)
	, farPlane(500.0f)
	, mag_factor(1.15) // 1.15
	, fieldData(nullptr)
{
	IComponent::type = ComponentType::Camera;

	input = context->GetSubsystem<Input>();
	renderer = context->GetSubsystem<Renderer>();
	timer = context->GetSubsystem<Timer>();
	resolution = renderer->GetResolution();

	view = Matrix::Identity;
	proj = Matrix::Identity;
	cameraBuffer = new ConstantBuffer(context);
	cameraBuffer->Create<CameraData>();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (transform) {
		position = Math::Lerp(timer->GetDeltaTimeSec() * 5.f, position, transform->GetPosition());
		position.z = -100;  // 가장 안쪽이 마이너스니까
	}
	
	resolution = renderer->GetResolution();
	RestrictCameraPosition();

	UpdateMatrix();
	UpdateBuffer();  
}

void Camera::UpdateBuffer()
{
	auto data = cameraBuffer->Map<CameraData>();
	{
		data->view = view;
		data->proj = proj;
		data->cameraPos = position;
		data->camera_near = nearPlane;
		data->camera_far = farPlane;
	}
	cameraBuffer->Unmap();
}

void Camera::RestrictCameraPosition()
{
	if (fieldData)
	{
		limitMax = Vector2(+fieldData->_width / 2 * BLOCK_SIZE, +fieldData->_height / 2 * BLOCK_SIZE);
		limitMin = Vector2(-fieldData->_width / 2 * BLOCK_SIZE, -fieldData->_height / 2 * BLOCK_SIZE);
		if (position.y < limitMin.y + resolution.y / 2.0f)
			position.y = limitMin.y + resolution.y / 2.0f;
		else if (position.y > limitMax.y - resolution.y / 2.0f + 2 * BLOCK_SIZE)
			position.y = limitMax.y - resolution.y / 2.0f + 2*BLOCK_SIZE;
		if (position.x < limitMin.x + resolution.x / 2.0f - BLOCK_SIZE)
			position.x = limitMin.x + resolution.x / 2.0f - BLOCK_SIZE;
		else if (position.x > limitMax.x - resolution.x / 2.0f)
			position.x = limitMax.x - resolution.x / 2.0f;
	}
}

void Camera::UpdateMatrix()
{
	view = Matrix::LookAtLH(position, (position + Vector3(0, 0, 1)), Vector3(0, 1, 0));
	proj = Matrix::OrthoLH(resolution.x / mag_factor, resolution.y / mag_factor, nearPlane, farPlane);
}

Vector3 Camera::GetWorldRay(const Vector2& in)
{
	Matrix unViewProj;
	unViewProj = (view * proj).Inverse();

	return Vector3::TransformCoord(in, unViewProj);
}
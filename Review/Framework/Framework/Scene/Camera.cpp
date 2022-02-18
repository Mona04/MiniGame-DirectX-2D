#include "Framework.h"
#include "Camera.h"

Camera::Camera(Context * context)
	: context(context)
	, transform(nullptr)
	, position(0, 0, 0)
	, nearPlane(1.0f)
	, farPlane(3.0f)
	, worldRay(0, 0, 0)
	, fieldData(nullptr)
{
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
		//position = transform->GetPosition();
	}
	
	resolution = renderer->GetResolution();
	RestrictCameraPosition();

	UpdateMatrix();
	UpdateBuffer();  
	UpdateWorldRay();
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

void Camera::UpdateWorldRay()
{
	Vector2 pos_window = context->GetSubsystem<Input>()->GetMousePosition() * mag_factor;

	if (pos_window.x > resolution.x / 2 && pos_window.y > resolution.y / 2)
		int a = 1;

	Vector3 position_clip;
	position_clip.x = + 2.0f * pos_window.x / resolution.x - 1.0f;
	position_clip.y = - 2.0f * pos_window.y / resolution.y + 1.0f;
	position_clip.z = 0.0f;

	Matrix unViewProj, unTmp1;
	unViewProj = (view * proj).Inverse();
	unTmp1 = proj.Inverse();

	worldRay = Vector3::TransformCoord(position_clip, unViewProj);
	worldRay.Normalize();
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

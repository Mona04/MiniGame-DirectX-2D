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
	mag_resolution = renderer->GetResolution();

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
	if(transform)
		position = transform->GetPosition();
	
	RestrictCameraPosition();

	resolution = renderer->GetResolution();
	mag_resolution = renderer->GetResolution() / mag_factor;

	UpdateMatrix();
	UpdateBuffer();
	UpdateWorldRay();
}

void Camera::UpdateBuffer()
{
	//view.Transpose();
	//proj.Transpose();
	auto data = cameraBuffer->Map<CameraData>();
	{
		data->view = view;
		data->proj = proj;
		//MatrixTranspose(&data->view, &view);
		//MatrixTranspose(&data->proj, &proj);
		data->cameraPos = position;
		data->camera_near = nearPlane;
		data->camera_far = farPlane;
	}
	cameraBuffer->Unmap();
}

void Camera::UpdateWorldRay()
{
	Vector2 pos_window = context->GetSubsystem<Input>()->GetMousePosition();

	if (pos_window.x > mag_resolution.x / 2 && pos_window.y > mag_resolution.y / 2)
		int a = 1;

	Vector3 position_clip;
	position_clip.x = + 2.0f * pos_window.x / mag_resolution.x - 1.0f;
	position_clip.y = - 2.0f * pos_window.y / mag_resolution.y + 1.0f;
	position_clip.z = 0.0f;

	Matrix unViewProj, unTmp1;
	unViewProj = (view * proj).Inverse();
	unTmp1 = proj.Inverse();
	//MatrixInverse(&unViewProj, nullptr, &(view * proj));
	//MatrixInverse(&unTmp1, nullptr, &(proj));

	worldRay = Vector3::TransformCoord(position_clip, unViewProj);
	worldRay.Normalize();
	//D3DXVec3TransformCoord(&worldRay, &position_clip, &unViewProj);
	//D3DXVec3Normalize(&worldRay, &worldRay);
}

void Camera::RestrictCameraPosition()
{
	if (fieldData)
	{
		offset = Vector2(0.0f, 0.0f);
		limitMax = Vector2(+fieldData->_width / 2 * BLOCK_SIZE, +fieldData->_height / 2 * BLOCK_SIZE);
		limitMin = Vector2(-fieldData->_width / 2 * BLOCK_SIZE, -fieldData->_height / 2 * BLOCK_SIZE);
		if (position.y < limitMin.y + mag_resolution.y / 2.0f)
		{
			offset.y = limitMin.y + mag_resolution.y / 2.0f - position.y;
			position.y = limitMin.y + mag_resolution.y / 2.0f;
		}
		else if (position.y > limitMax.y - mag_resolution.y / 2.0f + 2 * BLOCK_SIZE)
		{
			offset.y = limitMax.y - mag_resolution.y / 2.0f + 2* BLOCK_SIZE - position.y;
			position.y = limitMax.y - mag_resolution.y / 2.0f + 2*BLOCK_SIZE;
		}
		if (position.x < limitMin.x + mag_resolution.x / 2.0f - 2*BLOCK_SIZE)
		{
			offset.x = limitMin.x + mag_resolution.x / 2.0f - 2*BLOCK_SIZE - position.x;
			position.x = limitMin.x + mag_resolution.x / 2.0f - 2 * BLOCK_SIZE;
		}
		else if (position.x > limitMax.x - mag_resolution.x / 2.0f + 2*BLOCK_SIZE)
		{
			offset.x = limitMax.x - mag_resolution.x / 2.0f + 2*BLOCK_SIZE - position.x;
			position.x = limitMax.x - mag_resolution.x / 2.0f + 2*BLOCK_SIZE;
		}
		offset.x /= mag_factor;
	}
}

void Camera::UpdateMatrix()
{
	view = Matrix::LookAtLH(position, (position + Vector3(0, 0, 1)), Vector3(0, 1, 0));
	proj = Matrix::OrthoLH(mag_resolution.x / mag_factor, mag_resolution.y / mag_factor, nearPlane, farPlane);
	//MatrixLookAtLH( &view, &position, &(position + Vector3(0, 0, 1)), &Vector3(0, 1, 0));
	//MatrixOrthoLH( &proj, mag_resolution.x / mag_factor, mag_resolution.y / mag_factor, nearPlane, farPlane );
}

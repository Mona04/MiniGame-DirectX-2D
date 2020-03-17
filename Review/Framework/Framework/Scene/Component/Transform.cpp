#include "Framework.h"
#include "Transform.h"

Transform::Transform(Context * context)
	: IComponent(context)
	, transformBuffer(nullptr)
	, localScale(1, 1, 1)
	, localRotation(Math::EulerToQuaternion(Vector3(0.0f, 0.0f, 0.0f)))
	, localPosition(0, 0, 0)
	, parent(nullptr)
{
	local = Matrix::Identity;
	world = Matrix::Identity;
	//MatrixIdentity(&local);
	//MatrixIdentity(&world);

	IComponent::type = ComponentType::Transform;

	transformBuffer = new ConstantBuffer(context);
	transformBuffer->Create<TransformData>();
	UpdateBuffer();
}

void Transform::Update()
{
	UpdateBuffer();
}

void Transform::Render()
{
	transformBuffer->BindPipeline(ShaderStage::VS, 2);
}

void Transform::SetLocalScale(const Vector3 & vec)
{
	if (localScale == vec)
		return;

	localScale = vec;
	UpdateTransform();
}

void Transform::SetLocalRotation(const Quaternion & vec)
{
	if (localRotation == vec)
		return;

	localRotation = vec;
	UpdateTransform();
}

void Transform::SetLocalPosition(const Vector3 & vec)
{
	if (localPosition == vec)
		return;

	localPosition = vec;
	UpdateTransform();
}

const Vector3 Transform::GetScale() const
{
	return Math::MatrixToScale(world);
}

const Quaternion Transform::GetRotation() const 
{
	return Math::MatrixToQuaternion(world);
}

const Vector3 Transform::GetPosition() const 
{
	return Vector3(world._41, world._42, world._43);
}

void Transform::SetScale(const Vector3 & vec)
{
	if (GetScale() == vec)
		return;

	if (HasParent())
	{
		Vector3 parentScale = parent->GetScale();
		Vector3 scale;
		scale.x = vec.x / parentScale.x;
		scale.y = vec.y / parentScale.y;
		scale.z = vec.z / parentScale.z;

		SetLocalScale(vec);
	}
	else
		SetLocalScale(vec);
}

void Transform::SetRotation(const Quaternion & vec)
{

	if (GetRotation() == vec)
		return;

	if (HasParent())
	{
		Quaternion var = parent->GetRotation();
		var = Quaternion::QuaternionFromInverse(var);
		var = var * vec;
		var.Normalize();
		//QuaternionInverse(&var, &var);
		//QuaternionMultiply(&var, &var, &vec);
		//QuaternionNormalize(&var, &var);

		SetLocalRotation(var);
	}
	else
		SetLocalRotation(vec);
}

void Transform::SetPosition(const Vector3 & vec)
{
	if (GetPosition() == vec)
		return;

	if (HasParent())
	{
		Matrix inv = parent->GetWorldMatrix();
		inv = inv.Inverse();
		//MatrixInverse(&inv, nullptr, &inv);

		Vector3 position;
		position = Vector3::TransformCoord(vec, inv);
		//D3DXVec3TransformCoord(&position, &vec, &inv);

		SetLocalPosition(position);
	}
	else
		SetLocalPosition(vec);
}

void Transform::SetParent(Transform * newParent)
{
	if (!newParent)
		return;

	if (newParent == this)
		return;

	parent = newParent;
	parent->AddChild(this);
}

void Transform::AddChild(Transform * child)
{
	if (!child)
		return;

	if (child == this)
		return;

	child->SetParent(this);
	childs.emplace_back(child);
}

void Transform::UpdateTransform()
{
	Matrix S, R, T;
	S = Matrix::Scaling(localScale.x, localScale.y, localScale.z);
	R = Matrix::RotationQuaternion(localRotation);
	T = Matrix::Translation(localPosition.x, localPosition.y, localPosition.z);
	//MatrixScaling(&S, localScale.x, localScale.y, localScale.z);
	//MatrixRotationQuaternion(&R, &localRotation);
	//MatrixTranslation(&T, localPosition.x, localPosition.y, localPosition.z);

	local = S * R * T;

	if (HasParent())
		world = local * parent->GetWorldMatrix();
	else
		world = local;

	if (world._22 < 0)
		int a = 1;

	UpdateBuffer();

	for (const auto& child : childs)
		child->UpdateTransform();
}

void Transform::UpdateBuffer()
{
	auto data = transformBuffer->Map<TransformData>();
	{
		data->World = GetWorldMatrix();
		//data->World = GetWorldMatrix().Transpose();
		//MatrixTranspose(&data->World, &GetWorldMatrix());
	}
	transformBuffer->Unmap();
}

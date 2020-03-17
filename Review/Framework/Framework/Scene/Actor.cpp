#include "Framework.h"
#include "Actor.h"

Actor::Actor(Context * context)
    : context(context)
	, bActive(true)
	, timeLimit(-1.0f)
	, timeFlowed(0.0f)
	, name("")
{
	timer = context->GetSubsystem<Timer>();
}

Actor::~Actor()
{
	Clear();
}

void Actor::LoadFromFile(const std::string& path)
{	
	Clear();

	DataManager* dataManager = context->GetSubsystem<DataManager>();

	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		ComponentType componentType;
		uint nComponent = stream.ReadUInt();

		for (int i = 0; i < nComponent; i++)
		{
			componentType = static_cast<ComponentType>(stream.ReadUInt());
			switch (componentType)
			{
			case ComponentType::Transform:
			{
				Transform* transform = AddComponent<Transform>();
				Vector3 pos;
				Quaternion quart;
				Vector3 scale;
				stream.Read(pos);
				stream.Read(quart);
				stream.Read(scale);
				transform->SetPosition(pos);
				transform->SetRotation(quart);
				transform->SetScale(scale);
				break;
			}
			case ComponentType::Renderable:
			{
				uint nTexture;
				TextureType textureType;
				std::string texturePath;
				std::string textureName;

				Renderable* component = AddComponent<Renderable>();
				std::string _path;
				std::string _name;
				stream.Read(_path);
				stream.Read(_name);
				component->SetMesh(_path, _name);
				stream.Read(_path);
				stream.Read(_name);
				component->SetMaterial(_path, _name);

				nTexture = stream.ReadUInt();
				for (int i = 0; i < nTexture; i++)
				{
					textureType = static_cast<TextureType>(stream.ReadUInt());
					stream.Read(texturePath);
					stream.Read(textureName);
					component->SetTexture(textureType, texturePath, textureName);
				}

				break;
			}
			case ComponentType::Animator:
			{
				Animator* component = AddComponent<Animator>();
				std::string _path;
				std::string _name;
				stream.Read(_path);
				stream.Read(_name);
				component->SetAnimation(_path, _name, GetComponent<Renderable>());
				break;
			}
			case ComponentType::RigidBody:
			{
				RigidBody* component = AddComponent<RigidBody>();
				float mass, friction;
				Vector3 maxPoint, minPoint;
				RigidBodyType type = static_cast<RigidBodyType>(stream.ReadUInt());
				stream.Read(mass);
				stream.Read(friction);
				stream.Read(maxPoint); stream.Read(minPoint);
				component->SetRigidBodyType(type);
				component->SetMass(mass);
				component->SetFriction(mass);
				component->GetBoundBox().maxPoint = maxPoint;
				component->GetBoundBox().minPoint = minPoint;
				component->SetBoundBoxAndTransform(GetComponent<Transform>());
				break;
			}
			case ComponentType::AudioResource:
			{
				AudioSource* component = AddComponent<AudioSource>();
				break;
			}
			case ComponentType::Scripter:
			{	
				Scripter* component = AddComponent<Scripter>();
				std::string path, name;
				stream.Read(path);
				stream.Read(name);
				component->SetScript(path, name, this);
				break;
			}
			case ComponentType::Controller:
			{
				Controller* component = AddComponent<Controller>();
				std::string mobName, attack1, attack2, guard, portal, dialog;
				stream.Read(mobName);
				stream.Read(attack1);
				stream.Read(attack2);
				stream.Read(guard);
				stream.Read(portal);
				stream.Read(dialog);
				component->SetActor(this);
				component->SetMobData(dataManager->GetData<Data_Mob>(mobName));
				component->SetAttack1Data(dataManager->GetData<Data_Skill>(attack1));
				component->SetAttack2Data(dataManager->GetData<Data_Skill>(attack2));
				component->SetGuardData(dataManager->GetData<Data_Skill>(guard));
				component->SetPortalData(dataManager->GetData<Data_Portal>(portal));
				component->SetDialogData(dataManager->GetData<Data_Dialog>(dialog));
				break;
			}
			}
		}
	}
	stream.Close();
}

void Actor::SaveToFile(const std::string& path)
{
	ComponentType componentType;

	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(components.size());

		for (const auto& component : components)
		{
			componentType = component->GetType();
			stream.Write(static_cast<uint>(componentType));

			switch (componentType)
			{
			case ComponentType::Transform:
			{
				Transform* component = GetComponent<Transform>();
				stream.Write(component->GetPosition());
				stream.Write(component->GetRotation());
				stream.Write(component->GetScale());
				break;
			}
			case ComponentType::Renderable:
			{
				Renderable* component = GetComponent<Renderable>();
				stream.Write(component->GetMesh()->GetResourcePath());
				stream.Write(component->GetMesh()->GetResourceName());
				stream.Write(component->GetMaterial()->GetResourcePath());
				stream.Write(component->GetMaterial()->GetResourceName());

				stream.Write(static_cast<uint>(component->GetTextures().size()));
				for (int i = 0; i < 4; i++)
				{
					if (component->HasTexture(static_cast<TextureType>(i)))
					{
						stream.Write(static_cast<uint>(i));
						stream.Write(component->GetTexture(static_cast<TextureType>(i))->GetResourcePath());
						stream.Write(component->GetTexture(static_cast<TextureType>(i))->GetResourceName());
					}
				}
				break;
			}
			case ComponentType::Animator:
			{
				Animator* component = GetComponent<Animator>();
				stream.Write(component->GetAnimation()->GetResourcePath());
				stream.Write(component->GetAnimation()->GetResourceName());
				break;
			}
			case ComponentType::RigidBody:
			{
				RigidBody* component = GetComponent<RigidBody>();
				stream.Write(static_cast<uint>(component->GetRigidBodyType()));
				stream.Write(component->GetMass());
				stream.Write(component->GetFriction());
				stream.Write(component->GetBoundBox().maxPoint);
				stream.Write(component->GetBoundBox().minPoint);
				break;
			}
			case ComponentType::AudioResource:
			{
				AudioSource* component = GetComponent<AudioSource>();
				break;
			}
			case ComponentType::Controller:
			{
				Controller* component = GetComponent<Controller>();
				stream.Write(component->GetMobData() ? component->GetMobData()->GetName() : "N\A");
				stream.Write(component->GetAttack1Data() ? component->GetAttack1Data()->GetName() : "N\A");
				stream.Write(component->GetAttack2Data() ? component->GetAttack2Data()->GetName() : "N\A");
				stream.Write(component->GetGuardData() ? component->GetGuardData()->GetName() : "N\A");
				stream.Write(component->GetPortalData() ? component->GetPortalData()->GetName() : "N\A");
				stream.Write(component->GetDialogData() ? component->GetDialogData()->GetName() : "N\A");
				break;
			}
			case ComponentType::Scripter:
				Scripter* component = GetComponent<Scripter>();
				stream.Write(component->GetScript()->GetResourcePath());
				stream.Write(component->GetScript()->GetResourceName());
				break;
			}
		}
	}
	stream.Close();
}

void Actor::Clear()
{
	for (auto component : components)
		SAFE_DELETE(component);
	components.clear();
	components.shrink_to_fit();
}

void Actor::Update()
{
	if (!bActive)
		return;

	for (auto& component : components)
		component->Update();

	if (timeLimit > 0)
	{
		timeFlowed += timer->GetDeltaTimeMs();
		if (timeFlowed >= timeLimit)
		{
			bActive = false;
			timeFlowed = 0;
			timeLimit = -1;
		}
	}
}

void Actor::Render()
{
	if (!bActive)
		return;

	for (auto& component : components)
		component->Render();
}

const bool Actor::HasComponent(const ComponentType & type)
{
	for (const auto& component : components)
	{
		if (component->GetType() == type)
			return true;
	}
	return false;
}

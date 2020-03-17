#include "Framework.h"
#include "Scene1.h"

Scene1::Scene1(Context * context)
	: Scene(context)
	, bgm(nullptr)
{
	Create();
	createFunction = std::move(std::bind(&Scene1::Create, this));
	updateFunction = std::move(std::bind(&Scene1::Update, this));
}

Scene1::~Scene1()
{
	Scene::~Scene();

	SAFE_DELETE(bgm);
}

void Scene1::Create()
{
	graphics = context->GetSubsystem<Graphics>();
	input = context->GetSubsystem<Input>();
	timer = context->GetSubsystem<Timer>();

	CreateActor();
	actors.back()->SetName("Player");
	CreateActor();
	actors.back()->SetName("Monster");

	{
		auto temp = FindActor("Player");
		temp->SetActive(true);
		auto transform = temp->AddComponent<Transform>();
		auto renderable = temp->AddComponent<Renderable>();
		auto animator = temp->AddComponent<Animator>();
		auto collider = temp->AddComponent<Collider>();
		transform->SetPosition({ -50, 0, 0 });
		transform->SetScale({ 100, 70, 0 });
		transform->SetCollider(collider);
		animator->SetAnimation("Idle.anim", "Idle", renderable->GetMaterial());
		animator->Play();

	}

	{
		auto temp = FindActor("Monster");
		temp->SetActive(true);
		auto transform = temp->AddComponent<Transform>();
		auto renderable = temp->AddComponent<Renderable>();
		auto animator = temp->AddComponent<Animator>();
		auto collider = temp->AddComponent<Collider>();
		transform->SetPosition({ 20, 0, 0 });
		transform->SetScale({ 100, 70, 0 });
		transform->SetCollider(collider);
		animator->SetAnimation("Idle.anim" , "Idle", renderable->GetMaterial());
		animator->Play();
	}
	//bgm = new AudioSource(context);
	//bgm->SetAudioClip("Stage1.mp3");
	//bgm->Play();
}

void Scene1::Update()
{
	auto transform = FindActor("Monster")->GetComponent<Transform>();
	D3DXVECTOR3 position = transform->GetPosition();

	if (input->KeyPress('A'))
		position.x -= 10 * timer->GetDeltaTimeSec();
	else if (input->KeyPress('D'))
		position.x += 10 * timer->GetDeltaTimeSec();
	else if (input->KeyPress('1'))
		for (auto& actor : actors)
			actor->SetActive(true);

	transform->SetPosition(position);

	for (auto& actor : actors)
	{
		auto collider = actor->GetComponent<Collider>();
		collider->SetCenter(actor->GetComponent<Transform>()->GetPosition());
		collider->SetSize({ 28, 38, 1 });
	}

	for (auto& actor1 : actors)
		for (auto& actor2 : actors)
		{
			if (actor1->GetName() == actor2->GetName())
				continue;
			auto receiver = actor1->GetComponent<Collider>();
			auto attacker = actor2->GetComponent<Collider>();
			if (receiver->AABB(attacker))
			{
				if (receiver->Event != nullptr)
					receiver->Event();
			}
		}

	///////////////////////////////////////////////////////////////////

	//if (input->KeyDown('E'))
	//    bgm->Play();
	//else if (input->KeyDown('R'))
	//    bgm->Pause();
	//else if (input->KeyDown('T'))
	//    bgm->Stop();

	//float volume = bgm->GetVolume();

	//if (input->KeyDown('Q'))
	//    volume -= 0.1f;
	//else if (input->KeyDown('W'))
	//    volume += 0.1f;

	//bgm->SetVolume(volume);

	//float pitch = bgm->GetPitch();

	//if (input->KeyDown('Q'))
	//    pitch -= 0.1f;
	//else if (input->KeyDown('W'))
	//    pitch += 0.1f;

	//bgm->SetPitch(pitch);

	//////////////////////////////////////////////////////////////////
	
	/* if (input->BtnDown(0))
	{
		auto audioSource = new AudioSource(context);
		audioSource->SetAudioClip("Shoot1.wav");
		audioSource->Play();

		audioSources.emplace_back(audioSource);
	}*/
}


#include "stdafx.h"
#include "Widget_Scene.h"

Widget_Scene::Widget_Scene(Context * context)
	: IWidget(context)
	, framePos(0.0f, 0.0f)
	, frameSize(0.0f, 0.0f)
{
	title = "Scene";
	windowFlags |=
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse;

	input = context->GetSubsystem<Input>();
	renderer = context->GetSubsystem<Renderer>();
	sceneManager = context->GetSubsystem<SceneManager>();

	Window::InputProc = [this](HWND handle, const uint& message, const WPARAM& wParam, const LPARAM& lParam)
	{
		input->SetMousePosition_Before(input->GetMousePosition());

		if (message == WM_LBUTTONDOWN || message == WM_MOUSEMOVE)
		{
			ImVec2 pos = ImGui::GetMousePos() - framePos;
			input->SetMousePosition(Vector2(pos.x, pos.y));
		}

		if (message == WM_MOUSEWHEEL)
		{
			input->SetWheelOldStatus(input->GetWheelStatus());
			input->SetWheelStatus(Vector3(0, 0, static_cast<short>(HIWORD(wParam))));
		}

		return TRUE;
	};	
}

Widget_Scene::~Widget_Scene()
{
}

void Widget_Scene::Render()
{
	ShowFrame();
	Manipulate();
	Picking();
}

void Widget_Scene::ShowFrame()
{
	framePos = ImGui::GetCursorPos() + ImGui::GetWindowPos();   // ¿Ö?
	frameSize = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();

	frameSize.x -= static_cast<int>(frameSize.x) % 2 == 0 ? 0.0f : 1.0f;
	frameSize.y -= static_cast<int>(frameSize.y) % 2 == 0 ? 0.0f : 1.0f;

	renderer->SetResolution(Vector2(static_cast<float>(frameSize.x), static_cast<float>(frameSize.y)));

	ImGui::Image(
		renderer->GetFrameResourseView(),
		frameSize,
		ImVec2(0, 0),
		ImVec2(1, 1),
		ImVec4(1, 1, 1, 1),
		ImVec4(50, 127, 166, 155)
	);
}

void Widget_Scene::Manipulate()
{
	if (!EditorHelper::Get()->GetSelectedActor())
		return;

	auto camera = renderer->GetCamera();
	auto transform = EditorHelper::Get()->GetSelectedActor()->GetComponent<Transform>();

	if (!camera || !transform)
		return;

	static ImGuizmo::OPERATION operation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mode(ImGuizmo::WORLD);

	if (ImGui::IsKeyPressed(87)) //w
	{
		switch (operation)
		{
		case ImGuizmo::TRANSLATE:
			operation = ImGuizmo::SCALE; break;
		case ImGuizmo::SCALE:
			operation = ImGuizmo::ROTATE; break;
		case ImGuizmo::ROTATE:
			operation = ImGuizmo::TRANSLATE; break;
		}		
	}


	D3DXMATRIX matrix;
	matrix = transform->GetWorldMatrix();

	ImGuizmo::SetOrthographic(true);
	ImGuizmo::SetDrawlist();
	ImGuizmo::SetRect(framePos.x, framePos.y, frameSize.x, frameSize.y);
	ImGuizmo::Manipulate
	(
		camera->GetViewMatrix(),
		camera->GetProjectionMatrix(),
		operation,
		mode,
		matrix
	);

	Vector3 scale, trans;
	D3DXQUATERNION rotate;
	D3DXMatrixDecompose(&scale, &rotate, &trans, &matrix);
	transform->SetPosition(trans);
	//transform->SetRotation(rotate);
	//transform->SetScale(scale);
}

void Widget_Scene::Picking()
{
	Camera* camera = renderer->GetCamera();	
	Scene* scene = sceneManager->GetCurrentScene();
	if (!camera || !scene || !ImGui::IsWindowHovered() || !ImGui::IsMouseClicked(0))
		return;

	//Vector2 mousePos = EditorHelper::ToD3DVec2(ImGui::GetMousePos() - framePos);
	Vector3 worldPos = camera->GetWorldRay();

	std::vector<Actor*> actors = sceneManager->GetCurrentScene()->GetActors();
	for (auto& actor : actors) {
		Renderable* renderable = actor->GetComponent<Renderable>();
		if(!renderable)
			continue;
	//	BoundBox boundBox = actor->GetComponent<RigidBody>()->GetBoundBox();
	//
	//	if (Intersection::Inside == boundBox.IsInside(worldPos))
	//	{
	//		EditorHelper::Get()->SelectActor(actor);
	//		return;
	//	}
	}
}

void Widget_Scene::DragAndDropEven()
{
}

#include "Framework.h"
#include "Renderer.h"
#include "Pipeline.h"
#include "CommandList.h"
#include "Framework/Core/Engine.h"
#include "Framework/Core/D3D11/BasicData/Geometry.h"

Renderer::Renderer(Context * context)
	: ISubsystem(context)
	, resolution(0.0f, 0.0f)
	, rendererFlags(0)
	, postprocessFlags(0)
	, bloomIntensity(1.0f)
	, blurSigma(2.0f)
	, blurStride(1.0f)
	, forActorFrame(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();
	sceneManager = context->GetSubsystem<SceneManager>();
	dataManager = context->GetSubsystem<DataManager>();

	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));
	EventSystem::Get()->Subscribe(EventType::Render, EVENT_HANDLER(Render));
}

Renderer::~Renderer()
{
	SAFE_DELETE(forActorFrame);
}

const bool Renderer::Initialize()
{
	commandList = std::make_shared<CommandList>(context);

	editorCamera = std::make_shared<Actor>(context);
	editorCamera->AddComponent<Transform>(); 
	editorCamera->AddComponent<Camera>()->SetTransform(editorCamera->GetComponent<Transform>());
	editorCamera->AddComponent<Scripter>()->SetScript("EditorCamera_Actor.as", "EditorCamera_Actor.as", editorCamera.get());
	editorCamera->Update();

	CreateShaders();
	CreateDefaultBuffers();
	CreateStates();

	CreateActorFrame();

	UpdateDefaultBuffer();

	return true;
}

ID3D11ShaderResourceView * Renderer::GetFrameResourseView()
{
	return renderTextures[RenderTextureType::FULL_HDR_TARGET1]->GetShaderResourceView();

	//if (IsEnabledPostProcessFlags(PostprocessFlag::None))
	//	return renderTextures[RenderTextureType::GBUFFER_ALBEDO]->GetShaderResourceView();
	//if (IsEnabledPostProcessFlags(PostprocessFlag::Blending))
	//	return renderTextures[RenderTextureType::FULL_HDR_TARGET1]->GetShaderResourceView();
	//else if (IsEnabledPostProcessFlags(PostprocessFlag::Upsample2))
	//	return renderTextures[RenderTextureType::SPARE_FULL]->GetShaderResourceView();
	//else if (IsEnabledPostProcessFlags(PostprocessFlag::Upsample1))
	//	return renderTextures[RenderTextureType::SPARE_HALf]->GetShaderResourceView();
	//else if (IsEnabledPostProcessFlags(PostprocessFlag::GaussianBlur))
	//	return renderTextures[RenderTextureType::BLUR_QUARTER1]->GetShaderResourceView();
	//else if (IsEnabledPostProcessFlags(PostprocessFlag::Bright))
	//	return renderTextures[RenderTextureType::BLUR_QUARTER2]->GetShaderResourceView();
	//else if (IsEnabledPostProcessFlags(PostprocessFlag::DownSample))
	//	return renderTextures[RenderTextureType::BLUR_QUARTER1]->GetShaderResourceView();
	//return renderTextures[RenderTextureType::FULL_HDR_TARGET1]->GetShaderResourceView();
	//renderTextures[RenderTextureType::GBUFFER_ALBEDO];
}

Camera * Renderer::GetCamera() const
{
	if (ProgressReport::Get()->GetIsLoadingOfReport(ProgressReport::Scene))
		return editorCamera->GetComponent<Camera>();
	if(context->GetEngine()->IsOnEngineFlags(ENGINEFLAGS_EDITOR) == false)
		return sceneCamera ? sceneCamera : editorCamera->GetComponent<Camera>();
	if (context->GetEngine()->IsOnEngineFlags(ENGINEFLAGS_PLAY) == false)
		return editorCamera->GetComponent<Camera>();
	return sceneCamera ? sceneCamera : editorCamera->GetComponent<Camera>();
}

void Renderer::SetResolution(const Vector2 & var)
{
	if (var == resolution)
		return;

	resolution = var; 
	CreateRenderTarget(static_cast<uint>(resolution.x), static_cast<uint>(resolution.y));
	CreateScreenBuffers(resolution.x, resolution.y);
	UpdateDefaultBuffer();
	UpdatePostProcessBuffer(resolution.x, resolution.y);
}

void Renderer::AcquireScene(Scene * scene)
{
	ClearRenderables();
	
	currentScene = scene;
	sceneCamera = scene->GetCamera();

	std::vector<Actor*> actors = scene->GetActors();

	for (auto& actor : actors)
	{
		if (actor->GetComponent<Renderable>())
			actorsList[RenderableType::Opaque].emplace_back(actor);
		else
			actorsList[RenderableType::Transparent].emplace_back(actor);
	}
}

// Monster 등 기존에서 추가
void Renderer::UpdateActorList(Actor * actor)
{
	std::string name = actor->GetName();

	for (auto& pair : actorsList) {
		for (auto i = pair.second.begin(); i != pair.second.end(); i++) {
			if ((*i)->GetName() == name) {
				Actor* actor = *i;
				pair.second.erase(i);
				pair.second.shrink_to_fit();
				if ((actor)->GetComponent<Renderable>())
					actorsList[RenderableType::Opaque].emplace_back(actor);
				else
					actorsList[RenderableType::Transparent].emplace_back(actor);
				return;
			}
		}
	}

	if (actor->GetComponent<Renderable>())
		actorsList[RenderableType::Opaque].emplace_back(actor);
	else
		actorsList[RenderableType::Transparent].emplace_back(actor);
	return;
}

void Renderer::ClearRenderables()
{
	sceneCamera = nullptr;
	actorsList.clear();
}

void Renderer::AcquireUI(UI* ui)
{
	UIComponentList.clear();
	UIComponentList = ui->GetComponents();
}

void Renderer::AcquirePreUI(UI* ui)
{
	preUIComponentList.clear();
	preUIComponentList = ui->GetComponents();
}

void Renderer::UpdateDefaultBuffer()
{
	{
		auto data = transformDefaultBuffer->Map<TransformData>();
		{
			data->World = Matrix::Identity;
			data->WVP_Current = Matrix::Identity;
			data->WVP_Previous = Matrix::Identity;
			//MatrixIdentity(&data->World);
			//MatrixIdentity(&data->WVP_Current);
			//MatrixIdentity(&data->WVP_Previous);
		}
		transformDefaultBuffer->Unmap();
	}

	{
		auto data = materialDefaultBuffer->Map<MaterialData>();
		{
			data->Material_albedo = Color4(1.0f, 1.0f, 1.0f, 1.0f);
			data->Material_normal_strength = 0.0f;
			data->Material_offset = Vector2(0.0f, 0.0f);
			data->Material_tiling = Vector2(0.0f, 0.0f);
		}
		materialDefaultBuffer->Unmap();
	}

	{
		auto data = animationDefaultBuffer->Map<AnimationData>();
		{
			data->SpriteOffset = Vector2(0.0f, 0.0f);
			data->SpriteSize = Vector2(1.0f, 1.0f);
			data->TextureSize = Vector2(1.0f, 1.0f);
		}
		animationDefaultBuffer->Unmap();
	}

	{
		auto data = cameraDefaultBuffer->Map<CameraData>();
		{
			data->cameraPos = Vector3(0.0f, 0.0f, 0.0f);
			data->camera_far = 3.0f;
			data->camera_near = 1.0f;
			data->view = Matrix::LookAtLH(data->cameraPos, (data->cameraPos + Vector3(0, 0, 1)), Vector3(0, 1, 0));
			data->proj = Matrix::OrthoLH(resolution.x, resolution.y, data->camera_near, data->camera_far);
			data->view.Transpose();
			data->proj.Transpose();
			///MatrixLookAtLH(&data->view, &data->cameraPos, &(data->cameraPos + Vector3(0, 0, 1)), &Vector3(0, 1, 0));
			///MatrixOrthoLH(&data->proj, resolution.x, resolution.y, data->camera_near, data->camera_far);
			///MatrixTranspose(&data->view, &data->view);
			///MatrixTranspose(&data->proj, &data->proj);
		}
		cameraDefaultBuffer->Unmap();
	}
}

void Renderer::UpdatePostProcessBuffer(const float& width, const float& height, const float& intensity, const float& sigma, const Vector2& dir)
{
	auto data = postProcessBuffer->Map<PostProcessData>();
	{
		if (!data)
		{
			LOG_ERROR("Invalid PostProcessBuffer");
			return;
		}

		data->bloomIntensity = intensity;
		data->blurDir = dir;
		data->blurSigma = sigma;
		data->resolution = Vector2(width, height);
	}
	postProcessBuffer->Unmap();
}

void Renderer::Update()
{	
	editorCamera->Update();

	Camera* camera = GetCamera();
	camera->Update();
}

void Renderer::Render()
{	
	UpdatePostProcessBuffer(resolution.x, resolution.y);

	if(ProgressReport::Get()->GetIsLoadingOfReport(ProgressReport::Scene))
		PassPreUI();
	else {
		PassMain();
		PassUI();
	}
}

void Renderer::CreateActorFrame()
{
	forActorFrame = new Actor(context);
	forActorFrame->SetActive(true); // 시발 시발 시발
	auto component = forActorFrame->AddComponent<Renderable>();
	component->SetMesh("QUAD.mesh");
	component->SetMaterial("Dirt.material");
	auto transform =forActorFrame->AddComponent<Transform>();
	transform->SetPosition(Vector3(0, 0, 0));
	transform->SetScale(Vector3(30, 30, 0));

	frameInstanceBuffer = std::make_shared<VertexBuffer>(context);
	frameGeometry = std::make_shared<Geometry<VertexPositionScaleSprite>>();
	frameGeometry->AddVertex(VertexPositionScaleSprite(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector2(0, 0)));

	frameInstanceBuffer->Create<VertexPositionScaleSprite>(frameGeometry->GetVertices(), D3D11_USAGE_DYNAMIC);
}


void Renderer::CreateDefaultBuffers()
{
	for(int instanced = 0 ; instanced < 2; instanced++)
		for (int animated = 0; animated < 2; animated++)
			for(int albedo = 0 ; albedo < 2 ; albedo++)
				for(int normal = 0 ; normal < 2 ; normal++)
					for(int emissive = 0 ; emissive < 2; emissive++)
					{
						auto buffer = std::make_shared<ConstantBuffer>(context);
						buffer->Create<RenderOptionData>();
						auto data = buffer->Map<RenderOptionData>();
						data->isInstanced = instanced;  data->isAnimated = animated;
						data->hasAlbedoTexture = albedo; data->hasNormalTexture = normal; 
						data->hasEmissiveTexture = emissive;
						buffer->Unmap();
						gbufferRenderOptionBuffers[static_cast<GBufferRenderOption>(16 * instanced + 8 * animated + 4 * albedo + 2 * normal + emissive)] = buffer;
					}

	postProcessBuffer = std::make_shared<ConstantBuffer>(context);
	postProcessBuffer->Create<PostProcessData>();

	transformDefaultBuffer = std::make_shared<ConstantBuffer>(context);
	transformDefaultBuffer->Create<TransformData>();

	animationDefaultBuffer = std::make_shared<ConstantBuffer>(context);
	animationDefaultBuffer->Create<AnimationData>();

	materialDefaultBuffer = std::make_shared<ConstantBuffer>(context);
	materialDefaultBuffer->Create<MaterialData>();

	cameraDefaultBuffer = std::make_shared<ConstantBuffer>(context);
	cameraDefaultBuffer->Create<CameraData>();
}

void Renderer::CreateScreenBuffers(const float& width, const float& height)
{
	Geometry<VertexTextureNormal> geometry;
	GeometryGenerator::CreateScreenQuad(&geometry);
	screenIndexBuffer = std::make_shared<IndexBuffer>(context);
	screenIndexBuffer->Create(geometry.GetIndices());
	screenVertexBuffer = std::make_shared<VertexBuffer>(context);
	screenVertexBuffer->Create(geometry.GetVertices());
}

void Renderer::CreateShaders()
{
	std::shared_ptr<Shader> vp_gBuffer = std::make_shared<Shader>(context);
	vp_gBuffer->AddShader(ShaderStage::VS, "../../_Assets/Shader/GBuffer.hlsl");
	vp_gBuffer->AddShader(ShaderStage::PS, "../../_Assets/Shader/GBuffer.hlsl");
	shaders[ShaderType::VP_GBUFFER] = vp_gBuffer;

	std::shared_ptr<Shader> vs_postprocess = std::make_shared<Shader>(context);
	vs_postprocess->AddShader(ShaderStage::VS, "../../_Assets/Shader/Postprocess.hlsl");
	shaders[ShaderType::VS_POSTPROCESS] = vs_postprocess;

	std::shared_ptr<Shader> vp_light = std::make_shared<Shader>(context);
	vp_light->AddShader(ShaderStage::VS, "../../_Assets/Shader/Light.hlsl");
	vp_light->AddShader(ShaderStage::PS, "../../_Assets/Shader/Light.hlsl");
	shaders[ShaderType::VP_LIGHT] = vp_light;

	std::shared_ptr<Shader> ps_downsample = std::make_shared<Shader>(context);
	ps_downsample->AddDefine("PASS_DOWNSAMPLE_BOX");
	ps_downsample->AddShader(ShaderStage::PS, "../../_Assets/Shader/Postprocess.hlsl");
	shaders[ShaderType::PS_DOWN_SAMPLING] = ps_downsample;

	std::shared_ptr<Shader> ps_upsample = std::make_shared<Shader>(context);
	ps_upsample->AddDefine("PASS_UPSAMPLE_BOX");
	ps_upsample->AddShader(ShaderStage::PS, "../../_Assets/Shader/Postprocess.hlsl");
	shaders[ShaderType::PS_UP_SAMPLING] = ps_upsample;

	std::shared_ptr<Shader> ps_bright = std::make_shared<Shader>(context);
	ps_bright->AddDefine("PASS_BRIGHT");
	ps_bright->AddShader(ShaderStage::PS, "../../_Assets/Shader/Postprocess.hlsl");
	shaders[ShaderType::PS_BRIGHT] = ps_bright;

	std::shared_ptr<Shader> ps_blend = std::make_shared<Shader>(context);
	ps_blend->AddDefine("PASS_BLEND");
	ps_blend->AddShader(ShaderStage::PS, "../../_Assets/Shader/Postprocess.hlsl");
	shaders[ShaderType::PS_BLEND] = ps_blend;

	std::shared_ptr<Shader> ps_blur_gaussian = std::make_shared<Shader>(context);
	ps_blur_gaussian->AddDefine("PASS_GAUSSIAN_BLUR");
	ps_blur_gaussian->AddShader(ShaderStage::PS, "../../_Assets/Shader/Postprocess.hlsl");
	shaders[ShaderType::PS_BLUR_GAUSSIAN] = ps_blur_gaussian;

	std::shared_ptr<Shader> vp_UI_texture = std::make_shared<Shader>(context);
	vp_UI_texture->AddDefine("PASS_TEXTURE");
	vp_UI_texture->AddShader(ShaderStage::VS, "../../_Assets/Shader/UI.hlsl");
	vp_UI_texture->AddShader(ShaderStage::PS, "../../_Assets/Shader/UI.hlsl");
	shaders[ShaderType::VP_UI_TEXTURE] = vp_UI_texture;

	std::shared_ptr<Shader> vp_UI_color = std::make_shared<Shader>(context);
	vp_UI_color->AddDefine("PASS_COLOR");
	vp_UI_color->AddShader(ShaderStage::VS, "../../_Assets/Shader/UI.hlsl");
	vp_UI_color->AddShader(ShaderStage::PS, "../../_Assets/Shader/UI.hlsl");
	shaders[ShaderType::VP_UI_COLOR] = vp_UI_color;

	inputLayout_GBuffer = std::make_shared<InputLayout>(context);
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
		for (int i = 0; i < VertexTextureNormal::count; i++)
			descs.emplace_back(VertexTextureNormal::descs[i]);
		for (int i = 0; i < VertexPositionScaleSprite::count; i++)
			descs.emplace_back(VertexPositionScaleSprite::descs[i]);

		inputLayout_GBuffer->Create(descs.data(), descs.size(), vp_gBuffer->GetVertexShader()->GetBlob());
	}

	inputLayout_UI = std::make_shared<InputLayout>(context);
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
		for (int i = 0; i < VertexTexture::count; i++)
			descs.emplace_back(VertexTexture::descs[i]);
		for (int i = 0; i < VertexPositionScaleSprite::count; i++)
			descs.emplace_back(VertexPositionScaleSprite::descs[i]);

		inputLayout_UI->Create(descs.data(), descs.size(), vp_UI_color->GetVertexShader()->GetBlob());
	}
}

void Renderer::CreateStates()
{
	samplerState_clamp_point = std::make_shared<Sampler>(context);
	samplerState_clamp_point->Create(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_CLAMP);

	samplerState_clamp_bilinear = std::make_shared<Sampler>(context);
	samplerState_clamp_bilinear->Create(D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT, D3D11_TEXTURE_ADDRESS_CLAMP);

	samplerState_wrap_bilinear = std::make_shared<Sampler>(context);
	samplerState_wrap_bilinear->Create(D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);

	samplerState_wrap_trilinear = std::make_shared<Sampler>(context);
	samplerState_wrap_trilinear->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);

	samplerState_wrap_anisotropic = std::make_shared<Sampler>(context);
	samplerState_wrap_anisotropic->Create(D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_WRAP);

	rasterizerState_solid_Back = std::make_shared<RasterizerState>(context);
	rasterizerState_solid_Back->Create(D3D11_FILL_SOLID, D3D11_CULL_BACK);

	rasterizerState_wire_Back = std::make_shared<RasterizerState>(context);
	rasterizerState_wire_Back->Create(D3D11_FILL_WIREFRAME, D3D11_CULL_BACK);

	blendState_alpha_true = std::make_shared<BlendState>(context);
	blendState_alpha_true->Create(
		true,
		D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_ONE,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_OP_ADD
	);

	depthStencilState_depth_enable = std::make_shared<DepthStencilState>(context);
	depthStencilState_depth_enable->Create(true);
}

void Renderer::CreateRenderTarget(const uint & width, const uint & height)
{
	std::shared_ptr<RenderTexture> gbuffer_albedo = std::make_shared<RenderTexture>(context);
	gbuffer_albedo->Create(width, height, false, DXGI_FORMAT_R8G8B8A8_UNORM);
	renderTextures[RenderTextureType::GBUFFER_ALBEDO] = gbuffer_albedo;

	std::shared_ptr<RenderTexture> gbuffer_normal = std::make_shared<RenderTexture>(context);
	gbuffer_normal->Create(width, height, false, DXGI_FORMAT_R16G16B16A16_FLOAT);
	renderTextures[RenderTextureType::GBUFFER_NORMAL] = gbuffer_normal;

	std::shared_ptr<RenderTexture> gbuffer_velocity = std::make_shared<RenderTexture>(context);
	gbuffer_velocity->Create(width, height, false, DXGI_FORMAT_R16G16_FLOAT);
	renderTextures[RenderTextureType::GBUFFER_VELOCITY] = gbuffer_velocity;

	std::shared_ptr<RenderTexture> gbuffer_depth = std::make_shared<RenderTexture>(context);
	gbuffer_depth->Create(width, height, true, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_D32_FLOAT);
	renderTextures[RenderTextureType::GBUFFER_DEPTH] = gbuffer_depth;

	std::shared_ptr<RenderTexture> fullHdrTarget1 = std::make_shared<RenderTexture>(context);
	fullHdrTarget1->Create(width, height, false, DXGI_FORMAT_R32G32B32A32_FLOAT);
	renderTextures[RenderTextureType::FULL_HDR_TARGET1] = fullHdrTarget1;

	std::shared_ptr<RenderTexture> fullHdrTarget2 = std::make_shared<RenderTexture>(context);
	fullHdrTarget2->Create(width, height, false, DXGI_FORMAT_R32G32B32A32_FLOAT);
	renderTextures[RenderTextureType::FULL_HDR_TARGET2] = fullHdrTarget2;

	std::shared_ptr<RenderTexture> spareHalf = std::make_shared<RenderTexture>(context);
	spareHalf->Create(width / 2, height / 2, false, DXGI_FORMAT_R16G16B16A16_FLOAT);
	renderTextures[RenderTextureType::SPARE_HALf] = spareHalf;

	std::shared_ptr<RenderTexture> spareFull = std::make_shared<RenderTexture>(context);
	spareFull->Create(width, height, false, DXGI_FORMAT_R16G16B16A16_FLOAT);
	renderTextures[RenderTextureType::SPARE_FULL] = spareFull;

	std::shared_ptr<RenderTexture> blur1Quarter = std::make_shared<RenderTexture>(context);
	blur1Quarter->Create(width / 4, height / 4, false, DXGI_FORMAT_R16G16B16A16_FLOAT);
	renderTextures[RenderTextureType::BLUR_QUARTER1] = blur1Quarter;

	std::shared_ptr<RenderTexture> blur2Quarter = std::make_shared<RenderTexture>(context);
	blur2Quarter->Create(width / 4, height / 4, false, DXGI_FORMAT_R16G16B16A16_FLOAT);
	renderTextures[RenderTextureType::BLUR_QUARTER2] = blur2Quarter;
}

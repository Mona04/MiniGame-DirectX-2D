#pragma once
#include "../ISubsystem.h"

enum GBufferRenderOption : uint  // instance, animated, albedo, normal, emissive 
{
	FFFFF, FFFFT, FFFTF, FFFTT, FFTFF, FFTFT, FFTTF, FFTTT, 
	FTFFF, FTFFT, FTFTF, FTFTT, FTTFF, FTTFT, FTTTF, FTTTT,
	TFFFF, TFFFT, TFFTF, TFFTT, TFTFF, TFTFT, TFTTF, TFTTT,
	TTFFF, TTFFT, TTFTF, TTFTT, TTTFF, TTTFT, TTTTF, TTTTT,
};

enum RendererFlags : uint
{
	PostProcess_Bloom = 1U << 0,
	PostProcess_FXAA = 1U << 1,    //Fast Approximate Anti Aliasing
	PostProcess_TAA = 1U << 2,     //Temporal Anti Aliasing
	PostProcess_Sharpening = 1U << 3,   
	GBuffer_Show_RigidBody = 1U << 4,
};

enum PostprocessFlag : uint
{
	None = 1U << 0,
	DownSample = 1U << 1,
	Bright = 1U << 2,
	GaussianBlur = 1U << 3,
	Upsample1 = 1U << 4,
	Upsample2 = 1U << 5,
	Blending = 1U << 6
};

enum class RenderableType : uint
{
	Opaque,
	Transparent,
	Camera
};

enum class ShaderType : uint
{
	VP_GBUFFER,
	VS_POSTPROCESS,
	VP_LIGHT,
	PS_DOWN_SAMPLING,
	PS_UP_SAMPLING,
	PS_BRIGHT,
	PS_BLEND,
	PS_BLUR_GAUSSIAN,
	VP_UI_TEXTURE,
	VP_UI_COLOR
};

enum class RenderTextureType : uint
{
	GBUFFER_ALBEDO,
	GBUFFER_NORMAL,
	GBUFFER_VELOCITY,
	GBUFFER_DEPTH,
	FULL_HDR_TARGET1,
	FULL_HDR_TARGET2,
	SPARE_HALf,
	SPARE_FULL,
	BLUR_QUARTER1,
	BLUR_QUARTER2
};

class Renderer final : public ISubsystem
{
public:
	Renderer(class Context* context);
	~Renderer();

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	const bool Initialize() override;
	
	ID3D11ShaderResourceView* GetFrameResourseView();

	const uint& GetRendererFlags() { return rendererFlags; }
	void SetRendererFlags(const uint& flags) { rendererFlags = flags; }
	const bool IsEnableRendererFlag(const RendererFlags& flag) { return rendererFlags & flag; }
	void OnRendererFlag(const RendererFlags& flag) { rendererFlags |= flag; }
	void OffRendererFlag(const RendererFlags& flag) { rendererFlags &= ~flag; }

	const uint& GetPostprocessFlags() { return postprocessFlags; }
	void SetPostprocessFlags(const uint& flags) { postprocessFlags = flags; }
	const bool IsEnabledPostProcessFlags(const uint& flag) const { return postprocessFlags & flag; }
	void OnPostprocessFlags(const uint& flag) { postprocessFlags |= flag; }
	void OffPostprocessFlags(const uint& flag) { postprocessFlags &= ~flag; }

	const float& GetBloomIntensity() { return bloomIntensity; }
	void SetBloomIntensity(const float& intensity) { bloomIntensity = intensity; }

	const float& GetBlurSigma() { return blurSigma; }
	void SetBlurSigma(const float& sigma) { blurSigma = sigma; }

	const float& GetBlurStride() { return blurStride; }
	void SetBlurStride(const float& sigma) { blurStride = sigma; }

public:
	class Camera* GetCamera() const;
	void Clear_Camera() { sceneCamera = nullptr; }

	const Vector2& GetResolution() { return resolution; }
	void SetResolution(const Vector2& var);

	void AcquireScene(class Scene* scene);
	void UpdateActorList(class Actor* actor);
	void ClearRenderables();

	void AcquireUI(class UI* ui);
	void AcquirePreUI(class UI* ui);

	void UpdateDefaultBuffer();
	void UpdatePostProcessBuffer(const float& width, const float& height, const float& intensity = 1.0f, const float& sigma = 3.2f, const Vector2 & dir = Vector2(1.0f, 1.0f));

	void Render();
	void RenderForEngine(class UI_Component_Frame* renderable);

private:
	void PassMain();
	void PassGBuffer();
	void DrawActor(class Actor* actor, class VertexBuffer* instanceBuffer = nullptr, const bool& isBackGround = false, const bool& isFrame = false);

	void PassPreLight();
	void PassLight(std::shared_ptr<class RenderTexture>& out);
	void PassPostLight(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out);

	void PassBoxBlur(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out);
	void PassGaussianBlur(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out);
	void PassBilateralGaussianBlur(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out);
	void PassBloom(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out);
	void PassShine(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out);

	void PassForSampling(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out, const std::shared_ptr<Shader> shader);

	void PassPreUI();
	void PassUI();
	void DrawUIComponent(class IUIComponent* compoent, class VertexBuffer* instanceBuffer = nullptr);
	void DrawUIFrame(class UI_Component_Frame* frame, class VertexBuffer* instanceBuffer = nullptr);

private:
	void CreateDefaultBuffers();
	void CreateScreenBuffers(const float& width, const float& height);
	void CreateShaders();
	void CreateStates();
	void CreateRenderTarget(const uint& width, const uint& height);

private:
	//buffers
	std::map<GBufferRenderOption, std::shared_ptr<class ConstantBuffer>> gbufferRenderOptionBuffers;
	std::shared_ptr<class ConstantBuffer> postProcessBuffer;

	std::shared_ptr<class ConstantBuffer> cameraDefaultBuffer;
	std::shared_ptr<class ConstantBuffer> transformDefaultBuffer;
	std::shared_ptr<class ConstantBuffer> animationDefaultBuffer;
	std::shared_ptr<class ConstantBuffer> materialDefaultBuffer;

	std::shared_ptr<class VertexBuffer> screenVertexBuffer;
	std::shared_ptr<class IndexBuffer> screenIndexBuffer;

	//shaders
	std::map<ShaderType, std::shared_ptr<class Shader>> shaders;
	std::shared_ptr<InputLayout> inputLayout_GBuffer;
	std::shared_ptr<InputLayout> inputLayout_UI;

	//States
	std::shared_ptr<class Sampler> samplerState_clamp_point;
	std::shared_ptr<class Sampler> samplerState_clamp_bilinear;
	std::shared_ptr<class Sampler> samplerState_wrap_bilinear;
	std::shared_ptr<class Sampler> samplerState_wrap_trilinear;
	std::shared_ptr<class Sampler> samplerState_wrap_anisotropic;

	std::shared_ptr<class RasterizerState> rasterizerState_solid_Back;
	std::shared_ptr<class RasterizerState> rasterizerState_wire_Back;
	std::shared_ptr<class BlendState> blendState_alpha_true;
	std::shared_ptr<class DepthStencilState> depthStencilState_depth_enable;

	//Target
	std::map<RenderTextureType, std::shared_ptr<RenderTexture>> renderTextures;

private:
	class Graphics* graphics;
	class SceneManager* sceneManager;
	class DataManager* dataManager;

	Scene* currentScene;
	Camera* sceneCamera;
	std::shared_ptr<class Camera> editorCamera;
	std::shared_ptr<class CommandList> commandList;

	std::unordered_map<RenderableType, std::vector<class Actor*>> actorsList;
	std::vector<class IUIComponent*> preUIComponentList;
	std::vector<class IUIComponent*> UIComponentList;

	Vector2 resolution;

	uint rendererFlags;
	uint postprocessFlags;

	float bloomIntensity;
	float blurSigma;
	float blurStride;

	uint current_material = 0;
	uint current_mesh = 0;
	uint current_shader = 0;

private:
	Actor* forActorFrame;
	std::shared_ptr<class VertexBuffer> frameInstanceBuffer;
	std::shared_ptr<class Geometry<class VertexPositionScaleSprite>> frameGeometry;

	void CreateActorFrame();
	void ShowActorFrame();
};
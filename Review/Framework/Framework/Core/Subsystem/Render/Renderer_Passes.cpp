#include "Framework.h"
#include "Renderer.h"
#include "Pipeline.h"
#include "CommandList.h"
#include "Framework/Core/Engine.h"

void Renderer::PassMain()
{
	commandList->Begin("PassMain");
	{
		PassGBuffer();
		PassLight(renderTextures[RenderTextureType::FULL_HDR_TARGET1]);
		PassPostLight(renderTextures[RenderTextureType::FULL_HDR_TARGET1], renderTextures[RenderTextureType::FULL_HDR_TARGET2]);
		renderTextures[RenderTextureType::FULL_HDR_TARGET1].swap(renderTextures[RenderTextureType::FULL_HDR_TARGET2]);
		PassShine(renderTextures[RenderTextureType::FULL_HDR_TARGET1], renderTextures[RenderTextureType::FULL_HDR_TARGET2]);
		renderTextures[RenderTextureType::FULL_HDR_TARGET1].swap(renderTextures[RenderTextureType::FULL_HDR_TARGET2]);
	}
	commandList->End();
	commandList->Submit();
}

void Renderer::PassGBuffer()
{
	commandList->Begin("PassGBuffer");
	{
		std::vector<ID3D11RenderTargetView*> renderTargets   // 비효율적?
		{
			renderTextures[RenderTextureType::GBUFFER_ALBEDO]->GetRenderTargetView(),
			renderTextures[RenderTextureType::GBUFFER_NORMAL]->GetRenderTargetView(),
			renderTextures[RenderTextureType::GBUFFER_VELOCITY]->GetRenderTargetView(),
			renderTextures[RenderTextureType::GBUFFER_DEPTH]->GetRenderTargetView(),
		};

		std::shared_ptr<Shader> shader = shaders[ShaderType::VP_GBUFFER];

		commandList->SetRSState(rasterizerState_solid_Back->GetState());
		commandList->SetBlendState(blendState_alpha_true->GetState());
		commandList->SetDepthStencilState(depthStencilState_depth_enable->GetState());
		commandList->SetSamplerState(0, ShaderStage::PS, samplerState_wrap_anisotropic->GetState());

		commandList->SetRenderTargets(renderTargets, renderTextures[RenderTextureType::GBUFFER_DEPTH]->GetDepthStencilView());
		commandList->SetViewPort(renderTextures[RenderTextureType::GBUFFER_ALBEDO]->GetViewport());
		commandList->ClearRenderTargets(renderTargets);
		commandList->ClearDetphStencilTarget(renderTextures[RenderTextureType::GBUFFER_DEPTH]->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f);

		commandList->SetInputLayout(shader->GetInputLayout());
		commandList->SetVertexShader(shader->GetVertexShader());
		commandList->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		current_material = 0;
		current_mesh = 0;
		current_shader = 0;

		if (!!currentScene)   // Less 로 처리해서 같은 깊이면 먼저그리면 앞에 옴. 참고로 0 혹은 음수일수록 가까움.
		{
			if (IsEnableRendererFlag(RendererFlags::GBuffer_Show_RigidBody))
				ShowActorFrame();

			for (auto& pair : context->GetSubsystem<MonsterManager>()->GetEffectsMap())
			{
				for (auto& effect : pair.second)
				{
					if (effect->IsActive())
						DrawActor(effect);
				}
			}

			for (auto& monster : context->GetSubsystem<MonsterManager>()->GetMonsters())
			{
				if (!monster) continue;
				DrawActor(monster);
				if (monster->HasComponent<Controller>())
					DrawActor(monster->GetComponent<Controller>()->GetEffectActor());
			}

			for (int i = actorsList[RenderableType::Opaque].size() - 1; i > -1; i--)
			{
				auto actor = actorsList[RenderableType::Opaque][i];
				DrawActor(actor);
				if (actor->HasComponent<Controller>())
					DrawActor(actor->GetComponent<Controller>()->GetEffectActor());
			}

			for (auto& blockKind : dataManager->GetBlockKinds()) // Block 갯수가 많지 않아서 그냥 돌림
			{
				current_mesh = 0;
				if (sceneManager->GetBlock(blockKind))
					DrawActor(sceneManager->GetBlock(blockKind), currentScene->GetInstanceBuffer(blockKind));
			}

			DrawActor(currentScene->GetBackGround(), nullptr);
		}
	}
	commandList->End();
	commandList->Submit();
}


void Renderer::DrawActor(Actor* actor, VertexBuffer* instancedBuffer, bool isFrame)
{
	if (!actor || !actor->IsActive() || (instancedBuffer && instancedBuffer->GetBuffer() == nullptr))
		return;

	Renderable* renderable = actor->GetComponent<Renderable>(); if (!renderable) return;
	Mesh* mesh = renderable->GetMesh();
	Material* material = renderable->GetMaterial();
	Transform* transform = actor->GetComponent<Transform>();
	Animator* animator = actor->GetComponent<Animator>();
	RigidBody* rigidBody = actor->GetComponent<RigidBody>();

	bool isInstanced = instancedBuffer ? true : false;
	bool isAnimated = animator ? true : false;
	bool hasAlbedoTexture = false; bool hasNormalTexture = false; bool hasEmissiveTexture = false;

	if (hasAlbedoTexture = renderable->HasTexture(TextureType::Albedo))
		commandList->SetShaderResource(0, ShaderStage::PS, renderable->GetTexture(TextureType::Albedo)->GetShaderResourceView());
	if (hasEmissiveTexture = renderable->HasTexture(TextureType::Emissive))
		commandList->SetShaderResource(1, ShaderStage::PS, renderable->GetTexture(TextureType::Emissive)->GetShaderResourceView());
	if (hasNormalTexture = renderable->HasTexture(TextureType::Normal))
		commandList->SetShaderResource(2, ShaderStage::PS, renderable->GetTexture(TextureType::Normal)->GetShaderResourceView());

	if (mesh && current_mesh != mesh->GetID()) {
		commandList->SetVertexBuffer(mesh->GetVertexBuffer(), instancedBuffer);
		commandList->SetIndexBuffer(mesh->GetIndexBuffer());
		current_mesh = mesh->GetID();
	}

	if (material && current_material != material->GetID()) {

		std::shared_ptr<Shader> shader = shaders[ShaderType::VP_GBUFFER];
		if (shader && current_shader != shader->GetShaderID()) {
			commandList->SetPixelShader(shader->GetPixelShader());
			commandList->SetInputLayout(inputLayout_GBuffer.get());
			current_shader = shader->GetShaderID();
		}

		switch (material->GetSamplerType())
		{
		case SamplerType::clamp_point:
			commandList->SetSamplerState(0, ShaderStage::PS, samplerState_clamp_point->GetState());
			break;
		case SamplerType::clamp_bilinear:
			commandList->SetSamplerState(0, ShaderStage::PS, samplerState_clamp_bilinear->GetState());
			break;
		case SamplerType::wrap_bilinear:
			commandList->SetSamplerState(0, ShaderStage::PS, samplerState_wrap_bilinear->GetState());
			break;
		case SamplerType::wrap_trilinear:
			commandList->SetSamplerState(0, ShaderStage::PS, samplerState_wrap_trilinear->GetState());
			break;
		case SamplerType::wrap_anisotropic:
			commandList->SetSamplerState(0, ShaderStage::PS, samplerState_wrap_anisotropic->GetState());
			break;
		}
	}

	commandList->SetConstantBuffer(0, ShaderStage::ALL, gbufferRenderOptionBuffers[static_cast<GBufferRenderOption>(16 * isInstanced + 8 * isAnimated + 4 * hasAlbedoTexture + 2 * hasNormalTexture + hasEmissiveTexture)]->GetBuffer());	
	commandList->SetConstantBuffer(1, ShaderStage::ALL, GetCamera()->GetCameraBuffer()->GetBuffer());

	if (transform)
		commandList->SetConstantBuffer(2, ShaderStage::VS, transform->GetTransformBuffer()->GetBuffer());
	else commandList->SetConstantBuffer(2, ShaderStage::VS, transformDefaultBuffer->GetBuffer());

	if (renderable)
		commandList->SetConstantBuffer(2, ShaderStage::PS, renderable->GetMaterialBuffer()->GetBuffer());
	else commandList->SetConstantBuffer(2, ShaderStage::PS, materialDefaultBuffer->GetBuffer());

	if (animator)
		commandList->SetConstantBuffer(3, ShaderStage::ALL, animator->GetAnimationBuffer()->GetBuffer());
	else commandList->SetConstantBuffer(3, ShaderStage::ALL, animationDefaultBuffer->GetBuffer());

	if (mesh)
	{
		if (!isInstanced)
			commandList->DrawIndexed(mesh->GetIndexBuffer()->GetIndexCount(), mesh->GetIndexBuffer()->GetIndexOffset(), mesh->GetVertexBuffer()->GetVertexOffset());
		else
			commandList->DrawIndexedInstanced(mesh->GetIndexBuffer()->GetIndexCount(), instancedBuffer->GetVertexCount());
	}
}

void Renderer::PassLight(std::shared_ptr<class RenderTexture>& out)
{
	commandList->Begin("PassLight");
	{
		std::vector<ID3D11SamplerState*> samplers{ samplerState_wrap_trilinear->GetState(), samplerState_clamp_point->GetState() };
		std::vector<ID3D11ShaderResourceView*> textures
		{
			renderTextures[RenderTextureType::GBUFFER_ALBEDO]->GetShaderResourceView(),
			renderTextures[RenderTextureType::GBUFFER_NORMAL]->GetShaderResourceView(),
			renderTextures[RenderTextureType::GBUFFER_VELOCITY]->GetShaderResourceView()
		};

		std::shared_ptr<Shader> shader = shaders[ShaderType::VP_LIGHT];

		commandList->SetRenderTarget(out->GetRenderTargetView());
		commandList->SetViewPort(out->GetViewport());
		commandList->SetSamplerStates(0, ShaderStage::PS, samplers);

		commandList->SetVertexBuffer(screenVertexBuffer.get());
		commandList->SetIndexBuffer(screenIndexBuffer.get());
		commandList->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		commandList->SetInputLayout(shader->GetInputLayout());
		commandList->SetVertexShader(shader->GetVertexShader());
		commandList->SetPixelShader(shader->GetPixelShader());
		commandList->SetShaderResources(0, ShaderStage::PS, textures);

		commandList->DrawIndexed(screenIndexBuffer->GetIndexCount(), screenIndexBuffer->GetIndexOffset(), screenVertexBuffer->GetVertexOffset());
	}
	commandList->End();
	commandList->Submit();
}

void Renderer::PassPostLight(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out)
{
	commandList->Begin("PassPostLight");
	{
		std::shared_ptr<Shader> shader = shaders[ShaderType::VS_POSTPROCESS];

		commandList->SetVertexBuffer(screenVertexBuffer.get());
		commandList->SetIndexBuffer(screenIndexBuffer.get());
		commandList->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		commandList->SetInputLayout(shader->GetInputLayout());
		commandList->SetVertexShader(shader->GetVertexShader());
		
		if (IsEnableRendererFlag(PostProcess_Bloom))
			PassBloom(in, out);
	}

	commandList->Submit();
	commandList->End();
}

void Renderer::PassBoxBlur(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out)
{
}

void Renderer::PassGaussianBlur(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out)
{
	if (in->GetWidth() != out->GetWidth() || in->GetHeight() != out->GetHeight() || in->GetRTVFormat() != out->GetRTVFormat())
	{
		LOG_ERROR("Invalid parameter, textures must match because they will get swapped");
		return;
	}

	commandList->Begin("PassGaussianBlur");
	{
		std::shared_ptr<Shader> shader = shaders[ShaderType::PS_BLUR_GAUSSIAN];

		commandList->SetViewPort(out->GetViewport());
		commandList->SetPixelShader(shader->GetPixelShader());
		commandList->SetSamplerState(0, ShaderStage::PS, samplerState_wrap_trilinear->GetState());

		commandList->Begin("PassGaussianBlur Horizontal");
		{
			UpdatePostProcessBuffer(in->GetWidth(), in->GetHeight(), bloomIntensity, blurSigma, Vector2(blurStride, 0.0f));
			commandList->SetRenderTarget(out->GetRenderTargetView());
			commandList->SetShaderResource(0, ShaderStage::PS, in->GetShaderResourceView());
			commandList->SetConstantBuffer(0, ShaderStage::PS, postProcessBuffer->GetBuffer());
			commandList->DrawIndexed(screenIndexBuffer->GetIndexCount(), screenIndexBuffer->GetIndexOffset(), screenVertexBuffer->GetVertexOffset());
		}
		commandList->End();

		commandList->Begin("PassGaussianBlur Vertical");
		{
			UpdatePostProcessBuffer(in->GetWidth(), in->GetHeight(), bloomIntensity, blurSigma, Vector2(0.0f, blurStride));
			commandList->SetRenderTarget(in->GetRenderTargetView());
			commandList->SetShaderResource(0, ShaderStage::PS, out->GetShaderResourceView());
			commandList->SetConstantBuffer(0, ShaderStage::PS, postProcessBuffer->GetBuffer());
			commandList->DrawIndexed(screenIndexBuffer->GetIndexCount(), screenIndexBuffer->GetIndexOffset(), screenVertexBuffer->GetVertexOffset());
		}
		commandList->End();
	}
	commandList->End();
}

void Renderer::PassBilateralGaussianBlur(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out)
{
}

void Renderer::PassBloom(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out)
{
	commandList->Begin("PassBloom");
	{
		std::shared_ptr<RenderTexture> blur1Quarter = renderTextures[RenderTextureType::BLUR_QUARTER1];
		std::shared_ptr<RenderTexture> blur2Quarter = renderTextures[RenderTextureType::BLUR_QUARTER2];
		std::shared_ptr<RenderTexture> spareHalf = renderTextures[RenderTextureType::SPARE_HALf];
		std::shared_ptr<RenderTexture> spareFull = renderTextures[RenderTextureType::SPARE_FULL];

		commandList->SetSamplerState(0, ShaderStage::PS, samplerState_clamp_bilinear->GetState());

		if (IsEnabledPostProcessFlags(PostprocessFlag::DownSample))
			PassForSampling(in, blur1Quarter, shaders[ShaderType::PS_DOWN_SAMPLING]);
		if (IsEnabledPostProcessFlags(PostprocessFlag::Bright))
			PassForSampling(blur1Quarter, blur2Quarter, shaders[ShaderType::PS_BRIGHT]);
		if (IsEnabledPostProcessFlags(PostprocessFlag::GaussianBlur))
			PassGaussianBlur(blur2Quarter, blur1Quarter);
		if (IsEnabledPostProcessFlags(PostprocessFlag::Upsample1))
			PassForSampling(blur1Quarter, spareHalf, shaders[ShaderType::PS_UP_SAMPLING]);
		if (IsEnabledPostProcessFlags(PostprocessFlag::Upsample2))
		{
			if(IsEnabledPostProcessFlags(PostprocessFlag::Upsample1))
				PassForSampling(spareHalf, spareFull, shaders[ShaderType::PS_UP_SAMPLING]);
			else 
				PassForSampling(blur1Quarter, spareFull, shaders[ShaderType::PS_UP_SAMPLING]);
		}
		
		if (IsEnabledPostProcessFlags(PostprocessFlag::Blending))
		{
			commandList->Begin("Blending");
			{
				UpdatePostProcessBuffer(out->GetWidth(), out->GetHeight(), bloomIntensity);

				std::vector<ID3D11ShaderResourceView*> textures
				{
					in->GetShaderResourceView(),
					spareFull->GetShaderResourceView()
				};

				std::shared_ptr<Shader> shader = shaders[ShaderType::PS_BLEND];

				commandList->SetRenderTarget(out->GetRenderTargetView());
				commandList->SetViewPort(out->GetViewport());

				commandList->SetPixelShader(shader->GetPixelShader());
				commandList->SetShaderResources(0, ShaderStage::PS, textures);
				commandList->SetConstantBuffer(0, ShaderStage::PS, postProcessBuffer->GetBuffer());

				commandList->DrawIndexed(screenIndexBuffer->GetIndexCount(), screenIndexBuffer->GetIndexOffset(), screenVertexBuffer->GetVertexOffset());
			}
			commandList->End();
		}
	}
	commandList->End();
}

void Renderer::PassShine(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out)
{
	commandList->Begin("PassShine");
	{
		auto frame = context->GetEngine()->GetFrame();
		Renderable* renderable = frame->GetRenderable();
		Transform* trans = frame->GetTransform();
		Animator* animator = frame->GetAnimator();
		Mesh* mesh = renderable->GetMesh();
		Material* material = renderable->GetMaterial();
		std::shared_ptr<Shader> shader = shaders[ShaderType::VP_UI_TEXTURE];

		commandList->SetShaderResource(0, ShaderStage::PS, renderTextures[RenderTextureType::FULL_HDR_TARGET1]->GetShaderResourceView());
		commandList->SetVertexBuffer(mesh->GetVertexBuffer());
		commandList->SetIndexBuffer(mesh->GetIndexBuffer());
		commandList->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		commandList->SetVertexShader(shader->GetVertexShader());
		commandList->SetPixelShader(shader->GetPixelShader());
		commandList->SetInputLayout(inputLayout_UI.get());

		commandList->SetConstantBuffer(0, ShaderStage::VS, trans->GetTransformBuffer()->GetBuffer());
		commandList->SetConstantBuffer(1, ShaderStage::ALL, frame->GetUIBuffer()->GetBuffer());
		commandList->SetConstantBuffer(2, ShaderStage::PS, renderable->GetMaterialBuffer()->GetBuffer());
		commandList->SetConstantBuffer(3, ShaderStage::ALL, animationDefaultBuffer->GetBuffer());

		commandList->DrawIndexed(mesh->GetIndexBuffer()->GetIndexCount(), mesh->GetIndexBuffer()->GetIndexOffset(), mesh->GetVertexBuffer()->GetVertexOffset());
	}
	commandList->End();
}

void Renderer::PassForSampling(std::shared_ptr<class RenderTexture>& in, std::shared_ptr<class RenderTexture>& out, const std::shared_ptr<Shader> shader)
{
	commandList->Begin("Sampling");
	{
		UpdatePostProcessBuffer(out->GetWidth(), out->GetHeight());

		commandList->SetRenderTarget(out->GetRenderTargetView());
		commandList->SetViewPort(out->GetViewport());

		commandList->SetPixelShader(shader->GetPixelShader());
		commandList->SetShaderResource(0, ShaderStage::PS, in->GetShaderResourceView());
		commandList->SetConstantBuffer(0, ShaderStage::PS, postProcessBuffer->GetBuffer());

		commandList->DrawIndexed(screenIndexBuffer->GetIndexCount(), screenIndexBuffer->GetIndexOffset(), screenVertexBuffer->GetVertexOffset());
	}
	commandList->End();
}

void Renderer::RenderForEngine(class UIWidgetFrame* frame)
{
	graphics->BeginScene();
	commandList->Begin("Sampling");
	{
		Renderable* renderable = frame->GetRenderable();
		Transform* trans = frame->GetTransform();
		Animator* animator = frame->GetAnimator();
		Mesh* mesh = renderable->GetMesh();
		Material* material = renderable->GetMaterial();
		std::shared_ptr<Shader> shader = shaders[ShaderType::VP_UI_TEXTURE];
		
		commandList->SetShaderResource(0, ShaderStage::PS, renderTextures[RenderTextureType::FULL_HDR_TARGET1]->GetShaderResourceView());
		commandList->SetVertexBuffer(mesh->GetVertexBuffer());
		commandList->SetIndexBuffer(mesh->GetIndexBuffer());
		commandList->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		commandList->SetVertexShader(shader->GetVertexShader());
		commandList->SetPixelShader(shader->GetPixelShader());
		commandList->SetInputLayout(inputLayout_UI.get());

		commandList->SetConstantBuffer(0, ShaderStage::VS, trans->GetTransformBuffer()->GetBuffer());
		commandList->SetConstantBuffer(1, ShaderStage::ALL, frame->GetUIBuffer()->GetBuffer());
		commandList->SetConstantBuffer(2, ShaderStage::PS, renderable->GetMaterialBuffer()->GetBuffer());
		commandList->SetConstantBuffer(3, ShaderStage::ALL, animationDefaultBuffer->GetBuffer());

		commandList->DrawIndexed(mesh->GetIndexBuffer()->GetIndexCount(), mesh->GetIndexBuffer()->GetIndexOffset(), mesh->GetVertexBuffer()->GetVertexOffset());
	}
	commandList->End();
	commandList->Submit();
	graphics->EndScene();
}

void Renderer::PassPreUI()
{
	commandList->Begin("PreUI");
	{
		std::shared_ptr<RenderTexture> renderTexture = renderTextures[RenderTextureType::FULL_HDR_TARGET1];
		commandList->SetRenderTarget(renderTexture->GetRenderTargetView());
		commandList->SetViewPort(renderTexture->GetViewport());
		commandList->SetBlendState(blendState_alpha_true->GetState());
		commandList->SetDepthStencilState(depthStencilState_depth_enable->GetState());

		for (const auto& component : preUIComponentList)
			DrawUIComponent(component);
	}
	commandList->Submit();
	commandList->End();
}

void Renderer::PassUI()
{
	commandList->Begin("UI");
	{
		std::shared_ptr<RenderTexture> renderTexture = renderTextures[RenderTextureType::FULL_HDR_TARGET1];
		commandList->SetRenderTarget(renderTexture->GetRenderTargetView());

		commandList->SetViewPort(renderTexture->GetViewport());
		commandList->SetBlendState(blendState_alpha_true->GetState());
		commandList->SetSamplerState(0, ShaderStage::PS, samplerState_wrap_trilinear->GetState());
		commandList->SetDepthStencilState(depthStencilState_depth_enable->GetState());

		if (context->GetEngine()->IsOnEngineFlags(ENGINEFLAGS_PLAY))
		{
			auto monsterManager = context->GetSubsystem<MonsterManager>();
			DrawUIFrame(monsterManager->GetHP_Bar()->GetFrame("Frame"), monsterManager->GetHPBarInstanceBuffer_Frame());
			DrawUIFrame(monsterManager->GetHP_Bar()->GetFrame("Gauge"), monsterManager->GetHPBarInstanceBuffer_Gauge());
		}

		for (const auto& component : UIComponentList)
			DrawUIComponent(component);
	}
	commandList->Submit();
	commandList->End();
}

void Renderer::DrawUIComponent(IUIWidget* component, VertexBuffer* instancedBuffer)
{
	if (component == nullptr || !component->GetIsVisible())
		return;

	commandList->Begin("UI Component" + std::to_string(component->GetID()));
	{
		for (auto& frame : component->GetFrames())
			DrawUIFrame(frame, instancedBuffer);
	}
	commandList->End();
}

void Renderer::DrawUIFrame(UIWidgetFrame* frame, VertexBuffer* instancedBuffer)
{
	if (!frame || frame->IsVisible() == false)
		return;

	Renderable* renderable = frame->GetRenderable();
	Transform* trans = frame->GetTransform();
	Animator* animator = frame->GetAnimator();
	Mesh* mesh = renderable->GetMesh();
	Material* material = renderable->GetMaterial();
	Texture* texture = nullptr;
	std::shared_ptr<Shader> shader;
	if (renderable->HasTexture(TextureType::Albedo))
	{
		texture = renderable->GetTexture(TextureType::Albedo);
		commandList->SetShaderResource(0, ShaderStage::PS, texture->GetShaderResourceView());
		shader = shaders[ShaderType::VP_UI_TEXTURE];
	}
	else {
		shader = shaders[ShaderType::VP_UI_COLOR];
	}

	commandList->SetVertexBuffer(mesh->GetVertexBuffer(), instancedBuffer);
	commandList->SetIndexBuffer(mesh->GetIndexBuffer());
	commandList->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commandList->SetVertexShader(shader->GetVertexShader());
	commandList->SetPixelShader(shader->GetPixelShader());
	commandList->SetInputLayout(inputLayout_UI.get());

	commandList->SetConstantBuffer(0, ShaderStage::VS, trans->GetTransformBuffer()->GetBuffer());
	commandList->SetConstantBuffer(1, ShaderStage::ALL, frame->GetUIBuffer()->GetBuffer());
	commandList->SetConstantBuffer(2, ShaderStage::PS, renderable->GetMaterialBuffer()->GetBuffer());
	if (animator->GetAnimation())
		commandList->SetConstantBuffer(3, ShaderStage::ALL, animator->GetAnimationBuffer()->GetBuffer());
	else commandList->SetConstantBuffer(3, ShaderStage::ALL, animationDefaultBuffer->GetBuffer());

	if (instancedBuffer == nullptr)
		commandList->DrawIndexed(mesh->GetIndexBuffer()->GetIndexCount(), mesh->GetIndexBuffer()->GetIndexOffset(), mesh->GetVertexBuffer()->GetVertexOffset());
	else
		commandList->DrawIndexedInstanced(mesh->GetIndexBuffer()->GetIndexCount(), instancedBuffer->GetVertexCount());
}

void Renderer::ShowActorFrame()
{
	frameGeometry->Clear();

	for (auto& actor : actorsList[RenderableType::Opaque])
	{
		if (actor->HasComponent<RigidBody>())
		{
			Transform* trans = actor->GetComponent<Transform>();
			frameGeometry->AddVertex(VertexPositionScaleSprite(trans->GetPosition(), trans->GetScale(), Vector2(0, 0)));
		}
	}

	for (auto& pair : context->GetSubsystem<MonsterManager>()->GetEffectsMap())
	{
		for (auto& actor : pair.second)
		{
			if (actor->HasComponent<RigidBody>() && actor->IsActive())
			{
				Transform* trans = actor->GetComponent<Transform>();
				frameGeometry->AddVertex(VertexPositionScaleSprite(trans->GetPosition(), trans->GetScale(), Vector2(0, 0)));
			}
		}
	}

	if (frameGeometry->GetVertexCount() > frameInstanceBuffer->GetVertexCount())
	{
		frameInstanceBuffer->Clear();
		frameInstanceBuffer->Create(frameGeometry->GetVertices(), D3D11_USAGE_DYNAMIC);
	}
	else
	{
		auto vdata = frameInstanceBuffer->Map<VertexPositionScaleSprite>();
		{
			memcpy(vdata, frameGeometry->GetVertexData(), frameGeometry->GetVertexCount() * sizeof(VertexPositionScaleSprite));
			frameInstanceBuffer->SetVertexCount(frameGeometry->GetVertexCount());
		}
		frameInstanceBuffer->Unmap();
	}

	commandList->Begin("Actor Frame");
	{
		commandList->SetRSState(rasterizerState_wire_Back->GetState());
		forActorFrame->Update();
		DrawActor(forActorFrame, frameInstanceBuffer.get(), true);
		commandList->SetRSState(rasterizerState_solid_Back->GetState());
	}
	commandList->End();
}
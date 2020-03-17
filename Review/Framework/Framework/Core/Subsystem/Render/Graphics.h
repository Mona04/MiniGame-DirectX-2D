#pragma once
#include "../ISubsystem.h"

class Graphics final : public ISubsystem
{
public:
	Graphics(class Context* context);
	~Graphics();

	const bool Initialize() override;

	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }

	void BeginScene();
	void EndScene();

	ID3D11RenderTargetView* GetRTV() { return rtv; }

private:
	void CreateSwapChain();
	void CreateBackBuffer(const uint& width, const uint& height);
	void DisableAltEnter();

private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;

	uint gpuMemorySize;
	std::wstring gpuDescription;
	uint numerator;
	uint denominator;

	ID3D11RenderTargetView* rtv;
	D3D11_VIEWPORT viewport;
	Color4 clearColor;
};
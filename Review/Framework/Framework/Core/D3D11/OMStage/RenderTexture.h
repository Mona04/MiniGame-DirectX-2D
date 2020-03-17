#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class RenderTexture final : public IPipeline
{
public:
	RenderTexture(class Context* context);
	~RenderTexture();

	RenderTexture(RenderTexture&) = delete;
	RenderTexture& operator=(RenderTexture&) = delete;

	ID3D11ShaderResourceView* GetShaderResourceView() const { return srv; }
	ID3D11RenderTargetView* GetRenderTargetView() const { return rtv; }
	ID3D11DepthStencilView* GetDepthStencilView() const { return dsv; }
	D3D11_VIEWPORT GetViewport() const { return viewport; }
	DXGI_FORMAT& GetDSVFormat() { return dsv_format; }
	DXGI_FORMAT& GetRTVFormat() { return rtv_format; }

	const uint& GetWidth() { return static_cast<uint>(viewport.Width); }
	const uint& GetHeight() { return static_cast<uint>(viewport.Height); }

	void Create
	(
		const uint& width,
		const uint& height,
		const bool& useDepth = false,
		const DXGI_FORMAT& rtv_format = DXGI_FORMAT_R8G8B8A8_UNORM,
		const DXGI_FORMAT & dsv_format = DXGI_FORMAT_D24_UNORM_S8_UINT
	);
	void Clear();
	void ClearTarget(const Color4& color = Color4(1, 0, 0, 1));
	void SetTarget();
	void Save(const std::string& path);

private:
	class Graphics* graphics;

	ID3D11Texture2D* rtvTexture;
	ID3D11Texture2D* dsvTexture;
	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* dsv;
	ID3D11ShaderResourceView* srv;
	D3D11_VIEWPORT viewport;
	DXGI_FORMAT rtv_format;
	DXGI_FORMAT dsv_format;
};
#include "Framework.h"
#include "RenderTexture.h"

RenderTexture::RenderTexture(Context * context)
	: rtvTexture(nullptr)
	, dsvTexture(nullptr)
	, rtv(nullptr)
	, dsv(nullptr)
	, srv(nullptr)
	, rtv_format(DXGI_FORMAT_R8G8B8A8_UNORM)
	, dsv_format(DXGI_FORMAT_D24_UNORM_S8_UINT)
{
	graphics = context->GetSubsystem<Graphics>();
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
}

RenderTexture::~RenderTexture()
{
	Clear();
}

void RenderTexture::Create(const uint & width, const uint & height, const bool& useDepth, const DXGI_FORMAT & rtv_format, const DXGI_FORMAT& dsv_format)
{
	if (width == 0 || height == 0)
	{
		LOG_ERROR("Invalid Parameter");
		return;
	}
	this->rtv_format = rtv_format;
	this->dsv_format = dsv_format;

	//viewPort 설정
	{
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(width);
		viewport.Height = static_cast<float>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
	}

	{
		//2D텍스쳐 설정
		CD3D11_TEXTURE2D_DESC desc;
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = rtv_format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		auto hr = graphics->GetDevice()->CreateTexture2D(&desc, nullptr, &rtvTexture);
		if (FAILED(hr))
		{
			LOG_ERROR("Fail to Create rtvTexture");
			return;
		}

		//RTV 설정
		{
			D3D11_RENDER_TARGET_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Format = rtv_format;
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = 0;

			auto hr = graphics->GetDevice()->CreateRenderTargetView
			(
				rtvTexture,
				&desc,
				&rtv
			);
			if (FAILED(hr))
			{
				LOG_ERROR("Fail to Create RenderTargetView");
				return;
			}
		}


		//ShaderResourceView 설정  위의 2d texture 에 관해서 만드는 것
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Format = rtv_format;
			desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipLevels = 1;
			desc.Texture2D.MostDetailedMip = 0;

			auto hr = graphics->GetDevice()->CreateShaderResourceView
			(
				rtvTexture,
				&desc,
				&srv
			);

			if (FAILED(hr))
			{
				LOG_ERROR("Fail to Create ShaderResourceView");
				return;
			}
		}
	}

	if (useDepth)
	{
		{
			//2D텍스쳐 설정
			CD3D11_TEXTURE2D_DESC desc;
			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = dsv_format;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;

			auto hr = graphics->GetDevice()->CreateTexture2D(&desc, nullptr, &dsvTexture);
			if (FAILED(hr))
			{
				LOG_ERROR("Fail to Create dsvTexture");
				return;
			}
		}
		//dsv 설정
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Format = dsv_format;
			desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			desc.Texture2D.MipSlice = 0;

			auto hr = graphics->GetDevice()->CreateDepthStencilView
			(
				dsvTexture,
				&desc,
				&dsv
			);
			if (FAILED(hr))
			{
				LOG_ERROR("Fail to Create DepthStencilView");
				return;
			}
		}
	}
}

void RenderTexture::Clear()
{
	SAFE_RELEASE(srv);
	SAFE_RELEASE(dsv);
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(rtvTexture);
	SAFE_RELEASE(dsvTexture);

	ZeroMemory(&viewport, sizeof(viewport));
	rtv_format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dsv_format = DXGI_FORMAT_D24_UNORM_S8_UINT;
}


void RenderTexture::ClearTarget(const Color4 & color)
{
	float tmp[4] = { color.r, color.g, color.b, color.a };
	graphics->GetDeviceContext()->ClearRenderTargetView(rtv, tmp);
}

void RenderTexture::SetTarget()
{
	graphics->GetDeviceContext()->RSSetViewports(1, &viewport);
	graphics->GetDeviceContext()->OMSetRenderTargets(1, &rtv, nullptr);
}

void RenderTexture::Save(const std::string & path)
{
	//auto hr = D3DX11SaveTextureToFileA
	//(
	//	graphics->GetDeviceContext(),
	//	rtvTexture,
	//	D3DX11_IFF_PNG,
	//	path.c_str()
	//);
	//
	//if (FAILED(hr))
	//{
	//	LOG_ERROR("Failed to Save rtvTexture");
	//	return;
	//}
}

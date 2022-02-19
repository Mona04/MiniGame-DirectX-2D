#pragma once
#include "stdafx.h"

namespace Rescale
{
	struct RescaleJob
	{
		uint width;
		uint height;
		uint channel;
		std::vector<std::byte>* data;
		bool done;

		RescaleJob(const uint& width, const uint& height, const uint& channel)
			: width(width), height(height), channel(channel), data(nullptr), done(false) {}
	};
}

class ImageImporter final
{
public:
	ImageImporter(class Context* context);
	~ImageImporter();

	ImageImporter(const ImageImporter&) = delete;
	ImageImporter& operator=(const ImageImporter&) = delete;

	const bool Load(const std::string& path, class Texture* texture);

private:
	struct FIBITMAP* ApplyBitmapCorrections(struct FIBITMAP* bitmap);
	struct FIBITMAP* Rescale(struct FIBITMAP* bitmap, const uint& width, const uint& height);

	const bool CopyBitsFromBITMAP(std::vector<std::byte>* data, struct FIBITMAP* bitmap, const uint& width, const uint& height, const uint& channel);
	void GenerateMipmaps(Texture* texture, struct FIBITMAP* bitmap, uint width, uint height, uint channel);
	void GenerateMipmap(Rescale::RescaleJob& job, struct FIBITMAP* bitmap);
	const uint ComputeChannelCount(struct FIBITMAP* bitmap);
	const uint ComputeBitsPerChannel(struct FIBITMAP* bitmap);
	const DXGI_FORMAT ComputeTextureFormat(const uint& bpp, const uint& channel);
	const bool IsVisuallyGrayScaled(struct FIBITMAP* bitmap);
	struct FIBITMAP* ConvertTo32Bits(struct FIBITMAP* bitmap);
	const bool SwapRedBlue32_Wrapper(struct FIBITMAP* bitmap);

private:
	class Context* context;
};

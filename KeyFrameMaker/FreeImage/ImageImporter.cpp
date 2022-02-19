#include "stdafx.h"
#include "ImageImporter.h"
#include "Texture.h"
#include "FreeImage/FreeImage.h"
#include "FreeImage/Utilities.h"

namespace Rescale
{
	FREE_IMAGE_FILTER rescaleFilter;
}

ImageImporter::ImageImporter(Context* context)
	: context(context)
{
	auto FreeImageErrorHandler = [](FREE_IMAGE_FORMAT fif, const char* message)
	{
		char buff[1024];

		const char* format = (fif != FIF_UNKNOWN) ? FreeImage_GetFormatFromFIF(fif) : "Unknown Error";
		const char* text = (message != nullptr) ? message : "Unknown Error";
		snprintf(buff, sizeof(buff), "%s , Format : %s.", text, format);
		MessageBoxA(Setting::Get()->GetHWND(), buff, nullptr, MB_OK);
	};

	FreeImage_SetOutputMessage(FreeImageErrorHandler);
}

ImageImporter::~ImageImporter()
{
	FreeImage_DeInitialise();
}

const bool ImageImporter::Load(const std::string& path, Texture* texture)
{
	if (!texture)
	{
		MessageBoxA(Setting::Get()->GetHWND(), "Invalid Parameter", nullptr, MB_OK);
		return false;
	}
	if (!FileSystem::IsExist(path))
	{
		std::string result = "Path " + path + " is invalid";
		MessageBoxA(Setting::Get()->GetHWND(), result.c_str(), nullptr, MB_OK);
		return false;
	}

	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);
	format = (format == FIF_UNKNOWN) ? FreeImage_GetFIFFromFilename(path.c_str()) : format; // 모르는 형식은 파일 이름에서 가져옴

	if (!FreeImage_FIFSupportsReading(format))
	{
		MessageBoxA(Setting::Get()->GetHWND(), "Unknown or unsupported format", nullptr, MB_OK);
		return false;
	}

	FIBITMAP* bitmap = FreeImage_Load(format, path.c_str()); // 1 Load

	bitmap = FreeImage_ConvertTo32Bits(bitmap);
	//bitmap = ApplyBitmapCorrections(bitmap);   // 2 Correcting
	if (!bitmap) return false;

	//필요시 모든 배율 조사
	const bool userDefineDimension = (texture->GetWidth() != 0 && texture->GetHeight() != 0);
	const bool dimensionMismatch = (FreeImage_GetWidth(bitmap) != texture->GetWidth() && FreeImage_GetHeight(bitmap) != texture->GetHeight());
	const bool scale = userDefineDimension && dimensionMismatch;
	//bitmap = scale ? Rescale(bitmap, texture->GetWidth(), texture->GetHeight()) : bitmap;  // 3 Rescale

	//이미지 속성 추정
	const bool imageTransparency = FreeImage_IsTransparent(bitmap);
	const uint imageWidth = FreeImage_GetWidth(bitmap);
	const uint imageHeight = FreeImage_GetHeight(bitmap);
	const uint imageBPP = FreeImage_GetBPP(bitmap);
	const uint imagePitch = FreeImage_GetPitch(bitmap);
	const uint imageBPC = ComputeBitsPerChannel(bitmap);
	const uint imageChannel = ComputeChannelCount(bitmap);
	const DXGI_FORMAT imageFormat = ComputeTextureFormat(imageBPC, imageChannel);
	const bool imageGrayScaled = IsVisuallyGrayScaled(bitmap);

	std::vector<std::byte>* mip = texture->AddMipData();
	CopyBitsFromBITMAP(mip, bitmap, imageWidth, imageHeight, imageChannel);   // 4 GetBitsFromBitmap

	if (texture->IsMipChained())
		GenerateMipmaps(texture, bitmap, imageWidth, imageHeight, imageChannel);    // 5 GenerateMipmap

	FreeImage_Unload(bitmap);

	//이미지속성을 Texture 에 세팅
	texture->SetBPP(imageBPP);
	texture->SetBPC(imageBPC);
	texture->SetWidth(imageWidth);
	texture->SetHeight(imageHeight);
	texture->SetChannel(imageChannel);
	texture->SetPitch(imagePitch);
	texture->SetTransparent(imageTransparency);
	texture->SetGrayScaled(imageGrayScaled);

	return true;
}


FIBITMAP* ImageImporter::ApplyBitmapCorrections(FIBITMAP* bitmap)
{
	if (!bitmap)
	{
		MessageBoxA(Setting::Get()->GetHWND(), "Invalid Parameter", nullptr, MB_OK);
		return nullptr;
	}

	unsigned int channels = ComputeChannelCount(bitmap);
	if (channels == 1)
	{
		int bpp = ComputeBitsPerChannel(bitmap);
		if (bpp == 16)
		{
			FIBITMAP* previousBitmap = bitmap;
			bitmap = FreeImage_ConvertTo8Bits(bitmap);
			FreeImage_Unload(previousBitmap);
		}
	}

	//32bit 로 변환
	if (FreeImage_GetBPP(bitmap) < 32)
		bitmap = ConvertTo32Bits(bitmap);

	if (FreeImage_GetBPP(bitmap) == 32)
	{
		if (FreeImage_GetRedMask(bitmap) == 0x00ff0000 && ComputeChannelCount(bitmap) >= 2)
		{
			bool swapped = SwapRedBlue32_Wrapper(bitmap);
			if (!swapped)
				MessageBoxA(Setting::Get()->GetHWND(), "Failed to swap red with blue channel", nullptr, MB_OK);
		}
	}

	//수직으로 뒤집기  -> 이건 뒤집어서 나오니까 일단 이래보자 심정임
//	FreeImage_FlipVertical(bitmap);

	return bitmap;
}

FIBITMAP* ImageImporter::Rescale(FIBITMAP* bitmap, const uint& width, const uint& height)
{
	if (!bitmap || width == 0 || height == 0)
	{
		MessageBoxA(Setting::Get()->GetHWND(), "Invalid Parameter", nullptr, MB_OK);
		return nullptr;
	}

	FIBITMAP* previousBitmap = bitmap;
	bitmap = FreeImage_Rescale(previousBitmap, width, height, Rescale::rescaleFilter);
	if (!bitmap)
	{
		MessageBoxA(Setting::Get()->GetHWND(), "Failed", nullptr, MB_OK);
		return previousBitmap;
	}

	FreeImage_Unload(previousBitmap);
	return bitmap;
}

const bool ImageImporter::CopyBitsFromBITMAP(std::vector<std::byte>* data, FIBITMAP* bitmap, const uint& width, const uint& height, const uint& channel)
{
	if (!data || width == 0 || height == 0 || channel == 0)
	{
		LOG_ERROR("Invalid Parameter");
		return false;
	}

	uint size = width * height * channel * (ComputeBitsPerChannel(bitmap) / 8);
	if (size != data->size())
	{
		data->clear();
		data->reserve(size);
		data->resize(size);
	}

	BYTE* bits = FreeImage_GetBits(bitmap);
	memcpy(&(*data)[0], bits, size);

	return true;
}

void ImageImporter::GenerateMipmaps(Texture* texture, FIBITMAP* bitmap, uint width, uint height, uint channel)
{
	if (!texture)
	{
		LOG_ERROR("Invalid Parameter");
		return;
	}

	std::vector<Rescale::RescaleJob> jobs;

	while (width > 1 && height > 1)
	{
		width = std::max<uint>(width / 2, 1);
		height = std::max<uint>(height / 2, 1);
		jobs.emplace_back(width, height, channel);

		uint size = width * height * channel * (ComputeBitsPerChannel(bitmap) / 8);;
		std::vector<std::byte>* mip = texture->AddMipData();

		mip->reserve(size);
		mip->resize(size);
	}

	for (uint i = 0; i < jobs.size(); i++)
		jobs[i].data = &texture->GetMipChain()[i + 1];  // 이미 한개 만들어져 있엄, 따로 돌리는 이유는 vector 크기가 바뀌니까 reserve 해야하는데 크기 알아내기 귀찮아서

	for (auto& job : jobs)
		GenerateMipmap(job, bitmap);   // thread 쓰면 데드락 발생함.

	bool ready = false;
	while (!ready)  // 그렇다고 냅두면 지역변수 소멸자 호출됨
	{
		int num = 0;
		ready = true;
		for (const auto& job : jobs)
		{
			if (!job.done)
				ready = false;
			else num++;
		}
		if (num > 0)
			num = 1000;
	}
}

void ImageImporter::GenerateMipmap(Rescale::RescaleJob& job, FIBITMAP* bitmap)
{
	FIBITMAP* bitmapScaled = FreeImage_Rescale(bitmap, job.width, job.height, Rescale::rescaleFilter);  // resize

	if (!CopyBitsFromBITMAP(job.data, bitmapScaled, job.width, job.height, job.channel))    // copy resized
	{
		LOG_ERROR("Failed to create Level %d %d.", job.width, job.height);
	}
	FreeImage_Unload(bitmapScaled);

	job.done = true;
}

const uint ImageImporter::ComputeChannelCount(FIBITMAP* bitmap)
{
	if (!bitmap)
	{
		MessageBoxA(Setting::Get()->GetHWND(), "Invalid Parameter", nullptr, MB_OK);
		return 0;
	} 
	uint bytespp = FreeImage_GetLine(bitmap) / FreeImage_GetWidth(bitmap);
	uint channels = bytespp / (ComputeBitsPerChannel(bitmap) / 8);

	return channels;
}

const uint ImageImporter::ComputeBitsPerChannel(FIBITMAP* bitmap)
{
	if (!bitmap)
	{
		LOG_ERROR("Invalid Parameter");
		return 0;
	}

	FREE_IMAGE_TYPE type = FreeImage_GetImageType(bitmap);
	unsigned int size = 0;

	if (type == FIT_BITMAP) // 1
		size = sizeof(BYTE);
	else if (type == FIT_UINT16 || type == FIT_RGB16 || type == FIT_RGBA16)  // 2
		size = sizeof(WORD);
	else if (type == FIT_FLOAT || type == FIT_RGBF || type == FIT_RGBAF)  // 4
		size = sizeof(float);

	return size * 8;
}

const DXGI_FORMAT ImageImporter::ComputeTextureFormat(const uint& bpc, const uint& channel)
{
	if (channel == 3)
	{
		if (bpc == 32) return DXGI_FORMAT_R32G32B32_FLOAT;
	}
	else if (channel == 4)
	{
		if (bpc == 8)	return DXGI_FORMAT_R8G8B8A8_UNORM;
		if (bpc == 16)	return DXGI_FORMAT_R16G16B16A16_FLOAT;
		if (bpc == 32) return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}

	MessageBoxA(Setting::Get()->GetHWND(), "Invalid Parameter", nullptr, MB_OK);
	return DXGI_FORMAT_R8_UNORM;
}

const bool ImageImporter::IsVisuallyGrayScaled(FIBITMAP* bitmap)
{
	if (!bitmap)
	{
		MessageBoxA(Setting::Get()->GetHWND(), "Invalid Parameter", nullptr, MB_OK);
		return false;
	}

	switch (FreeImage_GetBPP(bitmap))
	{
	case 1:
	case 4:
	case 8:
	{
		const auto rgb = FreeImage_GetPalette(bitmap);
		if ((rgb->rgbRed != rgb->rgbGreen) || (rgb->rgbRed != rgb->rgbBlue))
			return false;

		return true;
	}
	default:
		return (FreeImage_GetColorType(bitmap) == FIC_MINISBLACK);
	}
}

FIBITMAP* ImageImporter::ConvertTo32Bits(FIBITMAP* bitmap)
{
	if (!bitmap)
	{
		LOG_ERROR("Invalid Parameter");
		return nullptr;
	}

	FIBITMAP* previousBitmap = bitmap;
	bitmap = FreeImage_ConvertTo32Bits(previousBitmap);
	if (!bitmap)
	{
		char buff[1024];
		snprintf(buff, sizeof(buff), "Failed (%d bpp, %d channels).", FreeImage_GetBPP(previousBitmap), ComputeChannelCount(previousBitmap));
		MessageBoxA(Setting::Get()->GetHWND(), buff, nullptr, MB_OK);
		return nullptr;
	}

	FreeImage_Unload(previousBitmap);
	return bitmap;
}

const bool ImageImporter::SwapRedBlue32_Wrapper(FIBITMAP* bitmap)
{
	if (FreeImage_GetImageType(bitmap) != FIT_BITMAP)
		return false;

	const unsigned bytesperpixel = FreeImage_GetBPP(bitmap) / 8;
	if (bytesperpixel > 4 || bytesperpixel < 3)
		return false;

	const uint height = FreeImage_GetHeight(bitmap);
	const uint pitch = FreeImage_GetPitch(bitmap);

	BYTE* line = FreeImage_GetBits(bitmap);
	for (uint y = 0; y < height; ++y, line += pitch) {
		for (BYTE* pixel = line; pixel < line + pitch; pixel += bytesperpixel)
			INPLACESWAP(pixel[0], pixel[2]);
	}

	return true;
}

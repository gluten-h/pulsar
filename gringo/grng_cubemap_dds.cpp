
#include "grng_cubemap.h"


void		grng_cubemap::create_dds_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path)
{
	std::unique_ptr<ScratchImage> scratch_img[6];
	Image img[6];

	uint8_t *pix_data = NULL;

	for (size_t i = 0; i < 6; i++)
	{
		scratch_img[i] = std::make_unique<ScratchImage>();
		HRESULT hr = LoadFromWICFile(wic_path[i], WIC_FLAGS_NONE, NULL, *scratch_img[i]);
		img[i] = *scratch_img[i]->GetImage(0, 0, 0);
	}

	TexMetadata meta_data;
	meta_data.width = img[0].width;
	meta_data.height = img[0].height;
	meta_data.depth = 1;
	meta_data.arraySize = 6;
	meta_data.mipLevels = 1;
	meta_data.miscFlags = TEX_MISC_TEXTURECUBE;
	meta_data.miscFlags2 = TEX_ALPHA_MODE_OPAQUE;
	meta_data.format = img[0].format;
	meta_data.dimension = TEX_DIMENSION_TEXTURE2D;

	bool c = meta_data.IsCubemap();

	HRESULT hr = SaveToDDSFile(img, 6u, meta_data, DDS_FLAGS_NONE, output_dds_path);
}

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION  
#include "stb_image.h"

Texture::Texture(std::string path, std::string file)
	:file(file)
{
	int imgWidth, imgHeight;
	unsigned char* image = stbi_load((path).c_str(), &imgWidth, &imgHeight, nullptr, STBI_rgb_alpha);

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = imgWidth;
	textureDesc.Height = imgHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.MiscFlags = 0;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = image;
	data.SysMemPitch = imgWidth * STBI_rgb_alpha;

	ID3D11Texture2D* img;
	if (FAILED(Graphics::GetDevice().CreateTexture2D(&textureDesc, &data, &img)))
	{
		Print("FAILED TO CREATE TEXTURE 2D");
		return;
	}

	if (FAILED(Graphics::GetDevice().CreateShaderResourceView(img, nullptr, &this->srv)))
	{
		Print("FAILED TO CREATE SHADER RESOURCE VIEW");
		return;
	}

	stbi_image_free(image);
	img->Release();
	img = nullptr;
}
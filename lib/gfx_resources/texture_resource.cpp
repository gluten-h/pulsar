
#include "texture_resource.h"
#include "exceptions/gfx_exception.h"


pulsar::texture_resource::~texture_resource()
{
	this->destroy_texture();
}

void	pulsar::texture_resource::create_texture(D3D11_TEXTURE2D_DESC &td)
{
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateTexture2D(&td, NULL, &this->mp_texture));
}

void	pulsar::texture_resource::destroy_texture()
{
	if (this->mp_texture)
	{
		this->mp_texture->Release();
		this->mp_texture = NULL;
	}
}

ID3D11Texture2D		*pulsar::texture_resource::texture()
{
	return (this->mp_texture);
}

XMUINT2		pulsar::texture_resource::size() const
{
	XMUINT2 size{ 0u, 0u };
	D3D11_TEXTURE2D_DESC td;

	if (!this->mp_texture)
		return (size);

	this->mp_texture->GetDesc(&td);
	size.x = td.Width;
	size.y = td.Height;

	return (size);
}

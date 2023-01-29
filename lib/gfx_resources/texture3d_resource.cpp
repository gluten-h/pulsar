
#include "texture3d_resource.h"
#include "exceptions/gfx_exception.h"


pulsar::texture3d_resource::~texture3d_resource()
{
	this->destroy_texture();
}

void	pulsar::texture3d_resource::create_texture(D3D11_TEXTURE3D_DESC *td, const D3D11_SUBRESOURCE_DATA *subresource_data)
{
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateTexture3D(td, subresource_data, &this->mp_texture));
}

void	pulsar::texture3d_resource::destroy_texture()
{
	if (this->mp_texture)
	{
		this->mp_texture->Release();
		this->mp_texture = NULL;
	}
}

ID3D11Texture3D		*pulsar::texture3d_resource::texture()
{
	return (this->mp_texture);
}

XMUINT3		pulsar::texture3d_resource::size() const
{
	XMUINT3 size{ 0u, 0u, 0u };
	D3D11_TEXTURE3D_DESC td;

	if (!this->mp_texture)
		return (size);

	this->mp_texture->GetDesc(&td);
	size.x = td.Width;
	size.y = td.Height;
	size.z = td.Depth;

	return (size);
}

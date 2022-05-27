
#include "render_texture.h"
#include "utils/math.h"


pulsar::render_texture::render_texture(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags, UINT slot)
{
	this->create_rt(width, height, format, bind_flags, cpu_access_flags);
	this->set_slot(slot);
}

pulsar::render_texture::~render_texture()
{
	this->free();
}

void	pulsar::render_texture::resize(UINT width, UINT height)
{
	if (this->mp_texture)
	{
		D3D11_TEXTURE2D_DESC td;
		this->mp_texture->GetDesc(&td);
		this->set(width, height, td.Format, td.BindFlags, td.CPUAccessFlags);
	}

	this->resize_linked(width, height);
}

void	pulsar::render_texture::clear()
{
	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0 };
	pulsar::gfx::instance().device_context()->ClearRenderTargetView(this->mp_rtv, clear_color);
}

void	pulsar::render_texture::bind_srv() const
{
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}
void	pulsar::render_texture::bind_rtv(ID3D11DepthStencilView *ds_view) const
{
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, &this->mp_rtv, ds_view);
}

void	pulsar::render_texture::unbind_srv() const
{
	ID3D11ShaderResourceView *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, null_ptr);
}
void	pulsar::render_texture::unbind_rtv() const
{
	ID3D11RenderTargetView *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, null_ptr, NULL);
}

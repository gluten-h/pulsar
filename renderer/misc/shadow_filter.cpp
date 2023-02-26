
#include "shadow_filter.h"
#include "exceptions/gfx_exception.h"
#include <random>


pulsar::shadow_filter::shadow_filter(UINT filter_size, UINT filter_samples, UINT slot)
{
	static std::default_random_engine generator;
	static std::uniform_real_distribution<float> distr(-0.5f, 0.5f);

	this->m_data.resize(filter_size * filter_size * filter_samples * filter_samples * 2u);

	int id = 0;
	for (int tex_y = 0; tex_y < filter_size; tex_y++)
	{
		for (int tex_x = 0; tex_x < filter_size; tex_x++)
		{
			for (int v = filter_samples - 1; v >= 0; v--)
			{
				for (int u = 0; u < filter_samples; u++)
				{
					float x = ((float)u + 0.5f + distr(generator)) / (float)filter_samples;
					float y = ((float)v + 0.5f + distr(generator)) / (float)filter_samples;

					//float x = ((float)u + 0.5f) / (float)filter_samples;
					//float y = ((float)v + 0.5f) / (float)filter_samples;

					this->m_data[id] = sqrtf(y) * cosf(XM_2PI * x);
					this->m_data[id + 1] = sqrtf(y) * sinf(XM_2PI * x);

					id += 2;
				}
			}
		}
	}

	D3D11_TEXTURE3D_DESC td;
	D3D11_SUBRESOURCE_DATA sd;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE3D_DESC));
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	td.Width = filter_samples * filter_samples;// / 2u;
	td.Height = filter_size;
	td.Depth = filter_size;
	td.MipLevels = 1u;
	td.Format = DXGI_FORMAT_R32G32_FLOAT;//DXGI_FORMAT_R8G8B8A8_SNORM;
	td.Usage = D3D11_USAGE_IMMUTABLE;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	sd.pSysMem = this->m_data.data();
	sd.SysMemPitch = td.Width * 2u * sizeof(float);
	sd.SysMemSlicePitch = td.Width * td.Height * 2u * sizeof(float);
	this->create_texture(&td, &sd);

	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	srvd.Texture3D.MipLevels = 1u;
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateShaderResourceView(this->mp_texture, &srvd, &this->mp_srv));

	this->set_slot(slot);
}

pulsar::shadow_filter::~shadow_filter()
{
	if (this->mp_srv)
	{
		this->mp_srv->Release();
		this->mp_srv = NULL;
	}
}

void	pulsar::shadow_filter::set_slot(UINT slot)
{
	this->m_slot = slot;
}

void	pulsar::shadow_filter::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}

void	pulsar::shadow_filter::unbind() const
{
	ID3D11ShaderResourceView *null[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, null);
}

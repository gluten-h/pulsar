
#include "cubemap.h"


pulsar::cubemap		&pulsar::cubemap::operator=(const pulsar::cubemap &c)
{
	this->copy_assign(c);
	return (*this);
}

pulsar::cubemap::cubemap(const pulsar::cubemap &c)
{
	this->copy_assign(c);
}

pulsar::cubemap::cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path, pulsar::CUBEMAP_DDS dds_behavior, UINT slot)
{
	this->set(wic_path, output_dds_path, dds_behavior);
	this->set_slot(slot);
}

pulsar::cubemap::cubemap(LPCWSTR dds_path, UINT slot)
{
	this->create_cubemap(dds_path);
	this->set_slot(slot);
}

pulsar::cubemap::~cubemap()
{
	this->free();
}

void	pulsar::cubemap::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}

void	pulsar::cubemap::unbind() const
{
	ID3D11ShaderResourceView *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, null_ptr);
}

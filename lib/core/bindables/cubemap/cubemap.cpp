
#include "cubemap.h"


PULSAR::cubemap::cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path, PULSAR::CUBEMAP_DDS dds_behavior, UINT slot)
{
	this->set(wic_path, output_dds_path, dds_behavior);
	this->set_slot(slot);
}

PULSAR::cubemap::cubemap(LPCWSTR dds_path, UINT slot)
{
	this->create_cubemap(dds_path);
	this->set_slot(slot);
}

PULSAR::cubemap::~cubemap()
{
	this->free();
}

void	PULSAR::cubemap::bind() const
{
	PULSAR::gfx::get().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}

void	PULSAR::cubemap::unbind() const
{
	ID3D11ShaderResourceView *null_ptr[1] = { NULL };
	PULSAR::gfx::get().device_context()->PSSetShaderResources(this->m_slot, 1u, null_ptr);
}

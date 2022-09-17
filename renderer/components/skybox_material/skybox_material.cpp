
#include "skybox_material.h"
#include "config/cubemap.h"


pulsar::skybox_material::skybox_material()
{
	this->m_albedo_map = pulsar::BLACK_CUBEMAP;
	this->m_exposure_map = pulsar::WHITE_CUBEMAP;

	pulsar::dcb::raw_layout raw;
	raw.add<pulsar::dcb::Float3>(pulsar::SKYBOX_MATERIAL_DCB_ALBEDO_COLOR);
	raw.add<pulsar::dcb::Bool>(pulsar::SKYBOX_MATERIAL_DCB_ALBEDO_SRGB);
	raw.add<pulsar::dcb::Float>(pulsar::SKYBOX_MATERIAL_DCB_EXPOSURE);

	this->m_dcb_buffer.set_layout(std::move(raw));
	this->m_dcb_buffer[pulsar::SKYBOX_MATERIAL_DCB_ALBEDO_COLOR] = XMFLOAT3(1.0f, 1.0f, 1.0f);
	this->m_dcb_buffer[pulsar::SKYBOX_MATERIAL_DCB_ALBEDO_SRGB] = true;
	this->m_dcb_buffer[pulsar::SKYBOX_MATERIAL_DCB_EXPOSURE] = 1.0f;

	this->m_cbuffer.set(&this->m_dcb_buffer);
	this->m_cbuffer.set_slot(pulsar::FRAG_SKYBOX_SKYBOX_MATERIAL_SLOT);
	this->set_tex_bind_slots();
}

void	pulsar::skybox_material::set_tex_bind_slots()
{
	this->m_albedo_map.set_slot(pulsar::FRAG_SKYBOX_SKYBOX_MATERIAL_ALBEDO_MAP_SLOT);
	this->m_exposure_map.set_slot(pulsar::FRAG_SKYBOX_SKYBOX_MATERIAL_EXPOSURE_MAP_SLOT);
}

void	pulsar::skybox_material::bind()
{
	if (this->m_cbuffer.is_modified())
		this->m_cbuffer.update();

	this->m_cbuffer.bind();
	this->m_albedo_map.bind();
	this->m_exposure_map.bind();
}

void	pulsar::skybox_material::unbind()
{	
	this->m_exposure_map.unbind();
	this->m_albedo_map.unbind();
	this->m_cbuffer.unbind();
}

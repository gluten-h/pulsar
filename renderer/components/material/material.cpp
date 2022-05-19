
#include "material.h"
#include "config/material.h"
#include "config/shader_texture.h"
#include "shaders/frag_shader.h"


PULSAR::material::material()
{
	this->mp_shader = &PULSAR::OPAQUE_GEOMETRY_G_BUFFER_FS;

	this->m_albedo_map = PULSAR::WHITE_QUAD_TEXTURE;
	this->m_normal_map = PULSAR::NORMAL_QUAD_TEXTURE;
	this->m_roughness_map = PULSAR::WHITE_QUAD_TEXTURE;
	this->m_metalness_map = PULSAR::WHITE_QUAD_TEXTURE;
	this->m_ao_map = PULSAR::WHITE_QUAD_TEXTURE;
	this->m_exposure_map = PULSAR::WHITE_QUAD_TEXTURE;

	PULSAR::dcb::raw_layout raw;
	raw.add<PULSAR::dcb::Float3>(MATERIAL_DCB_ALBEDO_COLOR);
	raw.add<PULSAR::dcb::Bool>(MATERIAL_DCB_ALBEDO_MAP_SRGB);
	raw.add<PULSAR::dcb::Float>(MATERIAL_DCB_NORMAL_FACTOR);
	raw.add<PULSAR::dcb::Float>(MATERIAL_DCB_ROUGHNESS);
	raw.add<PULSAR::dcb::Float>(MATERIAL_DCB_METALNESS);
	raw.add<PULSAR::dcb::Float>(MATERIAL_DCB_AO);
	raw.add<PULSAR::dcb::Float>(MATERIAL_DCB_EXPOSURE);

	this->m_dcb_buffer.set_layout(std::move(raw));
	this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_COLOR] = XMFLOAT3(1.0f, 1.0f, 1.0f);
	this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_MAP_SRGB] = true;
	this->m_dcb_buffer[MATERIAL_DCB_NORMAL_FACTOR] = 1.0f;
	this->m_dcb_buffer[MATERIAL_DCB_ROUGHNESS] = 1.0f;
	this->m_dcb_buffer[MATERIAL_DCB_METALNESS] = 1.0f;
	this->m_dcb_buffer[MATERIAL_DCB_AO] = 0.0f;
	this->m_dcb_buffer[MATERIAL_DCB_EXPOSURE] = 1.0f;

	this->m_cbuffer.set_dcb_buffer(&this->m_dcb_buffer);
	this->m_cbuffer.set_slot(MATERIAL_SLOT);
	this->set_tex_bind_slots();
}

void	PULSAR::material::set_tex_bind_slots()
{
	this->m_albedo_map.set_slot(MATERIAL_ALBEDO_MAP_SLOT);
	this->m_normal_map.set_slot(MATERIAL_NORMAL_MAP_SLOT);
	this->m_roughness_map.set_slot(MATERIAL_ROUGHNESS_MAP_SLOT);
	this->m_metalness_map.set_slot(MATERIAL_METALNESS_MAP_SLOT);
	this->m_ao_map.set_slot(MATERIAL_AO_MAP_SLOT);
	this->m_exposure_map.set_slot(MATERIAL_EXPOSURE_MAP_SLOT);
}

void	PULSAR::material::set_shader(PULSAR::frag_shader *shader)
{
	this->mp_shader = shader;
}

void	PULSAR::material::bind()
{
	if (this->m_cbuffer.is_modified())
		this->m_cbuffer.update();
	
	this->m_cbuffer.bind();
	this->mp_shader->bind();

	this->m_albedo_map.bind();
	this->m_normal_map.bind();
	this->m_roughness_map.bind();
	this->m_metalness_map.bind();
	this->m_ao_map.bind();
	this->m_exposure_map.bind();
}


#include "material.h"
#include "config/config.h"
#include "config/shader_texture.h"
#include "config/cubemap.h"
#include "config/shader.h"
#include "gfx_resources/frag_shader.h"


pulsar::material::material()
{
	this->mp_shader = &pulsar::OPAQUE_GEOMETRY_G_BUFFER_FS;

	this->m_albedo_map = pulsar::WHITE_QUAD_TEXTURE;
	this->m_normal_map = pulsar::NORMAL_QUAD_TEXTURE;
	this->m_roughness_map = pulsar::WHITE_QUAD_TEXTURE;
	this->m_metalness_map = pulsar::WHITE_QUAD_TEXTURE;
	this->m_ao_map = pulsar::WHITE_QUAD_TEXTURE;
	this->m_exposure_map = pulsar::WHITE_QUAD_TEXTURE;
	this->m_irradiance_map = pulsar::BLACK_CUBEMAP;

	pulsar::dcb::raw_layout raw;
	raw.add<pulsar::dcb::Float3>(pulsar::MATERIAL_DCB_ALBEDO_COLOR);
	raw.add<pulsar::dcb::Bool>(pulsar::MATERIAL_DCB_ALBEDO_MAP_SRGB);
	raw.add<pulsar::dcb::Float>(pulsar::MATERIAL_DCB_NORMAL_FACTOR);
	raw.add<pulsar::dcb::Float>(pulsar::MATERIAL_DCB_ROUGHNESS);
	raw.add<pulsar::dcb::Float>(pulsar::MATERIAL_DCB_METALNESS);
	raw.add<pulsar::dcb::Float>(pulsar::MATERIAL_DCB_AO);
	raw.add<pulsar::dcb::Float>(pulsar::MATERIAL_DCB_EXPOSURE);
	raw.add<pulsar::dcb::Float3>(pulsar::MATERIAL_DCB_IRRADIANCE_COLOR);

	this->m_dcb_buffer.set_layout(std::move(raw));
	this->m_dcb_buffer[pulsar::MATERIAL_DCB_ALBEDO_COLOR] = XMFLOAT3(1.0f, 1.0f, 1.0f);
	this->m_dcb_buffer[pulsar::MATERIAL_DCB_ALBEDO_MAP_SRGB] = true;
	this->m_dcb_buffer[pulsar::MATERIAL_DCB_NORMAL_FACTOR] = 1.0f;
	this->m_dcb_buffer[pulsar::MATERIAL_DCB_ROUGHNESS] = 1.0f;
	this->m_dcb_buffer[pulsar::MATERIAL_DCB_METALNESS] = 1.0f;
	this->m_dcb_buffer[pulsar::MATERIAL_DCB_AO] = 1.0f;
	this->m_dcb_buffer[pulsar::MATERIAL_DCB_EXPOSURE] = 1.0f;
	this->m_dcb_buffer[pulsar::MATERIAL_DCB_IRRADIANCE_COLOR] = XMFLOAT3(1.0f, 1.0f, 1.0f);

	this->m_cbuffer.set(&this->m_dcb_buffer);
	this->m_cbuffer.set_slot(pulsar::FRAG_G_BUFFER_MATERIAL_SLOT);
	this->set_tex_bind_slots();
}

void	pulsar::material::set_tex_bind_slots()
{
	this->m_albedo_map.set_slot(pulsar::FRAG_G_BUFFER_MATERIAL_ALBEDO_MAP_SLOT);
	this->m_normal_map.set_slot(pulsar::FRAG_G_BUFFER_MATERIAL_NORMAL_MAP_SLOT);
	this->m_roughness_map.set_slot(pulsar::FRAG_G_BUFFER_MATERIAL_ROUGHNESS_MAP_SLOT);
	this->m_metalness_map.set_slot(pulsar::FRAG_G_BUFFER_MATERIAL_METALNESS_MAP_SLOT);
	this->m_ao_map.set_slot(pulsar::FRAG_G_BUFFER_MATERIAL_AO_MAP_SLOT);
	this->m_exposure_map.set_slot(pulsar::FRAG_G_BUFFER_MATERIAL_EXPOSURE_MAP_SLOT);
	this->m_irradiance_map.set_slot(pulsar::FRAG_G_BUFFER_MATERIAL_IRRADIANCE_MAP_SLOT);
}

void	pulsar::material::set_shader(pulsar::frag_shader *shader)
{
	this->mp_shader = shader;
}

void	pulsar::material::bind()
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
	this->m_irradiance_map.bind();
}

void	pulsar::material::unbind()
{
	this->m_irradiance_map.unbind();
	this->m_exposure_map.unbind();
	this->m_ao_map.unbind();
	this->m_metalness_map.unbind();
	this->m_roughness_map.unbind();
	this->m_normal_map.unbind();
	this->m_albedo_map.unbind();

	this->mp_shader->unbind();
	this->m_cbuffer.unbind();
}

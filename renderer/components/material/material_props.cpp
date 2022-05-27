
#include "material.h"
#include "config/config.h"


pulsar::shader_texture	&pulsar::material::albedo_map()
{
	return (this->m_albedo_map);
}

pulsar::dcb::layout_elem_ref	pulsar::material::albedo_color()
{
	return (this->m_dcb_buffer[pulsar::MATERIAL_DCB_ALBEDO_COLOR]);
}

pulsar::dcb::layout_elem_ref	pulsar::material::albedo_map_srgb()
{
	return (this->m_dcb_buffer[pulsar::MATERIAL_DCB_ALBEDO_MAP_SRGB]);
}

pulsar::shader_texture	&pulsar::material::normal_map()
{
	return (this->m_normal_map);
}

pulsar::dcb::layout_elem_ref	pulsar::material::normal_factor()
{
	return (this->m_dcb_buffer[pulsar::MATERIAL_DCB_NORMAL_FACTOR]);
}

pulsar::shader_texture	&pulsar::material::roughness_map()
{
	return (this->m_roughness_map);
}

pulsar::dcb::layout_elem_ref	pulsar::material::roughness()
{
	return (this->m_dcb_buffer[pulsar::MATERIAL_DCB_ROUGHNESS]);
}

pulsar::shader_texture	&pulsar::material::metalness_map()
{
	return (this->m_metalness_map);
}

pulsar::dcb::layout_elem_ref	pulsar::material::metalness()
{
	return (this->m_dcb_buffer[pulsar::MATERIAL_DCB_METALNESS]);
}

pulsar::shader_texture	&pulsar::material::ao_map()
{
	return (this->m_ao_map);
}

pulsar::dcb::layout_elem_ref	pulsar::material::ao()
{
	return (this->m_dcb_buffer[pulsar::MATERIAL_DCB_AO]);
}

pulsar::shader_texture	&pulsar::material::exposure_map()
{
	return (this->m_exposure_map);
}

pulsar::dcb::layout_elem_ref	pulsar::material::exposure()
{
	return (this->m_dcb_buffer[pulsar::MATERIAL_DCB_EXPOSURE]);
}

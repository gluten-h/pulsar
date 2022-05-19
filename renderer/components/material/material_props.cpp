
#include "material.h"
#include "config/material.h"


PULSAR::shader_texture	&PULSAR::material::albedo_map()
{
	return (this->m_albedo_map);
}

PULSAR::dcb::layout_elem_ref	PULSAR::material::albedo_color()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_COLOR]);
}

PULSAR::dcb::layout_elem_ref	PULSAR::material::albedo_map_srgb()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_MAP_SRGB]);
}

PULSAR::shader_texture	&PULSAR::material::normal_map()
{
	return (this->m_normal_map);
}

PULSAR::dcb::layout_elem_ref	PULSAR::material::normal_factor()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_NORMAL_FACTOR]);
}

PULSAR::shader_texture	&PULSAR::material::roughness_map()
{
	return (this->m_roughness_map);
}

PULSAR::dcb::layout_elem_ref	PULSAR::material::roughness()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_ROUGHNESS]);
}

PULSAR::shader_texture	&PULSAR::material::metalness_map()
{
	return (this->m_metalness_map);
}

PULSAR::dcb::layout_elem_ref	PULSAR::material::metalness()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_METALNESS]);
}

PULSAR::shader_texture	&PULSAR::material::ao_map()
{
	return (this->m_ao_map);
}

PULSAR::dcb::layout_elem_ref	PULSAR::material::ao()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_AO]);
}

PULSAR::shader_texture	&PULSAR::material::exposure_map()
{
	return (this->m_exposure_map);
}

PULSAR::dcb::layout_elem_ref	PULSAR::material::exposure()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_EXPOSURE]);
}

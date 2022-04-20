
#include "material.h"


PULSAR::TEXTURE		&PULSAR::MATERIAL::albedo_map()
{
	return (this->m_albedo_map);
}
PULSAR::dcb::layout_elem_ref	PULSAR::MATERIAL::albedo_color()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_COLOR]);
}
PULSAR::dcb::layout_elem_ref	PULSAR::MATERIAL::albedo_map_srgb()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_MAP_SRGB]);
}

PULSAR::TEXTURE		&PULSAR::MATERIAL::normal_map()
{
	return (this->m_normal_map);
}
PULSAR::dcb::layout_elem_ref	PULSAR::MATERIAL::normal_factor()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_NORMAL_FACTOR]);
}

PULSAR::TEXTURE		&PULSAR::MATERIAL::roughness_map()
{
	return (this->m_roughness_map);
}
PULSAR::dcb::layout_elem_ref	PULSAR::MATERIAL::roughness()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_ROUGHNESS]);
}

PULSAR::TEXTURE		&PULSAR::MATERIAL::metalness_map()
{
	return (this->m_metalness_map);
}
PULSAR::dcb::layout_elem_ref	PULSAR::MATERIAL::metalness()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_METALNESS]);
}

PULSAR::TEXTURE		&PULSAR::MATERIAL::ao_map()
{
	return (this->m_ao_map);
}
PULSAR::dcb::layout_elem_ref	PULSAR::MATERIAL::ao()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_AO]);
}

PULSAR::TEXTURE		&PULSAR::MATERIAL::exposure_map()
{
	return (this->m_exposure_map);
}
PULSAR::dcb::layout_elem_ref	PULSAR::MATERIAL::exposure()
{
	return (this->m_dcb_buffer[MATERIAL_DCB_EXPOSURE]);
}

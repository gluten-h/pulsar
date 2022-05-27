
#include "skybox_material.h"
#include "config/config.h"


pulsar::cubemap		&pulsar::skybox_material::albedo_map()
{
	return (this->m_albedo_map);
}

pulsar::dcb::layout_elem_ref	pulsar::skybox_material::albedo_color()
{
	return (this->m_dcb_buffer[pulsar::SKYBOX_MATERIAL_DCB_ALBEDO_COLOR]);
}

pulsar::dcb::layout_elem_ref	pulsar::skybox_material::albedo_map_srgb()
{
	return (this->m_dcb_buffer[pulsar::SKYBOX_MATERIAL_DCB_ALBEDO_SRGB]);
}

pulsar::cubemap	&pulsar::skybox_material::exposure_map()
{
	return (this->m_exposure_map);
}

pulsar::dcb::layout_elem_ref	pulsar::skybox_material::exposure()
{
	return (this->m_dcb_buffer[pulsar::SKYBOX_MATERIAL_DCB_EXPOSURE]);
}


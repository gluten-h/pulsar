//
//#include "skybox.h"
//
//
//void		PULSAR::SKYBOX::copy_assign(const SKYBOX &s)
//{
//	this->env_map = s.env_map;
//	this->mesh = s.mesh;
//}
//
//
//PULSAR::SKYBOX		&PULSAR::SKYBOX::operator=(const SKYBOX &s)
//{
//	this->copy_assign(s);
//
//	return (*this);
//}
//
//PULSAR::SKYBOX::SKYBOX(const SKYBOX &s)
//{
//	this->copy_assign(s);
//}
//
//PULSAR::SKYBOX::SKYBOX()
//{
//	D3D11_INPUT_ELEMENT_DESC ied[] =
//	{
//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//	};
//	SKYBOX::input_layout.set(PULSAR::SKYBOX::vs.get_shader_blob(), ied, (UINT)std::size(ied));
//}

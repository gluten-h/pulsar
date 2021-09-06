
#include "cubemap.h"


void		PULSAR::CUBEMAP::copy_assign(const PULSAR::CUBEMAP &c)
{
	this->tex2d = c.tex2d;
	this->cubemap_srv = c.cubemap_srv;
	this->slot = c.slot;

	if (this->tex2d)
		this->tex2d->AddRef();
	if (this->cubemap_srv)
		this->cubemap_srv->AddRef();
}


PULSAR::CUBEMAP &PULSAR::CUBEMAP::operator=(const PULSAR::CUBEMAP &c)
{
	if (this->tex2d != c.tex2d)
		this->remove_tex2d_memory();
	if (this->cubemap_srv != c.cubemap_srv)
		this->remove_cubemap_srv_memory();
	this->copy_assign(c);

	return (*this);
}

PULSAR::CUBEMAP::CUBEMAP(const PULSAR::CUBEMAP &c) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::CUBEMAP;
	this->copy_assign(c);
}

PULSAR::CUBEMAP::CUBEMAP() : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::CUBEMAP;
}

PULSAR::CUBEMAP::CUBEMAP(LPCWSTR *wic_path, LPCWSTR output_dds_path, PULSAR::CUBEMAP_DDS dds_behavior, UINT slot) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::CUBEMAP;

	this->set(wic_path, output_dds_path, dds_behavior);
	this->set_slot(slot);
}

PULSAR::CUBEMAP::CUBEMAP(LPCWSTR dds_path, UINT slot) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::CUBEMAP;

	this->set_cubemap_memory(dds_path);
	this->set_slot(slot);
}

PULSAR::CUBEMAP::~CUBEMAP()
{
	this->remove_cubemap_memory();
}

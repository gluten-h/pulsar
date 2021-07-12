
#include "grng_cubemap.h"


void		grng_cubemap::copy_assign(const grng_cubemap &c)
{
	this->tex2d = c.tex2d;
	this->cubemap_srv = c.cubemap_srv;
	this->slot = c.slot;

	if (this->tex2d)
		this->tex2d->AddRef();
	if (this->cubemap_srv)
		this->cubemap_srv->AddRef();
}


grng_cubemap	&grng_cubemap::operator=(const grng_cubemap &c)
{
	if (this->tex2d != c.tex2d)
		this->remove_tex2d_memory();
	if (this->cubemap_srv != c.cubemap_srv)
		this->remove_cubemap_srv_memory();
	this->copy_assign(c);

	return (*this);
}

grng_cubemap::grng_cubemap(const grng_cubemap &c) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::CUBEMAP;
	this->copy_assign(c);
}

grng_cubemap::grng_cubemap() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::CUBEMAP;
}

grng_cubemap::grng_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path, GRNG_CUBEMAP_DDS dds_behavior, UINT slot) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::CUBEMAP;

	this->set(wic_path, output_dds_path, dds_behavior);
	this->set_slot(slot);
}

grng_cubemap::grng_cubemap(LPCWSTR dds_path, UINT slot) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::CUBEMAP;

	this->set_cubemap_memory(dds_path);
	this->set_slot(slot);
}

grng_cubemap::~grng_cubemap()
{
	this->remove_cubemap_memory();
}

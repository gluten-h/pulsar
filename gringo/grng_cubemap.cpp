
#include "grng_cubemap.h"


void		grng_cubemap::copy_assign(const grng_cubemap &c)
{
	this->cubemap_srv = c.cubemap_srv;
	this->slot = c.slot;
	if (this->cubemap_srv)
		this->cubemap_srv->AddRef();
}


grng_cubemap	&grng_cubemap::operator=(const grng_cubemap &c)
{
	if (this->cubemap_srv != c.cubemap_srv)
		this->remove_cubemap_memory();
	this->copy_assign(c);

	return (*this);
}

grng_cubemap::grng_cubemap(const grng_cubemap &c) : GRNG_BINDABLE()
{
	this->copy_assign(c);
}

grng_cubemap::grng_cubemap() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::CUBEMAP;
}

grng_cubemap::grng_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path, UINT slot) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::CUBEMAP;

	this->create_dds_cubemap(wic_path, output_dds_path);
	this->set_cubemap_memory(output_dds_path);
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


#include "grng_viewport.h"


void				grng_viewport::copy_assign(const grng_viewport &v)
{
	this->viewport = v.viewport;
}


grng_viewport		&grng_viewport::operator=(const grng_viewport &v)
{
	this->copy_assign(v);

	return (*this);
}

grng_viewport::grng_viewport(const grng_viewport &v) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::VIEWPORT;
	this->copy_assign(v);
}

grng_viewport::grng_viewport() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::VIEWPORT;
}

grng_viewport::grng_viewport(float width, float height, float min_depth, float max_depth) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::VIEWPORT;
	this->set_viewport_memory(width, height, min_depth, max_depth);
}

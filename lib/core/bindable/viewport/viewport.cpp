
#include "viewport.h"


void		PULSAR::VIEWPORT::copy_assign(const VIEWPORT &v)
{
	this->viewport = v.viewport;
}


PULSAR::VIEWPORT		&PULSAR::VIEWPORT::operator=(const VIEWPORT &v)
{
	this->copy_assign(v);

	return (*this);
}

PULSAR::VIEWPORT::VIEWPORT(const VIEWPORT &v) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::VIEWPORT;
	this->copy_assign(v);
}

PULSAR::VIEWPORT::VIEWPORT() : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::VIEWPORT;
}

PULSAR::VIEWPORT::VIEWPORT(float width, float height, float min_depth, float max_depth) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::VIEWPORT;
	this->set_viewport_memory(width, height, min_depth, max_depth);
}

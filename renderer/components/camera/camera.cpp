
#include "camera.h"


PULSAR::camera::camera(const XMMATRIX &projection)
{
	this->m_projection = projection;
}

const XMMATRIX	&PULSAR::camera::projection() const
{
	return (this->m_projection);
}

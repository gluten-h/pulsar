
#include "camera.h"


pulsar::camera::camera(const XMMATRIX &projection)
{
	this->m_projection = projection;
}

const XMMATRIX	&pulsar::camera::get_projection() const
{
	return (this->m_projection);
}

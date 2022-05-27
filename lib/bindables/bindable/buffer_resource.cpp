
#include "buffer_resource.h"


void	pulsar::buffer_resource::resize_linked(UINT width, UINT height)
{
	for (buffer_resource *br : this->m_linked_buffer_resources)
		br->resize(width, height);
}

void	pulsar::buffer_resource::clear_linked()
{
	for (buffer_resource *br : this->m_linked_buffer_resources)
		br->clear();
}

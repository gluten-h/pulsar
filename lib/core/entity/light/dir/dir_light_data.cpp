
#include "dir_light.h"


void		PULSAR::DIR_LIGHT::set_params(const XMFLOAT3 &dir, const XMFLOAT3 &color)
{
	XMVECTOR dir_vec = XMVector3NormalizeEst(XMVectorSet(dir.x, dir.y, dir.z, 1.0f));

	this->dir = XMFLOAT3(XMVectorGetX(dir_vec), XMVectorGetY(dir_vec), XMVectorGetZ(dir_vec));
	this->color = color;
}

void		PULSAR::DIR_LIGHT::set_shader_light(PULSAR::SHADER_LIGHT &sl)
{
	sl.type = (int)this->light_type;

	sl.dir = this->dir;
	sl.color = this->color;
}

void		PULSAR::DIR_LIGHT::set(const XMFLOAT3 &dir, const XMFLOAT3 &color)
{
	this->set_params(dir, color);
}

void		PULSAR::DIR_LIGHT::set_dir(const XMFLOAT3 &dir)
{
	this->set_params(dir, this->color);
}

void		PULSAR::DIR_LIGHT::set_color(const XMFLOAT3 &color)
{
	this->color = color;
}


PULSAR::DIR_LIGHT		*PULSAR::DIR_LIGHT::create()
{
	return ((PULSAR::DIR_LIGHT*)PULSAR::LIGHT::add_to_manager(new PULSAR::DIR_LIGHT));
}

void		PULSAR::DIR_LIGHT::destroy()
{
	if (!this->is_alloc)
		return;
	this->is_alloc = false;

	for (auto &it : this->scene_local_id)
	{
		PULSAR::SCENE *scene_ptr = PULSAR::SCENE_MANAGER::get_instance().get_elem(it.first);
		if (scene_ptr)
			scene_ptr->remove_light(it.second);
	}
	this->scene_local_id.clear();

	PULSAR::LIGHT_MANAGER::get_instance().remove(this);
	delete this;
}


#include "grng_dir_light.h"


void			grng_dir_light::set_params(const XMFLOAT3 &dir, const XMFLOAT3 &color)
{
	XMVECTOR dir_vec = XMVector3NormalizeEst(XMVectorSet(dir.x, dir.y, dir.z, 1.0f));

	this->dir = XMFLOAT3(XMVectorGetX(dir_vec), XMVectorGetY(dir_vec), XMVectorGetZ(dir_vec));
	this->color = color;
}

void			grng_dir_light::set_shader_light(GRNG_SHADER_LIGHT &sl)
{
	sl.type = (int)this->light_type;

	sl.dir = this->dir;
	sl.color = this->color;
}

void			grng_dir_light::set(const XMFLOAT3 &dir, const XMFLOAT3 &color)
{
	this->set_params(dir, color);
}

void			grng_dir_light::set_dir(const XMFLOAT3 &dir)
{
	this->set_params(dir, this->color);
}

void			grng_dir_light::set_color(const XMFLOAT3 &color)
{
	this->color = color;
}


grng_dir_light	*grng_dir_light::create()
{
	grng_dir_light *dl = new grng_dir_light;
	dl->id = GRNG_LM.add(dl);
	if (dl->id == -1)
	{
		delete dl;
		return (NULL);
	}
	dl->is_alloc = true;

	return (dl);
}

void			grng_dir_light::destroy()
{
	if (!this->is_alloc)
		return;
	this->is_alloc = false;

	for (auto &it : this->scene_local_id)
	{
		GRNG_SCENE *scene = GRNG_SM.get_data_secure(it.first);
		if (scene)
			scene->remove_light(it.second);
	}
	this->scene_local_id.clear();

	GRNG_LM.remove_secure(this);
	delete this;
}

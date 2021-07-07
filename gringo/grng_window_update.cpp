
#include "grng_window.h"


void		grng_window::update()
{
	GRNG_GFX::set_curr_win_event(this->win_id, this->hwnd);
	if (this->curr_camera)
		GRNG_GFX::set_curr_camera_event(this->curr_camera);

	for (auto &it : this->win_update)
		it.first(it.second);
}

void		grng_window::add_update(GRNG_WIN_UPDATE_DEF win_update, void *win_update_data)
{
	this->win_update[win_update] = win_update_data;
}

void		grng_window::remove_update(GRNG_WIN_UPDATE_DEF win_update)
{
	this->win_update.erase(win_update);
}

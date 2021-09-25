
#include "window.h"


void		PULSAR::WINDOW::update()
{
	PULSAR::GFX::set_curr_win_event(this, this->hwnd);
	if (this->curr_camera)
		PULSAR::GFX::set_curr_camera_event(this->curr_camera);

	for (auto &it : this->win_update)
		it.first(it.second);
}

void		PULSAR::WINDOW::add_update(PULSAR::WIN_UPDATE_DEF win_update, void *win_update_data)
{
	this->win_update[win_update] = win_update_data;
}

void		PULSAR::WINDOW::remove_update(PULSAR::WIN_UPDATE_DEF win_update)
{
	this->win_update.erase(win_update);
}

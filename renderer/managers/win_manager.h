#pragma once


#include "pulsar_id3d.h"
#include "manager.h"
#include "def_window.h"
#include "fixed_vector.h"
#include "gfx.h"
#include "pulsar_input.h"

#include <algorithm>
#include <unordered_map>
#include <mutex>


namespace PULSAR
{
	class WINDOW;

	class WIN_MANAGER : public PULSAR::PULSAR_ID3D, public PULSAR::MANAGER<PULSAR::WINDOW, PULSAR::MAX_WIN_COUNT>
	{
	public:
		static WIN_MANAGER	&get_instance()
		{
			static WIN_MANAGER win_manager;
			return (win_manager);
		}

		int		add(WINDOW *win)
		{
			if (!this->is_available(win))
				return (-1);
			
			return (this->add_manager(win));
		}
	};
}

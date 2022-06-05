#pragma once

#include "script.h"


namespace pulsar
{
	struct script_component
	{
		pulsar::script *script = NULL;

		script_component() = default;
		script_component(pulsar::script *script)
		{
			this->script = script;
		}
		~script_component() = default;
	};
}

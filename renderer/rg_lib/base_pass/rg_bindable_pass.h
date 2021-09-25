#pragma once

#include "rg_pass.h"
#include "render_target.h"
#include "depth_stencil_view.h"

#include <unordered_set>


namespace PULSAR
{
	class RG_BINDABLE_PASS : public PULSAR::RG_PASS
	{
	private:
		PULSAR::RENDER_TARGET			*render_target = NULL;
		PULSAR::DEPTH_STENCIL_VIEW		*ds_view = NULL;

		std::unordered_set<PULSAR::BINDABLE*>	bindables;

	public:
		RG_BINDABLE_PASS(const std::string &name) : PULSAR::RG_PASS(name){ }

		void	add_bindable(PULSAR::BINDABLE *bindable)
		{
			this->bindables.insert(bindable);
		}

		void	bind() const
		{
			this->render_target->bind(PULSAR::BIND_SCOPE::GLOBAL);
			if (this->ds_view)
				this->ds_view->bind(PULSAR::BIND_SCOPE::GLOBAL);

			for (auto &b : this->bindables)
				b->bind(PULSAR::BIND_SCOPE::GLOBAL);
		}

		void	validate() const override
		{
			PULSAR::RG_PASS::validate();
			if (!this->render_target)
				THROW_RG_EXC("RG_BINDABLE_PASS " + this->get_name() + ": Render Target is NULL");
		}
	};
}

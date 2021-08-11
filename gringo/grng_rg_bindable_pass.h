#pragma once

#include "grng_rg_pass.h"
#include "grng_render_target.h"
#include "grng_depth_stencil_view.h"

#include <unordered_set>


class grng_rg_bindable_pass : public GRNG_RG_PASS
{
private:
	GRNG_RENDER_TARGET			*render_target = NULL;
	GRNG_DEPTH_STENCIL_VIEW		*ds_view = NULL;

	std::unordered_set<GRNG_BINDABLE*>		bindables;

public:
	grng_rg_bindable_pass(){ }
	grng_rg_bindable_pass(const std::string &name) : GRNG_RG_PASS(name){ }

	void		add_bindable(GRNG_BINDABLE *bindable)
	{
		this->bindables.insert(bindable);
	}

	void		bind() const
	{
		this->render_target->bind(GRNG_BIND_SCOPE::GLOBAL);
		if (this->ds_view)
			this->ds_view->bind(GRNG_BIND_SCOPE::GLOBAL);

		for (auto &b : this->bindables)
			b->bind(GRNG_BIND_SCOPE::GLOBAL);
	}

	void		validate() const override
	{
		GRNG_RG_PASS::validate();
		if (!this->render_target)
			GRNG_THROW_RG_EXC("GRNG_RG_BINDABLE_PASS " + this->get_name() + ": Render Target is NULL");
	}
};

using GRNG_RG_BINDABLE_PASS = grng_rg_bindable_pass;

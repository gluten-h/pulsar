#pragma once

#include "bindable/bindable.h"


namespace PULSAR
{
	class viewport : public PULSAR::bindable
	{
	private:
		D3D11_VIEWPORT m_viewport = { 0 };

	private:
		void	create_viewport(UINT width, UINT height, float min_depth, float max_depth);

	public:
		viewport &operator=(const viewport&) = delete;
		viewport &operator=(viewport&) = delete;
		viewport(const viewport&) = delete;
		viewport(viewport&&) = delete;
		viewport() = default;
		viewport(UINT width, UINT height, float min_depth = 0.0f, float max_depth = 1.0f);
		~viewport() = default;

		void	set(UINT width, UINT height, float min_depth = 0.0f, float max_depth = 1.0f);
		D3D11_VIEWPORT	&get();

		void	bind() const override;
		void	unbind() const override;
	};
}

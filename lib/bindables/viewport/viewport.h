#pragma once

#include "bindable/bindable.h"
#include "bindable/buffer_resource.h"


namespace pulsar
{
	class viewport : public pulsar::bindable, public pulsar::buffer_resource
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

		void	resize(UINT width, UINT height) override;
		void	clear() override;

		void	bind() const;
		void	unbind() const;
	};
}

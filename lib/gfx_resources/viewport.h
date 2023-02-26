#pragma once

#include "sync_resource.h"


namespace pulsar
{
	class viewport : public pulsar::sync_resource
	{
	private:
		D3D11_VIEWPORT m_viewport{ 0 };

		void	create_viewport(UINT top_left_x, UINT top_left_y, UINT width, UINT height, float min_depth, float max_depth);

	protected:
		void	resize_resource(UINT width, UINT height) override;

	public:
		viewport &operator=(const viewport&) = delete;
		viewport &operator=(viewport&) = delete;
		viewport(const viewport&) = delete;
		viewport(viewport&&) = delete;
		viewport() = default;
		viewport(UINT width, UINT height, float min_depth = 0.0f, float max_depth = 1.0f);
		viewport(D3D11_RECT *rect, float min_depth = 0.0f, float max_depth = 1.0f);
		~viewport() = default;

		void	set(UINT width, UINT height, float min_depth = 0.0f, float max_depth = 1.0f);
		void	set(D3D11_RECT *rect, float min_depth = 0.0f, float max_depth = 1.0f);

		XMUINT2	size() const;

		void	bind() const;
		void	unbind() const;
	};
}

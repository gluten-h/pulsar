#pragma once

#include "utils/math.h"
#include "const_buffers/vert_const_buffer.h"


namespace pulsar
{
	struct shader_transform
	{
		XMMATRIX model;
		XMMATRIX norm;
	};

	class transform
	{
	private:
		using cbuffer = pulsar::vert_const_buffer<pulsar::shader_transform>;

		XMMATRIX m_mat = XMMatrixIdentity();

		mutable pulsar::shader_transform m_shader_transform;
		mutable cbuffer m_transform_cbuffer;

	private:
		void	init_cbuffer();

	public:
		transform &operator=(const transform&);
		transform &operator=(transform&&) = delete;
		transform(const transform&);
		transform(transform&&) = delete;
		transform();
		~transform() = default;

		const XMMATRIX	&get_matrix() const;
		void	set_matrix(const XMMATRIX &matrix);

		XMFLOAT3	get_position() const;
		void	set_position(const XMFLOAT3 &pos);

		XMFLOAT3	forward() const;
		XMFLOAT3	right() const;
		XMFLOAT3	up() const;

		void	bind() const;
		void	unbind() const;
	};
}

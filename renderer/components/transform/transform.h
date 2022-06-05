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

		XMFLOAT3 m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3 m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3 m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

		mutable pulsar::shader_transform m_shader_transform;
		mutable cbuffer m_transform_cbuffer;

	private:
		void	init_cbuffer();
		void	construct_matrix();

	public:
		transform &operator=(const transform&);
		transform &operator=(transform&&) = delete;
		transform(const transform&);
		transform(transform&&) = delete;
		transform();
		~transform() = default;

		const XMMATRIX	&get_matrix() const;
		const XMFLOAT3	&get_position() const;
		const XMFLOAT3	&get_rotation() const;
		const XMFLOAT3	&get_scale() const;

		void	set_position(const XMVECTOR &pos);
		void	set_position(const XMFLOAT3 &pos);
		void	set_rotation(const XMVECTOR &rot);
		void	set_rotation(const XMFLOAT3 &rot);
		void	set_scale(const XMVECTOR &scale);
		void	set_scale(const XMFLOAT3 &scale);

		XMFLOAT3	forward() const;
		XMFLOAT3	right() const;
		XMFLOAT3	up() const;

		void	bind() const;
		void	unbind() const;
	};
}

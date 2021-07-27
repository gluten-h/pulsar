#pragma once

#include "grng_component.h"
#include "grng_transform.h"
#include "grng_const_buffers.h"
#include "grng_camera_deferred_shader.h"
#include "grng_camera_post_effects_shader.h"
#include "grng_deffered_def.h"


class grng_camera : public GRNG_COMPONENT
{
private:
	friend class grng_manager_ptr;
	friend class grng_window;

private:
	GRNG_TRANSFORM		transform;
	XMFLOAT3			forward = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3			right = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3			up = XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMMATRIX			view_matrix = XMMatrixIdentity();
	XMMATRIX			proj_matrix = XMMatrixIdentity();

	float				fov_rad = 1.57f;
	float				z_near = 0.0f;
	float				z_far = 1000.0f;

	float				exposure = 1.0f;
	float				gamma = 2.2f;


	static GRNG_FRAG_CONST_BUFFER<GRNG_CAMERA_DEFERRED_SHADER>		cam_deferred_cbuffer;
	static GRNG_CAMERA_DEFERRED_SHADER								cam_deferred_shader;

	static GRNG_FRAG_CONST_BUFFER<GRNG_CAMERA_POST_EFFECTS_SHADER>	cam_post_effects_cbuffer;
	static GRNG_CAMERA_POST_EFFECTS_SHADER							cam_post_effects_shader;


	void		update_view_matrix();
	void		update_proj_matrix(float w, float h);
	void		update_camera_deferred_shader();
	void		update_camera_post_effects_shader();
	void		update(float w, float h);

	static GRNG_COMPONENT		*create_manager_ptr();

	void			copy_assign(const grng_camera &c);

public:
	grng_camera		&operator=(const grng_camera &c);
	grng_camera(const grng_camera &c);
	grng_camera();
	grng_camera(const GRNG_TRANSFORM &transform, float fov_rad, float z_near, float z_far, float exposure = 1.0f, float gamma = 2.2f);

	void		set(const GRNG_TRANSFORM &transform, float fov_rad, float z_near = 0.001f, float z_far = D3D11_FLOAT32_MAX, float exposure = 1.0f, float gamma = 2.2f);

	const XMMATRIX		&get_view_matrix() const;
	const XMMATRIX		&get_proj_matrix() const;
	const XMFLOAT3		&get_position() const;
	const XMFLOAT3		&get_forward() const;
	const XMFLOAT3		&get_right() const;
	const XMFLOAT3		&get_up() const;
	GRNG_TRANSFORM		&get_transform();

	void				set_z_near(float z_near);
	void				set_z_far(float z_far);
	void				set_exposure(float exposure);
	void				set_gamma(float gamma);

	float				get_z_near() const;
	float				get_z_far() const;
	float				get_gamma() const;

	void		bind_deferred()
	{
		this->update_camera_deferred_shader();
	}

	void		bind_post_effects()
	{
		this->update_camera_post_effects_shader();
	}
};

using GRNG_CAMERA = grng_camera;

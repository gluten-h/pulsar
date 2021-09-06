#pragma once

#include "component.h"
#include "transform.h"
#include "const_buffers.h"
#include "camera_deferred_shader.h"
#include "camera_post_effects_shader.h"
#include "def_deferred.h"


namespace PULSAR
{
	class CAMERA : public PULSAR::COMPONENT
	{
	private:
		friend class WINDOW;

	private:
		PULSAR::TRANSFORM	transform;
		XMFLOAT3	forward = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3	right = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3	up = XMFLOAT3(0.0f, 0.0f, 0.0f);

		XMMATRIX	view_matrix = XMMatrixIdentity();
		XMMATRIX	proj_matrix = XMMatrixIdentity();

		float	fov_rad = 1.57f;
		float	z_near = 0.0f;
		float	z_far = 1000.0f;

		float	exposure = 1.0f;
		float	gamma = 2.2f;


		static PULSAR::FRAG_CONST_BUFFER<PULSAR::CAMERA_DEFERRED_SHADER>	cam_deferred_cbuffer;
		static PULSAR::CAMERA_DEFERRED_SHADER								cam_deferred_shader;

		static PULSAR::FRAG_CONST_BUFFER<PULSAR::CAMERA_POST_EFFECTS_SHADER>	cam_post_effects_cbuffer;
		static PULSAR::CAMERA_POST_EFFECTS_SHADER								cam_post_effects_shader;


		void	update_view_matrix();
		void	update_proj_matrix(float w, float h);
		void	update_camera_deferred_shader(BIND_SCOPE scope);
		void	update_camera_post_effects_shader(BIND_SCOPE scope);
		void	update(float w, float h);

		void	copy_assign(const CAMERA &c);

	public:
		CAMERA &operator=(const CAMERA &c);
		CAMERA(const CAMERA &c);
		CAMERA();
		CAMERA(const PULSAR::TRANSFORM &transform, float fov_rad, float exposure = 1.0f, float gamma = 2.2f, float z_near = 0.001f, float z_far = D3D11_FLOAT32_MAX);

		void	set(const PULSAR::TRANSFORM &transform, float fov_rad, float exposure = 1.0f, float gamma = 2.2f, float z_near = 0.001f, float z_far = D3D11_FLOAT32_MAX);

		static CAMERA	*create();

		const XMMATRIX &get_view_matrix() const;
		const XMMATRIX &get_proj_matrix() const;
		const XMFLOAT3 &get_position() const;
		const XMFLOAT3 &get_forward() const;
		const XMFLOAT3 &get_right() const;
		const XMFLOAT3 &get_up() const;
		PULSAR::TRANSFORM	&get_transform();

		void	set_z_near(float z_near);
		void	set_z_far(float z_far);
		void	set_exposure(float exposure);
		void	set_gamma(float gamma);

		float	get_z_near() const;
		float	get_z_far() const;
		float	get_gamma() const;

		void	bind_deferred(PULSAR::BIND_SCOPE scope)			//	TODO: TRY TO AVOID SUCH METHODS
		{
			this->update_camera_deferred_shader(scope);
		}

		void	bind_post_effects(PULSAR::BIND_SCOPE scope)
		{
			this->update_camera_post_effects_shader(scope);
		}
	};
}

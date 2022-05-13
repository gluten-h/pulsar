//#pragma once
//
//#include "transform_shader.h"
//#include "vert_const_buffer.h"
//
//
//namespace PULSAR
//{
//	class TRANSFORM
//	{
//	private:
//		friend class CAMERA;
//
//	private:
//		XMMATRIX			transform_matrix = XMMatrixIdentity();
//		static XMMATRIX		cam_view_matrix;
//		static XMMATRIX		cam_proj_matrix;
//
//		static PULSAR::TRANSFORM_SHADER								transform_shader;
//		static PULSAR::VERT_CONST_BUFFER<PULSAR::TRANSFORM_SHADER>	transform_cbuffer;
//
//
//		void	update_transform_matrix()
//		{
//			this->transform_matrix = XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z)
//				* XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z)
//				* XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
//		}
//
//	public:
//		XMFLOAT3	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
//		XMFLOAT3	rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
//		XMFLOAT3	scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
//
//
//		TRANSFORM	&operator=(const TRANSFORM &t)
//		{
//			this->transform_matrix = t.transform_matrix;
//			this->position = t.position;
//			this->rotation = t.rotation;
//			this->scale = t.scale;
//
//			return (*this);
//		}
//		TRANSFORM(const TRANSFORM &t)
//		{
//			this->transform_matrix = t.transform_matrix;
//			this->position = t.position;
//			this->rotation = t.rotation;
//			this->scale = t.scale;
//		}
//		TRANSFORM(){ }
//		TRANSFORM(const XMFLOAT3 &position, const XMFLOAT3 &rotation, const XMFLOAT3 &scale)
//		{
//			this->position = position;
//			this->rotation = rotation;
//			this->scale = scale;
//		}
//
//		void	bind(BIND_SCOPE scope)
//		{
//			this->update_transform_matrix();
//			PULSAR::TRANSFORM::transform_shader.model = this->transform_matrix;
//			PULSAR::TRANSFORM::transform_shader.view = PULSAR::TRANSFORM::cam_view_matrix;
//			PULSAR::TRANSFORM::transform_shader.proj = PULSAR::TRANSFORM::cam_proj_matrix;
//			PULSAR::TRANSFORM::transform_shader.norm = XMMatrixTranspose(XMMatrixInverse(NULL, this->transform_matrix));
//
//			PULSAR::TRANSFORM::transform_cbuffer.update(PULSAR::TRANSFORM::transform_shader);
//			PULSAR::TRANSFORM::transform_cbuffer.bind(scope);
//		}
//
//
//		const XMMATRIX &get_transform_matrix()
//		{
//			return (this->transform_matrix);
//		}
//	};
//}

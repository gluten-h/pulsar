#pragma once

#include "utils/math.h"
#include "config/config.h"


namespace pulsar
{
	struct shader_light
	{
		int type;
		XMFLOAT3 pos_dir;

		XMFLOAT3 color;
		float pd1;

		XMFLOAT4 attenuation;
	};
	struct deferred_frag_lights
	{
		int lights_count;
		float pd0[3];

		pulsar::shader_light lights[pulsar::MAX_SCENE_LIGHTS_COUNT];
	};

	enum class LIGHT_TYPE : int
	{
		NONE = -1,
		POINT = 0,
		DIR = 1
	};

	class light
	{
	private:
		LIGHT_TYPE m_type = LIGHT_TYPE::NONE;

	public:
		light &operator=(const light&) = delete;
		light &operator=(light&&) = delete;
		light(const light&) = delete;
		light(light&&) = delete;
		light() = delete;
		light(pulsar::LIGHT_TYPE type);
		virtual ~light() = default;

		LIGHT_TYPE	type() const;
	};
}

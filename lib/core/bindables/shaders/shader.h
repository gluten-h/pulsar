#pragma once

#include "bindable/bindable.h"


namespace PULSAR
{
	const LPCSTR VERT_TARGET = "vs_5_0";
	const LPCSTR GEOM_TARGET = "gs_5_0";
	const LPCSTR FRAG_TARGET = "ps_5_0";

	const LPCSTR VERT_ENTRY = "vert";
	const LPCSTR GEOM_ENTRY = "geom";
	const LPCSTR FRAG_ENTRY = "frag";


class shader : public PULSAR::bindable
{
protected:
	ID3DBlob *mp_shader_blob = NULL;

protected:
	void	free();
	void	create_shader(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target);

public:
	shader &operator=(const shader&) = delete;
	shader &operator=(shader&&) = delete;
	shader(const shader&) = delete;
	shader(shader&&) = delete;
	shader() = default;
	~shader();

	ID3DBlob *get_shader_blob() const;
};
}
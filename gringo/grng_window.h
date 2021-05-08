#pragma once

#include "igrng_d3d.h"


class grng_window : public IGRNG_D3D
{
private:

public:
	grng_window() : IGRNG_D3D(){ }
};

using GRNG_WINDOW = grng_window;

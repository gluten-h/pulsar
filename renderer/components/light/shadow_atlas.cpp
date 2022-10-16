
#include "shadow_atlas.h"
#include "config/config.h"


pulsar::shadow_atlas::shadow_atlas()
{
	this->m_rt.set(pulsar::SHADOW_ATLAS_SIZE.x, pulsar::SHADOW_ATLAS_SIZE.y, pulsar::SHADOW_ATLAS_FORMAT);
	this->m_rt.set_slot(pulsar::FRAG_DEFERRED_SHADOW_ATLAS_SLOT);
	this->m_dsv.resize(pulsar::SHADOW_ATLAS_SIZE.x, pulsar::SHADOW_ATLAS_SIZE.y);

	this->m_available_tiles.push_back(D3D11_RECT{ 0, 0, (LONG)pulsar::SHADOW_ATLAS_SIZE.x, (LONG)pulsar::SHADOW_ATLAS_SIZE.y });
}

D3D11_RECT	pulsar::shadow_atlas::insert(UINT width, UINT height)
{
	D3D11_RECT rect{ 0, 0, 0, 0 };

	for (auto it = this->m_available_tiles.rbegin(); it != this->m_available_tiles.rend(); it++)
	{
		D3D11_RECT &tile = *it;
		UINT tile_width = tile.right - tile.left;
		UINT tile_height = tile.bottom - tile.top;

		if (width > tile_width || height > tile_height)
			continue;

		if (width == tile_width && height == tile_height)
		{
			rect = tile;
			std::swap(tile, this->m_available_tiles[this->m_available_tiles.size() - 1]);
			this->m_available_tiles.pop_back();

			break;
		}
		else if (width == tile_width)
		{
			rect = tile;
			rect.bottom = rect.top + height;
			tile.top = rect.bottom;

			break;
		}
		else if (height == tile_height)
		{
			rect = tile;
			rect.right = rect.left + width;
			tile.left = rect.right;

			break;
		}
		else
		{
			rect = tile;
			rect.right = rect.left + width;
			rect.bottom = rect.top + height;

			tile.left = rect.right;
			this->m_available_tiles.push_back(D3D11_RECT{ rect.left, rect.bottom, rect.right, tile.bottom });

			break;
		}
	}

	return (rect);
}

void	pulsar::shadow_atlas::free(D3D11_RECT *rect)
{
	this->m_available_tiles.push_back(*rect);
}

void	pulsar::shadow_atlas::clear(D3D11_RECT *rect)
{
	float clear_color[4] = { FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX };
	this->m_rt.clear(rect, clear_color);
	this->m_dsv.clear(rect);
}

void	pulsar::shadow_atlas::set_slot(UINT slot)
{
	this->m_rt.set_slot(slot);
}

void	pulsar::shadow_atlas::bind_srv()
{
	this->m_rt.bind_srv();
}

void	pulsar::shadow_atlas::bind_rtv()
{
	this->m_rt.bind_rtv(this->m_dsv.dsv());
}

void	pulsar::shadow_atlas::unbind_srv()
{
	this->m_rt.unbind_srv();
}

void	pulsar::shadow_atlas::unbind_rtv()
{
	this->m_rt.unbind_rtv();
}

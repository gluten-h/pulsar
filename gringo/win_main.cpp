
#include "grng_d3d.h"

#include "grng_const_buffer.h"
#include "grng_input_layout.h"
#include "grng_vert_shader.h"
#include "grng_geom_shader.h"
#include "grng_frag_shader.h"

#include "grng_mesh.h"

#include "grng_win_manager.h"


int CALLBACK		WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show)
{
	GRNG_D3D::create();
	GRNG_WM::create(h_instance);

	ID3D11Device *device = GRNG_D3D::get_device();
	ID3D11DeviceContext *device_context = GRNG_D3D::get_device_context();
	auto *iwin = GRNG_WM::get_iwin();

	GRNG_WM::create_win(L"gringo0", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL);
	//GRNG_WM::create_win(L"gringo1", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL);
	//GRNG_WM::create_win(L"gringo2", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL);
	//GRNG_WM::create_win(L"gringo3", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL);


	GRNG_VERT_SHADER vs = GRNG_VERT_SHADER(L"shader.hlsl", "vert");
	GRNG_FRAG_SHADER fs = GRNG_FRAG_SHADER(L"shader.hlsl", "frag");
	vs.bind();
	fs.bind();


	XMMATRIX transform = XMMatrixTranspose(XMMatrixRotationZ(0.0f));


	GRNG_MESH mesh = GRNG_MESH("resources/meshes/cube.obj", GRNG_MESH_FILE_FORMAT::GRNG_MESH_FILE_OBJ);
	mesh.create_buffer();

	GRNG_VERT_CONST_BUFFER<XMMATRIX> vcb(transform);
	vcb.bind();

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	GRNG_INPUT_LAYOUT input_layout = GRNG_INPUT_LAYOUT(vs.get_shader_blob(), ied, std::size(ied));
	input_layout.bind();


	int rot_i = 0;
	while (GRNG_WM::win_event())
	{
		int i = -1;
		while (++i < iwin->size)
		{
			const GRNG_WIN *win = iwin->data[i].data;
			int win_id = iwin->data[i].global_id;
			device_context->OMSetRenderTargets(1, &win->back_buffer, win->depth_stencil_view);
			device_context->OMSetDepthStencilState(win->depth_stencil_state, 1u);
			device_context->RSSetViewports(1, &win->viewport);
			device_context->ClearRenderTargetView(win->back_buffer, D3DXCOLOR(0.0f + 0.25f * win_id, 0.2f + 0.2f * win_id, 0.4f - 0.1f * win_id, 1.0f));
			device_context->ClearDepthStencilView(win->depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0u);

			transform = XMMatrixTranspose(XMMatrixRotationZ((float)rot_i * 0.0001f) * XMMatrixRotationX((float)rot_i * 0.0001f) * XMMatrixTranslation(0.0f, 0.0f, 3.0f) * XMMatrixPerspectiveFovLH(1.57f, win->viewport.Width / win->viewport.Height, 0.001f, 1000.0f));
			vcb.update(transform);

			mesh.bind();
			mesh.draw();
			win->swap_chain->Present(0, 0);
		}

		rot_i++;
	}

	GRNG_WM::destroy();
	GRNG_D3D::destroy();

	return (0);
}

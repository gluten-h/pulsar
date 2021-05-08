
#include "grng_d3d.h"

#include "grng_bindables.h"
#include "grng_assets.h"
#include "grng_drawables.h"

#include "grng_win_manager.h"


int CALLBACK		WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show)
{
	//GRNG_D3D::create();
	GRNG_WM::create(h_instance);

	ID3D11Device *device = GRNG_D3D::get_device();
	ID3D11DeviceContext *device_context = GRNG_D3D::get_device_context();
	auto *iwin = GRNG_WM::get_iwin();

	int win0 = GRNG_WM::create_win(L"gringo0", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL);
	//int win1 = GRNG_WM::create_win(L"gringo1", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL);
	//int win2 = GRNG_WM::create_win(L"gringo2", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL);
	//int win3 = GRNG_WM::create_win(L"gringo3", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL);


	GRNG_COMPONENT_TRANSFORM cam_transform = GRNG_COMPONENT_TRANSFORM(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	GRNG_CAMERA camera(cam_transform, 1.57f, 0.001f, D3D11_FLOAT32_MAX);
	GRNG_WM::set_camera(win0, camera);


	GRNG_VERT_SHADER vs(L"shader.hlsl", "vert");
	GRNG_FRAG_SHADER fs(L"shader.hlsl", "frag");

	GRNG_VERT_SHADER vs1(L"shader1.hlsl", "vert");
	GRNG_FRAG_SHADER fs1(L"shader1.hlsl", "frag");


	GRNG_MESH cube_mesh("resources/meshes/cube.obj", GRNG_MESH_FILE_FORMAT::GRNG_MESH_FILE_OBJ);
	GRNG_MESH sph_mesh("resources/meshes/icosphere2.obj", GRNG_MESH_FILE_FORMAT::GRNG_MESH_FILE_OBJ);


	GRNG_OBJ cube_obj;
	cube_obj.add_mesh(cube_mesh);

	GRNG_OBJ sph_obj;
	sph_obj.add_mesh(sph_mesh);


	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	D3D11_INPUT_ELEMENT_DESC ied1[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	GRNG_INPUT_LAYOUT input_layout(vs.get_shader_blob(), ied, (UINT)std::size(ied));
	GRNG_INPUT_LAYOUT input_layout1(vs1.get_shader_blob(), ied1, (UINT)std::size(ied1));

	GRNG_TEXTURE texture(L"resources/textures/p3.jpg");
	GRNG_SAMPLER tex_sampler;


	cube_obj.add_bindable(vs1);
	cube_obj.add_bindable(fs1);
	cube_obj.add_bindable(input_layout1);
	cube_obj.add_bindable(texture);
	cube_obj.add_bindable(tex_sampler);

	sph_obj.add_bindable(vs);
	sph_obj.add_bindable(fs);
	sph_obj.add_bindable(input_layout);


	cube_obj.transform.position = XMFLOAT3(1.0f, 0.0f, 3.5f);
	cube_obj.transform.scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	sph_obj.transform.position = XMFLOAT3(-1.0f, 0.0f, 1.75f);
	sph_obj.transform.scale = XMFLOAT3(0.5f, 0.5f, 0.5f);


	int rot_i = 0;
	while (GRNG_WM::win_event())
	{
		int i = -1;
		while (++i < iwin->size)
		{
			const GRNG_WIN *win = iwin->data[i].data;
			if (!win->curr_camera)
				continue;
			win->bind();

			cube_obj.transform.rotation = XMFLOAT3((float)rot_i * 0.0001f, 0.0f, (float)rot_i * 0.0001f);
			sph_obj.transform.rotation = XMFLOAT3((float)rot_i * 0.0001f, (float)rot_i * 0.0001f, 0.0f);

			cube_obj.draw();
			sph_obj.draw();

			win->swap_chain->Present(0, 0);
		}

		rot_i++;
	}

	GRNG_WM::destroy();
	GRNG_D3D::destroy();

	return (0);
}

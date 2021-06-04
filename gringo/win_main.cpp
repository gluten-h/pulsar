
#include "grng_d3d.h"
#include "grng_bindables.h"
#include "grng_assets.h"
#include "grng_drawables.h"
#include "grng_scene.h"
#include "grng_win_manager.h"

#include "cam_controller.h"


int CALLBACK		WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show)
{
	GRNG_D3D::create();
	GRNG_WM::create(h_instance);

	ID3D11Device *device = GRNG_D3D::get_device();
	ID3D11DeviceContext *device_context = GRNG_D3D::get_device_context();
	auto *iwin = GRNG_WM::get_iwin();

	GRNG_COMPONENT_TRANSFORM cam_transform = GRNG_COMPONENT_TRANSFORM(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	GRNG_CAMERA camera(cam_transform, 1.57f, 0.001f, D3D11_FLOAT32_MAX);
	GRNG_CAM_CONTROLLER cam_controller{ 8.0f, 8.0f, 0.01f };

	int win0 = GRNG_WM::create_window(L"gringo0", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, grng_cam_controller, &cam_controller);
	//int win1 = GRNG_WM::create_window(L"gringo1", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL, NULL);
	//int win2 = GRNG_WM::create_window(L"gringo2", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL, NULL);
	//int win3 = GRNG_WM::create_window(L"gringo3", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, NULL, NULL);

	GRNG_WM::set_camera(win0, camera);


	GRNG_VERT_SHADER gb_pass_vs(L"g_buffer_pass_vs.hlsl", GRNG_VERT_ENTRY, NULL);
	GRNG_FRAG_SHADER gb_pass_fs(L"g_buffer_pass_fs.hlsl", GRNG_FRAG_ENTRY, NULL);


	GRNG_MESH cube_mesh("resources/meshes/cube.obj", GRNG_MESH_FILE_FORMAT::GRNG_MESH_FILE_OBJ);
	GRNG_MESH sph_mesh("resources/meshes/sphere64.obj", GRNG_MESH_FILE_FORMAT::GRNG_MESH_FILE_OBJ);


	GRNG_OBJ cube_obj;
	cube_obj.set_mesh(cube_mesh);

	GRNG_MATERIAL cube_mat;
	cube_mat.albedo.set_texture(L"resources/textures/p3.jpg");
	cube_obj.set_material(cube_mat);


	GRNG_OBJ ico_obj;
	ico_obj.set_mesh(sph_mesh);

	GRNG_MATERIAL ico_mat;
	ico_mat.albedo_color = XMFLOAT3(1.0f, 0.25f, 0.25f);
	ico_obj.set_material(ico_mat);


	GRNG_POINT_LIGHT pl1(XMFLOAT3(-5.0f, -2.0f, -1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 1.0f);
	GRNG_DIR_LIGHT dl1(XMFLOAT3(-1.0f, -0.6f, 0.25f), XMFLOAT3(1.0f, 1.0f, 1.0f));


	GRNG_SCENE scene;
	GRNG_WM::set_scene(win0, scene);

	int pl1_id = scene.add_light(pl1);
	int dl1_id = scene.add_light(dl1);

	int cube_id = scene.add_drawable(cube_obj);
	int ico_id = scene.add_drawable(ico_obj);


	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	GRNG_INPUT_LAYOUT input_layout(gb_pass_vs.get_shader_blob(), ied, (UINT)std::size(ied));

	GRNG_SAMPLER tex_sampler;


	cube_obj.add_bindable(gb_pass_vs);
	cube_obj.add_bindable(gb_pass_fs);
	cube_obj.add_bindable(input_layout);

	ico_obj.add_bindable(gb_pass_vs);
	ico_obj.add_bindable(gb_pass_fs);
	ico_obj.add_bindable(input_layout);


	cube_obj.transform.position = XMFLOAT3(1.0f, 0.0f, 3.5f);
	cube_obj.transform.scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	ico_obj.transform.position = XMFLOAT3(-1.0f, 0.0f, 1.75f);
	ico_obj.transform.scale = XMFLOAT3(0.5f, 0.5f, 0.5f);


	int rot_i = 0;
	while (GRNG_WM::win_event())
	{
		int i = -1;
		while (++i < iwin->size)
		{
			GRNG_WINDOW *win = iwin->data[i].data;

			cube_obj.transform.rotation = XMFLOAT3((float)rot_i * 0.01f, 0.0f, (float)rot_i * 0.01f);
			ico_obj.transform.rotation = XMFLOAT3((float)rot_i * 0.01f, (float)rot_i * 0.01f, 0.0f);

			win->update();
			win->draw_g_pass();
			win->draw_deferred();

			win->present();
		}

		rot_i++;
	}

	GRNG_WM::destroy();
	GRNG_D3D::destroy();

	return (0);
}

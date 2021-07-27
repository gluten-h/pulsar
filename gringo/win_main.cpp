
#include "grng_exc_macros.h"
#include "grng_win_manager.h"
#include "grng_scene_manager.h"
#include "grng_bindable_manager.h"
#include "grng_component_manager.h"

#include "cam_controller.h"


int CALLBACK		WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show)
{
	GRNG_D3D::create();
	GRNG_WM::create(h_instance);
	GRNG_MP::create();


	auto *iwin = GRNG_WM::get_iwin();

	int win0 = GRNG_WM::create_window("gringo0", WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL);


	GRNG_CAMERA &camera = *(GRNG_CAMERA*)GRNG_CM.add(GRNG_COMPONENT_TYPE::CAMERA);
	GRNG_TRANSFORM cam_transform = GRNG_TRANSFORM(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
	camera.set(cam_transform, grng_deg2rad(75.0f));
	GRNG_CAM_CONTROLLER cam_controller{ 5.0f, 6.0f, 0.8f, 0.75f, { cam_transform.rotation.x, cam_transform.rotation.y } };
	GRNG_WM::set_camera(win0, camera);

	GRNG_WM::add_win_update(win0, grng_cam_controller, &cam_controller);


	GRNG_SCENE &scene = *GRNG_SM.add();
	GRNG_WM::set_scene(win0, scene);

	GRNG_SKYBOX_MATERIAL &skybox_mat = *(GRNG_SKYBOX_MATERIAL*)GRNG_CM.add(GRNG_COMPONENT_TYPE::SKYBOX_MATERIAL);
	skybox_mat.env_map.set(L"resources/cubemaps/cm00/cm00.dds");
	scene.set_skybox_material(skybox_mat);


	GRNG_VERT_SHADER &gb_pass_vs = *(GRNG_VERT_SHADER*)GRNG_BM.add(GRNG_BINDABLE_TYPE::VERT_SHADER);
	GRNG_GEOM_SHADER &gb_pass_gs = *(GRNG_GEOM_SHADER*)GRNG_BM.add(GRNG_BINDABLE_TYPE::GEOM_SHADER);
	GRNG_FRAG_SHADER &gb_pass_fs = *(GRNG_FRAG_SHADER*)GRNG_BM.add(GRNG_BINDABLE_TYPE::FRAG_SHADER);

	gb_pass_vs.set(L"g_buffer_pass_vs.hlsl", GRNG_VERT_ENTRY, NULL);
	gb_pass_gs.set(L"g_buffer_pass_gs.hlsl", GRNG_GEOM_ENTRY, NULL);
	gb_pass_fs.set(L"g_buffer_pass_fs.hlsl", GRNG_FRAG_ENTRY, NULL);


	GRNG_OBJECT &cube_obj = *(GRNG_OBJECT*)scene.add_entity(GRNG_ENTITY_TYPE::OBJECT);
	GRNG_OBJECT &sph_obj = *(GRNG_OBJECT*)scene.add_entity(GRNG_ENTITY_TYPE::OBJECT);
	GRNG_OBJECT &sph1_obj = *(GRNG_OBJECT*)scene.add_entity(GRNG_ENTITY_TYPE::OBJECT);
	GRNG_OBJECT &sph2_obj = *(GRNG_OBJECT*)scene.add_entity(GRNG_ENTITY_TYPE::OBJECT);


	cube_obj.set_mesh(GRNG_STD_CUBE_MESH);

	GRNG_MATERIAL &cube_mat = *(GRNG_MATERIAL*)GRNG_CM.add(GRNG_COMPONENT_TYPE::MATERIAL);
	cube_mat.albedo_map.set(L"resources/textures/p3.jpg");
	cube_mat.normal_map.set(L"resources/textures/brick00/normal.png");
	cube_mat.normal_factor = 1.0f;
	cube_obj.set_material(cube_mat);


	sph_obj.set_mesh(GRNG_STD_SPHERE64_MESH);

	GRNG_MATERIAL &sph_mat = *(GRNG_MATERIAL*)GRNG_CM.add(GRNG_COMPONENT_TYPE::MATERIAL);
	sph_mat.albedo_map.set(L"resources/textures/brick00/albedo.png");
	sph_mat.normal_map.set(L"resources/textures/brick00/normal.png");
	sph_mat.normal_factor = 1.5f;
	sph_mat.roughness_map.set(L"resources/textures/brick00/roughness.png");
	sph_mat.metalness = 0.0f;
	sph_mat.ao = 0.01f;
	sph_obj.set_material(sph_mat);


	sph1_obj.set_mesh(GRNG_STD_SPHERE64_MESH);

	GRNG_MATERIAL &sph1_mat = *(GRNG_MATERIAL*)GRNG_CM.add(GRNG_COMPONENT_TYPE::MATERIAL);;
	sph1_mat.albedo_map.set(L"resources/textures/metal00/albedo.png");
	sph1_mat.normal_map.set(L"resources/textures/metal00/normal.png");
	sph1_mat.normal_factor = 5.0f;
	sph1_mat.roughness_map.set(L"resources/textures/metal00/roughness.png");
	sph1_mat.metalness_map.set(L"resources/textures/metal00/metalness.png");
	sph1_mat.ao = 0.01f;
	sph1_obj.set_material(sph1_mat);


	sph2_obj.set_mesh(GRNG_STD_SPHERE64_MESH);

	GRNG_MATERIAL &sph2_mat = *(GRNG_MATERIAL*)GRNG_CM.add(GRNG_COMPONENT_TYPE::MATERIAL);;
	sph2_mat.albedo_map.set(L"resources/textures/wood00/albedo.png");
	sph2_mat.normal_map.set(L"resources/textures/wood00/normal.png");
	sph2_mat.normal_factor = 4.0f;
	sph2_mat.roughness_map.set(L"resources/textures/wood00/roughness.png");
	sph2_mat.metalness_map.set(L"resources/textures/wood00/metalness.png");
	sph2_mat.ao = 0.01f;
	sph2_obj.set_material(sph2_mat);


	GRNG_POINT_LIGHT &pl1 = *(GRNG_POINT_LIGHT*)scene.add_light(GRNG_LIGHT_TYPE::POINT);
	GRNG_DIR_LIGHT &dl1 = *(GRNG_DIR_LIGHT*)scene.add_light(GRNG_LIGHT_TYPE::DIR);

	pl1.set(XMFLOAT3(-5.0f, -2.0f, -1.0f), XMFLOAT3(0.15f, 0.15f, 1.0f), 1.0f, 0.005f, 0.0007f);
	dl1.set(XMFLOAT3(0.0f, -0.25f, 1.0f), XMFLOAT3(1.0f, 1.0f, 0.5f));


	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	GRNG_INPUT_LAYOUT &input_layout = *(GRNG_INPUT_LAYOUT*)GRNG_BM.add(GRNG_BINDABLE_TYPE::INPUT_LAYOUT);
	input_layout.set(gb_pass_vs.get_shader_blob(), ied, (UINT)std::size(ied));


	cube_obj.add_bindable(gb_pass_vs);
	cube_obj.add_bindable(gb_pass_gs);
	cube_obj.add_bindable(gb_pass_fs);
	cube_obj.add_bindable(input_layout);

	sph_obj.add_bindable(gb_pass_vs);
	sph_obj.add_bindable(gb_pass_gs);
	sph_obj.add_bindable(gb_pass_fs);
	sph_obj.add_bindable(input_layout);

	sph1_obj.add_bindable(gb_pass_vs);
	sph1_obj.add_bindable(gb_pass_gs);
	sph1_obj.add_bindable(gb_pass_fs);
	sph1_obj.add_bindable(input_layout);

	sph2_obj.add_bindable(gb_pass_vs);
	sph2_obj.add_bindable(gb_pass_gs);
	sph2_obj.add_bindable(gb_pass_fs);
	sph2_obj.add_bindable(input_layout);


	cube_obj.transform.position = XMFLOAT3(1.0f, 0.0f, 5.5f);
	cube_obj.transform.scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	sph_obj.transform.position = XMFLOAT3(0.0f, 0.0f, 1.75f);
	sph_obj.transform.scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	sph1_obj.transform.position = XMFLOAT3(1.25f, 0.0f, 1.75f);
	sph1_obj.transform.scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	sph2_obj.transform.position = XMFLOAT3(-1.25f, 0.0f, 1.75f);
	sph2_obj.transform.scale = XMFLOAT3(0.5f, 0.5f, 0.5f);


	while (GRNG_WM::win_event())
	{
		int i = -1;
		while (++i < iwin->size)
		{
			GRNG_WINDOW *win = iwin->data[i].data;

			float delta_time = GRNG_GFX::get_delta_time();
			cube_obj.transform.rotation = XMFLOAT3(cube_obj.transform.rotation.x + delta_time * 0.25f, 0.0f, cube_obj.transform.rotation.z + delta_time * 0.25f);
			sph_obj.transform.rotation = XMFLOAT3(sph_obj.transform.rotation.x + delta_time * 0.25f, sph_obj.transform.rotation.y + delta_time * 0.25f, sph_obj.transform.rotation.z + delta_time * 0.25f);
			sph1_obj.transform.rotation = XMFLOAT3(sph1_obj.transform.rotation.x + delta_time * 0.25f, sph1_obj.transform.rotation.y + delta_time * 0.25f, sph1_obj.transform.rotation.z + delta_time * 0.25f);
			sph2_obj.transform.rotation = XMFLOAT3(sph2_obj.transform.rotation.x + delta_time * 0.25f, sph2_obj.transform.rotation.y + delta_time * 0.25f, sph2_obj.transform.rotation.z + delta_time * 0.25f);

			win->update();
			win->draw();

			win->present();
		}
		GRNG_GFX::set_delta_time();
	}

	GRNG_MP::destroy();
	GRNG_WM::destroy();
	GRNG_D3D::destroy();

	return (0);
}

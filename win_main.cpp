
#include "pulsar.h"

#include "scripts/camera_controller.h"
#include "scripts/node_rotation.h"
#include "scripts/node_rotation_orbit.h"


int CALLBACK	WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int n_cmd_show)
{
	pulsar::init(h_instance);

	pulsar::window win("pulsar", 1280u, 720u);
	pulsar::deferred_render_graph render_graph(win.framebuffer());

	pulsar::scene scene;
	pulsar::scene::set_active_scene(&scene);

	pulsar::filesystem::create_mount_point(pulsar::filesystem::absolute_path(L"resources/textures"));
	pulsar::filesystem::create_mount_point(pulsar::filesystem::absolute_path(L"resources/cubemaps"));

	//scene.skybox_material().albedo_map().set(L"cm00/cm00.dds");


	pulsar::node camera_node = scene.create_node();
	pulsar::perspective_camera camera(1280u, 720u, pulsar::deg2rad(90.0f), 0.001f, 1000.0f);
	//pulsar::camera_controller camera_controller(&camera_node, 5.0f, 6.0f, 0.7f);
	pulsar::camera_controller camera_controller(&camera_node, 0.75f, 4.0f, 6.0f, 0.7f);
	{
		camera_node.add_component<pulsar::camera_component>(&camera);
		camera_node.add_component<pulsar::script_component>(&camera_controller);
	}
	win.framebuffer().link(&camera.viewport());
	scene.set_main_camera(&camera_node);


	pulsar::node cube = scene.create_node();
	pulsar::cube cube_mesh;
	pulsar::material pepega_mat;
	pulsar::node_rotation cube_nr(&cube, 0.25f, XMFLOAT3(1.0f, 0.0f, 1.0f));
	{
		pepega_mat.albedo_map().set(L"p3.jpg");
		pepega_mat.normal_map().set(L"brick00/normal.png");
		pepega_mat.normal_factor() = 1.0f;
		//pepega_mat.irradiance_map().set(L"cm00/cm00_irradiance.dds");

		cube.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(1.0f, 1.0f, 5.5f));
		cube.add_component<pulsar::mesh_component>(&cube_mesh);
		cube.add_component<pulsar::material_component>(pulsar::rq_material(&pepega_mat));
		cube.add_component<pulsar::script_component>(&cube_nr);
	}

	pulsar::node cube1 = scene.create_node();
	{
		cube1.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(-0.2f, -0.3f, 1.0f));
		cube1.get_component<pulsar::transform_component>().transform.set_rotation(0.0f, XM_PIDIV4, 0.0f);
		cube1.get_component<pulsar::transform_component>().transform.set_scale(XMFLOAT3(0.2f, 0.2f, 0.2f));

		cube1.add_component<pulsar::mesh_component>(&cube_mesh);
		cube1.add_component<pulsar::material_component>(pulsar::rq_material(&pepega_mat));
	}

	pulsar::node quad = scene.create_node();
	pulsar::quad quad_mesh;
	pulsar::material quad_mat;
	{
		//quad_mat.irradiance_map().set(L"cm00/cm00_irradiance.dds");

		quad.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(0.0f, -0.5f, 0.0f));
		quad.get_component<pulsar::transform_component>().transform.set_scale(XMFLOAT3(10.0f, 10.0f, 10.0f));
		quad.add_component<pulsar::mesh_component>(&quad_mesh);
		quad.add_component<pulsar::material_component>(pulsar::rq_material(&quad_mat));
		quad.get_component<pulsar::metadata_component>().mask.shadows = 0x0;
	}

	pulsar::node sphere = scene.create_node();
	pulsar::material brick_mat;
	pulsar::node_rotation sphere_nr(&sphere, 0.25f);
	{
		brick_mat.albedo_map().set(L"brick00/albedo.png");
		brick_mat.normal_map().set(L"brick00/normal.png");
		brick_mat.normal_factor() = 1.5f;
		brick_mat.roughness_map().set(L"brick00/roughness.png");
		brick_mat.metalness() = 0.0f;
		brick_mat.ao() = 0.5f;
		//brick_mat.irradiance_map().set(L"cm00/cm00_irradiance.dds");

		sphere.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(0.0f, 0.0f, 1.75f));
		sphere.get_component<pulsar::transform_component>().transform.set_scale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		sphere.add_component<pulsar::mesh_component>((pulsar::mesh*)&pulsar::SPHERE64);
		sphere.add_component<pulsar::material_component>(pulsar::rq_material(&brick_mat));
		//sphere.add_component<pulsar::script_component>(&sphere_nr);
	}

	pulsar::node sphere1 = scene.create_node();
	pulsar::material metal_mat;
	pulsar::node_rotation sphere1_nr(&sphere1, 0.25f);
	{
		metal_mat.albedo_map().set(L"metal00/albedo.png");
		metal_mat.normal_map().set(L"metal00/normal.png");
		metal_mat.normal_factor() = 5.0f;
		metal_mat.roughness_map().set(L"metal00/roughness.png");
		metal_mat.metalness_map().set(L"metal00/metalness.png");
		metal_mat.ao() = 0.5f;
		//metal_mat.irradiance_map().set(L"cm00/cm00_irradiance.dds");

		sphere1.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(1.25f, 0.0f, 1.75f));
		sphere1.get_component<pulsar::transform_component>().transform.set_scale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		sphere1.add_component<pulsar::mesh_component>((pulsar::mesh*)&pulsar::SPHERE64);
		sphere1.add_component<pulsar::material_component>(pulsar::rq_material(&metal_mat));
		//sphere1.add_component<pulsar::script_component>(&sphere1_nr);
	}

	pulsar::node sphere2 = scene.create_node();
	pulsar::material wood_mat;
	pulsar::node_rotation sphere2_nr(&sphere2, 0.25f);
	{
		wood_mat.albedo_map().set(L"wood00/albedo.png");
		wood_mat.normal_map().set(L"wood00/normal.png");
		wood_mat.normal_factor() = 4.0f;
		wood_mat.roughness_map().set(L"wood00/roughness.png");
		wood_mat.metalness_map().set(L"wood00/metalness.png");
		wood_mat.ao_map().set(L"wood00/ao.png");
		wood_mat.ao() = 0.5f;
		//wood_mat.irradiance_map().set(L"cm00/cm00_irradiance.dds");

		sphere2.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(-1.25f, 0.0f, 1.75f));
		sphere2.get_component<pulsar::transform_component>().transform.set_scale(XMFLOAT3(0.5f, 0.5f, 0.5f));
		sphere2.add_component<pulsar::mesh_component>((pulsar::mesh*)&pulsar::SPHERE64);
		sphere2.add_component<pulsar::material_component>(pulsar::rq_material(&wood_mat));
		//sphere2.add_component<pulsar::script_component>(&sphere2_nr);
	}


	pulsar::node pl_node = scene.create_node();
	pulsar::point_light pl(XMFLOAT3(0.15f, 0.1f, 1.0f), 0.1f, 0.005f, 0.0007f);
	pulsar::node_rotation_orbit pl_nro(&pl_node, 0.25f, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));
	{
		pl_node.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(3.0f, 1.5f, 1.0f));
		//pl_node.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(0.0f, 1.5f, -1.0f));
		pl_node.add_component<pulsar::light_component>().light = &pl;
		pl_node.get_component<pulsar::light_component>().light->shadow_map()->set(1024u, 1024u);

		pl_node.add_component<pulsar::script_component>(&pl_nro);
	}

	//pulsar::node dl_node = scene.create_node();
	//pulsar::dir_light dl(XMFLOAT3(1.0f, 1.0f, 0.5f));
	//{
	//	dl_node.get_component<pulsar::transform_component>().transform.set_position(XMFLOAT3(0.0f, -0.25f, 1.0f));
	//	dl_node.add_component<pulsar::light_component>().light = &dl;
	//}


	while (win.process_events())
	{
		//std::string dt_str = "delta_time: " + std::to_string(win.delta_time()) + '\n';
		//OutputDebugString(dt_str.c_str());

		win.begin_frame();
		scene.update(win.delta_time());
		scene.update_render(win.delta_time());
		render_graph.execute();
		win.end_frame();
	}

	pulsar::terminate();

	return (0);
}

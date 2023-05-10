#include <array>
#include <iostream>
#include <memory>
#include <unordered_map>

//https://github.com/ademirtug/de2/
#include "../de2/de2.h"
#include "../de2/camera.h"
#include "../de2/model.h"

//https://github.com/ademirtug/ecs_s/
using namespace ecs_s;

int main()
{
	de2& eng = de2::get_instance();
	eng.init();
	//camera+texture+point_light
	eng.programs["c_t_point"] = std::make_shared<program>("c_t_point", "shaders/c_t_point.vert", "shaders/c_t_point.frag");
	eng.programs["c_t_direct"] = std::make_shared<program>("c_t_direct", "shaders/c_t_direct.vert", "shaders/c_t_direct.frag");

	//approximate sun position
	time_t rawtime;
	time(&rawtime);
	float e2 = 2 * glm::pi<float>() * ((gmtime(&rawtime)->tm_hour - 12) / 24.0);

	//greenwich
	float x = cos(e2);
	//south pole
	float y = 0;
	//panama
	float z = sin(e2);

	renderer_system renderer;
	renderer.l = std::make_shared<directional_light>(glm::vec3({ x, y, z }));

	registry world;
	entity earth = world.new_entity();

	auto mm = de2::get_instance().load_model<texture_model>(std::string("earth"), std::string("models/tcube.obj"), std::string("textures/earth.bmp"), true);
	mm->attach_program(eng.programs["c_t_direct"]);
	world.add_component(earth, mm);

	de2::get_instance().on<render>([&world, &renderer](std::chrono::nanoseconds ns) {
		renderer.process(world, ns);
		});
	eng.run();
}


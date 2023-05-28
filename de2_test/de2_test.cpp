#include <array>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <glm/gtx/vector_angle.hpp>

//https://github.com/ademirtug/de2/
#include "../de2/de2.h"
#include "../de2/camera.h"
#include "../de2/model.h"
#include "test_camera.h"
//https://github.com/ademirtug/ecs_s/
using namespace ecs_s;


class frustum : public mesh {
public:
	glm::vec3 normal{ 0, 0, 0 };
	double z_far{ 0 };
	glm::vec3 front, back, up, down, left, right;

	frustum(glm::vec3 cam_pos) {
		double z_near = 0.001;
		double scr_width = 1024;
		double scr_height = 768;
		double ratio = scr_width / scr_height;

		//z_far = - cam_pos.z / 60;
		//double nheight = 2 * z_near * std::tan(glm::pi<float>() / 8.0f);
		//double nwidth = ratio * nheight;
		//glm::vec3 nll{- nwidth / 2	, - nheight / 2, z_far};
		//glm::vec3 nlr{nwidth / 2	, -nheight / 2, z_far};
		//glm::vec3 nul{- nwidth / 2	, nheight / 2, z_far};
		//glm::vec3 nur{nwidth / 2	, nheight / 2, z_far};

		//double fheight = 2 * z_far * std::tan(glm::pi<float>() / 8.0f);
		//double fwidth = ratio * fheight;
		//glm::vec3 fll{-fwidth / 2, -fheight / 2, 0};
		//glm::vec3 flr{fwidth / 2, -fheight /2, 0};
		//glm::vec3 ful{-fwidth / 2, fheight / 2, 0};
		//glm::vec3 fur{fwidth / 2, fheight / 2, 0};



		z_far = -cam_pos.z;
		double nheight = 2 * z_near * std::tan(glm::pi<float>() / 8.0f);
		double nwidth = ratio * nheight;
		glm::vec3 nll{nwidth / 2, nheight / 2, z_far};
		glm::vec3 nlr{-nwidth / 2, nheight / 2, z_far};
		glm::vec3 nul{nwidth / 2, -nheight / 2, z_far};
		glm::vec3 nur{-nwidth / 2, -nheight / 2, z_far};

		double fheight = 2 * z_far * std::tan(glm::pi<float>() / 8.0f);
		double fwidth = ratio * fheight;
		glm::vec3 fll{fwidth / 2, fheight / 2, 0};
		glm::vec3 flr{-fwidth / 2, fheight / 2, 0};
		glm::vec3 ful{fwidth / 2, -fheight / 2, 0};
		glm::vec3 fur{-fwidth / 2, -fheight / 2, 0};



		vertices.push_back({
			nll,
			{0, 0, 0},
			{0, 0}
		});
		vertices.push_back({
			nlr,
			{0, 0, 0},
			{0, 0}
			});
		vertices.push_back({
			nul,
			{0, 0, 0},
			{0, 0}
			});
		vertices.push_back({
			nur,
			{0, 0, 0},
			{0, 0}
			});		
		vertices.push_back({
			fll,
			{0, 0, 0},
			{0, 0}
			});		
		vertices.push_back({
			flr,
			{0, 0, 0},
			{0, 0}
			});		
		vertices.push_back({
			ful,
			{0, 0, 0},
			{0, 0}
			});
		vertices.push_back({
			fur,
			{0, 0, 0},
			{0, 0}
			});


		front = glm::normalize(glm::cross(ful - fll, ful - fur));
		back = glm::normalize(glm::cross(nul - nll, nul - nur));

		up = glm::normalize(glm::cross(ful - nul, ful - fur));
		down = glm::normalize(glm::cross(fll - nll, fll - flr));
		
		left = glm::normalize(glm::cross(ful - nul, ful - fll));
		right = glm::normalize(glm::cross(fur - nur, fur - flr));


		//front
		indices.insert(indices.end(), { 0, 2, 1 });
		indices.insert(indices.end(), { 1, 2, 3 });

		//left
		indices.insert(indices.end(), { 4, 6, 0 });
		indices.insert(indices.end(), { 0, 6, 2 });

		//right
		indices.insert(indices.end(), { 1, 3, 5 });
		indices.insert(indices.end(), { 5, 3, 7 });

		//bottom
		indices.insert(indices.end(), { 4, 0, 5 });
		indices.insert(indices.end(), { 5, 0, 1 });

		//up
		indices.insert(indices.end(), { 2, 6, 3 });
		indices.insert(indices.end(), { 3, 6, 7 });

		////back
		indices.insert(indices.end(), { 4, 5, 6 });
		indices.insert(indices.end(), { 5, 7, 6 });

		size_of_indices = indices.size();
	}

	bool contains(glm::vec3 x) {
		auto pi2 = glm::pi<double>() / 2 ;
		double a_up = glm::angle(x+up, up);
		double a_down = glm::angle(x+down, down);

		double a_front = glm::angle(x, front);
		double a_back = glm::angle(x, back);
		
		double a_left = glm::angle(x, left);
		double a_right = glm::angle(x, right);

 		return false;
	}
};

template<typename T>
class frustum_visualizer : public model {
public:
	frustum_visualizer(glm::vec3 cam_pos) {
		m = std::make_shared<T>(cam_pos);
		//mat_model = glm::scale(mat_model, glm::vec3{0.01, 0.01, 0.01});
	}

	bool upload() {
		if (vao > 0)
			return true;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		m->upload();
		glBindVertexArray(0);
		return true;
	}
	void draw() {

		prg->use();
		prg->setuniform("model", mat_model);
		prg->setuniform("material.specular", m->specular);
		prg->setuniform("material.shininess", m->shininess);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, m->size_of_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};

int main()
{
	de2::get_instance().init();
	de2::get_instance().programs["c_t_point"] = std::make_shared<program>("c_t_point", "shaders/c_t_point.vert", "shaders/c_t_point.frag");
	de2::get_instance().programs["c_t_direct"] = std::make_shared<program>("c_t_direct", "shaders/c_t_direct.vert", "shaders/c_t_direct.frag");

	renderer_system renderer;
	renderer.l = std::make_shared<directional_light>(glm::vec3({ 1, 0, 0 }));
	renderer.cam_ = std::make_shared<test_camera>();
	
	//+x sol
	//+y = south pole - aşağı
	// +z ileri
	//-z cam - panama
	registry world;
	auto vp = de2::get_instance().viewport;
	auto view = renderer.get_view();
	auto projection = renderer.get_projection();


	entity earth = world.new_entity();
	auto mm = de2::get_instance().load_model<texture_model>(std::string("earth"), std::string("models/earthn.obj"), std::string("textures/earth.bmp"));
	mm->attach_program(de2::get_instance().programs["c_t_direct"]);
	world.add_component(earth, mm);
	world.add_component(earth, visible{});


	entity box = world.new_entity();
	std::shared_ptr<model> av = std::make_shared<frustum_visualizer<frustum>>(renderer.cam_->get_world_pos());
	av->attach_program(de2::get_instance().programs["c_t_direct"]);
	av->upload();
	world.add_component(box, av);
	world.add_component(box, visible{});

	renderer.enable_wireframe_mode();

	frustum f(renderer.cam_->get_world_pos());
	bool fb = f.contains(glm::vec3{0, 0, -1});


	std::vector<model> models;

	de2::get_instance().on<render>([&](std::chrono::nanoseconds ns) {
		renderer.process(world, ns);
	});
	de2::get_instance().run();
}


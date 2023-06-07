# de2
A simplistics ECS based 3D rendering engine.

## Requirements
- [msvc](https://visualstudio.microsoft.com/) **>= 2022**

## Installation

- Include its header.
```cpp
#include "de2.h"
```

## Basic Usage

```cpp
#include "../de2/de2.h"
#include "../de2/camera.h"
#include "../de2/model.h"

//https://github.com/ademirtug/ecs_s/
using namespace ecs_s;

int main()
{
	de2::get_instance().init();
	de2::get_instance().programs["c_t_direct"] = std::make_shared<program>("c_t_direct", "shaders/c_t_direct.vert", "shaders/c_t_direct.frag");
	renderer_system renderer;
	renderer.l = std::make_shared<directional_light>(glm::vec3({ 0, 1, 0 }));

	registry world;
	entity earth = world.new_entity();
	auto mm = de2::get_instance().load_model<texture_model>(std::string("earth"), std::string("models/tcube.obj"), std::string("textures/earth.bmp"), true);
	mm->attach_program(de2::get_instance().programs["c_t_direct"]);
	world.add_component(earth, mm);
	world.add_component(earth, visible{});
	

	de2::get_instance().on<render>([&world, &renderer](std::chrono::nanoseconds ns) {
		renderer.process(world, ns);
		});
	de2::get_instance().run();
}

```

#include "pch.h"
#include "de2.h"
#include "model.h"
#include "camera.h"
#include "shader.h"
#include <Windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

de2::de2(){
    on_resize = [&](int width, int height) { resize(width, height); };
    on_key = [&](int key, int scancode, int action, int mods) { if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);};
    on_process_input = [&]() { };
    
}
de2& de2::get_instance() {
    static de2 pInstance;
    return pInstance;
}
void de2::set_title(const std::string& title) {
    glfwSetWindowTitle(window, title.c_str());
}
std::string de2::get_title() {
    std::string title(GetWindowTextLength(glfwGetWin32Window(de2::get_instance().window)) + 1, '\0');
    GetWindowTextA(glfwGetWin32Window(de2::get_instance().window), &title[0], title.size());
    return title;
}
void de2::resize(size_t width, size_t height) {
    viewport.x = width; viewport.y = height; glViewport(0, 0, width, height);
}
bool de2::has_model(const std::string& key) {
    return model_cache_.exists(key);
}


void de2::init() {
    glfwSetErrorCallback([](int error, const char* desc) { if (de2::get_instance().on_error) de2::get_instance().on_error(error, desc); });

    if (!glfwInit())
        throw std::exception("failed to init glfw");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(viewport.x, viewport.y, "", (GLFWmonitor*)NULL, (GLFWwindow*)NULL);
    if (window == NULL) {
        glfwTerminate();
        throw std::exception("failed to create a window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { if (de2::get_instance().on_resize) de2::get_instance().on_resize(width, height); });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) { if(de2::get_instance().mouse_button_callback) de2::get_instance().mouse_button_callback(window, button, action, mods);});
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {if(de2::get_instance().cursor_pos_callback) de2::get_instance().cursor_pos_callback(window, xpos, ypos);});
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {if(de2::get_instance().mouse_wheel_callback) de2::get_instance().mouse_wheel_callback(window, xoffset, yoffset);});
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){ if(de2::get_instance().on_key) de2::get_instance().on_key(key, scancode, action, mods); });
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::exception("failed to init glad");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    resize(viewport.x, viewport.y);
}


void de2::run() {
    auto begin = std::chrono::high_resolution_clock::now();
    auto fps_begin = std::chrono::high_resolution_clock::now();
    size_t cfps = 0;
    while (!glfwWindowShouldClose(window))
    {
        GLenum err = 0;
        for (auto f : get_subs<pre_render>()) {
            f(std::chrono::high_resolution_clock::now() - begin);
        }

        for (auto f : get_subs<render>()) {
            f(std::chrono::high_resolution_clock::now() - begin);
        }

        auto end = std::chrono::high_resolution_clock::now();
        for (auto f : get_subs<post_render>()) {
            f(std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin));
        }

        begin = end;

        //term: fps counter;
        cfps++;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() > 10000000) {
            //perf = "Frame Time(msec): " + std::to_string(1000 / cfps) + " - ";
            fps = cfps;
            fps_begin = end;
            cfps = 0;
        }

        glfwSwapBuffers(de2::get_instance().window);
        glfwPollEvents();
        if (err != GL_NO_ERROR) {
            //TODO:: error handling
        }
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


//RENDERER_SYSTEM
renderer_system::renderer_system() {
    l = std::make_shared<directional_light>(glm::vec3({ 1.0, 0, 0 }));
    cam_ = std::make_shared<euler_angle_orbit>();

    de2::get_instance().mouse_button_callback = [&](GLFWwindow* window, int button, int action, int mods) { cam_->mouse_button_callback(window, button, action, mods); };
    de2::get_instance().mouse_wheel_callback = [&](GLFWwindow* window, double xoffset, double yoffset) { cam_->mouse_wheel_callback(window, xoffset, yoffset); };
    de2::get_instance().cursor_pos_callback = [&](GLFWwindow* window, double xpos, double ypos) { mouse_pos = { xpos, ypos }; cam_->cursor_pos_callback(window, xpos, ypos); };
}
void renderer_system::process(ecs_s::registry& world, std::chrono::nanoseconds& interval) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (de2::get_instance().viewport.x == 0 || de2::get_instance().viewport.x == 0)
        return;

    glm::mat4 view = get_view();
    glm::mat4 projection = get_projection();

    for (auto pp : de2::get_instance().programs) {
        pp.second->setuniform("view", view);
        pp.second->setuniform("projection", projection);
        pp.second->setuniform("view_pos", cam_->get_world_pos());

        if (l) {
            pp.second->setuniform("light.ambient", l->ambient);
            pp.second->setuniform("light.diffuse", l->diffuse);
            pp.second->setuniform("light.specular", l->specular);
            pp.second->setuniform("light.position", l->position);
        }
    }

    world.view<std::shared_ptr<model>> ([&](ecs_s::entity e, std::shared_ptr<model>& m) {
        m->draw();
    });

};

glm::mat4 renderer_system::get_view() {
    return cam_->getview();
}
glm::mat4 renderer_system::get_projection() {
    if (de2::get_instance().viewport.x == 0) {
        return glm::mat4{ 1.0f };
    }
    return glm::perspective(glm::radians(fov), (float)de2::get_instance().viewport.x / (float)de2::get_instance().viewport.y, z_near, z_far);
}

void renderer_system::enable_wireframe_mode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void renderer_system::enable_point_mode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glPointSize(5);
}
void renderer_system::enable_fill_mode() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

#pragma once
#include <optional>
#include <vector>
#include "../Abstraction/abstraction.h"
#include "../Texture/texture.h"
#include "../../glm-master/glm-master/glm/glm.hpp"
#include "../../glm-master/glm-master/glm/gtc/matrix_transform.hpp"
#include "../../glm-master/glm-master/glm/gtc/type_ptr.hpp"
#include "../Block/block.h"


struct Entity {
    GLuint VAO;
    glm::vec3 Pos;
};

class Camera : public Input{
private:
    float Yaw = -90.0f;
    float Pitch = 0.0f;
    glm::vec3 Dir = glm::vec3(0.0f,0.0f,0.0f);

    glm::vec3 CameraPos = glm::vec3(0.0f,0.0f,10.0f);
    const glm::vec3 Up = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 CameraFront = glm::vec3(0.0f,0.0f,-1.0f);
    float CameraSpeed = 50.0f;
    const float Sensitivity = 0.1f;
    GLFWwindow* Window = nullptr;

    void camera_cursor_mov();

public:
    explicit Camera(GLFWwindow* window);
    void camera_movement(float delta_time);
    glm::mat4 glm_view();

};

class Renderer {
public:
    static Renderer& get_inst();
    void add_render_target(Entity &e);
    void get_mat_loc(GLuint mloc,GLuint vloc,GLuint projloc,GLuint tloc);
    void render(glm::mat4 &view,glm::mat4 &proj,GLuint atl);
private:
    GLuint ModelLoc,ViewLoc,ProjLoc,TextureLoc;        //locations of mat uniforms in our shader
    static Renderer RendererInst;
    std::vector<Entity> RenderTargets;


    Renderer();

};





void delete_game_objs();



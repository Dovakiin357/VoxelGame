#pragma once
#include <vector>
#include"abstraction.h"
#include "texture.h"
#include "../glm-master/glm-master/glm/glm.hpp"
#include "../glm-master/glm-master/glm/gtc/matrix_transform.hpp"
#include "../glm-master/glm-master/glm/gtc/type_ptr.hpp"

struct Vector {
    float x;
    float y;

};


class GameObject : public Vertex{
public:
    static float ObjWidth;
    static float ObjHeight;
    TextureAtlas* TexAtlas;

    static std::vector<GLuint> Indices;
    static std::vector<GLfloat> Vertices;

    glm::vec3 pos;
    GameObject(glm::vec3 Pos,TextureAtlas* texture_atlas);
    ~GameObject();
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




inline std::vector<GameObject*> GameObjects;

void render_game_objects(int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc,Camera &camera,float DeltaTime);
void delete_game_objs();



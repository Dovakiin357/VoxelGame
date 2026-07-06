#pragma once
#include <vector>
#include"abstraction.h"
#include "../glm-master/glm-master/glm/glm.hpp"
#include "../glm-master/glm-master/glm/gtc/matrix_transform.hpp"
#include "../glm-master/glm-master/glm/gtc/type_ptr.hpp"

struct Vector {
    float x;
    float y;

};

class Movement {
public:
    float Speed;
    Movement(float speed);

protected:
    void move(glm::vec2 &pos);

};

class GameObject : public Vertex,public Texture{
public:
    glm::vec3 pos;
    float ObjWidth = 1.0f;
    float ObjHeight = 1.0f;

    std::vector<GLuint> Indices = {
        0,  1,  2,   2,  3,  0,  // front
        4,  5,  6,   6,  7,  4,  // back
        8,  9, 10,  10, 11,  8,  // left
       12, 13, 14,  14, 15, 12,  // right
       16, 17, 18,  18, 19, 16,  // top
       20, 21, 22,  22, 23, 20,  // bottom
    };

    GameObject(glm::vec3 Pos);
    ~GameObject();
};

class Camera {
public:
    glm::vec3 CameraPos = glm::vec3(0.0f,0.0f,5.0f);
    const glm::vec3 Up = glm::vec3(0.0f,1.0f,0.0f);
    const glm::vec3 CameraFront = glm::vec3(0.0f,0.0f,-1.0f);
    const float CameraSpeed = 0.04f;
    GLFWwindow* Window;
    explicit Camera(GLFWwindow* window);
    void camera_movement();
    glm::mat4 glm_view();

};

std::vector<float> build_quad_vertices( float width, float height);


inline std::vector<GameObject*> GameObjects;

void render_game_objects(int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc,Camera &camera);
void delete_game_objs();


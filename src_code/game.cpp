#include "game.h"
#include "glad/glad.h"
#include <array>



std::vector<float> build_cube_vertices() {
    return std::vector<float>{
        // Front face (z = +1)
        -1, -1,  1,   0, 0,
         1, -1,  1,   1, 0,
         1,  1,  1,   1, 1,
        -1,  1,  1,   0, 1,

        // Back face (z = -1)
        -1, -1, -1,   1, 0,
        -1,  1, -1,   1, 1,
         1,  1, -1,   0, 1,
         1, -1, -1,   0, 0,

        // Left face (x = -1)
        -1, -1, -1,   0, 0,
        -1, -1,  1,   1, 0,
        -1,  1,  1,   1, 1,
        -1,  1, -1,   0, 1,

        // Right face (x = +1)
         1, -1,  1,   0, 0,
         1, -1, -1,   1, 0,
         1,  1, -1,   1, 1,
         1,  1,  1,   0, 1,

        // Top face (y = +1)
        -1,  1,  1,   0, 0,
         1,  1,  1,   1, 0,
         1,  1, -1,   1, 1,
        -1,  1, -1,   0, 1,

        // Bottom face (y = -1)
        -1, -1, -1,   0, 0,
         1, -1, -1,   1, 0,
         1, -1,  1,   1, 1,
        -1, -1,  1,   0, 1,
    };
}

std::vector<GLuint> build_cube_indices() {
    return std::vector<GLuint>{
        // Front face (Vertices 0, 1, 2, 3)
        0,  1,  2,      2,  3,  0,

        // Back face (Vertices 4, 5, 6, 7)
        4,  5,  6,      6,  7,  4,

        // Left face (Vertices 8, 9, 10, 11)
        8,  9, 10,     10, 11,  8,

        // Right face (Vertices 12, 13, 14, 15)
        12, 13, 14,     14, 15, 12,

        // Top face (Vertices 16, 17, 18, 19)
        16, 17, 18,     18, 19, 16,

        // Bottom face (Vertices 20, 21, 22, 23)
        20, 21, 22,     22, 23, 20
    };
}

float GameObject::ObjWidth = 1.0f;
float GameObject::ObjHeight = 1.0f;

std::vector<GLuint> GameObject::Indices = build_cube_indices();
std::vector<GLfloat> GameObject::Vertices = build_cube_vertices();




GameObject::GameObject(glm::vec3 Pos,TextureAtlas* texture_atlas)
    :pos(Pos),Vertex(Vertices,Indices),TexAtlas(texture_atlas)
{
    GameObjects.push_back(this);
}

GameObject::~GameObject() {
    std::erase(GameObjects,this);
}


void draw(GameObject &obj,int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc,Camera &camera,float DeltaTime) {
    auto Model = glm::mat4(1.0f);

    Model = glm::translate(Model, glm::vec3(obj.pos));
    Model = glm::scale(Model, glm::vec3(GameObject::ObjWidth, GameObject::ObjHeight, 1.0f));

    glm::mat4 View = camera.glm_view();
    glUniformMatrix4fv(ModelLoc,1,GL_FALSE,glm::value_ptr(Model));
    glUniformMatrix4fv(ViewLoc,1,GL_FALSE,glm::value_ptr(View));

    glActiveTexture(GL_TEXTURE0 + TextureUnit);
    glBindTexture(GL_TEXTURE_2D,obj.TexAtlas->Atlas);
    glUniform1i(TextureLoc,TextureUnit);

    glBindVertexArray(obj.VAO);
    glDrawElements(GL_TRIANGLES,(int)GameObject::Indices.size(),GL_UNSIGNED_INT,nullptr);
}



void render_game_objects(int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc,Camera &camera,float DeltaTime) {
    for (GameObject *obj:GameObjects) {
        draw(*(obj),ModelLoc,TextureLoc,TextureUnit,ViewLoc,camera,DeltaTime);
    }
}

void delete_game_objs() {
    for (GameObject *obj:GameObjects) {
        obj->~GameObject();   }
}



Camera::Camera(GLFWwindow* window)
    :Window(window),Input(window)
{
    Dir.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    Dir.y = glm::sin(glm::radians(Pitch));
    Dir.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
}

void Camera::camera_cursor_mov() {
    float xOffset = CursorPosX - LastX;
    float yOffset = CursorPosY - LastY;

    LastX = CursorPosX;
    LastY = CursorPosY;


    if (IsPressingLeftMouse) {
        xOffset *= Sensitivity;
        yOffset *= Sensitivity;

        Yaw += xOffset;
        Pitch += yOffset;

        if(Pitch > 89.0f)
            Pitch =  89.0f;
        if(Pitch < -89.0f)
            Pitch = -89.0f;

        Dir.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
        Dir.y = glm::sin(glm::radians(Pitch));
        Dir.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
    }
}



void Camera::camera_movement(float delta_time) {

    float Speed =  CameraSpeed * delta_time;
    camera_cursor_mov();
    CameraFront = glm::normalize(Dir);


    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
        CameraPos += Speed * CameraFront;
    if  (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
        CameraPos -= Speed * CameraFront;
    if(glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
        CameraPos -=  glm::normalize(glm::cross(CameraFront,Up)) * Speed;
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
        CameraPos += glm::normalize(glm::cross(CameraFront,Up)) * Speed;
}


glm::mat4 Camera::glm_view() {
    glm::mat4 View = glm::lookAt(CameraPos,CameraFront+CameraPos,Up);
    return View;
}












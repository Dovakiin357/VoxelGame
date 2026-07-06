#include "game.h"
#include "glad/glad.h"
#include <array>



std::vector<float> build_cube_vertices() {
    return {
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

Movement::Movement(float speed) {
    this->Speed = speed;
}

void Movement::move(glm::vec2 &pos) {
    pos.x += this->Speed;
}

GameObject::GameObject(glm::vec3 Pos) {
    this->pos = Pos;
    GameObjects.push_back(this);


   std::vector<float> Vertices = build_cube_vertices();
    vertex_setup(Vertices,Indices);
    texture_setup();
}

GameObject::~GameObject() {
    std::erase(GameObjects,this);

}


void draw(GameObject &obj,int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc,Camera &camera) {
    glm::mat4 Model = glm::mat4(1.0f);

    Model = glm::translate(Model, glm::vec3(obj.pos));
    Model = glm::rotate(Model,(float)glfwGetTime() * glm::radians(50.0f),glm::vec3(0.5f,1.0f,0.0f));
    Model = glm::scale(Model, glm::vec3(obj.ObjWidth, obj.ObjHeight, 1.0f));

    glm::mat4 View = camera.glm_view();
    camera.camera_movement();
    glUniformMatrix4fv(ModelLoc,1,GL_FALSE,glm::value_ptr(Model));
    glUniformMatrix4fv(ViewLoc,1,GL_FALSE,glm::value_ptr(View));

    glActiveTexture(GL_TEXTURE0 + TextureUnit);
    glBindTexture(GL_TEXTURE_2D,obj.TextureObj);
    glUniform1i(TextureLoc,TextureUnit);

    glBindVertexArray(obj.VAO);
    glDrawElements(GL_TRIANGLES,obj.Indices.size(),GL_UNSIGNED_INT,0);

}



void render_game_objects(int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc,Camera &camera) {
    for (GameObject *obj:GameObjects) {
        draw(*(obj),ModelLoc,TextureLoc,TextureUnit,ViewLoc,camera);
    }
}

void delete_game_objs() {
    for (GameObject *obj:GameObjects) {
        obj->~GameObject();   }
}
Camera::Camera(GLFWwindow* window) {
    Window = window;
}

void Camera::camera_movement() {
    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
        CameraPos += CameraSpeed * CameraFront;
    if  (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
        CameraPos -= CameraSpeed * CameraFront;
    if(glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
        CameraPos -=  glm::normalize(glm::cross(CameraFront,Up)) * CameraSpeed;
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
        CameraPos += glm::normalize(glm::cross(CameraFront,Up)) * CameraSpeed;
}

glm::mat4 Camera::glm_view() {
    glm::mat4 View = glm::lookAt(CameraPos,CameraFront+CameraPos,Up);
    std::cout << CameraPos.x;
    return View;
}












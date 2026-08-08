#include "game.h"
#include "glad/glad.h"
#include <array>






void draw(Block &obj,int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc,Camera &camera,float DeltaTime) {
    auto Model = glm::mat4(1.0f);

    Model = glm::translate(Model, glm::vec3(obj.Pos));
    Model = glm::scale(Model, glm::vec3(1.0f, 1.0f, 1.0f));

    glm::mat4 View = camera.glm_view();
    glUniformMatrix4fv(ModelLoc,1,GL_FALSE,glm::value_ptr(Model));
    glUniformMatrix4fv(ViewLoc,1,GL_FALSE,glm::value_ptr(View));

    glActiveTexture(GL_TEXTURE0 + TextureUnit);
    glBindTexture(GL_TEXTURE_2D,obj.TexAtlas->Atlas);
    glUniform1i(TextureLoc,TextureUnit);

    glBindVertexArray(obj.VAO);
    glDrawElements(GL_TRIANGLES,(int)Block::Indices.size(),GL_UNSIGNED_INT,nullptr);
}



void render_game_objects(int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc,Camera &camera,float DeltaTime) {
    for (auto *obj:Blocks) {
        draw(*(obj),ModelLoc,TextureLoc,TextureUnit,ViewLoc,camera,DeltaTime);
    }
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












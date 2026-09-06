#include "../Game/game.h"
#include "glad/glad.h"
#include <array>

#include "../Chunk/chunk.h"


BlockManager::BlockManager() = default;
BlockManager BlockManager::blockmanager;
BlockManager &BlockManager::get_inst() {return blockmanager;}

void BlockManager::add_block_mesh(BlockTypes t,std::vector<Vertex> bmesh) {
    BlockDataBase.insert({t,bmesh});
}


const std::vector<Vertex>& BlockManager::get_block_mesh(BlockTypes t) {
    return BlockDataBase.at(t);
}

Renderer::Renderer() = default;
Renderer Renderer::RendererInst;
Renderer &Renderer::get_inst() {return RendererInst;}

void Renderer::add_render_target(Entity &e) {RenderTargets.push_back(e);}
void Renderer::get_mat_loc(GLuint mloc, GLuint vloc, GLuint projloc,GLuint tloc) {
    ModelLoc = mloc;
    ViewLoc = vloc;
    ProjLoc = projloc;
    TextureLoc = tloc;
}

void Renderer::render(glm::mat4 &view, glm::mat4 &proj, GLuint atl) {


    for (auto const& obj:RenderTargets) {
        auto Model = glm::mat4(1.0f);
        Model = glm::translate(Model, glm::vec3(obj.Pos));

        glUniformMatrix4fv((int)ModelLoc,1,GL_FALSE,glm::value_ptr(Model));
        glUniformMatrix4fv((int)ViewLoc,1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv((int)ProjLoc,1,GL_FALSE,glm::value_ptr(proj));

        glActiveTexture(0);   //we get all textures from atlas
        glBindTexture(GL_TEXTURE_2D,atl);
        glUniform1i((int)TextureLoc,0);

        glBindVertexArray(obj.VAO);
        glDrawArrays(GL_TRIANGLES,0,CHUNK_VERTEX_COUNT);
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












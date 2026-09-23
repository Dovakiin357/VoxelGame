#include "../Game/game.h"
#include "glad/glad.h"
#include <array>

#include "../Chunk/chunk.h"




Renderer::Renderer() = default;
Renderer Renderer::RendererInst;
Renderer &Renderer::get_inst() {return RendererInst;}

void Renderer::add_render_target(GameObj &obj) {RenderTargets.push_back(obj);}
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
















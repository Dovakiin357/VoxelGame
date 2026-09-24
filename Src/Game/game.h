#pragma once
#include <vector>
#include "../Abstraction/abstraction.h"
#include "../Texture/texture.h"
#include "../../glm-master/glm-master/glm/glm.hpp"
#include "../../glm-master/glm-master/glm/gtc/matrix_transform.hpp"
#include "../../glm-master/glm-master/glm/gtc/type_ptr.hpp"
#include "../Block/block.h"


struct GameObj {
    GLuint VAO;
    glm::vec3 Pos;
};


class Renderer {
public:
    static Renderer& get_inst();
    void add_render_target(GameObj &obj);
    void get_mat_loc(GLuint mloc,GLuint vloc,GLuint projloc,GLuint tloc);
    void render(glm::mat4 &view,glm::mat4 &proj,GLuint atl);

    Renderer(const Renderer& other) = delete;
private:
    GLuint ModelLoc,ViewLoc,ProjLoc,TextureLoc;        //locations of mat uniforms in our shader
    static Renderer RendererInst;
    std::vector<GameObj> RenderTargets;

    Renderer();
};





void delete_game_objs();



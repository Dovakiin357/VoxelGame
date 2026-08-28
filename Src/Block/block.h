#pragma once
#include "../Game/game.h"

#include "glad/glad.h"
#include "glm-master/glm/vec3.hpp"
#include "../Texture/texture.h"

struct Block {
    BlockTypes Type = Air;  //let default be air
};


std::vector<Vertex> make_block_mesh(TextureAtlas &ta,BlockTypes type);
void add_uv_face(Tex &texture,std::vector<Vertex> &mesh,const std::vector<Vertex> &Face);


void create_blocks(size_t count,std::vector<Vertex> &Bmesh);




#pragma once
#include "../Game/game.h"

#include "glad/glad.h"
#include "glm-master/glm/vec3.hpp"
#include "../Texture/texture.h"

struct Block {
    BlockTypes Type = Air;  //let default be air
};

class BlockManager {
public:
    static BlockManager& get_inst();
    void add_block_mesh(BlockTypes t,std::vector<Vertex> bmesh);
    const std::vector<Vertex>& get_block_mesh(BlockTypes t);  //returns a block mesh from DataBase
    BlockManager(const BlockManager& other) = delete;
private:
    static BlockManager blockmanager;
    std::unordered_map<BlockTypes,const std::vector<Vertex>> BlockDataBase = {};
    BlockManager();
};


std::vector<Vertex> make_block_mesh(TextureAtlas &ta,BlockTypes type);
void add_uv_face(Tex &texture,std::vector<Vertex> &mesh,const std::vector<Vertex> &Face);


void create_blocks(size_t count,const std::vector<Vertex> &Bmesh);




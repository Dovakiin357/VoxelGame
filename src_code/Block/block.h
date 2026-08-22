#pragma once
#include "../Game/game.h"

#include "glad/glad.h"
#include "glm-master/glm/vec3.hpp"
#include "../Texture/texture.h"



// class Block{
// public:
//     GLuint VAO;
//     glm::vec3 Pos;
//     TextureAtlas* TexAtlas;
//     std::vector<Vertex> mesh;
//     static std::vector<GLuint> Indices;
//     Block(glm::vec3 pos,TextureAtlas* ta);
//     ~Block();
// private:
//     // static const  std::vector<Vertex> LeftFace;
//     // static const  std::vector<Vertex> RightFace;
//     // static const  std::vector<Vertex> TopFace;
//     // static const  std::vector<Vertex> BottomFace;
//     // static const std::vector<Vertex> FrontFace;
//     // static const std::vector<Vertex> BackFace;
// };

std::vector<Vertex> make_block_mesh(TextureAtlas &ta,BlockTypes type);
void add_uv_face(Tex &texture,std::vector<Vertex> &mesh,const std::vector<Vertex> &Face);

// inline std::vector<Entity> RenderTargets;
void create_blocks(size_t count,std::vector<Vertex> &Bmesh);




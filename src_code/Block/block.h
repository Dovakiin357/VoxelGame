#pragma once
#include "../Abstraction/abstraction.h"
#include "glad/glad.h"
#include "glm-master/glm/vec3.hpp"
#include "../Texture/texture.h"




class Block{
public:
    GLuint VAO;
    glm::vec3 Pos;
    TextureAtlas* TexAtlas;
    std::vector<Vertex> mesh;
    static std::vector<GLuint> Indices;
    Block(glm::vec3 pos,TextureAtlas* ta);
    ~Block();
private:
    static const  std::vector<Vertex> LeftFace;
    static const  std::vector<Vertex> RightFace;
    static const  std::vector<Vertex> TopFace;
    static const  std::vector<Vertex> BottomFace;
    static const std::vector<Vertex> FrontFace;
    static const std::vector<Vertex> BackFace;


};
// inline int count = 300;
inline std::vector<Block*> Blocks;
void  add_face(Block* b,const std::vector<Vertex> &vert,const std::string &k);

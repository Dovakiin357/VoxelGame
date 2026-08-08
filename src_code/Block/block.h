#pragma once
#include "../abstraction.h"
#include "glad/glad.h"
#include "glm-master/glm/vec3.hpp"
#include "../texture.h"




class Block{
public:
    GLuint VAO;
    glm::vec3 Pos;
    TextureAtlas* TexAtlas;
    std::vector<GLfloat> mesh;
    static std::vector<GLuint> Indices;
    Block(glm::vec3 pos,TextureAtlas* ta);
    ~Block();
private:
    static const  std::vector<GLfloat> LeftFace;
    static const  std::vector<GLfloat> RightFace;
    static const  std::vector<GLfloat> TopFace;
    static const  std::vector<GLfloat> BottomFace;
    static const std::vector<GLfloat> FrontFace;


};
// inline int count = 300;
inline std::vector<Block*> Blocks;
void  add_face(Block* b,const std::vector<GLfloat> &vert,const std::string &k);

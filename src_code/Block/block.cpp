#include "block.h"

// Format per vertex: Position (X, Y, Z), UV (U, V)

// Front Face (+Z)
// const std::vector<GLfloat> Block::FrontFace = {
//  // Position           // UV
//  // Triangle 1
//  0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
//  1.0f, 0.0f, 1.0f,    1.0f, 0.0f,
//  1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
//  // Triangle 2
//  1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
//  0.0f, 1.0f, 1.0f,    0.0f, 1.0f,
//  0.0f, 0.0f, 1.0f,    0.0f, 0.0f
// };

const std::vector<GLfloat> Block::FrontFace = {
 0.0f, 0.0f, 1.0f,     // 0: Bottom-Left
 1.0f, 0.0f, 1.0f,     // 1: Bottom-Right
 1.0f, 1.0f, 1.0f,     // 2: Top-Right
 0.0f, 1.0f, 1.0f,     // 3: Top-Left
};

// Left Face (-X)
const std::vector<GLfloat> Block::LeftFace = {
 // Position           // UV
 // Triangle 1
 0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
 0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
 0.0f, 1.0f, 1.0f,    1.0f, 1.0f,
 // Triangle 2
 0.0f, 1.0f, 1.0f,    1.0f, 1.0f,
 0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
 0.0f, 0.0f, 0.0f,    0.0f, 0.0f
};

// Right Face (+X)
const std::vector<GLfloat> Block::RightFace = {
 // Position           // UV
 // Triangle 1
 1.0f, 0.0f, 1.0f,    0.0f, 0.0f,
 1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
 1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
 // Triangle 2
 1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
 1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
 1.0f, 0.0f, 1.0f,    0.0f, 0.0f
};

// Top Face (+Y)
const std::vector<GLfloat> Block::TopFace = {
 // Position           // UV
 // Triangle 1
 0.0f, 1.0f, 1.0f,    0.0f, 0.0f,
 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
 1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
 // Triangle 2
 1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
 0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
 0.0f, 1.0f, 1.0f,    0.0f, 0.0f
};

// Bottom Face (-Y)
const std::vector<GLfloat> Block::BottomFace = {
 // Position
 // Triangle 1
 0.0f, 0.0f, 0.0f,
 1.0f, 0.0f, 0.0f,
 1.0f, 0.0f, 1.0f,
 // Triangle 2
 1.0f, 0.0f, 1.0f,
 0.0f, 0.0f, 1.0f,
 0.0f, 0.0f, 0.0f,
};


std::vector<GLuint> Block::Indices = {
 // Front face (Vertices 0, 1, 2, 3)
 0, 1, 2,  2, 3, 0

};


void add_face(Block *b, const std::vector<GLfloat> &vert, const std::string &k) {
 Tex t = TextureManager::Textures[k];
 std::vector<GLfloat> uv = get_norm(t, b->TexAtlas->AtlasWidth, b->TexAtlas->AtlasHeight);

 // Remove b->mesh.insert()! Only use the interleaving loop:
 for (int v = 0; v < 4; ++v) {
  // Position (X, Y, Z)
  b->mesh.push_back(vert[v * 3 + 0]);
  b->mesh.push_back(vert[v * 3 + 1]);
  b->mesh.push_back(vert[v * 3 + 2]);

  // UV (U, V)
  b->mesh.push_back(uv[v * 2 + 0]);
  b->mesh.push_back(uv[v * 2 + 1]);
 }
}


Block::Block(glm::vec3 pos,TextureAtlas* ta) :Pos(pos),TexAtlas(ta){
 add_face(this,Block::FrontFace,"Resources/dirt.jpg");
 Blocks.push_back(this);
 set_vao(this->VAO,this->mesh,Block::Indices);

}

Block::~Block() {
 std::erase(Blocks,this);
}




#include "block.h"

// Format per vertex: Position (X, Y, Z), UV (U, V)

// // Front Face (+Z)
// const std::vector<Vertex> Block::FrontFace = {
//  { glm::vec3(0.0f, 0.0f, 1.0f)}, // Index 0: Bottom-Left
//  { glm::vec3(1.0f, 0.0f, 1.0f)}, // Index 1: Bottom-Right
//  { glm::vec3(1.0f, 1.0f, 1.0f)}, // Index 2: Top-Right
//  { glm::vec3(0.0f, 1.0f, 1.0f)}  // Index 3: Top-Left
//
// };
//
//
// // Left Face (-X)
// const std::vector<Vertex> Block::LeftFace = {
//  { glm::vec3(0.0f, 0.0f, 0.0f) }, // 0: Bottom-Left
//  { glm::vec3(0.0f, 0.0f, 1.0f) }, // 1: Bottom-Right
//  { glm::vec3(0.0f, 1.0f, 1.0f) }, // 2: Top-Right
//  { glm::vec3(0.0f, 1.0f, 0.0f) }  // 3: Top-Left
// };
//
// // Right Face (+X)
// const std::vector<Vertex> Block::RightFace = {
//  { glm::vec3(1.0f, 0.0f, 1.0f) }, // 0: Bottom-Left
//  { glm::vec3(1.0f, 0.0f, 0.0f) }, // 1: Bottom-Right
//  { glm::vec3(1.0f, 1.0f, 0.0f) }, // 2: Top-Right
//  { glm::vec3(1.0f, 1.0f, 1.0f) }  // 3: Top-Left
// };
//
// // Top Face (+Y)
// const std::vector<Vertex> Block::TopFace = {
//  { glm::vec3(0.0f, 1.0f, 1.0f) }, // 0: Bottom-Left
//  { glm::vec3(1.0f, 1.0f, 1.0f) }, // 1: Bottom-Right
//  { glm::vec3(1.0f, 1.0f, 0.0f) }, // 2: Top-Right
//  { glm::vec3(0.0f, 1.0f, 0.0f) }  // 3: Top-Left
// };
//
// // Bottom Face (-Y)
// const std::vector<Vertex> Block::BottomFace = {
//  { glm::vec3(0.0f, 0.0f, 0.0f) }, // 0: Bottom-Left
//  { glm::vec3(1.0f, 0.0f, 0.0f) }, // 1: Bottom-Right
//  { glm::vec3(1.0f, 0.0f, 1.0f) }, // 2: Top-Right
//  { glm::vec3(0.0f, 0.0f, 1.0f) }  // 3: Top-Left
// };
//
// const std::vector<Vertex> Block::BackFace = {
//  { glm::vec3(1.0f, 0.0f, 0.0f) }, // 0: Bottom-Left
//  { glm::vec3(0.0f, 0.0f, 0.0f) }, // 1: Bottom-Right
//  { glm::vec3(0.0f, 1.0f, 0.0f) }, // 2: Top-Right
//  { glm::vec3(1.0f, 1.0f, 0.0f) }  // 3: Top-Left
// };



//  std::vector<GLuint> Block::Indices = {
//  // Front
//  0, 1, 2, 2, 3, 0,
//  // Back
//  4, 5, 6, 6, 7, 4,
//  // Left
//  8, 9, 10, 10, 11, 8,
//  // Right
//  12, 13, 14, 14, 15, 12,
//  // Top
//  16, 17, 18, 18, 19, 16,
//  // Bottom
//  20, 21, 22, 22, 23, 20
// };


// void add_face(Block *b, const std::vector<Vertex> &vert,BlockTypes type) {
//  Tex tex = b->TexAtlas->Textures[type];
//
//  for(size_t i = 0;i < vert.size();i++) {
//   Vertex v = vert[i];
//   v.uv = tex.uv[i];
//   b->mesh.push_back(v);
//  }
// }




// Block::Block(glm::vec3 pos,TextureAtlas* ta) :Pos(pos),TexAtlas(ta){
//
//  add_face(this,Block::FrontFace,DirtGrass);
//  add_face(this,Block::BackFace,DirtGrass);
//  add_face(this,Block::LeftFace,DirtGrass);
//  add_face(this,Block::RightFace,DirtGrass);
//  add_face(this,Block::TopFace,Grass);
//  add_face(this,Block::BottomFace,Dirt);
//
//  Blocks.push_back(this);
//  set_vao(this->VAO,this->mesh,Block::Indices);
//
// }

// Block::~Block() {
// //  std::erase(Blocks,this);
// // }


void add_uv_face(Tex &texture, std::vector<Vertex> &mesh,const std::vector<Vertex> &Face) {

 for (size_t i = 0;i < Face.size();i++) {
  Vertex v = Face[i];
  v.uv = texture.uv[i];
  mesh.push_back(v);
 }

}


std::vector<Vertex> make_block_mesh(TextureAtlas &ta,BlockTypes type) {
 // Front Face (+Z)
 static const std::vector<Vertex> FrontFace = {
  { glm::vec3(0.0f, 0.0f, 1.0f)}, // Index 0: Bottom-Left
  { glm::vec3(1.0f, 0.0f, 1.0f)}, // Index 1: Bottom-Right
  { glm::vec3(1.0f, 1.0f, 1.0f)}, // Index 2: Top-Right
  { glm::vec3(0.0f, 1.0f, 1.0f)}  // Index 3: Top-Left

 };


 // Left Face (-X)
 static const std::vector<Vertex> LeftFace = {
  { glm::vec3(0.0f, 0.0f, 0.0f) }, // 0: Bottom-Left
  { glm::vec3(0.0f, 0.0f, 1.0f) }, // 1: Bottom-Right
  { glm::vec3(0.0f, 1.0f, 1.0f) }, // 2: Top-Right
  { glm::vec3(0.0f, 1.0f, 0.0f) }  // 3: Top-Left
 };

 // Right Face (+X)
 static const std::vector<Vertex> RightFace = {
  { glm::vec3(1.0f, 0.0f, 1.0f) }, // 0: Bottom-Left
  { glm::vec3(1.0f, 0.0f, 0.0f) }, // 1: Bottom-Right
  { glm::vec3(1.0f, 1.0f, 0.0f) }, // 2: Top-Right
  { glm::vec3(1.0f, 1.0f, 1.0f) }  // 3: Top-Left
 };

 // Top Face (+Y)
 static const std::vector<Vertex> TopFace = {
  { glm::vec3(0.0f, 1.0f, 1.0f) }, // 0: Bottom-Left
  { glm::vec3(1.0f, 1.0f, 1.0f) }, // 1: Bottom-Right
  { glm::vec3(1.0f, 1.0f, 0.0f) }, // 2: Top-Right
  { glm::vec3(0.0f, 1.0f, 0.0f) }  // 3: Top-Left
 };

 // Bottom Face (-Y)
 static const std::vector<Vertex> BottomFace = {
  { glm::vec3(0.0f, 0.0f, 0.0f) }, // 0: Bottom-Left
  { glm::vec3(1.0f, 0.0f, 0.0f) }, // 1: Bottom-Right
  { glm::vec3(1.0f, 0.0f, 1.0f) }, // 2: Top-Right
  { glm::vec3(0.0f, 0.0f, 1.0f) }  // 3: Top-Left
 };

 static const std::vector<Vertex> BackFace = {
  { glm::vec3(1.0f, 0.0f, 0.0f) }, // 0: Bottom-Left
  { glm::vec3(0.0f, 0.0f, 0.0f) }, // 1: Bottom-Right
  { glm::vec3(0.0f, 1.0f, 0.0f) }, // 2: Top-Right
  { glm::vec3(1.0f, 1.0f, 0.0f) }  // 3: Top-Left
 };

 std::vector<Vertex> mesh;


 switch (type) {
  case DirtGrass: {
   Tex DirtTex = ta.Textures[Dirt];
   Tex DirtGrassTex = ta.Textures[DirtGrass];
   Tex GrassTex = ta.Textures[Grass];

   add_uv_face(DirtGrassTex,mesh,FrontFace);
   add_uv_face(DirtGrassTex,mesh,BackFace);
   add_uv_face(DirtGrassTex,mesh,LeftFace);

   add_uv_face(DirtGrassTex,mesh,RightFace);
   add_uv_face(GrassTex,mesh,TopFace);
   add_uv_face(DirtTex,mesh,BottomFace);
   break;
  }
  default: {
   std::cout << "runs";
   Tex texture = ta.Textures[type];
   add_uv_face(texture,mesh,FrontFace);
   add_uv_face(texture,mesh,BackFace);
   add_uv_face(texture,mesh,LeftFace);

   add_uv_face(texture,mesh,RightFace);
   add_uv_face(texture,mesh,TopFace);
   add_uv_face(texture,mesh,BottomFace);
   break;
  }
 }

 return mesh;

}

void create_blocks(size_t count,std::vector<Vertex> &Bmesh) {
 static std::vector<GLuint> Indices = {
  // Front
  0, 1, 2, 2, 3, 0,
  // Back
  4, 5, 6, 6, 7, 4,
  // Left
  8, 9, 10, 10, 11, 8,
  // Right
  12, 13, 14, 14, 15, 12,
  // Top
  16, 17, 18, 18, 19, 16,
  // Bottom
  20, 21, 22, 22, 23, 20
 };
 static float x_off = 1.0f;
 for (size_t i = 0;i <= count;i++) {
  GLuint vao;
  set_vao(vao,Bmesh,Indices);
  RenderTargets.push_back(Entity{vao,glm::vec3(x_off,0.0f,0.0f),&Indices});
  x_off += 1.0f;
 }
}






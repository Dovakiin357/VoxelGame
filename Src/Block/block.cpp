#include "block.h"


BlockManager::BlockManager() = default;
BlockManager BlockManager::blockmanager;
BlockManager &BlockManager::get_inst() {return blockmanager;}

void BlockManager::add_block_mesh(BlockTypes t,std::vector<Vertex> bmesh) {
 BlockDataBase.insert({t,bmesh});
}


const std::vector<Vertex>& BlockManager::get_block_mesh(BlockTypes t) {
 return BlockDataBase.at(t);
}


void add_uv_face(Tex &texture, std::vector<Vertex> &mesh,const std::vector<Vertex> &Face) {

 static const std::array<int, 6> uvIndices = { 0, 3, 2, 2, 1, 0 };

 for (size_t i = 0;i < Face.size();i++) {
  Vertex v = Face[i];
  v.uv = texture.uv[uvIndices[i]];
  mesh.push_back(v);
 }

}


std::vector<Vertex> make_block_mesh(TextureAtlas &ta,BlockTypes type) {
 static const std::vector<Vertex> FrontFace = {
  { glm::vec3(0.0f, 0.0f, 1.0f) },
  { glm::vec3(0.0f, 1.0f, 1.0f) },
  { glm::vec3(1.0f, 1.0f, 1.0f) },
  { glm::vec3(1.0f, 1.0f, 1.0f) },
  { glm::vec3(1.0f, 0.0f, 1.0f) },
  { glm::vec3(0.0f, 0.0f, 1.0f) }
 };

 static const std::vector<Vertex> LeftFace = {
  { glm::vec3(0.0f, 0.0f, 0.0f) },
  { glm::vec3(0.0f, 1.0f, 0.0f) },
  { glm::vec3(0.0f, 1.0f, 1.0f) },
  { glm::vec3(0.0f, 1.0f, 1.0f) },
  { glm::vec3(0.0f, 0.0f, 1.0f) },
  { glm::vec3(0.0f, 0.0f, 0.0f) }
 };

 static const std::vector<Vertex> RightFace = {
  { glm::vec3(1.0f, 0.0f, 1.0f) },
  { glm::vec3(1.0f, 1.0f, 1.0f) },
  { glm::vec3(1.0f, 1.0f, 0.0f) },
  { glm::vec3(1.0f, 1.0f, 0.0f) },
  { glm::vec3(1.0f, 0.0f, 0.0f) },
  { glm::vec3(1.0f, 0.0f, 1.0f) }
 };

 static const std::vector<Vertex> TopFace = {
  { glm::vec3(0.0f, 1.0f, 1.0f) },
  { glm::vec3(0.0f, 1.0f, 0.0f) },
  { glm::vec3(1.0f, 1.0f, 0.0f) },
  { glm::vec3(1.0f, 1.0f, 0.0f) },
  { glm::vec3(1.0f, 1.0f, 1.0f) },
  { glm::vec3(0.0f, 1.0f, 1.0f) }
 };

 static const std::vector<Vertex> BottomFace = {
  { glm::vec3(0.0f, 0.0f, 0.0f) },
  { glm::vec3(0.0f, 0.0f, 1.0f) },
  { glm::vec3(1.0f, 0.0f, 1.0f) },
  { glm::vec3(1.0f, 0.0f, 1.0f) },
  { glm::vec3(1.0f, 0.0f, 0.0f) },
  { glm::vec3(0.0f, 0.0f, 0.0f) }
 };

 static const std::vector<Vertex> BackFace = {
  { glm::vec3(1.0f, 0.0f, 0.0f) },
  { glm::vec3(1.0f, 1.0f, 0.0f) },
  { glm::vec3(0.0f, 1.0f, 0.0f) },
  { glm::vec3(0.0f, 1.0f, 0.0f) },
  { glm::vec3(0.0f, 0.0f, 0.0f) },
  { glm::vec3(1.0f, 0.0f, 0.0f) }
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

void create_blocks(size_t count,const std::vector<Vertex> &Bmesh) {

 static float x_off = 1.0f;
 GameObj e = {};
 for (size_t i = 0;i <= count;i++) {
  GLuint vao;
  set_vao(vao,Bmesh);

  e.VAO = vao;
  e.Pos = glm::vec3(0.0f,0.0f,x_off);

  Renderer::get_inst().add_render_target(e);
  x_off += 1.0f;
 }
}






#pragma once
#include "../Game/game.h"

#include "glad/glad.h"
#include "glm-master/glm/vec3.hpp"
#include "../Texture/texture.h"

struct Block {
    BlockTypes Type = Air;  //let default be air
};

enum BlockFace {
    RightFace,LeftFace,
    TopFace,BottomFace,
    FrontFace,Backface,
};



struct Face {
public:

    static size_t FACE_VERTEX_COUNT;

    static const std::array<Vertex,6>LeftFaceVertPos;
    static const std::array<Vertex,6>RightFaceVertPos;
    static const std::array<Vertex,6>TopFaceVertPos;

    static const std::array<Vertex,6>BottomFaceVertPos;
    static const std::array<Vertex,6>FrontFaceVertPos;
    static const std::array<Vertex,6>BackFaceVertPos;

    BlockFace FaceType;
    std::array<Vertex,6> FaceVertices;
};

struct BlockMesh {
    Face LeftFaceMesh{BlockFace::LeftFace, Face::LeftFaceVertPos};
    Face RightFaceMesh{BlockFace::RightFace, Face::RightFaceVertPos};
    Face TopFaceMesh{BlockFace::TopFace, Face::TopFaceVertPos};

    Face BottomFaceMesh{BlockFace::BottomFace, Face::BottomFaceVertPos};
    Face FrontFaceMesh{BlockFace::FrontFace, Face::FrontFaceVertPos};
    Face BackFaceMesh{BlockFace::Backface, Face::BackFaceVertPos};

    BlockTypes BlockType;
    std::vector<Vertex> MeshData;

    BlockMesh(BlockTypes types,const TextureAtlas &ta);
};


class BlockManager {
public:
    static BlockManager& get_inst();
    void add_block_mesh(BlockTypes t,const TextureAtlas &ta); //creates a block mesh and adds it to database
    const BlockMesh& get_block_mesh(BlockTypes t);  //returns a block mesh from DataBase
    BlockManager(const BlockManager& other) = delete;
private:
    static BlockManager blockmanager;
    std::unordered_map<BlockTypes,BlockMesh> BlockDataBase = {};
    BlockManager();
};


// std::vector<Vertex> make_block_mesh(TextureAtlas &ta,BlockTypes type);
std::vector<Vertex> create_block_mesh(TextureAtlas &ta,BlockTypes type);

// void add_uv_face(Tex &texture,std::vector<Vertex> &mesh,const std::vector<Vertex> &Face);

//mesh refers to the Block mesh on which we are adding the Face Pos data and UV data of "texture"
void add_face_vertices(Tex &texture,std::vector<Vertex> &mesh, Face &face);

// void create_blocks(size_t count,const std::vector<Vertex> &Bmesh);




#pragma once
#include "../Block/block.h"

constexpr int CHUNK_X = 16;
constexpr int CHUNK_Y = 256;
constexpr int CHUNK_Z = 16;

constexpr int CHUNK_DATA_SIZE = CHUNK_X * CHUNK_Y * CHUNK_Z * 36;



class Chunk {
public:
    Chunk(BlockTypes t,const std::unordered_map<BlockTypes,std::vector<Vertex>> &bmeshes);
private:
    Block chunk[CHUNK_X][CHUNK_Y][CHUNK_Z];
    std::vector<Vertex> ChunkVertices;
    GLuint VAO,VBO;

    // void create_chunk_mesh(const std::unordered_map<BlockTypes,std::vector<Vertex>> &bmeshes);
    // void set_chunk_vao();


};

struct CHUNK {
    Block chunk[CHUNK_X][CHUNK_Y][CHUNK_Z];
    std::vector<Vertex> ChunkVertices;
    GLuint VAO,VBO;
};

void create_chunks(int count);


    // Chunk(BlockTypes t,const auto &bmeshes) {
    //     for (int i = 0;i < CHUNK_X;i++) {
    //         for (int j = 0;j < CHUNK_Y;j++) {
    //             for (int k = 0;k < CHUNK_Z;k++) {
    //                 chunk[i][j][k].Type = Grass;
    //             }
    //         }
    //     }

    // Block chunk[CHUNK_X][CHUNK_Y][CHUNK_Z];
    // std::vector<Vertex> Vertices = {};
    // GLuint VAO = 0,VBO = 0;
#pragma once
#include "../Block/block.h"

constexpr int CHUNK_X = 16;
constexpr int CHUNK_Y = 16;
constexpr int CHUNK_Z = 16;

constexpr int CHUNK_VERTEX_COUNT = CHUNK_X * CHUNK_Y * CHUNK_Z * 36;



struct Chunk {
    Block ChunkBlocks[CHUNK_X][CHUNK_Y][CHUNK_Z];
    glm::vec3 WorldPos;

    std::vector<Vertex> ChunkVertices;
    GLuint VAO = 0,VBO = 0;
    GameObj ChunkObj;

    Chunk(BlockTypes t,glm::vec3 pos);
    void set_chunk_vao();
private:
    // void cull_face();


};

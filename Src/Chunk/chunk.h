#pragma once
#include "../Block/block.h"

constexpr int CHUNK_X = 16;
constexpr int CHUNK_Y = 256;
constexpr int CHUNK_Z = 16;

struct Chunk {
    std::array<Block,CHUNK_X*CHUNK_Y*CHUNK_Z> chunk;

    Block get_block(int x,int y,int z) {
        return chunk[x + CHUNK_X * (y + CHUNK_Y * z)];
    }
};


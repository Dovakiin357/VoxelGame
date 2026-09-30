
#include "chunk.h"


const std::array<const glm::ivec3,6> Directions = {
    glm::ivec3(0,0,1),
    glm::ivec3(0,0,-1),
    glm::ivec3(0,1,0),
    glm::ivec3(0,-1,0),
    glm::ivec3(1,0,0),
    glm::ivec3(-1,0,0),
};

Chunk::Chunk(BlockTypes t,glm::vec3 pos) :WorldPos(pos) {
     const auto &Bmesh = BlockManager::get_inst().get_block_mesh(t);
    ChunkVertices.reserve(CHUNK_VERTEX_COUNT);
    for (int i = 0;i < CHUNK_X;i++) {
        for (int j = 0;j < CHUNK_Y;j++) {
            for (int k = 0;k < CHUNK_Z;k++) {
                ChunkBlocks[i][j][k].Type = t;
                glm::vec3 offset(i,-j,k);
                // if (ChunkBlocks[i][j][k].Type == Air) continue;
                // // CHECKING Z DIRECTION
                // if (k < CHUNK_Z-1 && ChunkBlocks[i][j][k+1].Type == Air) {
                //     std::cout << "add Front Face";
                // }
                // if (k > 0 && ChunkBlocks[i][j][k-1].Type == Air) {
                //     std::cout << "add back face";
                // }
                //
                // // CHECKING J DIRECTION
                // if (j < CHUNK_Y-1 && ChunkBlocks[i][j+1][k].Type == Air) {
                //     std::cout << "add Front Face";
                // }
                // if (j > 0 && ChunkBlocks[i][j-1][k].Type == Air) {
                //     std::cout << "add back face";
                // }
                //
                // //CHECKING I DIRECTION
                // if (i < CHUNK_X-1 && ChunkBlocks[i+1][j][k].Type == Air) {
                //     std::cout << "add Front Face";
                // }
                // if (i > 0 && ChunkBlocks[i-1][j][k].Type == Air) {
                //     std::cout << "add back face";
                // for (const Vertex v:Bmesh.MeshData){
                //     ChunkVertices.emplace_back()
                // }
            }
        }
    }

    // std::cout << ChunkVertices.size() << std::endl;
    //
    // set_chunk_vao();
    // ChunkObj = {VAO,WorldPos};
    // if (VAO != 0) Renderer::get_inst().add_render_target(ChunkObj);

}

void Chunk::set_chunk_vao() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,CHUNK_VERTEX_COUNT * sizeof(Vertex),ChunkVertices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,pos));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glDeleteBuffers(1,&VBO);
}






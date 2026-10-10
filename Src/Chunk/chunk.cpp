
#include "chunk.h"


const std::array<const glm::ivec3,6> Directions = {
    glm::ivec3(0,0,1),
    glm::ivec3(0,0,-1),
    glm::ivec3(0,1,0),
    glm::ivec3(0,-1,0),
    glm::ivec3(1,0,0),
    glm::ivec3(-1,0,0),
};


void Chunk::add_face_vertices_chunk(const std::array<Vertex, 6> &vert, glm::vec3 &offset) {
    for (const Vertex v : vert) {
        Vertex ChunkV = v;
        ChunkV.pos += offset;
        ChunkVertices.emplace_back(ChunkV);
    }
}


Chunk::Chunk(BlockTypes t,glm::vec3 pos) :WorldPos(pos) {
     const auto &Bmesh = BlockManager::get_inst().get_block_mesh(t);
    for (int i = 0;i < CHUNK_X;i++) {
        for (int j = 0;j < CHUNK_Y;j++) {
            for (int k = 0;k < CHUNK_Z;k++) {
                ChunkBlocks[i][j][k].Type = t;


            }
        }
    }

//FACE CULLING
     for (int i = 0;i < CHUNK_X;i++) {
         for (int j = 0;j < CHUNK_Y;j++) {
             for (int k = 0;k < CHUNK_Z;k++) {
                 glm::vec3 Offset(i,-j,k);

                 //CHECKING K DIRECTION
                 if (k == CHUNK_Z-1 || ChunkBlocks[i][j][k+1].Type == Air) {
                     //add front face
                     add_face_vertices_chunk(Bmesh.FrontFaceMesh.FaceVertices,Offset);
                 }

                 if (k == 0 || ChunkBlocks[i][j][k-1].Type == Air) {
                     //add Back Face
                     add_face_vertices_chunk(Bmesh.BackFaceMesh.FaceVertices,Offset);
                 }


                 //CHECKING J DIRECTION
                 if (j == CHUNK_Y-1 || ChunkBlocks[i][j+1][k].Type == Air) {
                     //add Bottom Face
                     add_face_vertices_chunk(Bmesh.BottomFaceMesh.FaceVertices,Offset);
                 }
                 if (j == 0 || ChunkBlocks[i][j-1][k].Type == Air) {
                     //add Top Face
                     add_face_vertices_chunk(Bmesh.TopFaceMesh.FaceVertices,Offset);
                 }


                 //CHECKING I DIRECTION
                 if (i == CHUNK_X-1 || ChunkBlocks[i+1][j][k].Type == Air) {
                     //add Right Face
                     add_face_vertices_chunk(Bmesh.RightFaceMesh.FaceVertices,Offset);
                 }
                 if (i == 0 || ChunkBlocks[i-1][j][k].Type == Air) {
                     //add Left Face
                     add_face_vertices_chunk(Bmesh.LeftFaceMesh.FaceVertices,Offset);
                 }

             }
         }
     }


    set_chunk_vao();
    ChunkObj = {VAO,WorldPos,ChunkVertices.size()};
    if (VAO != 0) Renderer::get_inst().add_render_target(ChunkObj);

}

void Chunk::set_chunk_vao() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,ChunkVertices.size() * sizeof(Vertex),ChunkVertices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,pos));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glDeleteBuffers(1,&VBO);
}






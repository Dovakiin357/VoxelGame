#include "chunk.h"


//Loop through the Chunk Array,Assign a type to each block
//get the mesh of the block and get each individual Vertex  add it to ChunkVertices (the Offest is Covered by the Lppp)


Chunk::Chunk(BlockTypes t,const std::unordered_map<BlockTypes,std::vector<Vertex>> &bmeshes) {
    ChunkVertices.reserve(CHUNK_DATA_SIZE);
    for (int i = 0;i < CHUNK_X;i++) {
            for (int j = 0;j < CHUNK_Y;j++) {
                for (int k = 0;k < CHUNK_Z;k++) {
                    chunk[i][j][k].Type = t;

                    if (chunk[i][j][k].Type != Air) {
                        const auto &mesh = bmeshes.at(chunk[i][j][k].Type);
                        for (int s = 0;s < mesh.size();s++) {
                            Vertex v = mesh[s];

                            v.vert.x += (float)i;
                            v.vert.y += (float)j;
                            v.vert.z += (float)k;

                            ChunkVertices.push_back(v);
                        }
                    }
                }
            }
        }



}

// void Chunk::create_chunk_mesh(const std::unordered_map<BlockTypes,std::vector<Vertex>> &bmeshes) {
//     ChunkVertices.reserve(CHUNK_DATA_SIZE);
//
//     for (int i = 0;i < CHUNK_X;i++) {
//         for (int j = 0;j < CHUNK_Y;j++) {
//             for (int k = 0;k < CHUNK_Z;k++) {
//                 BlockTypes type = chunk[i][j][k].Type;
//                 if (type == Air) continue;
//                 const auto &mesh = bmeshes.at(type);
//
//
//                 for (int v = 0;v < mesh.size();v++) {
//                     Vertex vertex = mesh[v];
//
//                     vertex.vert.x += (float)i;
//                     vertex.vert.y += (float)j;
//                     vertex.vert.z += (float)k;
//
//                     this->ChunkVertices.push_back(vertex);
//                 }
//             }
//         }
//     }
// }

// void Chunk::set_chunk_vao() {
//     glGenBuffers(1,&VAO);
//     glGenBuffers(1,&VBO);
//
//     glBindVertexArray(VAO);
//
//     glBindBuffer(GL_ARRAY_BUFFER,VBO);
//     glBufferData(GL_ARRAY_BUFFER,ChunkVertices.size() * sizeof(Vertex),ChunkVertices.data(),GL_STATIC_DRAW);
//
//
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,vert));
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
//     glEnableVertexAttribArray(0);
//     glEnableVertexAttribArray(2);
//     glBindVertexArray(0);
//
//     glDeleteBuffers(1,&VBO);
//
//
//
// }




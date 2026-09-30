#include "block.h"


BlockManager::BlockManager() = default;
BlockManager BlockManager::blockmanager;
BlockManager &BlockManager::get_inst() {return blockmanager;}

void BlockManager::add_block_mesh(BlockTypes t,BlockMesh bmesh) {
 BlockDataBase.insert({t,bmesh});
}


const BlockMesh& BlockManager::get_block_mesh(BlockTypes t) {
 return BlockDataBase.at(t);
}

const std::array<Vertex,6> Face::LeftFaceVertPos = {
       Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) },
       Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
       Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
       Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
       Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
       Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) }
};

const std::array<Vertex,6> Face::RightFaceVertPos = {
       Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
       Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
       Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
       Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
       Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) },
       Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) }
};

const std::array<Vertex, 6> Face::FrontFaceVertPos = {
    Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) }
};

const std::array<Vertex, 6> Face::TopFaceVertPos = {
    Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) }
};

const std::array<Vertex, 6> Face::BottomFaceVertPos = {
    Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) }
};

const std::array<Vertex, 6> Face::BackFaceVertPos = {
    Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) },
    Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) }
};




void add_face_vertices(Tex &texture, std::vector<Vertex> &mesh,  Face &face) {
    static const std::array<int, 6> uvIndices = { 0, 3, 2, 2, 1, 0 };
    for (int i = 0;i < FACE_VERTEX_COUNT;i++) {
        Vertex v = face.FaceVertices[i];
        v.uv = texture.uv[uvIndices[i]];
        face.FaceVertices[i].uv = v.uv;
        mesh.emplace_back(v);
    }
}

BlockMesh::BlockMesh(BlockTypes types,TextureAtlas &ta) :BlockType(types) {
    MeshData.reserve(FACE_VERTEX_COUNT * 6);
    switch (types) {
        default: {
            Tex Texture = ta.Textures.at(types);

            add_face_vertices(Texture,MeshData,TopFaceVert);
            add_face_vertices(Texture,MeshData,BottomFaceVert);
            add_face_vertices(Texture,MeshData,RightFaceVert);

            add_face_vertices(Texture,MeshData,LeftFaceVert);
            add_face_vertices(Texture,MeshData,FrontFaceVert);
            add_face_vertices(Texture,MeshData,BackFaceVert);

        }
        case DirtGrass: {
            Tex TextureGrassTop = ta.Textures.at(Grass);
            Tex TextureDirtGrass = ta.Textures.at(DirtGrass);
            Tex DirtBottom = ta.Textures.at(Dirt);

            add_face_vertices(TextureGrassTop,MeshData,TopFaceVert);
            add_face_vertices(DirtBottom,MeshData,BottomFaceVert);
            add_face_vertices(TextureDirtGrass,MeshData,RightFaceVert);

            add_face_vertices(TextureDirtGrass,MeshData,LeftFaceVert);
            add_face_vertices(TextureDirtGrass,MeshData,FrontFaceVert);
            add_face_vertices(TextureDirtGrass,MeshData,BackFaceVert);
        }

    }
}



// std::vector<Vertex> create_block_mesh(TextureAtlas &ta, BlockTypes type) {
//  static const Face FrontFaceVert = {
//     BlockFace::FrontFace,
//     {
//         Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) },
//         Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
//         Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
//         Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) }
//     }
// };
//
// static const Face LeftFaceVert = {
//     BlockFace::LeftFace,
//     {
//         Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) },
//         Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
//         Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
//         Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) },
//         Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) }
//     }
// };
//
// static const Face RightFaceVert = {
//     BlockFace::RightFace,
//     {
//         Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) },
//         Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) }
//     }
// };
//
// static const Face TopFaceVert = {
//     BlockFace::TopFace,
//     {
//         Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
//         Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 1.0f) },
//         Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) }
//     }
// };
//
// static const Face BottomFaceVert = {
//     BlockFace::BottomFace,
//     {
//         Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) },
//         Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) },
//         Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
//         Vertex{ glm::vec3(1.0f, 0.0f, 1.0f) },
//         Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) },
//         Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) }
//     }
// };
//
// static const Face BackFaceVert = {
//     BlockFace::Backface,
//     {
//         Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) },
//         Vertex{ glm::vec3(1.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) },
//         Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) },
//         Vertex{ glm::vec3(1.0f, 0.0f, 0.0f) }
//     }
// };
//
//     std::vector<Vertex> BlockMesh;
//
//     switch (type) {
//         default: {
//             Tex Texture = ta.Textures.at(type);
//
//             add_face_vertices(Texture,BlockMesh,TopFaceVert);
//             add_face_vertices(Texture,BlockMesh,BottomFaceVert);
//             add_face_vertices(Texture,BlockMesh,RightFaceVert);
//
//             add_face_vertices(Texture,BlockMesh,LeftFaceVert);
//             add_face_vertices(Texture,BlockMesh,FrontFaceVert);
//             add_face_vertices(Texture,BlockMesh,BackFaceVert);
//         }
//         case DirtGrass: {
//             Tex TextureGrassTop = ta.Textures.at(Grass);
//             Tex TextureDirtGrass = ta.Textures.at(DirtGrass);
//             Tex DirtBottom = ta.Textures.at(Dirt);
//
//             add_face_vertices(TextureGrassTop,BlockMesh,TopFaceVert);
//             add_face_vertices(DirtBottom,BlockMesh,BottomFaceVert);
//             add_face_vertices(TextureDirtGrass,BlockMesh,RightFaceVert);
//
//             add_face_vertices(TextureDirtGrass,BlockMesh,LeftFaceVert);
//             add_face_vertices(TextureDirtGrass,BlockMesh,FrontFaceVert);
//             add_face_vertices(TextureDirtGrass,BlockMesh,BackFaceVert);
//         }
//     }
//
//     return BlockMesh;
//
//
// }







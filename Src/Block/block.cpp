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

const std::array<Vertex, 6> Face::LeftFaceVertPos = {
    Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 0.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 1.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 1.0f) },
    Vertex{ glm::vec3(0.0f, 0.0f, 0.0f) }
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


size_t Face::FACE_VERTEX_COUNT = 6;

void add_face_vertices(Tex &texture, std::vector<Vertex> &mesh,  Face &face) {
    static const std::array<int, 6> uvIndices = { 0, 3, 2, 2, 1, 0 };
    for (int i = 0;i < Face::FACE_VERTEX_COUNT;i++) {
        Vertex v = face.FaceVertices[i];
        v.uv = texture.uv[uvIndices[i]];
        face.FaceVertices[i].uv = v.uv;
        mesh.emplace_back(v);
    }
}

BlockMesh::BlockMesh(BlockTypes types,TextureAtlas &ta) :BlockType(types) {
    // MeshData.reserve(FACE_VERTEX_COUNT * 6);
    switch (types) {
        default: {
            Tex Texture = ta.Textures.at(types);

            add_face_vertices(Texture,MeshData,TopFaceMesh);
            add_face_vertices(Texture,MeshData,BottomFaceMesh);
            add_face_vertices(Texture,MeshData,RightFaceMesh);

            add_face_vertices(Texture,MeshData,LeftFaceMesh);
            add_face_vertices(Texture,MeshData,FrontFaceMesh);
            add_face_vertices(Texture,MeshData,BackFaceMesh);

            break;

        }
        case DirtGrass: {
            Tex TextureGrassTop = ta.Textures.at(Grass);
            Tex TextureDirtGrass = ta.Textures.at(DirtGrass);
            Tex DirtBottom = ta.Textures.at(Dirt);

            add_face_vertices(TextureGrassTop,MeshData,TopFaceMesh);
            add_face_vertices(DirtBottom,MeshData,BottomFaceMesh);
            add_face_vertices(TextureDirtGrass,MeshData,RightFaceMesh);

            add_face_vertices(TextureDirtGrass,MeshData,LeftFaceMesh);
            add_face_vertices(TextureDirtGrass,MeshData,FrontFaceMesh);
            add_face_vertices(TextureDirtGrass,MeshData,BackFaceMesh);
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







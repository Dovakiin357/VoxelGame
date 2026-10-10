#pragma once
#include <vector>
#include <string>
#include "../Abstraction/abstraction.h"
#include<unordered_map>
#include "glm-master/glm/vec2.hpp"

enum BlockTypes{Air = 0,Grass,DirtGrass,Dirt,Gengar,Stone};

struct Texture {
    int Width = 0;
    int Height = 0;
    int nrChannels = 0;

    unsigned char* Data = nullptr;
    glm::vec2 PosInAtlas = glm::vec2(0,0);
    std::array<glm::vec2,4> uv;
};


class TextureAtlas {
public:
    explicit TextureAtlas(std::unordered_map<BlockTypes,Texture> &textures);
    TextureAtlas(const TextureAtlas &other) = delete;
    GLuint Atlas;
    int AtlasHeight = 0;
    int AtlasWidth = 0;
    std::unordered_map<BlockTypes,Texture> &Textures;

private:
    void add_textures(std::unordered_map<BlockTypes,Texture> &textures);
    void create_atlas(std::unordered_map<BlockTypes,Texture> &textures);
    std::array<glm::vec2,4> get_uv(const Texture &t);

};

std::unordered_map<BlockTypes,Texture> create_textures(std::unordered_map<BlockTypes,const std::string> &tex_paths);
void free_texture_data(std::unordered_map<BlockTypes,Texture> &textures);




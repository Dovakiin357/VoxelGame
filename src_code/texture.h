#pragma once
#include <vector>
#include <string>
#include"abstraction.h"
#include<unordered_map>
#include "glm-master/glm/vec2.hpp"

struct Tex {
    int Width = 0;
    int Height = 0;
    int nrChannels = 0;
    unsigned char* Data = nullptr;
    glm::vec2 PosInAtlas = glm::vec2(0,0);
};


class TextureManager {
public:
    static std::unordered_map<std::string,Tex> Textures;
    static void free_textures();
    TextureManager();

private:
    const std::vector<std::string> TexPaths = {
        "Resources/dirt.jpg","Resources/grass.jpg","Resources/download.jpg"
    };
    static void create_textures(const std::vector<std::string> &tex_paths);


};

class TextureAtlas {
public:
    explicit TextureAtlas(std::unordered_map<std::string,Tex> &textures);
    GLuint Atlas;
    int AtlasHeight = 0;
    int AtlasWidth = 0;
private:


    void add_textures(std::unordered_map<std::string,Tex> &textures);
    void create_atlas(std::unordered_map<std::string,Tex> &textures);

};

std::vector<GLfloat> get_norm(Tex &t,int aw,int ah);

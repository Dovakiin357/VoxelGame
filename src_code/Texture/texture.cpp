#include "../Texture//texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Texture/stb_image.h"

std::unordered_map<BlockTypes,Tex> TextureManager::Textures = {};
std::unordered_map<BlockTypes,std::string> TextureManager::texpaths = {
    {Grass,"Resources/grass.jpg"},{DirtGrass,"Resources/dirt_grass.jpg"},
    {Dirt,"Resources/dirt.jpg"},{Gengar,"Resources/download.jpg"}
};

void TextureManager::create_textures(std::unordered_map<BlockTypes,std::string> &tex_paths) {
    for (const auto& [k,v]:tex_paths) {
        Tex texture;
        texture.Data = stbi_load(
            v.c_str(),&texture.Width,&texture.Height,
            &texture.nrChannels,0
            );
        if (texture.Data != nullptr) {
            TextureManager::Textures[k] = texture;
        }
        else
            std::cout << "Couldnt load Texture:" << v;
    }
}

void TextureManager::free_textures() {
    for (auto &pair:TextureManager::Textures) {
        if (pair.second.Data != nullptr)
            stbi_image_free(pair.second.Data);
        pair.second.Data = nullptr;
    }
}

TextureManager::TextureManager() {
    stbi_set_flip_vertically_on_load(true);
    create_textures(TextureManager::texpaths);
}

void TextureAtlas::create_atlas(std::unordered_map<BlockTypes, Tex> &textures) {
    AtlasHeight = 0;
    for (auto &[typ,t]:textures) {
        AtlasWidth += t.Width;
        if (t.Height > AtlasHeight)
            AtlasHeight = t.Height;
    }
    std::cout << AtlasWidth;
}

void TextureAtlas::add_textures(std::unordered_map<BlockTypes,Tex> &textures) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int Yoffset = 0;
    int Xoffset = 0;
    for (auto &[typ,tex]:textures) {
        if (tex.Data != nullptr) {
            glTexSubImage2D(GL_TEXTURE_2D,0,Xoffset,Yoffset,
            tex.Width,tex.Height,GL_RGB,GL_UNSIGNED_BYTE,
            tex.Data);

            tex.PosInAtlas = glm::vec2(Xoffset,Yoffset);
            tex.uv = get_uv(tex);
            Xoffset += tex.Width;
        }
        else std::cout << "tex data is nullptr";
    }
    glGenerateMipmap(GL_TEXTURE_2D);
}



TextureAtlas::TextureAtlas(std::unordered_map<BlockTypes, Tex> &textures) {

    glGenTextures(1,&Atlas);
    glBindTexture(GL_TEXTURE_2D,Atlas);
    create_atlas(textures);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D,0,GL_RGB,AtlasWidth,AtlasHeight,
        0,GL_RGB,GL_UNSIGNED_BYTE,nullptr);
    add_textures(textures);
    TextureManager::free_textures();

}


std::array<glm::vec2, 4> TextureAtlas::get_uv(const Tex &t) {
    glm::vec2 uvTopRight,uvBottomLeft,uvTopLeft,uvBottomRight;
    uvBottomLeft = glm::vec2(
       t.PosInAtlas.x/(float)AtlasWidth,
        t.PosInAtlas.y/(float)AtlasHeight
       );

    uvTopRight = glm::vec2(
        (t.PosInAtlas.x + (float)t.Width)/(float)AtlasWidth,
        (t.PosInAtlas.y + (float)t.Height)/(float)AtlasHeight
        );

    uvTopLeft = glm::vec2(
        (t.PosInAtlas.x)/(float)AtlasWidth,
        (t.PosInAtlas.y + (float)t.Height)/(float)AtlasHeight);


    uvBottomRight = glm::vec2(
    (t.PosInAtlas.x + (float)t.Width)/(float)AtlasWidth,
    t.PosInAtlas.y/(float)AtlasHeight
    );

    return {uvBottomLeft,uvBottomRight,uvTopRight,uvTopLeft};
}






#include "../Texture//texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Texture/stb_image.h"

std::unordered_map<std::string,Tex> TextureManager::Textures = {};

void TextureManager::create_textures(const std::vector<std::string> &tex_paths) {
    for (const auto&TexPath:tex_paths) {
        Tex texture;
        texture.Data = stbi_load(
            TexPath.c_str(),&texture.Width,&texture.Height,
            &texture.nrChannels,0
            );
        if (texture.Data != nullptr) {
            Textures[TexPath] = texture;
        }
        else
            std::cout << "Couldnt load Texture:" << TexPath;
    }
}

void TextureManager::free_textures() {
    for (auto &pair:Textures) {
        if (pair.second.Data != nullptr)
            stbi_image_free(pair.second.Data);
        pair.second.Data = nullptr;
    }
}

TextureManager::TextureManager() {
    stbi_set_flip_vertically_on_load(true);
    create_textures(TexPaths);
}

void TextureAtlas::create_atlas(std::unordered_map<std::string, Tex> &textures) {
    AtlasHeight = 0;
    for (auto &tex:textures) {
        AtlasWidth += tex.second.Width;
        if (tex.second.Height > AtlasHeight)
            AtlasHeight = tex.second.Height;
    }
}

void TextureAtlas::add_textures(std::unordered_map<std::string,Tex> &textures) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int Yoffset = 0;
    int Xoffset = 0;
    for (auto &tex:textures) {
        if (tex.second.Data != nullptr) {
            glTexSubImage2D(GL_TEXTURE_2D,0,Xoffset,Yoffset,
            tex.second.Width,tex.second.Height,GL_RGB,GL_UNSIGNED_BYTE,
            tex.second.Data);

            tex.second.PosInAtlas = glm::vec2(Xoffset,Yoffset);
            Xoffset += tex.second.Width;
        }
        else std::cout << "tex data is nullptr";
    }
    glGenerateMipmap(GL_TEXTURE_2D);
}



TextureAtlas::TextureAtlas(std::unordered_map<std::string, Tex> &textures) {

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

std::vector<glm::vec2> get_norm(Tex &t,int aw,int ah) {
    glm::vec2 uvTopRight,uvBottomLeft,uvTopLeft,uvBottomRight;
    uvBottomLeft = glm::vec2(
        t.PosInAtlas.x/(float)aw,
         t.PosInAtlas.y/(float)ah
        );

    uvTopRight = glm::vec2(
        (t.PosInAtlas.x + (float)t.Width)/(float)aw,
        (t.PosInAtlas.y + (float)t.Height)/(float)ah
        );

    uvTopLeft = glm::vec2(
        (t.PosInAtlas.x)/(float)aw,
        (t.PosInAtlas.y + (float)t.Height)/(float)ah
        );

    uvBottomRight = glm::vec2(
    (t.PosInAtlas.x + (float)t.Width)/(float)aw,
    t.PosInAtlas.y/(float)ah
    );

    return {uvBottomLeft,uvBottomRight,uvTopRight,uvTopLeft};
}





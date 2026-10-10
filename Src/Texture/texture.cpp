#include "../Texture//texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Texture/stb_image.h"



std::unordered_map<BlockTypes, Texture> create_textures(std::unordered_map<BlockTypes, const std::string> &tex_paths) {
    stbi_set_flip_vertically_on_load(true);
    std::unordered_map<BlockTypes,Texture> textures  = {};
    for (const auto& [block_t,path]:tex_paths) {
        Texture texture;
        texture.Data = stbi_load(
            path.c_str(),&texture.Width,&texture.Height,
            &texture.nrChannels,0
            );
        if (texture.Data != nullptr) {
            textures[block_t] = texture;
        }
        else
            std::cout << "Couldnt load Texture:" << path;
    }
    return textures;
}


void free_texture_data(std::unordered_map<BlockTypes, Texture> &textures) {
    for ( auto &[block_t,tex]:textures) {
        if (tex.Data != nullptr) {
            stbi_image_free(tex.Data);
            tex.Data = nullptr;
        }
        else std::cout << "Data is nullptr";
    }
}


void TextureAtlas::create_atlas(std::unordered_map<BlockTypes, Texture> &textures) {
    AtlasHeight = 0;
    for (auto &[block_t,tex]:textures) {
        AtlasWidth += tex.Width;
        if (tex.Height > AtlasHeight)
            AtlasHeight = tex.Height;
    }
}

void TextureAtlas::add_textures(std::unordered_map<BlockTypes,Texture> &textures) {

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int Yoffset = 0;
    int Xoffset = 0;

    for (auto &[block_t,tex]:textures) {
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



TextureAtlas::TextureAtlas(std::unordered_map<BlockTypes, Texture> &textures) :Textures(textures) {


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

    free_texture_data(textures);



}


std::array<glm::vec2, 4> TextureAtlas::get_uv(const Texture &t) {
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






#include "game.h"
#include "glad/glad.h"
#include <array>



std::vector<float> build_cube_vertices() {
    return {
        // Front face (z = +1)
        -1, -1,  1,   0, 0,
         1, -1,  1,   1, 0,
         1,  1,  1,   1, 1,
        -1,  1,  1,   0, 1,

        // Back face (z = -1)
        -1, -1, -1,   1, 0,
        -1,  1, -1,   1, 1,
         1,  1, -1,   0, 1,
         1, -1, -1,   0, 0,

        // Left face (x = -1)
        -1, -1, -1,   0, 0,
        -1, -1,  1,   1, 0,
        -1,  1,  1,   1, 1,
        -1,  1, -1,   0, 1,

        // Right face (x = +1)
         1, -1,  1,   0, 0,
         1, -1, -1,   1, 0,
         1,  1, -1,   1, 1,
         1,  1,  1,   0, 1,

        // Top face (y = +1)
        -1,  1,  1,   0, 0,
         1,  1,  1,   1, 0,
         1,  1, -1,   1, 1,
        -1,  1, -1,   0, 1,

        // Bottom face (y = -1)
        -1, -1, -1,   0, 0,
         1, -1, -1,   1, 0,
         1, -1,  1,   1, 1,
        -1, -1,  1,   0, 1,
    };
}

Movement::Movement(float speed) {
    this->Speed = speed;
}

void Movement::move(glm::vec2 &pos) {
    pos.x += this->Speed;
}

GameObject::GameObject(glm::vec2 Pos) {
    this->pos = Pos;
    GameObjects.push_back(this);


   std::vector<float> Vertices = build_cube_vertices();
    vertex_setup(Vertices,Indices);
    texture_setup();
}

GameObject::~GameObject() {
    std::erase(GameObjects,this);

}


void draw(GameObject &obj,int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc) {
    glm::mat4 Model = glm::mat4(1.0f);

    Model = glm::translate(Model, glm::vec3(obj.pos, 0.0f));
    Model = glm::rotate(Model,(float)glfwGetTime() * glm::radians(50.0f),glm::vec3(0.5f,1.0f,0.0f));
    Model = glm::scale(Model, glm::vec3(obj.ObjWidth, obj.ObjHeight, 1.0f));


    auto View = glm::mat4(1.0f);
     View = glm::translate(View,glm::vec3(-10.0f,0.0f,-50.0f));

    glUniformMatrix4fv(ModelLoc,1,GL_FALSE,glm::value_ptr(Model));
    glUniformMatrix4fv(ViewLoc,1,GL_FALSE,glm::value_ptr(View));

    glActiveTexture(GL_TEXTURE0 + TextureUnit);
    glBindTexture(GL_TEXTURE_2D,obj.TextureObj);
    glUniform1i(TextureLoc,TextureUnit);

    glBindVertexArray(obj.VAO);
    glDrawElements(GL_TRIANGLES,obj.Indices.size(),GL_UNSIGNED_INT,0);

}

void render_game_objects(int ModelLoc,int TextureLoc,int TextureUnit,int ViewLoc) {
    for (GameObject *obj:GameObjects) {
        draw(*(obj),ModelLoc,TextureLoc,TextureUnit,ViewLoc);
    }
}

void delete_game_objs() {
    for (GameObject *obj:GameObjects) {
        obj->~GameObject();   }
}

glm::vec2 WASD(Input &input,float speed) {
    float xPos = 0;
    float yPos = 0;

    int xDir = int(input.key_state.DKeyPressed) - int(input.key_state.AKeyPressed);
    int yDir = int(input.key_state.WKeyPressed) - int(input.key_state.SKeyPressed);

    xPos += xDir * speed;
    yPos += yDir * speed;

    return glm::vec2(xPos,yPos);

}
glm::mat4 camera(Input &input,float camera_speed) {
    auto View = glm::mat4(1.0f);
    auto input_vec = glm::vec2(0.0f,0.0f);
    input_vec += WASD(input,camera_speed);

    View = glm::translate(View,glm::vec3(input_vec,-30.0f));
    return  View;
}










#include "Abstraction/abstraction.h"
#include "Game/game.h"
#include "Texture/texture.h"
#include "../Src/Chunk/chunk.h"
#include"Camera/camera.h"
#include<cmath>
#include <filesystem>

#include "../glm-master/glm-master/glm/glm.hpp"
#include "../glm-master/glm-master/glm/gtc/matrix_transform.hpp"
#include "../glm-master/glm-master/glm/gtc/type_ptr.hpp"
#include "../Libraries/glad/include/glad/glad.h"
#include "../Libraries/glfw-3.4/include/GLFW/glfw3.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



// Settings

const auto FshaderPath = std::filesystem::path(std::string("Shaders/fragment_shader"));
const auto TexturePath = std::filesystem::path(std::string("Resources/grass.jpg"));
const auto VshaderPath = std::filesystem::path(std::string("Shaders/vertex_shader"));

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::unordered_map<BlockTypes,const std::string> TexPaths = {{Grass,"Resources/grass.jpg"},
                                                            {DirtGrass,"Resources/dirt_grass.jpg"},
                                                           {Dirt,"Resources/dirt.jpg"},
                                                           {Gengar,"Resources/download.jpg"},
                                                           {Stone,"Resources/stone.jpg"}};



    std::unordered_map<BlockTypes,Tex> Textures = create_textures(TexPaths);
    TextureAtlas texture_atlas(Textures);


    BlockManager::get_inst().add_block_mesh(DirtGrass,texture_atlas);
    BlockManager::get_inst().add_block_mesh(Grass,texture_atlas);
    BlockManager::get_inst().add_block_mesh(Dirt,texture_atlas);
    BlockManager::get_inst().add_block_mesh(Stone,texture_atlas);
    BlockManager::get_inst().add_block_mesh(Gengar,texture_atlas);



    Camera camera(window);
    Shader shader(VshaderPath,FshaderPath);

    glm::mat4 Proj = glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);

    int ModelLoc = glGetUniformLocation(shader.ShaderProgram,"model");
    int ProjLoc = glGetUniformLocation(shader.ShaderProgram,"proj");
    int ViewLoc = glGetUniformLocation(shader.ShaderProgram,"view");
    int TextureLoc = glGetUniformLocation(shader.ShaderProgram,"Texture");

    Renderer::get_inst().get_mat_loc(ModelLoc,ViewLoc,ProjLoc,TextureLoc);

    glClearColor(0.529f, 0.808f, 0.922f,1.0f);
    glEnable(GL_DEPTH_TEST);

    float DeltaTime = 0.0f;
    float LastFrame = 0.0f;


    // Row 1 (Z = 0.0f)
    Chunk c1  = { DirtGrass, glm::vec3(0.0f,  0.0f, 0.0f) };
    Chunk c2  = { DirtGrass, glm::vec3(16.0f, 0.0f, 0.0f) };
    Chunk c3  = { DirtGrass, glm::vec3(32.0f, 0.0f, 0.0f) };
    Chunk c4  = { DirtGrass, glm::vec3(48.0f, 0.0f, 0.0f) };
    Chunk c5  = { DirtGrass, glm::vec3(64.0f, 0.0f, 0.0f) };

    // Row 2 (Z = 16.0f)
    Chunk c6  = { DirtGrass, glm::vec3(0.0f,  0.0f, 16.0f) };
    Chunk c7  = { DirtGrass, glm::vec3(16.0f, 0.0f, 16.0f) };
    Chunk c8  = { DirtGrass, glm::vec3(32.0f, 0.0f, 16.0f) };
    Chunk c9  = { DirtGrass, glm::vec3(48.0f, 0.0f, 16.0f) };
    Chunk c10 = { DirtGrass, glm::vec3(64.0f, 0.0f, 16.0f) };

    // Row 3 (Z = 32.0f)
    Chunk c11 = { DirtGrass, glm::vec3(0.0f,  0.0f, 32.0f) };
    Chunk c12 = { DirtGrass, glm::vec3(16.0f, 0.0f, 32.0f) };
    Chunk c13 = { DirtGrass, glm::vec3(32.0f, 0.0f, 32.0f) };
    Chunk c14 = { DirtGrass, glm::vec3(48.0f, 0.0f, 32.0f) };
    Chunk c15 = { DirtGrass, glm::vec3(64.0f, 0.0f, 32.0f) };

    // Row 4 (Z = 48.0f)
    Chunk c16 = { DirtGrass, glm::vec3(0.0f,  0.0f, 48.0f) };
    Chunk c17 = { DirtGrass, glm::vec3(16.0f, 0.0f, 48.0f) };
    Chunk c18 = { DirtGrass, glm::vec3(32.0f, 0.0f, 48.0f) };
    Chunk c19 = { DirtGrass, glm::vec3(48.0f, 0.0f, 48.0f) };
    Chunk c20 = { DirtGrass, glm::vec3(64.0f, 0.0f, 48.0f) };




    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.ShaderProgram);

        auto CurrentFrame = static_cast<float>(glfwGetTime());
        DeltaTime = CurrentFrame - LastFrame;
        LastFrame = CurrentFrame;

        camera.camera_movement(DeltaTime);
        auto v = camera.glm_view();
        Renderer::get_inst().render(v,Proj,texture_atlas.Atlas);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}





void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
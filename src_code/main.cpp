#include "abstraction.h"
#include "game.h"
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
const auto TexturePath = std::filesystem::path(std::string("Resources/minecraft.jpg"));
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




    GameObject game_object(glm::vec3(0.0f,0.0f,0.0f));
    Camera camera(window);
    Shader shader(VshaderPath,FshaderPath);



    glm::mat4 Proj = glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);



    int ModelLoc = glGetUniformLocation(shader.ShaderProgram,"model");
    int ProjLoc = glGetUniformLocation(shader.ShaderProgram,"proj");
    int ViewLoc = glGetUniformLocation(shader.ShaderProgram,"view");
    int TextureLoc = glGetUniformLocation(shader.ShaderProgram,"Texture");

    glClearColor(0.529f, 0.808f, 0.922f,1.0f);
    glEnable(GL_DEPTH_TEST);

    float DeltaTime = 0.0f;
    float LastFrame = 0.0f;


    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.ShaderProgram);
        glUniformMatrix4fv(ProjLoc,1,GL_FALSE,glm::value_ptr(Proj));

        auto CurrentFrame = static_cast<float>(glfwGetTime());
        DeltaTime = CurrentFrame - LastFrame;
        LastFrame = CurrentFrame;

        camera.camera_movement(DeltaTime);
        render_game_objects(ModelLoc,TextureLoc,0,ViewLoc,camera,DeltaTime);


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
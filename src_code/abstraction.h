#pragma once
#include <string>
#include "../Libraries/glad/include/glad/glad.h"
#include "../Libraries/glfw-3.4/include/GLFW/glfw3.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include <vector>
#include<filesystem>

struct KeyState {
    bool WKeyPressed;
    bool AKeyPressed;
    bool SKeyPressed;
    bool DKeyPressed;
};
class Shader {
public:
    std::string VertexSourceCode;
    std::string FragmentSourceCode;

    GLuint ShaderProgram;

    Shader(const std::filesystem::path &VshaderPath,const std::filesystem::path &FshaderPath);

private:
    std::string get_file_content(const std::string &Filename);
    void shader_compile(GLuint &vs,const GLchar* Vptr,GLuint &fs,const GLchar* Fptr);
    void check_compilation_shader(GLuint &shader);
    void check_linking_program(GLuint &shaderprogram);


};

class Vertex {
protected:
    unsigned int VBO;
    unsigned int EBO;
    void vertex_setup(std::vector<float> &Vertices,std::vector<GLuint> &Indices);
public:
    unsigned int VAO;

};

class Texture {
public:
    GLuint TextureObj;
    static const std::filesystem::path TexturePath;
protected:
    void texture_setup();
};

class Input {
public:
    KeyState key_state = {false,false,false,false};
    float CursorPosX;
    float CursorPosY;

    bool IsPressingLeftMouse;
    bool FirstMouse = true;

    float LastX = 400.0f;
    float LastY = 300.0f;

    explicit Input(GLFWwindow* Window);


private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

};





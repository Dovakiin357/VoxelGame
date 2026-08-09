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

#include "glm-master/glm/glm.hpp"

struct Vertex {
    glm::vec3 vert;
    glm::vec2 uv = glm::vec2(0.0f,0.0f);
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



class Input {
public:
    float CursorPosX;
    float CursorPosY;

    bool IsPressingLeftMouse;
    bool FirstMouse = true;

    float LastX = 400.0f;
    float LastY = 300.0f;

    explicit Input(GLFWwindow* Window);


private:
    static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

};

void set_vao(GLuint &vao,std::vector<Vertex> &v,const std::vector<GLuint> &i);



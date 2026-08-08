#include "abstraction.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


std::string Shader::get_file_content(const std::string &file_name) {
    std::ifstream file;
    file.open(file_name);

    if (!file) {
        std::cerr << "Failed to open: " << file_name << std::endl;
        return "";
    }


    std::stringstream buffer;

    buffer << file.rdbuf();
    const std::string file_contents = buffer.str();

    return file_contents;
}



void Shader::check_compilation_shader(GLuint &shader) {
    int succes;
    char infolog[512];
    glGetShaderiv(shader,GL_COMPILE_STATUS,&succes);


    if (!succes) {
        glGetShaderInfoLog(shader,512,nullptr,infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }

}



void Shader::check_linking_program(GLuint &shaderprogram) {
    int succes;
    char infolog[512];
    glGetProgramiv(shaderprogram,GL_LINK_STATUS,&succes);

    if (!succes) {
        glGetProgramInfoLog(shaderprogram,512,nullptr,infolog);
    }
}



void Shader::shader_compile(GLuint &vs,const GLchar* Vptr,GLuint &fs,const GLchar* Fptr) {
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs,1,&Vptr,nullptr);
    glCompileShader(vs);
    check_compilation_shader(vs);

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &Fptr, nullptr);
    glCompileShader(fs);
    check_compilation_shader(fs);
}



Shader::Shader(const std::filesystem::path &VshaderPath,const std::filesystem::path &FshaderPath)
    :VertexSourceCode(get_file_content(VshaderPath.string())),
     FragmentSourceCode(get_file_content(FshaderPath.string())),
     ShaderProgram(glCreateProgram())
{

    const GLchar *VshaderPtr = VertexSourceCode.c_str();
    const GLchar *FshaderPtr = FragmentSourceCode.c_str();

    GLuint VertexShader,FragmentShader;
    shader_compile(VertexShader,VshaderPtr,FragmentShader,FshaderPtr);

    glAttachShader(ShaderProgram,VertexShader);
    glAttachShader(ShaderProgram,FragmentShader);
    glLinkProgram(ShaderProgram);
    check_linking_program(ShaderProgram);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

}



Input::Input(GLFWwindow* Window) {

    glfwSetWindowUserPointer(Window,this);
    glfwSetCursorPosCallback(Window,cursor_pos_callback);
    glfwSetMouseButtonCallback(Window,mouse_button_callback);

}


void Input::cursor_pos_callback(GLFWwindow *window, double xpos, double ypos) {
    auto Pinput = static_cast<Input *>(glfwGetWindowUserPointer(window));

    if (Pinput->FirstMouse == true) {
        Pinput->LastX = static_cast<float>(xpos);
        Pinput->LastY = static_cast<float>(ypos);
        Pinput->FirstMouse = false;
    }

    Pinput->CursorPosX = static_cast<float>(xpos);
    Pinput->CursorPosY = static_cast<float>(ypos);

}

void Input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    auto Pinput = static_cast<Input *>(glfwGetWindowUserPointer(window));
    Pinput->IsPressingLeftMouse = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
}

void set_vao(GLuint &vao, std::vector<GLfloat> &v, const std::vector<GLuint> &i) {
    GLuint EBO,VBO;

    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,v.size() * sizeof(float),v.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,i.size() * sizeof(GLuint),i.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);


}






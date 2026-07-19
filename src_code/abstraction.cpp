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

void Vertex::vertex_setup(std::vector<float> &Vertices, std::vector<GLuint> &Indices) {
    glGenVertexArrays(1,&this->VAO);
    glGenBuffers(1,&this->VBO);
    glGenBuffers(1,&this->EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
    glBufferData(GL_ARRAY_BUFFER,Vertices.size() * sizeof(float),Vertices.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,Indices.size() * sizeof(GLuint),Indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}
const std::filesystem::path Texture::TexturePath = std::filesystem::path(std::string("Resources/minecraft.jpg"));

void Texture::texture_setup() {
    glGenTextures(1,&TextureObj);
    glBindTexture(GL_TEXTURE_2D,TextureObj);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int Width,Height,nrChannels;
    unsigned char* data = stbi_load(TexturePath.string().c_str(),&Width,&Height,&nrChannels,0);
    if (data == nullptr) {
        std::cout << "coudnt load texture";
    }
    else {
        glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
}

Input::Input(GLFWwindow* Window) {

    glfwSetWindowUserPointer(Window,this);
    glfwSetKeyCallback(Window,key_callback);
    glfwSetCursorPosCallback(Window,cursor_pos_callback);
    glfwSetMouseButtonCallback(Window,mouse_button_callback);

}

void Input::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto Pinput = static_cast<Input *>(glfwGetWindowUserPointer(window));

    Pinput->key_state.WKeyPressed = (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS);
    Pinput->key_state.AKeyPressed = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
    Pinput->key_state.SKeyPressed = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
    Pinput->key_state.DKeyPressed = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);

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








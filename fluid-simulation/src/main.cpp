#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>


void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string loadShadersSrc(const char* filename);



int main() {


    int success;
    char infoLog[512];

    glfwInit();
    // opengl version print

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Create window Error" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Create window Error" << std::endl;
        glfwTerminate();
        return -1;

    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertShaderSrc = loadShadersSrc("assets/vertex_core.glsl");
    const GLchar* vertShader = vertShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error with vertex: " << infoLog << std::endl;
    }
    else {
        std::cout << "No Error at vertex" << std::endl;
    }
    unsigned int fragmentShaders[2];
    fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragShaderSrc = loadShadersSrc("assets/fragment_core.glsl");
    const GLchar* fragShader = fragShaderSrc.c_str();
    glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
    glCompileShader(fragmentShaders[0]);

    glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
        std::cout << "Error with fragment: " << infoLog << std::endl;
    }
    else {

        std::cout << "No Error at fragment" << std::endl;
    }




    fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
    fragShaderSrc = loadShadersSrc("assets/fragment_core2.glsl");
    const GLchar* fragShader2 = fragShaderSrc.c_str();
    glShaderSource(fragmentShaders[1], 1, &fragShader2, NULL);
    glCompileShader(fragmentShaders[1]);

    glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
        std::cout << "Error with fragment: " << infoLog << std::endl;
    }
    else {

        std::cout << "No Error at fragment" << std::endl;
    }



    unsigned int shaderPrograms[2];
    shaderPrograms[0] = glCreateProgram();

    glAttachShader(shaderPrograms[0], vertexShader);
    glAttachShader(shaderPrograms[0], fragmentShaders[0]);
    glLinkProgram(shaderPrograms[0]);

    glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
        std::cout << "Error with program: " << infoLog << std::endl;

    }
    else {

        std::cout << "No Error at shaderProgram" << std::endl;
    }

    shaderPrograms[1] = glCreateProgram();

    glAttachShader(shaderPrograms[1], vertexShader);
    glAttachShader(shaderPrograms[1], fragmentShaders[1]);
    glLinkProgram(shaderPrograms[1]);

    glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
        std::cout << "Error with program: " << infoLog << std::endl;

    }
    else {

        std::cout << "No Error at shaderProgram" << std::endl;
    }




    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaders[0]);
    glDeleteShader(fragmentShaders[1]);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f,0.0f,
        0.5f, -0.5f, 0.0f,
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        glClearColor(0.3f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glUseProgram(shaderPrograms[0]);
        //glDrawArrays(GL_LINE_STRIP, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glUseProgram(shaderPrograms[1]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));



        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;

}
void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

std::string loadShadersSrc(const char* filename) {
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filename);

    if (file.is_open()) {

        buf << file.rdbuf();
        ret = buf.str(); 
    }
    else {
        std::cout << "Could not open " << filename << std::endl;
    }

    file.close();
    return ret;
}

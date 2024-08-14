#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
  // Init window for opengl 3.3
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Define vertex shader
  const char *vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "}\0";
  // Creating shader object
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Compiling shader
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // Define fragment shader
  const char *fragmentShaderSourceA = "#version 330 core\n"
                                      "out vec4 FragColor;\n"
                                      "void main()\n"
                                      "{ FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                      "}";

  // Creating a fragment shader
  unsigned int fragmentShaderA;
  fragmentShaderA = glCreateShader(GL_FRAGMENT_SHADER);

  // Compiling a fragment shader
  glShaderSource(fragmentShaderA, 1, &fragmentShaderSourceA, NULL);
  glCompileShader(fragmentShaderA);

  const char *fragmentShaderSourceB = "#version 330 core\n"
                                      "out vec4 FragColor;\n"
                                      "void main()\n"
                                      "{ FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                      "}";

  unsigned int fragmentShaderB = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShaderB, 1, &fragmentShaderSourceB, NULL);
  glCompileShader(fragmentShaderB);

  // Init shader program
  unsigned int shaderProgramA;
  shaderProgramA = glCreateProgram();

  // Linking shaders
  glAttachShader(shaderProgramA, vertexShader);
  glAttachShader(shaderProgramA, fragmentShaderA);
  glLinkProgram(shaderProgramA);

  unsigned int shaderProgramB;
  shaderProgramB = glCreateProgram();

  glAttachShader(shaderProgramB, vertexShader);
  glAttachShader(shaderProgramB, fragmentShaderB);
  glLinkProgram(shaderProgramB);

  // Set and delete shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShaderA);
  glDeleteShader(fragmentShaderB);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  float verticesA[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
  };

  float verticesB[] = {
      -0.5f, 0.5f,  0.0f, // top left
      0.5f,  0.5f,  0.0f, // top right
      -0.5f, -0.5f, 0.0f, // bottom left
  };

  unsigned int VBO[2], VAO[2];
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);

  // first triangle setup
  glBindVertexArray(VAO[0]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // second triangle setup
  glBindVertexArray(VAO[1]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    // Input handling
    processInput(window);

    // Render commands
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw first triangle
    glUseProgram(shaderProgramA);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // draw second triangle
    glUseProgram(shaderProgramB);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time

    // Swaps buffers and handle I/O events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
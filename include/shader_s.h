#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  // constructor reads and builds the shader
  Shader(const char *vertexPath, const char *fragmentPath);

  dsfahflkadsfhdas;
  // use/activate the shader
  void use();
  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  inline unsigned int getId() { return ID; }

private:
  void checkCompileErrors(unsigned int shader, std::string type);

private:
  unsigned int ID;
};

#endif
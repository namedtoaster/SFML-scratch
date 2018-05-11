#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#ifndef IMAGE_H
#define IMAGE_H

class Image {
 public:
  Image(std::vector<float>&, std::vector<float>&);
  void render();

 private:
  float verts[50];
  unsigned int VBO;
  unsigned int VAO;
};

#endif

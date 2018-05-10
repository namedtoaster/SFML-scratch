#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef IMAGE_H
#define IMAGE_H

class Image {
 public:
  Image();
  void render();

  //private:
  float verts[18]= {
    // positions         // colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f    // top
  };
  unsigned int VBO;
  unsigned int VAO;
};

#endif

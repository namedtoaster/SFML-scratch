#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef IMAGE_H
#define IMAGE_H

class Image {
 public:
  Image(float*);
  void bind();
  //private:
  float * verts;
  unsigned int VBO;
  unsigned int VAO;
};

#endif

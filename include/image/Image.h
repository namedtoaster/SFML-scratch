#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef IMAGES_H
#define IMAGES_H

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

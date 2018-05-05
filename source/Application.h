#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef APPLICATION_H

class Application {
 public:
 Application(int W = 600, int H = 600) : width(W), height(H) {}
  int init();
  int run();
 private:
  int width; int height;
  GLFWwindow *window;
};

#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef APPLICATION_H

class Application {
 public:
  Application(int x, int y);
  int init();
  int run();
 private:
  int width; int height;
  GLFWwindow *window;
};

#endif

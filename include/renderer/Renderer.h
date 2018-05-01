#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Image.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
 public:
 Renderer() : ourShader("../shaders/shader.vert", "../shaders/shader.frag") {
    float vertices[] = {
      // positions         // colors
      0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   // bottom right
      -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
      0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f    // top
    };

    // will need some sort of Image list. The Renderer will add and bind them as required
    //Image image1(vertices);
  }

  int render_screen(GLFWwindow *);
  int drawImages();
  // private:
  Shader ourShader;
};

#endif

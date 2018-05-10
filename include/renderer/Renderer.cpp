#include <iostream>

#include "Renderer.h"
#include "Shader.h"
#include "Image.h"

void processInput(GLFWwindow *window);

int Renderer::draw_images() {
  // Eventually, this will need to go through a list of images and bind the VAOs then draw the arrays. For now, since there's only 1, we'll only do it once
  //image1.draw();

	return 0;
}

int Renderer::render_screen(GLFWwindow *window) {
  Image image1;

  // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
    {
      // input
      // -----
      processInput(window);

      // set the background color
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // user our shader
      ourShader.use();

      // render the image
      image1.render();

      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      // -------------------------------------------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  //glDeleteVertexArrays(1, &VAO);
  //glDeleteBuffers(1, &VBO);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

#include <iostream>

#include "Renderer.h"
#include "Shader.h"
#include "Image.h"

void processInput(GLFWwindow *window);

// For some reason, the image will not display on the screen whenever I bind the VBOs and VAOs outside of the render_screen method. At first, I tried creating a method in the Image class to do what I'm doing with this bind_image function and that didn't work. So I thought maybe if I did it inside the scope of this file, it would. It still doesn't however. I can manage with having to do that with multiple images by running through a loop, but I prefer to separate out the function. We'll see
//
// NOTE/UPDATE: SEE THE COMMENT RIGHT ABOVE THE GLBUFFERDATA FUNCTION BELOW
/*void bind_image(Image img) {
  glGenVertexArrays(1, &img.VAO);
  glGenBuffers(1, &img.VBO);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(img.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, img.VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(img.verts), img.verts, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);
  }*/

int Renderer::draw_images() {
  // Eventually, this will need to go through a list of images and bind the VAOs then draw the arrays. For now, since there's only 1, we'll only do it once
  //image1.draw();
	
	return 0;
}

int Renderer::render_screen(GLFWwindow *window) {
  float vertices[] = {
    // positions         // colors
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f    // top
  };

  Image image1(vertices);

  glGenVertexArrays(1, &image1.VAO);
  glGenBuffers(1, &image1.VBO);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(image1.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, image1.VBO);
  // NOTE: The image will only be drawn to the screen if using the vertices var, NOT the image1.verts member. Not really sure why, but this seems to be the source of my problem
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
    {
      // input
      // -----
      processInput(window);

      // render
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // draw our first triangle
      ourShader.use();

      // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
      glBindVertexArray(image1.VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // no need to unbind it every time
      // glBindVertexArray(0);
 
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

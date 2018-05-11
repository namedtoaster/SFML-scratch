#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Image.h"

Image::Image(std::vector<float>& pos, std::vector<float>& color) {
  std::vector<float> verts_init;

  // init vert member
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        verts_init.push_back(pos[3 * i + j]);
      }
    for (int j = 0; j < 3; j++) {
      verts_init.push_back(color[3 * i + j]);
    }
  }

  // since I don't know how to convert from a vector to a dynamic array, I will just create a temp vector whose contents i will copy to a static array. this needs to be fixed in the future
  std::copy(verts_init.begin(), verts_init.end(), verts);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  // now bind the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

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
}


void Image::render() {
  // we must re-bind the VAO since we need the data in order to render the triangle
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

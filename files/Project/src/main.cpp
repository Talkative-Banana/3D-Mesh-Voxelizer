#define VOXELIZER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <./stb/stb_image.h>
#include <./stb/stb_image_write.h>

#include "string.h"
#include "utils.h"

// uniform int numRenderTargets;

// Globals
int screen_width = 2240, screen_height = 1400;
float dim = 128.0;
GLint vModel_uniform, vView_uniform, vProjection_uniform;
GLint halfPxsize_uniform, color_uniform;
glm::mat4 modelT, viewT,
    projectionT; // The model, view and projection transformations
GLint voxel_dim = 1, Box_xl, Box_xu, Box_yl, Box_yu, Box_zl, Box_zu,
      voxel_count;
vector<vector<vector<bool>>>
    Grid(dim, vector<vector<bool>>(dim, vector<bool>(dim, false)));
GLint voxel_countx, voxel_county, voxel_countz;
glm::vec4 color = glm::vec4(0.0, 0.0, 0.0, 0.0);

GLfloat Nplane = -100.f, Fplane = -13200.f;

double oldX, oldY, currentX, currentY;
bool isDragging = false;
glm::vec4 camPosition;
char textKeyStatus[256];
float speed = 1.0f;
bool Perspective = false;

void createMeshObject(unsigned int &, unsigned int &);

void setupModelTransformation(unsigned int &);
void setupViewTransformation(unsigned int &);
void setupProjectionTransformation(unsigned int &);
glm::vec3 getTrackBallVector(double x, double y);
void camTrans(glm::vec3 &);
void saveTextureToFile(const std::string &filename, int width, int height);

GLuint nVertices;
float scale = 1; // Change Scale of the model as needed

string tex_name = "banana";
unsigned int shaderProgram, shaderProgram2;
bool mesh = true;
int mode_ = 1;

int main() {
  // Setup window
  GLFWwindow *window = setupWindow(screen_width, screen_height);
  ImGuiIO &io = ImGui::GetIO(); // Create IO object
  ImVec4 clearColor = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);

  // unsigned int shaderProgram = createProgram("./shaders/vshader.vs",
  // "./shaders/fshader.fs");
  shaderProgram =
      createProgram("./shaders/vshader1.vs", "./shaders/fshader1.fs",
                    "./shaders/gshader1.gs");
  shaderProgram2 =
      createProgram("./shaders/vshadervis.vs", "./shaders/fshadervis.fs",
                    "./shaders/gshadervis.gs");

  halfPxsize_uniform = glGetUniformLocation(shaderProgram, "halfPixelSize");
  if (halfPxsize_uniform == -1) {
    fprintf(stderr, "Could not bind location: halfPixelSize.\n");
  }

  color_uniform = glGetUniformLocation(shaderProgram, "color");
  if (color_uniform == -1) {
    fprintf(stderr, "Could not bind location: color.\n");
  }

  int vPoint_attrib = glGetAttribLocation(shaderProgram2, "vPoint");
  if (vPoint_attrib == -1) {
    fprintf(stderr, "Could not bind location: vPoint\n");
    exit(0);
  }

  glUseProgram(shaderProgram);
  glUniform2f(halfPxsize_uniform, 0.5 / dim, 0.5 / dim);

  oldX = oldY = currentX = currentY = 0.0;
  int prevLeftButtonState = GLFW_RELEASE;
  int mode = 0; // 0 for manual drag, 1 for auto rotate

  Box_xl = std::numeric_limits<GLint>::max();
  Box_xu = std::numeric_limits<GLint>::min();

  Box_yl = std::numeric_limits<GLint>::max();
  Box_yu = std::numeric_limits<GLint>::min();

  Box_zl = std::numeric_limits<GLint>::max();
  Box_zu = std::numeric_limits<GLint>::min();
  unsigned int VAO, VAO2;
  glGenVertexArrays(1, &VAO);
  glGenVertexArrays(1, &VAO2);

  vector<glm::vec3> point_vertices;
  GLfloat *Vertex;
  GLuint vertex_VBO2; // Vertex Buffer

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    // printf("%.3f\n", Nplane);

    glm::vec3 change(0.0f, 0.0f, 0.0f);
    // Get key presses
    if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow))) {
      strcpy(textKeyStatus, "Key status: Left");
      // TODO:
      change.x += speed;
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow))) {
      strcpy(textKeyStatus, "Key status: Right");
      // TODO:
      change.x -= speed;
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_UpArrow))) {
      if (io.KeyShift) {
        strcpy(textKeyStatus, "Key status: Shift + Up");
        // TODO:
        change.z -= speed;
        // Nplane -= speed; // going away
        // Fplane = Nplane - 1;
      } else {
        strcpy(textKeyStatus, "Key status: Up");
        // TODO:
        change.y += speed;
      }
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_DownArrow))) {
      if (io.KeyShift) {
        strcpy(textKeyStatus, "Key status: Shift + Down");
        // TODO:
        change.z += speed;
        // Nplane += speed;
        // Fplane = Nplane - 1;
      } else {
        strcpy(textKeyStatus, "Key status: Down");
        // TODO:
        change.y -= speed;
      }
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Z))) {
      if (io.KeyCtrl) {
        strcpy(textKeyStatus, "Key status: Ctrl + z");
        // Move camera to [0, 0, 100] i.e. => along z axis
        if (!Perspective || Perspective) {
          camPosition = {0.0f, 0.0f, 100.0f, 1.0f};
        }
      } else {
        strcpy(textKeyStatus, "Key status: z");
        Perspective = false;
      }
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_X))) {
      if (io.KeyCtrl) {
        strcpy(textKeyStatus, "Key status: Ctrl + x");
        // Move camera to [100, 0, 0] i.e. => along x axis
        if (!Perspective || Perspective) {
          camPosition = {100.0f, 0.0f, 0.0f, 1.0f};
        }
      } else {
        strcpy(textKeyStatus, "Key status: x");
        Perspective = true;
      }
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Y))) {
      if (io.KeyCtrl) {
        strcpy(textKeyStatus, "Key status: Ctrl + y");
        // Move camera to [0, 100, 0] i.e. => along y axis (due to camera
        // rolling gaze direction shouldn't be parallel to y) So Moved with some
        // offset
        if (!Perspective || Perspective) {
          camPosition = {0.0f, 100.0f, 0.20f, 1.0f};
        }
      }
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_C))) {
      strcpy(textKeyStatus, "Key status: Z");
      mode_ = (mode_ + 1) % 4;
      mesh = true;
    } else {
      strcpy(textKeyStatus, "Key status:");
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui UI menu
    ImGui::Begin("Main", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::CollapsingHeader("Information",
                                ImGuiTreeNodeFlags_DefaultOpen)) {
      ImGui::Text("%.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::Text("%s", textKeyStatus);
      ImGui::Text("Camera position: (%.2f, %.2f, %.2f)", camPosition.x,
                  camPosition.y, camPosition.z);
      ImGui::Text("mode: (%d)", mode_);
    }
    ImGui::End();

    // glUseProgram(shaderProgram);

    if (mesh) {
      setupModelTransformation(shaderProgram);
      camTrans(change);
      setupViewTransformation(shaderProgram);
      setupProjectionTransformation(shaderProgram);
      createMeshObject(shaderProgram, VAO);
      glUseProgram(shaderProgram2);
      mesh = false;

      // shaderProgram2 = createProgram("./shaders/vshadervis.vs",
      // "./shaders/fshadervis.fs"); -254.5 to 255.5
      point_vertices.clear();
      for (int i = 0; i < (int)dim; i++) {
        for (int j = 0; j < (int)dim; j++) {
          for (int k = 0; k < (int)dim; k++) {
            if (Grid[i][j][k]) {
              glm::vec3 temp =
                  glm::vec3(i - ((dim + 1) / 2), j - ((dim + 1) / 2),
                            k - ((dim + 1) / 2));
              point_vertices.push_back(temp);
            }
          }
        }
      }

      Vertex = new GLfloat[point_vertices.size() * 3];
      int k = 0;
      for (auto vec : point_vertices) {
        Vertex[k + 0] = vec.x;
        Vertex[k + 1] = vec.y;
        Vertex[k + 2] = vec.z;
        k += 3;
      }

      glGenBuffers(1, &vertex_VBO2);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO2);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * point_vertices.size() * 3,
                   Vertex, GL_STATIC_DRAW);
      Nplane = -100;
      Fplane = -1000;
      glUseProgram(shaderProgram2);
    }

    setupModelTransformation(shaderProgram2);
    camTrans(change);
    setupViewTransformation(shaderProgram2);
    setupProjectionTransformation(shaderProgram2);

    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // // Create VBOs for the VAO

    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*point_vertices.size()*3,
    // Vertex, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vPoint_attrib);
    glVertexAttribPointer(vPoint_attrib, 3, GL_FLOAT, GL_FALSE, 00, 0);
    // delete []Vertex;

    glViewport(0, 0, 1000,
               1000); // Render on the whole framebuffer, complete from the
                      // lower left corner to the upper right
    glBindVertexArray(VAO2);

    // // Visualize();
    glDrawArrays(GL_POINTS, 0, point_vertices.size() * 3);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // Cleanup
  cleanup(window);
}

void camTrans(glm::vec3 &Change) {
  // 1) Move from World Space to Camera Space
  // 2) Perform Translation based on key values
  // 3) Move back to World Space

  // uvw of camera space
  glm::vec3 t = {0.0f, 1.0f, 0.0f};
  glm::vec3 w = {camPosition.x, camPosition.y, camPosition.z};
  w = glm::normalize(w);
  glm::vec3 u = glm::normalize(glm::cross(t, w));
  glm::vec3 v = glm::normalize(glm::cross(w, u));

  // Traslation Matrix
  glm::mat4 matT = {1, 0, 0, 0, 0,        1,        0,        0,
                    0, 0, 1, 0, Change.x, Change.y, Change.z, 1};

  // XYZ wrt UVW
  glm::mat3 temp = {u.x, v.x, w.x, u.y, v.y, w.y, u.z, v.z, w.z};

  // Solution of 3x3 XYZ matrix
  glm::mat3 rev = glm::inverse(temp);

  glm::vec3 X = glm::normalize(rev[0]);
  glm::vec3 Y = glm::normalize(rev[1]);
  glm::vec3 Z = glm::normalize(rev[2]);

  // World to Camera Matrix Rotation
  glm::mat4 w2cr = {X.x, Y.x, Z.x, 0, X.y, Y.y, Z.y, 0,
                    X.z, Y.z, Z.z, 0, 0,   0,   0,   1};

  // World to Camera Matrix Transaltion
  glm::mat4 w2ct = {1,
                    0,
                    0,
                    0,
                    0,
                    1,
                    0,
                    0,
                    0,
                    0,
                    1,
                    0,
                    -camPosition.x,
                    -camPosition.y,
                    -camPosition.z,
                    1};

  // World to Camera Matrix
  glm::mat4 w2c = w2cr * w2ct;

  // New Adjusted vector involving key inputs
  glm::vec4 adjustedvec = matT * w2c * camPosition;

  // Camera to World Matrix Rotation
  glm::mat4 c2wr = {u.x, u.y, u.z, 0, v.x, v.y, v.z, 0,
                    w.x, w.y, w.z, 0, 0,   0,   0,   1};

  // Camera to World Matrix Transalation
  glm::mat4 c2wt = {1,
                    0,
                    0,
                    0,
                    0,
                    1,
                    0,
                    0,
                    0,
                    0,
                    1,
                    0,
                    adjustedvec.x,
                    adjustedvec.y,
                    adjustedvec.z,
                    1};

  // Camera to World Matrix
  glm::mat4 c2w = c2wr * c2wt;
  // Change vector in camPosition
  glm::vec4 newcampos = c2w * adjustedvec;

  camPosition.x += newcampos.x;
  camPosition.y += newcampos.y;
  camPosition.z += newcampos.z;
}

void setupModelTransformation(unsigned int &program) {
  // Modelling transformations (Model -> World coordinates)
  modelT = glm::translate(
      glm::mat4(1.0f),
      glm::vec3(0.0, 0.0, 0.0)); // Model coordinates are the world coordinates

  // Pass on the modelling matrix to the vertex shader
  glUseProgram(program);
  vModel_uniform = glGetUniformLocation(program, "vModel");
  if (vModel_uniform == -1) {
    fprintf(stderr, "Could not bind location: vModel\n");
    exit(0);
  }
  glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(modelT));
}

void setupViewTransformation(unsigned int &program) {
  // Viewing transformations (World -> Camera coordinates
  // Camera at (40, 20, 40)  in a right handed coordinate system
  viewT = glm::lookAt(glm::vec3(camPosition), glm::vec3(0.0, 0.0, 0.0),
                      glm::vec3(0.0, 1.0, 0.0));

  // Pass-on the viewing matrix to the vertex shader
  glUseProgram(program);
  vView_uniform = glGetUniformLocation(program, "vView");
  if (vView_uniform == -1) {
    fprintf(stderr, "Could not bind location: vView\n");
    exit(0);
  }
  glUniformMatrix4fv(vView_uniform, 1, GL_FALSE, glm::value_ptr(viewT));
}

void setupProjectionTransformation(unsigned int &program) {
  // Projection transformation
  //  mesh = true;
  if (mesh) {
    projectionT = glm::ortho(-255.0f, 256.0f, -255.0f, 256.0f, Nplane, Fplane);
  } else {
    projectionT = glm::perspective(
        45.0f, (GLfloat)screen_width / (GLfloat)screen_height, 0.1f, 1000.0f);
  }
  // mesh = false;
  // projectionT = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 12.0f, 13.0f);
  // projectionT = glm::ortho(-255.0f, 256.0f, -255.0f, 256.0f, 20.0f, 376.0f);
  // Pass on the projection matrix to the vertex shader
  glUseProgram(program);
  vProjection_uniform = glGetUniformLocation(program, "vProjection");
  if (vProjection_uniform == -1) {
    fprintf(stderr, "Could not bind location: vProjection\n");
    exit(0);
  }
  glUniformMatrix4fv(vProjection_uniform, 1, GL_FALSE,
                     glm::value_ptr(projectionT));
}

glm::vec3 getTrackBallVector(double x, double y) {
  glm::vec3 p =
      glm::vec3(2.0 * x / screen_width - 1.0, 2.0 * y / screen_height - 1.0,
                0.0); // Normalize to [-1, +1]
  p.y = -p.y; // Invert Y since screen coordinate and OpenGL coordinates have
              // different Y directions.

  float mag2 = p.x * p.x + p.y * p.y;
  if (mag2 <= 1.0f)
    p.z = sqrtf(1.0f - mag2);
  else
    p = glm::normalize(p); // Nearest point, close to the sides of the trackball
  return p;
}

void saveTextureToFile(const std::string &filename, int width, int height) {
  std::vector<unsigned char> pixels(4 * width * height);
  glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
  stbi_write_png(filename.c_str(), width, height, 4, pixels.data(), 0);
}

void Rasterize(char dir, vector<glm::vec3> &bucket, GLfloat *buc,
               unsigned int &shape_VAO, int vVertex_attrib) {
  int slabs = ceil((double)dim / (double)32);

  unsigned int sheetbuffer;

  camPosition = (dir == 'x')   ? glm::vec4(-100.0f, 0.0f, 0.0f, 1.0f)
                : (dir == 'y') ? glm::vec4(0.0f, -100.0f, 0.00001f, 1.0f)
                               : glm::vec4(0.0f, 0.0f, 100.0f, 1.0f);
  setupViewTransformation(shaderProgram);

  // Generate VAO object
  glGenVertexArrays(1, &shape_VAO);
  glBindVertexArray(shape_VAO);

  // Create VBOs for the VAO
  GLuint vertex_VBO; // Vertex Buffer
  glGenBuffers(1, &vertex_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bucket.size() * 3, buc,
               GL_STATIC_DRAW);
  // glBufferData(GL_FRAMEBUFFER, sizeof(GLfloat)*vertex_indices.size()*3,
  // shape_vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vVertex_attrib);
  glVertexAttribPointer(vVertex_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
  // -100 340

  for (int slab = 1; slab <= slabs; slab++) {
    int slab_len = dim, slab_wid = dim, slab_dep = 32;
    int nplane = -100 + 32 * (slab - 1);
    int fplane = nplane - slab_dep;
    Nplane = nplane, Fplane = fplane;
    setupProjectionTransformation(shaderProgram);

    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth
    // buffer.
    GLuint FramebufferName = 1;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    tex_name = "./textures/" + to_string(slab) + dir;
    // The texture we're going to render to
    GLuint renderedTexture;
    glGenTextures(1, &renderedTexture);
    // "Bind" the newly created texture : all future texture functions will
    // modify this texture
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dim, dim, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, NULL);
    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           renderedTexture, 0);

    // // Set the list of draw buffers.
    // GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    // glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      perror("Error in Fraame Buffer: ");
      exit(1);
    }

    // Render to our framebuffer

    glViewport(0, 0, dim, dim); // Render on the whole framebuffer, complete
                                // from the lower left corner to the upper right

    glBindVertexArray(shape_VAO);
    int count = 0;
    for (int Fplane = nplane - 1; Fplane >= fplane; Fplane--) {
      Nplane = Fplane + 1;
      // 32 total
      // first 8 will go in R
      // then  8 will go in G
      // and so on... for B and A
      // 1 1 1 1 1 1 1 1
      if (count < 8) {
        glUniform2f(color_uniform, 0.0, count);
      } else if (count < 16) {
        glUniform2f(color_uniform, 1.0, count - 8);
      } else if (count < 24) {
        glUniform2f(color_uniform, 2.0, count - 16);
      } else {
        glUniform2f(color_uniform, 3.0, count - 24);
      }
      glDrawArrays(GL_TRIANGLES, 0, bucket.size() * 3);
      count++;
    }
    saveTextureToFile(tex_name, dim, dim);

    glClear(GL_COLOR_BUFFER_BIT);
    glDeleteTextures(1, &renderedTexture);
    glDeleteFramebuffers(1, &FramebufferName);
  }
}

void BatchRender(string dir) {
  for (int slab = 1; slab <= dim / 32; slab++) {
    tex_name = "./textures/" + to_string(slab) + dir;
    int loadlen = dim, loadbre = dim, loadch = 4;
    const int textureSize = loadlen * loadbre;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load(tex_name.c_str(), &loadlen, &loadbre, &loadch, 4);
    if (data) {
      unsigned bytePerPixel = 4;
      for (int i = 0; i < loadlen; i++) {
        for (int j = 0; j < loadbre; j++) {
          unsigned char *pixelOffset = data + (i + loadlen * j) * bytePerPixel;
          int r = pixelOffset[0];
          int g = pixelOffset[1];
          int b = pixelOffset[2];
          int a = pixelOffset[3];
          if (r != 0 || g != 0 || b != 0 || a != 0) {
            // printf("%d %d %d %d \n", r, g, b, a);
            // On Z axis L yx
            // On X axis L zy
            // On Y axis L xz
            int l, m, n;
            for (int k = 0; k < 32; k++) {
              if (dir == "z")
                l = i, m = j, n = 16 * (slab - 1) + k;
              else if (dir == "x")
                l = 16 * (slab - 1) + k, m = j, n = i;
              else
                l = i, m = 16 * (slab - 1) + k, n = j;
              if (k < 8) {
                if ((r >> k) & 1) {
                  Grid[l][m][n] = true;
                }
              } else if (k < 16) {
                if ((g >> (k - 8)) & 1) {
                  Grid[l][m][n] = true;
                }
              } else if (k < 24) {
                if ((b >> (k - 16)) & 1) {
                  Grid[l][m][n] = true;
                }
              } else {
                if ((a >> (k - 24)) & 1) {
                  Grid[l][m][n] = true;
                }
              }
            }
          }
        }
      }
    } else {
      std::cout << "Failed to load texture" << std::endl;
      perror("Err: ");
    }
  }
}

void createMeshObject(unsigned int &program, unsigned int &shape_VAO) {
  vector<int> vertex_indices, uv_indices, normal_indices;
  vector<glm::vec3> temp_vertices;
  vector<glm::vec2> temp_uvs;
  vector<glm::vec3> temp_normals;
  int ct = 0;

  scale = 0.8; // Change Scale of the model as needed
  FILE *file = fopen("src/bunny.obj", "r");
  if (file == NULL)
    printf("File not found\n");

  while (true) {

    char head[128];
    // read the first word of the line
    int res = fscanf(file, "%s", head);
    if (res == EOF)
      break; // EOF = End Of File. Quit the loop.

    if (strcmp(head, "v") == 0) {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      // printf("%f %f %f\n", vertex.x, vertex.y, vertex.z );
      temp_vertices.push_back(vertex);
      ct++;
    }

    else if (strcmp(head, "vt") == 0) {
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      // printf("%f %f\n", uv.x, uv.y );
      temp_uvs.push_back(uv);
    }

    else if (strcmp(head, "vn") == 0) {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      // printf("%f %f %f\n", normal.x, normal.y, normal.z );
      temp_normals.push_back(normal);
    }

    else if (strcmp(head, "f") == 0) {
      string vertex1, vertex2, vertex3;
      int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                           &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                           &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                           &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
      if (matches != 9) {
        printf("OBJ File may not contain texture coordinates or normal "
               "coordinates\n");
      }
      vertex_indices.push_back(vertexIndex[0]);
      vertex_indices.push_back(vertexIndex[1]);
      vertex_indices.push_back(vertexIndex[2]);
      uv_indices.push_back(uvIndex[0]);
      uv_indices.push_back(uvIndex[1]);
      uv_indices.push_back(uvIndex[2]);
      normal_indices.push_back(normalIndex[0]);
      normal_indices.push_back(normalIndex[1]);
      normal_indices.push_back(normalIndex[2]);
    }
  }
  fclose(file);

  glUseProgram(program);

  // Bind shader variables
  int vVertex_attrib = glGetAttribLocation(program, "vVertex");
  if (vVertex_attrib == -1) {
    fprintf(stderr, "Could not bind location: vVertex\n");
    exit(0);
  }

  GLfloat *shape_vertices = new GLfloat[vertex_indices.size() * 3];
  GLfloat *vertex_normals = new GLfloat[normal_indices.size() * 3];

  nVertices = vertex_indices.size() * 3;

  for (int i = 0; i < vertex_indices.size(); i++) {
    int vertexIndex = vertex_indices[i];
    shape_vertices[i * 3] = temp_vertices[vertexIndex - 1][0] * scale;
    shape_vertices[i * 3 + 1] = temp_vertices[vertexIndex - 1][1] * scale;
    shape_vertices[i * 3 + 2] = temp_vertices[vertexIndex - 1][2] * scale;

    Box_xl = std::min((GLint)(std::floor(shape_vertices[i * 3])), Box_xl);
    Box_xu = std::max((GLint)std::ceil(shape_vertices[i * 3]), Box_xl);

    Box_yl = std::min((GLint)std::floor(shape_vertices[i * 3 + 1]), Box_yl);
    Box_yu = std::max((GLint)std::ceil(shape_vertices[i * 3 + 1]), Box_yu);

    Box_zl = std::min((GLint)std::floor(shape_vertices[i * 3]), Box_zl);
    Box_zu = std::max((GLint)std::ceil(shape_vertices[i * 3]), Box_zu);
  }

  // printf("%d %d %d   %d %d %d\n", Box_xl, Box_yl, Box_zl, Box_xu, Box_yu,
  // Box_zu);
  voxel_countx = Box_xu - Box_xl;
  voxel_county = Box_yu - Box_yl;
  voxel_countz = Box_zu - Box_zl;
  voxel_count = voxel_countx * voxel_county * voxel_countz;
  // cout << Box_zl << " " << Box_zu << endl;
  // printf("%d\n", voxel_count);

  // generated normals for the triangle mesh
  for (int i = 0; i < vertex_indices.size(); i += 3) {
    glm::vec3 v1 =
        glm::vec3(shape_vertices[(i + 1) * 3] - shape_vertices[i * 3],
                  shape_vertices[(i + 1) * 3 + 1] - shape_vertices[i * 3 + 1],
                  shape_vertices[(i + 1) * 3 + 2] - shape_vertices[i * 3 + 2]);
    glm::vec3 v2 = glm::vec3(
        shape_vertices[(i + 2) * 3] - shape_vertices[(i + 1) * 3],
        shape_vertices[(i + 2) * 3 + 1] - shape_vertices[(i + 1) * 3 + 1],
        shape_vertices[(i + 2) * 3 + 2] - shape_vertices[(i + 1) * 3 + 2]);

    glm::vec3 n = norm(v1, v2);

    vertex_normals[i * 3] = n.x;
    vertex_normals[(i + 1) * 3] = n.x;
    vertex_normals[(i + 2) * 3] = n.x;
    vertex_normals[i * 3 + 1] = n.y;
    vertex_normals[(i + 1) * 3 + 1] = n.y;
    vertex_normals[(i + 2) * 3 + 1] = n.y;
    vertex_normals[i * 3 + 2] = n.z;
    vertex_normals[(i + 1) * 3 + 2] = n.z;
    vertex_normals[(i + 2) * 3 + 2] = n.z;
  }

  vector<glm::vec3> bucketX, bucketY, bucketZ;

  for (int i = 0; i < vertex_indices.size(); i += 3) {
    // Represents vertices and normal of the triangle
    glm::vec3 P1 = glm::vec3(shape_vertices[i * 3], shape_vertices[i * 3 + 1],
                             shape_vertices[i * 3 + 2]); // x cords of triangle
    glm::vec3 P2 =
        glm::vec3(shape_vertices[(i + 1) * 3], shape_vertices[(i + 1) * 3 + 1],
                  shape_vertices[(i + 1) * 3 + 2]); // y cords of triangle
    glm::vec3 P3 =
        glm::vec3(shape_vertices[(i + 2) * 3], shape_vertices[(i + 2) * 3 + 1],
                  shape_vertices[(i + 2) * 3 + 2]); // z cords of triangle

    glm::vec3 v1 = P1 - P2;
    glm::vec3 v2 = P3 - P2;

    glm::vec3 normal = normalize(cross(v1, v2));

    float x = abs(glm::dot(normal, glm::vec3(1.0, 0.0, 0.0)));
    float y = abs(glm::dot(normal, glm::vec3(0.0, 1.0, 0.0)));
    float z = abs(glm::dot(normal, glm::vec3(0.0, 0.0, 1.0)));

    if (x > y) {
      if (x > z) {
        // x greatest
        bucketX.push_back(P1);
        bucketX.push_back(P2);
        bucketX.push_back(P3);
      } else {
        // z x y
        bucketZ.push_back(P1);
        bucketZ.push_back(P2);
        bucketZ.push_back(P3);
      }
    } else {
      if (y > z) {
        // y greatest
        bucketY.push_back(P1);
        bucketY.push_back(P2);
        bucketY.push_back(P3);
      } else {
        // z y x
        bucketZ.push_back(P1);
        bucketZ.push_back(P2);
        bucketZ.push_back(P3);
      }
    }
  }

  GLfloat bucX[bucketX.size() * 3];
  GLfloat bucY[bucketY.size() * 3];
  GLfloat bucZ[bucketZ.size() * 3];

  for (int i = 0; i < bucketX.size(); i++) {
    glm::vec3 temp = bucketX[i];
    for (int j = 0; j < 3; j++) {
      bucX[3 * i + j] = temp[j];
    }
  }

  for (int i = 0; i < bucketY.size(); i++) {
    glm::vec3 temp = bucketY[i];
    for (int j = 0; j < 3; j++) {
      bucY[3 * i + j] = temp[j];
    }
  }

  for (int i = 0; i < bucketZ.size(); i++) {
    glm::vec3 temp = bucketZ[i];
    for (int j = 0; j < 3; j++) {
      bucZ[3 * i + j] = temp[j];
    }
  }

  // RGBA
  Rasterize('x', bucketX, bucX, shape_VAO, vVertex_attrib);
  Rasterize('y', bucketY, bucY, shape_VAO, vVertex_attrib);
  Rasterize('z', bucketZ, bucZ, shape_VAO, vVertex_attrib);

  // Clearing the buffer
  for (int i = 0; i < (int)dim; i++) {
    for (int j = 0; j < (int)dim; j++) {
      for (int k = 0; k < (int)dim; k++) {
        Grid[i][j][k] = false;
      }
    }
  }

  if (mode_ == 1) {
    cout << "Rendering Along Z axis\n";
    BatchRender("z");
  } else if (mode_ == 2) {
    cout << "Rendering Along X axis\n";
    BatchRender("x");
  } else if (mode_ == 3) {
    cout << "Rendering Along X and Z axis\n";
    BatchRender("x");
    BatchRender("z");
  } else {
    cout << "Rendering Along X, Y and Z axis\n";
    BatchRender("x");
    BatchRender("y");
    BatchRender("z");
  }

  // BatchRender("x");
  // // BatchRender("y");
  // BatchRender("z");
}

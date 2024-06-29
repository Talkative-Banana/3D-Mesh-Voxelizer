#define VOXELIZER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <./stb/stb_image.h>
#include <./stb/stb_image_write.h>

#include "string.h"
#include <thread>
#include "utils.h"
#include "chunk.h"
#include "block.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

// uniform int numRenderTargets;

// Globals
int dim;
int texturedim = 256;
int screen_width = 1000, screen_height = 1000;
GLint vModel_uniform, vView_uniform, vProjection_uniform;
GLint halfPxsize_uniform, color_uniform, voxel_dim_uniform;
glm::mat4 modelT, viewT, projectionT; // The model, view and projection transformations
// TODO:
GLint voxel_dim = 2, Box_xl, Box_xu, Box_yl, Box_yu, Box_zl, Box_zu, voxel_count;
vector<vector<vector<bool>>> Grid;
GLint voxel_countx, voxel_county, voxel_countz;
glm::vec4 color = glm::vec4(0.0, 0.0, 0.0, 0.0);

GLfloat Nplane = -100.f, Fplane = -13200.f;

double oldX, oldY, currentX, currentY;
bool isDragging = false;
glm::vec4 camPosition;
char textKeyStatus[256];
float speed = 5.0f;
bool Perspective = false;

FILE *LoadModel(const char *);
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
unsigned int shaderProgram, shaderProgram3;
bool mesh = true;
int mode_ = 4;

int main() {
  // Setup window
  GLFWwindow *window = setupWindow(screen_width, screen_height);
  ImGuiIO &io = ImGui::GetIO(); // Create IO object
  ImVec4 clearColor = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);

  // unsigned int shaderProgram = createProgram("./shaders/vshader.vs",
  // "./shaders/fshader.fs");
  shaderProgram = createProgram("./shaders/vshader1.vs", "./shaders/fshader1.fs",
                    "./shaders/gshader1.gs");

  shaderProgram3 = createProgram("./shaders/vshader.vs", "./shaders/fshader.fs");

  halfPxsize_uniform = glGetUniformLocation(shaderProgram, "halfPixelSize");
  if (halfPxsize_uniform == -1) {
    fprintf(stderr, "Could not bind location: halfPixelSize.\n");
  }

  color_uniform = glGetUniformLocation(shaderProgram, "color");
  if (color_uniform == -1) {
    fprintf(stderr, "Could not bind location: color.\n");
  }

  glUseProgram(shaderProgram);
  // TODO:
  glUniform2f(halfPxsize_uniform, 1.0/256, 1.0/256);

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

  GLfloat *Vertex;
  GLuint vertex_VBO2; // Vertex Buffer
  VertexArray chunkva;
  int cntblocks;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    // printf("%.3f\n", Nplane);

    glm::vec3 change(0.0f, 0.0f, 0.0f);
    // Get key presses
    if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_LeftArrow))) {
      strcpy(textKeyStatus, "Key status: Left");
      change.x += speed;
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_RightArrow))) {
      strcpy(textKeyStatus, "Key status: Right");
      change.x -= speed;
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_UpArrow))) {
      if (io.KeyShift) {
        strcpy(textKeyStatus, "Key status: Shift + Up");
        change.z -= speed;
        // Nplane -= speed; // going away
        // Fplane = Nplane - 1;
      } else {
        strcpy(textKeyStatus, "Key status: Up");
        change.y += speed;
      }
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_DownArrow))) {
      if (io.KeyShift) {
        strcpy(textKeyStatus, "Key status: Shift + Down");
        change.z += speed;
        // Nplane += speed;
        // Fplane = Nplane - 1;
      } else {
        strcpy(textKeyStatus, "Key status: Down");
        change.y -= speed;
      }
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Z))) {
      if (io.KeyCtrl) {
        strcpy(textKeyStatus, "Key status: Ctrl + z");
        // Move camera to [0, 0, 100] i.e. => along z axis
        if (!Perspective || Perspective) {
          camPosition = {0.0f, 0.0f, -100.0f, 1.0f};
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
          camPosition = {-100.0f, 0.0f, 0.0f, 1.0f};
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
          camPosition = {0.0f, -100.0f, 0.20f, 1.0f};
        }
      }
    } else if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_C))) {
      strcpy(textKeyStatus, "Key status: C");
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
    if (ImGui::CollapsingHeader("Information", ImGuiTreeNodeFlags_DefaultOpen)) {
      ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::Text("%s", textKeyStatus);
      ImGui::Text("Camera position: (%.2f, %.2f, %.2f)", camPosition.x, camPosition.y, camPosition.z);
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
      mesh = false;

      // shaderProgram2 = createProgram("./shaders/vshadervis.vs",
      // "./shaders/fshadervis.fs"); -64.5 to 62.5 (65 on left 63 on right)
      chunk c = chunk(voxel_dim, glm::vec3(0.0, 0.0, 0.0), true);
      for (int i = 0; i < (int)dim; i++) {
        for (int j = 0; j < (int)dim; j++) {
          for (int k = 0; k < (int)dim; k++) {
            c.filled[i][j][k] = Grid[i][j][k];
          }
        }
      }

      c.Render();

      GLuint vcnt = c.rendervert.size(), icnt = c.indices.size(), cnt = c.count;
      // Allocate Heap memory for verticies and indices
      GLfloat* cube_vertices = (GLfloat*)malloc(vcnt * sizeof(GLfloat));
      GLuint* cube_indices = (GLuint*)malloc(icnt * sizeof(GLuint));
      // Assign the memory
      for(int i = 0; i < vcnt; i++) cube_vertices[i] = c.rendervert[i];
      for(int i = 0; i < icnt; i++) cube_indices[i] = c.indices[i];

      std::cout << "[Memory Usage: " << (1.0 * (vcnt * sizeof(GLfloat) + icnt * sizeof(GLuint))) / 1e6 << " mb]" << std::endl;

      //Create VBOs for the VAO
      int numofbytespervertex = 3;
      int numofvertexperblock = 8;
      cntblocks = cnt;
      VertexBuffer vb(cube_vertices, cnt * numofbytespervertex * numofvertexperblock * sizeof(GLfloat));
      // Create Layout for VAO
      // Position information (data + format)
      VertexBufferLayout layout;
      layout.Push(GL_FLOAT, 3);
      // Add vb and layout to vao
      chunkva.AddBuffer(vb, layout);
      // Create IBOs for the VAO
      IndexBuffer ib(cube_indices, icnt);
      ib.Bind();
      delete []cube_vertices;
      delete []cube_indices;
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0); //Unbind the VAO to disable changes outside this function.
    }
    setupModelTransformation(shaderProgram3);
    camTrans(change);
    setupViewTransformation(shaderProgram3);
    setupProjectionTransformation(shaderProgram3);

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    // Create VBOs for the VAO
    glUseProgram(shaderProgram3);
    glViewport(0, 0, 1000, 1000); // Render on the whole framebuffer, complete from the
    // lower left corner to the upper right
    chunkva.Bind();
		glDrawElements(GL_LINES, cntblocks * 12 * 3, GL_UNSIGNED_INT, nullptr);
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
  viewT = glm::lookAt(glm::vec3(camPosition), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

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
    projectionT = glm::ortho(-256.0f, 256.0f, -256.0f, 256.0f, Nplane, Fplane);
  } else {
    projectionT = glm::perspective(45.0f, (GLfloat)screen_width / (GLfloat)screen_height, 0.1f, 1000.0f);
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
  glUniformMatrix4fv(vProjection_uniform, 1, GL_FALSE,glm::value_ptr(projectionT));
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

void Rasterize(char dir, vector<glm::vec3> &bucket, GLfloat *buc, unsigned int &shape_VAO, int vVertex_attrib) {
  int slabs = ceil((double)dim / (double)32);

  camPosition = (dir == 'x') ? glm::vec4(-1000.0f, 0.0f, 0.0f, 1.0f)
              : (dir == 'y') ? glm::vec4(0.0f, -1000.0f, 0.0001f, 1.0f)
                             : glm::vec4(0.0f, 0.0f, -1000.0f, 1.0f);

  setupViewTransformation(shaderProgram);
  // Generate VAO object
  glGenVertexArrays(1, &shape_VAO);
  glBindVertexArray(shape_VAO);

  // Create VBOs for the VAO
  GLuint vertex_VBO; // Vertex Buffer
  glGenBuffers(1, &vertex_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bucket.size() * 3, buc, GL_STATIC_DRAW);
  // glBufferData(GL_FRAMEBUFFER, sizeof(GLfloat)*vertex_indices.size()*3,
  // shape_vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vVertex_attrib);
  glVertexAttribPointer(vVertex_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);

  // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
  GLuint FramebufferName = 1;
  glGenFramebuffers(1, &FramebufferName);
  glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

  int offset = dir == 'x' ? Box_xu - dim * voxel_dim : dir == 'y' ? Box_yu - dim * voxel_dim : Box_zu - dim * voxel_dim;
  for (int slab = 1; slab <= slabs; slab++) {
    int slab_len = texturedim, slab_wid = texturedim, slab_dep = 32 * voxel_dim;
    // int nplane = offset + 32 * voxel_dim * (slab - 1);
    int SrtPlane = 1000 - abs(offset) + (slab_dep * (slab - 1));
    int EndPlane = SrtPlane + (slabs * slab_dep) - (slab_dep * (slab - 1)); // const

    tex_name = "./textures/" + to_string(slab) + dir;
    // The texture we're going to render to
    GLuint renderedTexture;
    glGenTextures(1, &renderedTexture);
    // "Bind" the newly created texture : all future texture functions will
    // modify this texture
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texturedim, texturedim, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

    // // Set the list of draw buffers.
    // GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    // glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      perror("Error in Fraame Buffer: ");
      exit(1);
    }

    // Render to our framebuffer
    // from the lower left corner to the upper right
    glViewport(0, 0, texturedim, texturedim); // Render on the whole framebuffer, complete

    glBindVertexArray(shape_VAO);

    int count = 0;
    for (Fplane = SrtPlane + voxel_dim; Fplane <= SrtPlane + slab_dep; Fplane += voxel_dim) {
      Nplane = Fplane - voxel_dim;
      setupProjectionTransformation(shaderProgram);
      // 32 total
      // first 8 will go in R
      // then  8 will go in G
      // and so on... for B and A
      // 1 1 1 1 1 1 1 1
      if (count < 8) {
        glUniform2f(color_uniform, 0.0, pow(2, floor(8 - count)) / 256.0);
      } else if (count < 16) {
        glUniform2f(color_uniform, 1.0, pow(2, floor(16 - count)) / 256.0);
      } else if (count < 24) {
        glUniform2f(color_uniform, 2.0, pow(2, floor(24 - count)) / 256.0);
      } else {
        glUniform2f(color_uniform, 3.0, pow(2, floor(32 - count)) / 256.0);
      }
      glDrawArrays(GL_TRIANGLES, 0, bucket.size() * 3); 
      count++;
    }
    saveTextureToFile(tex_name, texturedim, texturedim);
    glClear(GL_COLOR_BUFFER_BIT);
    glDeleteTextures(1, &renderedTexture);
  }
    // Unbind Frame Buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Delete Frame Buffer
    glDeleteFramebuffers(1, &FramebufferName);
    glDisable(GL_BLEND);
}

void BatchRender(string dir) {
  int slabs = dim / 32;
  for (int slab = 1; slab <= slabs; slab++) {
    tex_name = "./textures/" + to_string(slab) + dir;
    int loadlen = texturedim, loadbre = texturedim, loadch = 4;
    const int textureSize = loadlen * loadbre;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(tex_name.c_str(), &loadlen, &loadbre, &loadch, 4);
    if (data) {
      unsigned bytePerPixel = 4;
      for (int i = 0; i < loadlen; i++) {
        for (int j = 0; j < loadbre; j++) {
          unsigned char *pixelOffset = data + (i + loadlen * j) * bytePerPixel;
          int r = pixelOffset[0];
          int g = pixelOffset[1];
          int b = pixelOffset[2];
          int a = pixelOffset[3];
          if ((r != 0) || (g != 0) || (b != 0) || (a != 0)) {
            // On Z axis L yx
            // On X axis L zy
            // On Y axis L xz
            // (l .) (m <-) n (up)
            // Grid (viewed from -x axis)
            // ^ <- (-k (left))
            // |    (+j)(up)
            // x    (+i (in screen))
            // For X
            // ->|  (+k (right))
            //   v  (-j (down))
            //   x  (+i (in screen))
            // For Z
            // ^    (+j (up))
            // <-   (+i (left))
            // x    (+k (in screen))
            int l, m, n;
            for (int k = 0; k < 32; k++) {
              int div = texturedim / dim;
              if (dir == "z"){
                l = i, m = j, n = 32 * (slabs - slab) + (32 - k - 1);
                l /= div, m /= div;
              } else if (dir == "x"){
                l = 32 * (slabs - slab) + (32 - k - 1), m = j, n = loadlen - i - 1;
                m /= div, n /= div;
              } else{
                l = loadlen - i - 1, m = 32 * (slab - 1) + k, n = loadlen - 1 - j;
                l /= div, n /= div;
              }

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

FILE *LoadModel(const char *path) {
	FILE *file = fopen(path, "r");
	return file;
}

void createMeshObject(unsigned int &program, unsigned int &shape_VAO) {
  vector<int> vertex_indices, uv_indices, normal_indices;
  vector<glm::vec3> temp_vertices;
  vector<glm::vec2> temp_uvs;
  vector<glm::vec3> temp_normals;
  int ct = 0;

  scale = 1.0; // Change Scale of the model as needed
  FILE *file = LoadModel("src/bunny.obj");
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
    Box_xu = std::max((GLint)std::ceil(shape_vertices[i * 3]), Box_xu);

    Box_yl = std::min((GLint)std::floor(shape_vertices[i * 3 + 1]), Box_yl);
    Box_yu = std::max((GLint)std::ceil(shape_vertices[i * 3 + 1]), Box_yu);

    Box_zl = std::min((GLint)std::floor(shape_vertices[i * 3]), Box_zl);
    Box_zu = std::max((GLint)std::ceil(shape_vertices[i * 3]), Box_zu);
  }

  // printf("%d %d %d   %d %d %d\n", Box_xl, Box_yl, Box_zl, Box_xu, Box_yu, Box_zu);
  int BBoxDim = 32 * ceil(max(Box_xu - Box_xl, max(Box_yu - Box_yl, Box_zu - Box_zl)) / 32.0);
  voxel_count = BBoxDim * BBoxDim * BBoxDim;
  dim = BBoxDim / voxel_dim;
  cout << "Dimension of Grid: " << dim << endl;
  Grid.assign(dim, vector<vector<bool>>(dim, vector<bool>(dim, false)));
  // printf("%d\n", voxel_count);

  // generated normals for the triangle mesh
  for (int i = 0; i < vertex_indices.size(); i += 3) {
    glm::vec3 v1 = glm::vec3(shape_vertices[(i + 1) * 3] - shape_vertices[i * 3],
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
    glm::vec3 P2 = glm::vec3(shape_vertices[(i + 1) * 3], shape_vertices[(i + 1) * 3 + 1],
                  shape_vertices[(i + 1) * 3 + 2]); // y cords of triangle
    glm::vec3 P3 = glm::vec3(shape_vertices[(i + 2) * 3], shape_vertices[(i + 2) * 3 + 1],
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

  delete[] shape_vertices;
  delete[] vertex_normals;

  // RGBA
  Rasterize('x', bucketX, bucX, shape_VAO, vVertex_attrib);
  Rasterize('y', bucketY, bucY, shape_VAO, vVertex_attrib);
  Rasterize('z', bucketZ, bucZ, shape_VAO, vVertex_attrib);

  // Clearing the buffer
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      for (int k = 0; k < dim; k++) {
        Grid[i][j][k] = false;
      }
    }
  }
  cout << dim << endl;

  if (mode_ == 1) {
    cout << "Rendering Along X axis\n";
    BatchRender("x");
  } else if (mode_ == 2) {
    cout << "Rendering Along Y axis\n";
    BatchRender("y");
  } else if (mode_ == 3) {
    cout << "Rendering Along Z axis\n";
    BatchRender("z");
  } else {
    cout << "Rendering Along X, Y and Z axis\n";
    BatchRender("x");
    BatchRender("y");
    BatchRender("z");
    // std::thread worker1(BatchRender, "x");
    // std::thread worker2(BatchRender, "y");
    // std::thread worker3(BatchRender, "z");
    // worker1.join();
    // worker2.join();
    // worker3.join();
  }

  // BatchRender("x");
  // // BatchRender("y");
  // BatchRender("z");
}

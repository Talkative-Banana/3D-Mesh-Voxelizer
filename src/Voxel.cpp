#include "utils.h"

struct Normals{
    glm::vec3 l
};

class Voxel{
public:
    GLuint side;
    glm::vec3 position;
    bool is_solid;
    vector<int> verticies;
    vector<int> indicies = {
        
    };

    Voxel(GLuint s, glm::vec3 pos, bool solid){
        side = s;
        position = pos;
        is_solid = solid;
        
    }

    void GenerateVerticies(){
        GLfloat hside = side / 2.0;
        Glfloat x = position.x, y = position.y, z = position.z;
        // Back Face
        verticies.push_back({x - hside, y - hside, z - hside}); // 0
        verticies.push_back({x + hside, y - hside, z - hside}); // 1
        verticies.push_back({x + hside, y + hside, z - hside}); // 2
        verticies.push_back({x - hside, y + hside, z - hside}); // 3
        // Front Face
        verticies.push_back({x - hside, y - hside, z + hside}); // 4
        verticies.push_back({x + hside, y - hside, z + hside}); // 5
        verticies.push_back({x + hside, y + hside, z + hside}); // 6
        verticies.push_back({x - hside, y + hside, z + hside}); // 7
    }

    void Render(){
        if(!is_solid) return;
        GenerateVerticies();

    }

    
};
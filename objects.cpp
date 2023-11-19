#include "objects.h"

#include <vector>

#include "core/engine.h"
#include "core/gpu/mesh.h"

using namespace PvZ;

Mesh *objects::CreateRectangle(const std::string &name,
                               const float width,
                               const float height,
                               const glm::vec3 color,
                               const bool fill) {
    const std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(width / 2, height / 2, 0), color),
        VertexFormat(glm::vec3(-width / 2, height / 2, 0), color),
        VertexFormat(glm::vec3(-width / 2, -height / 2, 0), color),
        VertexFormat(glm::vec3(width / 2, -height / 2, 0), color),
    };

    Mesh *rectangle = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2, 3};

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh *objects::CreateDefender(const std::string &name,
                              const float width,
                              const float height,
                              const glm::vec3 color) {
    const std::vector<VertexFormat> vertices =
    {
        // rhomb base
        VertexFormat(glm::vec3(width / 2, 0, 0), color),
        VertexFormat(glm::vec3(0, height / 2, 0), color),
        VertexFormat(glm::vec3(-width / 2, 0, 0), color),
        VertexFormat(glm::vec3(0, -height / 2, 0), color),

        // rectangle cannon
        VertexFormat(glm::vec3(height / 2, width / 4, 0), color),
        VertexFormat(glm::vec3(0, width / 4, 0), color),
        VertexFormat(glm::vec3(0, -width / 4, 0), color),
        VertexFormat(glm::vec3(height / 2, -width / 4, 0), color)
    };

    Mesh *defender = new Mesh(name);
    const std::vector<unsigned int> indices = {
        0, 1, 2,
        3, 0, 2,
        4, 5, 6,
        7, 4, 6
    };

    defender->InitFromData(vertices, indices);
    return defender;
}

Mesh *objects::CreateEnemy(const std::string &name,
                           const float outer_radius,
                           const float inner_radius,
                           const glm::vec3 outer_color,
                           const glm::vec3 inner_color) {
    float outer_ypos = outer_radius * sqrt(3) / 2;
    float inner_ypos = inner_radius * sqrt(3) / 2;

    const std::vector<VertexFormat> vertices =
    {
        // outer hex
        VertexFormat(glm::vec3(outer_radius, 0, 0), outer_color),
        VertexFormat(glm::vec3(outer_radius / 2, outer_ypos, 0), outer_color),
        VertexFormat(glm::vec3(-outer_radius / 2, outer_ypos, 0), outer_color),
        VertexFormat(glm::vec3(-outer_radius, 0, 0), outer_color),
        VertexFormat(glm::vec3(-outer_radius / 2, -outer_ypos, 0), outer_color),
        VertexFormat(glm::vec3(outer_radius / 2, -outer_ypos, 0), outer_color),

        // inner hex
        VertexFormat(glm::vec3(inner_radius, 0, 0), inner_color),
        VertexFormat(glm::vec3(inner_radius / 2, inner_ypos, 0), inner_color),
        VertexFormat(glm::vec3(-inner_radius / 2, inner_ypos, 0), inner_color),
        VertexFormat(glm::vec3(-inner_radius, 0, 0), inner_color),
        VertexFormat(glm::vec3(-inner_radius / 2, -inner_ypos, 0), inner_color),
        VertexFormat(glm::vec3(inner_radius / 2, -inner_ypos, 0), inner_color),
    };

    Mesh *defender = new Mesh(name);
    const std::vector<unsigned int> indices = {
        6, 7, 8,
        6, 8, 9,
        6, 9, 10,
        6, 10, 11,

        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
    };

    defender->InitFromData(vertices, indices);
    return defender;
}


//                B
//                *
//               * *
//           G *     * F
//  C *`*`*`*`*        *`*`*`*`*  A
//     *          *O         * 
//       *                 *
//       H *     .*.     *
//        *  .*`     `*.  *
//       * `             ` *
//       D                 E
Mesh *objects::CreateStar(const std::string &name,
                 const float outer_radius,
                 const glm::vec3 color) {
    float side_length = 2 * outer_radius * sin(2 * glm::pi<float>() / 10);
    float inner_radius = (5 + sqrt(5)) / 4 * outer_radius - outer_radius;
    float xA = (side_length * inner_radius / 2) * 2 / outer_radius;
    float yA = xA * cos(2 * glm::pi<float>() / 5);
    
    float xB = 0;
    float yB = outer_radius;

    float xC = -xA;
    float yC = yA;

    float xD = -side_length / 2;
    float yD = -inner_radius;
    
    float xE = side_length / 2;
    float yE = -inner_radius;

    float xF = (outer_radius - yA) * side_length / ( 2 * (inner_radius + outer_radius));
    float yF = yA;

    float xG = -xF;
    float yG = yA;

    float xH = xG - cos(2 * glm::pi<float>() / 5) * xF * 2;
    float yH = yG - sin(2 * glm::pi<float>() / 5) * xF * 2;
    


    const std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(xA, yA, 0), color),
        VertexFormat(glm::vec3(xB, yB, 0), color),
        VertexFormat(glm::vec3(xC, yC, 0), color),
        VertexFormat(glm::vec3(xD, yD, 0), color),
        VertexFormat(glm::vec3(xE, yE, 0), color),
        VertexFormat(glm::vec3(xF, yF, 0), color),
        VertexFormat(glm::vec3(xG, yG, 0), color),
        VertexFormat(glm::vec3(xH, yH, 0), color),
    };

    Mesh *star = new Mesh(name);
    const std::vector<unsigned int> indices = {
        0, 6, 3,
        4, 5, 2,
        1, 7, 4,
    };

    star->InitFromData(vertices, indices);
    return star;
}

Mesh * objects::CreateHearth(const std::string &name, float width, float height, glm::vec3 color) {
    const std::vector<VertexFormat> vertices =
   {
        VertexFormat(glm::vec3(0, height / 8 * 3, 0), color),

        VertexFormat(glm::vec3(-width / 8, height / 2, 0), color),
        VertexFormat(glm::vec3(-width / 8 * 3, height / 2, 0), color),
        VertexFormat(glm::vec3(-width / 2, height / 8 * 3, 0), color),
        VertexFormat(glm::vec3(-width / 2, 0, 0), color),

        VertexFormat(glm::vec3(0, -height / 2, 0), color),
        
        VertexFormat(glm::vec3(width / 2, 0, 0), color),
        VertexFormat(glm::vec3(width / 2, height / 8 * 3, 0), color),
        VertexFormat(glm::vec3(width / 8 * 3, height / 2, 0), color),
        VertexFormat(glm::vec3(width / 8, height / 2, 0), color),
    };

    Mesh *hearth = new Mesh(name);
    const std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 9
    };

    hearth->InitFromData(vertices, indices);
    return hearth;
}

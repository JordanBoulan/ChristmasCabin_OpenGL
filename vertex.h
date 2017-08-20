#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
   glm::vec4 coords;
   glm::vec2 texCoords;
};

struct VertexLit
{
   glm::vec4 coords;
   glm::vec2 texCoords;
   glm::vec3 normal;
};

struct VertexIce
{
   glm::vec4 coords;
};

#endif

#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

struct Material
{
   glm::vec4 ambRefl;
   glm::vec4 difRefl;
   glm::vec4 specRefl;
   glm::vec4 emitCols;
   float shininess;
};

static const Material floorMaterial =
{
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(0.0, 0.0, 0.0, 1.0),
	250.0
};

static const Material wallMaterial =
{
	glm::vec4(1.0, 0.8, 0.8, 1.0),
	glm::vec4(1.0, 0.8, 0.8, 1.0),
	glm::vec4(1.0, 0.8, 0.8, 1.0),
	glm::vec4(0.0, 0.0, 0.0, 1.0),
	50.0
};

static const Material treeMaterial =
{
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(0.0, 0.0, 0.0, 1.0),
	50.0
};




#endif

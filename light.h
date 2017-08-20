#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>


struct Light
{
   glm::vec4 ambCols;
   glm::vec4 difCols;
   glm::vec4 specCols;
   glm::vec4 coords;
};

static const Light light0 =
{
	glm::vec4(0.0, 0.0, 0.0, 1.0),
	glm::vec4(0.0, 1.0, 0.0, 1.0),
	glm::vec4(1.0, 1.0, 1.0, 1.0),
	glm::vec4(-10.0, 10.0, -20.0, 0.0)
};


static const glm::vec4 globAmb = glm::vec4(1.0, 1.0, 1.0, 1.0);

#endif

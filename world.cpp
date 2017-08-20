
#include "world.h"
#include "program.h"



using namespace glm;
using namespace std;



Vertex world::fieldVertices[4] =
{
	{vec4(100.0, 0.0, 100.0, 1.0), vec2(8.0, 0.0)},
	{vec4(100.0, 0.0, -100.0, 1.0), vec2(8.0, 8.0)},
	{vec4(-100.0, 0.0, 100.0, 1.0), vec2(0.0, 0.0)},
	{vec4(-100.0, 0.0, -100.0, 1.0), vec2(0.0, 8.0)}
};

Vertex world::skyVertices[16] =
{
	{vec4(100.0, 0.0, -70.0, 1.0), vec2(1.0, 0.0)}, //front sky
    {vec4(100.0, 120.0, -70.0, 1.0), vec2(1.0, 1.0)},
    {vec4(-100.0, 0.0, -70.0, 1.0), vec2(0.0, 0.0)},
    {vec4(-100.0, 120.0, -70.0, 1.0), vec2(0.0, 1.0)},
    {vec4(-100.0, 0.0, -70.0, 1.0), vec2(1.0, 0.0)}, //left sky
    {vec4(-100.0, 120.0, -70.0, 1.0), vec2(1.0, 1.0)},
    {vec4(-100.0, 0.0, 100.0, 1.0), vec2(0.0, 0.0)},
    {vec4(-100.0, 120.0, 100.0, 1.0), vec2(0.0, 1.0)},
    {vec4(100.0, 0.0, 100.0, 1.0), vec2(1.0, 0.0)}, //back sky
    {vec4(100.0, 120.0, 100.0, 1.0), vec2(1.0, 1.0)},
    {vec4(-100.0, 0.0, 100.0, 1.0), vec2(0.0, 0.0)},
    {vec4(-100.0, 120.0, 100.0, 1.0), vec2(0.0, 1.0)},
    {vec4(100.0, 0.0, 100.0, 1.0), vec2(1.0, 0.0)}, //right sky
    {vec4(100.0, 120.0, 100.0, 1.0), vec2(1.0, 1.0)},
    {vec4(100.0, 0.0, -70.0, 1.0), vec2(0.0, 0.0)},
    {vec4(100.0, 120.0, -70.0, 1.0), vec2(0.0, 1.0)}
};

Vertex world::skyTopVertices[4] =
{
    {vec4(100.0, 120.0, 100.0, 1.0), vec2(1.0, 0.9)},
    {vec4(-100.0, 120.0, 100.0, 1.0), vec2(1.0, 1.0)},
    {vec4(100.0, 120.0, -70.0, 1.0), vec2(0.9, 0.9)},
    {vec4(-100.0, 120.0, -70.0, 1.0), vec2(0.9, 1.0)}
};


void world::fillFieldVertices(unsigned int* mVao, unsigned int* mBuffer)
{

    glBindVertexArray(mVao[FIELD]);
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[FIELD_VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fieldVertices), fieldVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), (void*)(sizeof(fieldVertices[0].coords)));
    glEnableVertexAttribArray(1);

}

void world::fillSkyVertices(unsigned int* mVao, unsigned int* mBuffer)
{

    glBindVertexArray(mVao[SKY]);
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[SKY_VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), 0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), (void*)(sizeof(skyVertices[0].coords)));
    glEnableVertexAttribArray(3);
}

void world::fillSkyTopVertices(unsigned int* mVao, unsigned int* mBuffer)
{

    glBindVertexArray(mVao[SKY]);
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[SKY_VERTICES]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyTopVertices), skyTopVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(skyTopVertices[0]), 0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(skyTopVertices[0]), (void*)(sizeof(skyTopVertices[0].coords)));
    glEnableVertexAttribArray(3);

}

void world::drawField(unsigned int* mVao, unsigned int* mBuffer)
{

    glUniform1ui(objectLoc, FIELD);
    glBindVertexArray(mVao[FIELD]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}

void world::drawSky(unsigned int* mVao, unsigned int* mBuffer)
{

    world::fillSkyVertices(mVao, mBuffer);
    glUniform1ui(objectLoc, SKY);
    glBindVertexArray(mVao[SKY]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 16);

    world::fillSkyTopVertices(mVao, mBuffer);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}



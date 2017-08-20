#ifndef WORLD_H
#define WORLD_H
#include "vertex.h"

class world
{
    public:

    static Vertex fieldVertices[4];
    static Vertex skyVertices[16];
    static Vertex skyTopVertices[4];
    static void fillFieldVertices(unsigned int*, unsigned int*);
    static void fillSkyVertices(unsigned int*, unsigned int*);
    static void fillSkyTopVertices(unsigned int*, unsigned int*);
    static void drawField(unsigned int*, unsigned int*);
    static void drawSky(unsigned int*, unsigned int*);

};

#endif // WORLD_H

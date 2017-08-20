#ifndef HOUSE_H
#define HOUSE_H
#include "vertex.h"

class house
{
    public:

        static void fillLeftRoofVertices(unsigned int*, unsigned int*);
        static void fillRightRoofVertices(unsigned int*, unsigned int*);
        static void fillFrontRoofVertices(unsigned int*, unsigned int*);
        static void fillBackRoofVertices(unsigned int*, unsigned int*);
        static void drawRoof(unsigned int*, unsigned int*);
        static Vertex frontRoofVertices[3];
        static Vertex backRoofVertices[3];
        static Vertex leftRoofVertices[4];
        static Vertex rightRoofVertices[4];

        static VertexLit frontWallVertices[10];
        static VertexLit backWallVertices[4];
        static VertexLit leftWallVertices[4];
        static VertexLit rightWallVertices[4];
        static void fillLeftWallVertices(unsigned int*, unsigned int*);
        static void fillRightWallVertices(unsigned int*, unsigned int*);
        static void fillFrontWallVertices(unsigned int*, unsigned int*);
        static void fillBackWallVertices(unsigned int*, unsigned int*);
        static void drawWalls(unsigned int*, unsigned int*);

        static VertexLit floorVertices[4];
        static void fillFloorVertices(unsigned int*, unsigned int*);
        static void drawFloor(unsigned int*, unsigned int*);

        static Vertex doorVertices[4];
        static Vertex openDoorVertices[4];
        static void fillDoorVertices(unsigned int*, unsigned int*, bool);
        static void drawDoor(unsigned int*, unsigned int*, bool);

        static VertexLit treeVertices[3];
        static void fillTreeVertices(unsigned int*, unsigned int*);
        static void drawTree(unsigned int*, unsigned int*);

};

#endif // HOUSE_H

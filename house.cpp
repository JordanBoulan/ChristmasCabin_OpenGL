
#include "house.h"
#include "program.h"



using namespace glm;
using namespace std;



//START ROOF

Vertex house::frontRoofVertices[3] =
{

    {vec4(-25.0, 20.0, -10.0, 1.0), vec2(0.0, 0.0)}, //v0
	{vec4(0.0, 25.0, -10.0, 1.0), vec2(0.4, 1.0)}, //v2
	{vec4(25.0, 20.0, -10.0, 1.0), vec2(0.4, 0.0)} //v1

};

Vertex house::backRoofVertices[3] =
{

    {vec4(25.0, 20.0, -50.0, 1.0), vec2(0.4, 0.0)}, // v3
    {vec4(0, 25.0, -50.0, 1.0), vec2(0.4, 0.4)}, // v4
    {vec4(-25.0, 20.0, -50.0, 1.0), vec2(0.0, 0.0)} // v5

};


Vertex house::leftRoofVertices[4] =
{

    {vec4(-25.0, 20.0, -52.0, 1.0), vec2(0.0, 0.0)}, // v5
    {vec4(0, 25.0, -52.0, 1.0), vec2(0.0, 2.0)}, // v4
    {vec4(-25.0, 20.0, -8.0, 1.0), vec2(2.0, 0.0 )}, // v0
    {vec4(0.0, 25.0, -8.0, 1.0), vec2(2.0, 2.0)} // v2

};

Vertex house::rightRoofVertices[4] =
{

    {vec4(25.0, 20.0, -8.0, 1.0), vec2(0.0, 0.0)}, // v1
    {vec4(0.0, 25.0, -8.0, 1.0), vec2(0.0, 2.0)}, // v2
    {vec4(25.0, 20.0, -52.0, 1.0), vec2(2.0, 0.0)}, // v3
    {vec4(0, 25.0, -52.0, 1.0), vec2(2.0, 2.0)} // v4

};


void house::fillLeftRoofVertices(unsigned int* mVao, unsigned int* mBuffer)
{

   glBindVertexArray(mVao[ROOF]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[ROOF_VERTICIES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(leftRoofVertices), leftRoofVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(leftRoofVertices[0]), 0);
   glEnableVertexAttribArray(8);
   glVertexAttribPointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(leftRoofVertices[0]), (void*)(sizeof(leftRoofVertices[0].coords)));
   glEnableVertexAttribArray(9);

}

void house::fillRightRoofVertices(unsigned int* mVao, unsigned int* mBuffer)
{

   glBindVertexArray(mVao[ROOF]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[ROOF_VERTICIES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(rightRoofVertices), rightRoofVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(rightRoofVertices[0]), 0);
   glEnableVertexAttribArray(8);
   glVertexAttribPointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(rightRoofVertices[0]), (void*)(sizeof(rightRoofVertices[0].coords)));
   glEnableVertexAttribArray(9);

}


void house::fillFrontRoofVertices(unsigned int* mVao, unsigned int* mBuffer)
{

   glBindVertexArray(mVao[ROOF]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[ROOF_VERTICIES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(frontRoofVertices), frontRoofVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(frontRoofVertices[0]), 0);
   glEnableVertexAttribArray(8);
   glVertexAttribPointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(frontRoofVertices[0]), (void*)(sizeof(frontRoofVertices[0].coords)));
   glEnableVertexAttribArray(9);

}


void house::fillBackRoofVertices(unsigned int* mVao, unsigned int* mBuffer)
{

   glBindVertexArray(mVao[ROOF]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[ROOF_VERTICIES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(backRoofVertices), backRoofVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(backRoofVertices[0]), 0);
   glEnableVertexAttribArray(8);
   glVertexAttribPointer(9, 2, GL_FLOAT, GL_FALSE, sizeof(backRoofVertices[0]), (void*)(sizeof(backRoofVertices[0].coords)));
   glEnableVertexAttribArray(9);

}

void house::drawRoof(unsigned int* mVao, unsigned int* mBuffer)
{

    house::fillFrontRoofVertices(mVao, mBuffer);
    glUniform1ui(objectLoc, ROOF);
    glBindVertexArray(mVao[ROOF]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    house::fillBackRoofVertices(mVao, mBuffer);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    house::fillLeftRoofVertices(mVao, mBuffer);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    house::fillRightRoofVertices(mVao, mBuffer);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}


//END ROOF


//START WALLS
VertexLit house::leftWallVertices[4] =
{
	{vec4(-20, 0.0, -10.0, 1.0), vec2(1.0, 0.0), vec3{-1.0, 0.0, 0.0}},
	{vec4(-20, 20.0, -10.0, 1.0), vec2(1.0, 1.0), vec3{-1.0, 0.0, 0.0}},
	{vec4(-20, 0.0, -50.0, 1.0), vec2(0.0, 0.0), vec3{-1.0, 0.0, 0.0}},
	{vec4(-20, 20.0, -50.0, 1.0), vec2(0.0, 1.0), vec3{-1.0, 0.0, 0.0}}
};

VertexLit house::backWallVertices[4] =
{
	{vec4(-20, 0.0, -50.0, 1.0), vec2(1.0, 0.0), vec3{0.0, 0.0, -1.0}},
	{vec4(-20, 20.0, -50.0, 1.0), vec2(1.0, 1.0), vec3{0.0, 0.0, -1.0}},
	{vec4(20, 0.0, -50.0, 1.0), vec2(0.0, 0.0), vec3{0.0, 0.0, -1.0}},
	{vec4(20, 20.0, -50.0, 1.0), vec2(0.0, 1.0), vec3{0.0, 0.0, -1.0}}
};

VertexLit house::rightWallVertices[4] =
{
	{vec4(20, 0.0, -50.0, 1.0), vec2(1.0, 0.0), vec3{1.0, 0.0, 0.0}},
	{vec4(20, 20.0, -50.0, 1.0), vec2(1.0, 1.0), vec3{1.0, 0.0, 0.0}},
	{vec4(20, 0.0, -10.0, 1.0), vec2(0.0, 0.0), vec3{1.0, 0.0, 0.0}},
	{vec4(20, 20.0, -10.0, 1.0), vec2(0.0, 1.0), vec3{1.0, 0.0, 0.0}}
};

VertexLit house::frontWallVertices[10] =
{
	{vec4(20.0, 0.0, -10.0, 1.0), vec2(1.0, 0.0), vec3{0.0, 0.0, 1.0}},  //v0
	{vec4(20.0, 20.0, -10.0, 1.0), vec2(1.0, 1.0), vec3{0.0, 0.0, 1.0}}, //v1
	{vec4(5.0, 0.0, -10.0, 1.0), vec2(0.66, 0.0), vec3{0.0, 0.0, 1.0}}, //v2
	{vec4(5.0, 20.0, -10.0, 1.0), vec2(0.66, 1.0), vec3{0.0, 0.0, 1.0}}, //v3
	{vec4(5.0, 15.0, -10.0, 1.0), vec2(0.66, 0.75), vec3{0.0, 0.0, 1.0}}, //v4
	{vec4(-5.0, 20.0, -10.0, 1.0), vec2(0.33, 1.0), vec3{0.0, 0.0, 1.0}}, //v5
	{vec4(-5.0, 15.0, -10.0, 1.0), vec2(0.33, 0.75), vec3{0.0, 0.0, 1.0}}, //v6
	{vec4(-20.0, 20.0, -10.0, 1.0), vec2(0.0, 1.0), vec3{0.0, 0.0, 1.0}}, //v7
	{vec4(-5.0, 0.0, -10.0, 1.0), vec2(0.33, 0.0), vec3{0.0, 0.0, 1.0}}, //v8
	{vec4(-20.0, 0.0, -10.0, 1.0), vec2(0.0, 0.0), vec3{0.0, 0.0, 1.0}}, //v9
};

void house::fillLeftWallVertices(unsigned int* mVao, unsigned int* mBuffer)
{

    // left wall vao
   glBindVertexArray(mVao[WALL]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[WALL_VERTICIES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(leftWallVertices), leftWallVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(leftWallVertices[0]), 0);
   glEnableVertexAttribArray(4);
   glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(leftWallVertices[0]), (void*)(sizeof(leftWallVertices[0].coords)));
   glEnableVertexAttribArray(5);
   glVertexAttribPointer(13, 3, GL_FLOAT, GL_FALSE, sizeof(leftWallVertices[0]), (void*)(sizeof(leftWallVertices[0].coords) + sizeof(leftWallVertices[0].texCoords)));
   glEnableVertexAttribArray(13);

}

void house::fillBackWallVertices(unsigned int* mVao, unsigned int* mBuffer)
{

    // left wall vao
   glBindVertexArray(mVao[WALL]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[WALL_VERTICIES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(backWallVertices), backWallVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(backWallVertices[0]), 0);
   glEnableVertexAttribArray(4);
   glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(backWallVertices[0]), (void*)(sizeof(backWallVertices[0].coords)));
   glEnableVertexAttribArray(5);
   glVertexAttribPointer(13, 3, GL_FLOAT, GL_FALSE, sizeof(backWallVertices[0]), (void*)(sizeof(backWallVertices[0].coords) + sizeof(backWallVertices[0].texCoords)));
   glEnableVertexAttribArray(13);

}

void house::fillRightWallVertices(unsigned int* mVao, unsigned int* mBuffer)
{

    // left wall vao
   glBindVertexArray(mVao[WALL]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[WALL_VERTICIES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(rightWallVertices), rightWallVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(rightWallVertices[0]), 0);
   glEnableVertexAttribArray(4);
   glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(rightWallVertices[0]), (void*)(sizeof(rightWallVertices[0].coords)));
   glEnableVertexAttribArray(5);
   glVertexAttribPointer(13, 3, GL_FLOAT, GL_FALSE, sizeof(rightWallVertices[0]), (void*)(sizeof(rightWallVertices[0].coords) + sizeof(rightWallVertices[0].texCoords)));
   glEnableVertexAttribArray(13);

}


void house::fillFrontWallVertices(unsigned int* mVao, unsigned int* mBuffer)
{

    // left wall vao
   glBindVertexArray(mVao[WALL]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[WALL_VERTICIES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(frontWallVertices), frontWallVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(frontWallVertices[0]), 0);
   glEnableVertexAttribArray(4);
   glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(frontWallVertices[0]), (void*)(sizeof(frontWallVertices[0].coords)));
   glEnableVertexAttribArray(5);
   glVertexAttribPointer(13, 3, GL_FLOAT, GL_FALSE, sizeof(frontWallVertices[0]), (void*)(sizeof(frontWallVertices[0].coords) + sizeof(frontWallVertices[0].texCoords)));
   glEnableVertexAttribArray(13);

}

void house::drawWalls(unsigned int* mVao, unsigned int* mBuffer)
{

   // Draw left wall.
   house::fillLeftWallVertices(mVao, mBuffer);
   glUniform1ui(objectLoc, WALL);
   glBindVertexArray(mVao[WALL]);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Draw back wall.
   house::fillBackWallVertices(mVao, mBuffer);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Draw right wall.
   house::fillRightWallVertices(mVao, mBuffer);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Draw front wall.
   house::fillFrontWallVertices(mVao, mBuffer);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);

}

//END WALLS

//START FLOORS
VertexLit house::floorVertices[4] =
{
	{vec4(20.0, 0.2, -10.0, 1.0), vec2(8.0, 0.0), vec3{0.0, 1.0, 0.0}},
	{vec4(20.0, 0.2, -50.0, 1.0), vec2(8.0, 8.0), vec3{0.0, 1.0, 0.0}},
	{vec4(-20.0, 0.2, -10.0, 1.0), vec2(0.0, 0.0), vec3{0.0, 1.0, 0.0}},
	{vec4(-20.0, 0.2, -50.0, 1.0), vec2(0.0, 8.0), vec3{0.0, 1.0, 0.0}}
};

void house::fillFloorVertices(unsigned int* mVao, unsigned int* mBuffer)
{

   glBindVertexArray(mVao[FLOOR]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[FLOOR_VERTICES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(floorVertices[0]), 0);
   glEnableVertexAttribArray(6);
   glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(floorVertices[0]), (void*)(sizeof(floorVertices[0].coords)));
   glEnableVertexAttribArray(7);
   glVertexAttribPointer(12, 3, GL_FLOAT, GL_FALSE, sizeof(floorVertices[0]), (void*)(sizeof(floorVertices[0].coords) + sizeof(floorVertices[0].texCoords)));
   glEnableVertexAttribArray(12);

}

void house::drawFloor(unsigned int* mVao, unsigned int* mBuffer)
{

   house::fillFloorVertices(mVao, mBuffer);
   glUniform1ui(objectLoc, FLOOR);
   glBindVertexArray(mVao[FLOOR]);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


}
//END FLOORS

//START DOOR
Vertex house::doorVertices[4] =
{
    {vec4(-5.0, 15.0, -10.0, 1.0), vec2(0.52, 1.0)},
	{vec4(-5.0, 0.0, -10.0, 1.0), vec2(0.0, 0.0)},
	{vec4(5.0, 15.0, -10.0, 1.0), vec2(1.52, 1.0)},
	{vec4(5.0, 0.0, -10.0, 1.0), vec2(1.0, 0.0)}
};

Vertex house::openDoorVertices[4] =
{
    {vec4(-5.0, 15.0, -10.0, 1.0), vec2(0.52, 1.0)},
	{vec4(-5.0, 0.0, -10.0, 1.0), vec2(0.0, 0.0)},
	{vec4(-5.0, 15.0, -20.0, 1.0), vec2(1.52, 1.0)},
	{vec4(-5.0, 0.0, -20.0, 1.0), vec2(1.0, 0.0)}
};

void house::fillDoorVertices(unsigned int* mVao, unsigned int* mBuffer, bool isDoorOpen)
{
   if(isDoorOpen == false)
   {
       glBindVertexArray(mVao[DOOR]);
       glBindBuffer(GL_ARRAY_BUFFER, mBuffer[DOOR_VERTICES]);
       glBufferData(GL_ARRAY_BUFFER, sizeof(doorVertices), doorVertices, GL_STATIC_DRAW);
       glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(doorVertices[0]), 0);
       glEnableVertexAttribArray(10);
       glVertexAttribPointer(11, 2, GL_FLOAT, GL_FALSE, sizeof(doorVertices[0]), (void*)(sizeof(doorVertices[0].coords)));
       glEnableVertexAttribArray(11);
   }
   if(isDoorOpen == true)
   {
       glBindVertexArray(mVao[DOOR]);
       glBindBuffer(GL_ARRAY_BUFFER, mBuffer[DOOR_VERTICES]);
       glBufferData(GL_ARRAY_BUFFER, sizeof(openDoorVertices), openDoorVertices, GL_STATIC_DRAW);
       glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(openDoorVertices[0]), 0);
       glEnableVertexAttribArray(10);
       glVertexAttribPointer(11, 2, GL_FLOAT, GL_FALSE, sizeof(openDoorVertices[0]), (void*)(sizeof(openDoorVertices[0].coords)));
       glEnableVertexAttribArray(11);
   }

}

void house::drawDoor(unsigned int* mVao, unsigned int* mBuffer, bool isDoorOpen)
{
   house::fillDoorVertices(mVao, mBuffer, isDoorOpen);
   glUniform1ui(objectLoc, DOOR);
   glBindVertexArray(mVao[DOOR]);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}
//END DOOR

VertexLit house::treeVertices[3] =
{
    {vec4(0.0, 15.0, -48.0, 1.0), vec2(0.5, 1.0), vec3(0.0, 0.0, 1.0)},
	{vec4(-5.0, 0.0, -48.0, 1.0), vec2(0.0, 0.0), vec3(0.0, 0.0, 1.0)},
	{vec4(5.0, 0.0, -48.0, 1.0), vec2(1.0, 0.0), vec3(0.0, 0.0, 1.0)}
};

void house::fillTreeVertices(unsigned int* mVao, unsigned int* mBuffer)
{

    // left wall vao
   glBindVertexArray(mVao[TREE]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[TREE_VERTICES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(treeVertices), treeVertices, GL_STATIC_DRAW);
   glVertexAttribPointer(14, 4, GL_FLOAT, GL_FALSE, sizeof(treeVertices[0]), 0);
   glEnableVertexAttribArray(14);
   glVertexAttribPointer(15, 2, GL_FLOAT, GL_FALSE, sizeof(treeVertices[0]), (void*)(sizeof(treeVertices[0].coords)));
   glEnableVertexAttribArray(15);
   glVertexAttribPointer(13, 3, GL_FLOAT, GL_FALSE, sizeof(treeVertices[0]), (void*)(sizeof(treeVertices[0].coords) + sizeof(treeVertices[0].texCoords)));
   glEnableVertexAttribArray(13);
}

void house::drawTree(unsigned int* mVao, unsigned int* mBuffer)
{
   house::fillTreeVertices(mVao, mBuffer);
   glUniform1ui(objectLoc, TREE);
   glBindVertexArray(mVao[TREE]);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}

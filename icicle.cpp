#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif

#include "icicle.h"
#include "program.h"

using namespace std;

// Fill the vertex array with co-ordinates of the sample points.
void fillIceVertexArray(VertexIce iceVertices[(ICE_LONGS + 1) * (ICE_LATS + 1)])
{
   int i, j, k;

   k = 0;
   for (j = 0; j <= ICE_LATS; j++)
      for (i = 0; i <= ICE_LONGS; i++)
      {
         iceVertices[k].coords.x = changeRadius(i,j) * cos( (-1 + 2 * (float)i / ICE_LONGS) * PI );
         iceVertices[k].coords.y = changeRadius(i,j) * sin( (-1 + 2 * (float)i / ICE_LONGS) * PI );
         iceVertices[k].coords.z = -1 + 2 * (float)j / ICE_LATS;
		 iceVertices[k].coords.w = 1.0;

		 k++;
	  }
}

void fillIceIndices(unsigned int iceIndices[ICE_LATS][2 * (ICE_LONGS + 1)])
{
   int i, j;
   for(j = 0; j < ICE_LATS; j++)
   {
      for (i = 0; i <= ICE_LONGS; i++)
      {
	     iceIndices[j][2 * i]     = (j + 1) * (ICE_LONGS + 1) + i;
	     iceIndices[j][2 * i + 1] =    j    * (ICE_LONGS + 1) + i;
      }
   }
}

// Fill the array cylCounts.
void fillIceCounts(int iceCounts[ICE_LATS])
{
   int j;
   for(j = 0; j < ICE_LATS; j++) iceCounts[j] = 2 * (ICE_LONGS + 1);
}

// Fill the array cylOffsets.
void fillIceOffsets(void* iceOffsets[ICE_LATS])
{
   int j;
   for(j = 0; j < ICE_LATS; j++) iceOffsets[j] = (GLvoid*)(2 * (ICE_LONGS + 1) * j * sizeof(unsigned int));
}

void fillIcicle(VertexIce iceVertices[(ICE_LONGS + 1) * (ICE_LATS + 1)],
	         unsigned int iceIndices[ICE_LATS][2 * (ICE_LONGS+1)],
			 int iceCounts[ICE_LATS],
			 void* iceOffsets[ICE_LATS])
{
   fillIceVertexArray(iceVertices);
   fillIceIndices(iceIndices);
   fillIceCounts(iceCounts);
   fillIceOffsets(iceOffsets);
}

void loadIcicleVertices(unsigned int* mVao, unsigned int* mBuffer)
{

   glBindVertexArray(mVao[ICICLE]);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer[ICE_VERTICES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(iceVertices), iceVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer[ICE_INDICES]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iceIndices), iceIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(iceVertices[0]), 0);
   glEnableVertexAttribArray(4);


}

void drawIcicle(unsigned int* mVao, unsigned int* mBuffer)
{
   loadIcicleVertices(mVao, mBuffer);
   glUniform1ui(objectLoc, ICICLE);
   glBindVertexArray(mVao[ICICLE]);
   glMultiDrawElements(GL_TRIANGLE_STRIP, iceCounts, GL_UNSIGNED_INT, (const void **)iceOffsets, ICE_LATS);

}

void prepareIcicle()
{
    fillIcicle(iceVertices, iceIndices, iceCounts, iceOffsets);
}

float changeRadius(float i, float j)
{
    float radius = 0.3;
    float newRadius = 0.0;

    if (j == 15)
    {
        newRadius = 0.3;
        return newRadius;
    }
    else
      newRadius = (radius * 1.3 * (float)j/ICE_LATS);
      return newRadius;
}

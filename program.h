#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GLUT/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "light.h"
#include "material.h"
#include "getbmp.h"

using namespace glm;

enum object {FIELD, SKY, WALL, FLOOR, ROOF, DOOR, TREE, ICICLE}; // VAO ids.
enum buffer {FIELD_VERTICES, SKY_VERTICES, WALL_VERTICIES, FLOOR_VERTICES, ROOF_VERTICIES, DOOR_VERTICES, TREE_VERTICES, ICE_VERTICES, ICE_INDICES}; // VBO ids.

static unsigned int
   programId,
   vertexShaderId,
   fragmentShaderId,
   modelViewMatrixLoc,
   normalMatrixLoc,
   projectionMatrixLoc,
   grassTexLoc,
   skyTexLoc,
   brickTexLoc,
   floorTexLoc,
   doorTexLoc,
   roofTexLoc,
   treeTexLoc,
   objectLoc;

static void loadTextures(BitMapFile** image, unsigned int* texture)
{

   // Bind grass image.
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
	            GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   grassTexLoc = glGetUniformLocation(programId, "grassTex");
   glUniform1i(grassTexLoc, 0);

    // Bind sky image.
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D, texture[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->sizeX, image[1]->sizeY, 0,
	            GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   skyTexLoc = glGetUniformLocation(programId, "skyTex");
   glUniform1i(skyTexLoc, 1);

   // Bind brick.
   glActiveTexture(GL_TEXTURE2);
   glBindTexture(GL_TEXTURE_2D, texture[2]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->sizeX, image[2]->sizeY, 0,
	            GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   brickTexLoc = glGetUniformLocation(programId, "brickTex");
   glUniform1i(brickTexLoc, 2);

   // Bind floor image.
   glActiveTexture(GL_TEXTURE3);
   glBindTexture(GL_TEXTURE_2D, texture[3]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[3]->sizeX, image[3]->sizeY, 0,
	            GL_RGBA, GL_UNSIGNED_BYTE, image[3]->data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   floorTexLoc = glGetUniformLocation(programId, "floorTex");
   glUniform1i(floorTexLoc, 3);

   // Bind door image.
   glActiveTexture(GL_TEXTURE4);
   glBindTexture(GL_TEXTURE_2D, texture[4]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->sizeX, image[4]->sizeY, 0,
	            GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   doorTexLoc = glGetUniformLocation(programId, "doorTex");
   glUniform1i(doorTexLoc, 4);

   // Bind roof image.
   glActiveTexture(GL_TEXTURE5);
   glBindTexture(GL_TEXTURE_2D, texture[5]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[5]->sizeX, image[5]->sizeY, 0,
	            GL_RGBA, GL_UNSIGNED_BYTE, image[5]->data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   roofTexLoc = glGetUniformLocation(programId, "roofTex");
   glUniform1i(roofTexLoc, 5);

   // Bind tree image.
   glActiveTexture(GL_TEXTURE6);
   glBindTexture(GL_TEXTURE_2D, texture[6]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[6]->sizeX, image[6]->sizeY, 0,
	            GL_RGBA, GL_UNSIGNED_BYTE, image[6]->data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glGenerateMipmap(GL_TEXTURE_2D);
   treeTexLoc = glGetUniformLocation(programId, "treeTex");
   glUniform1i(treeTexLoc, 6);

}

static void loadNormals()
{

   glUniform4fv(glGetUniformLocation(programId, "light0.ambCols"), 1, &light0.ambCols[0]);
   glUniform4fv(glGetUniformLocation(programId, "light0.difCols"), 1, &light0.difCols[0]);
   glUniform4fv(glGetUniformLocation(programId, "light0.specCols"), 1, &light0.specCols[0]);
   glUniform4fv(glGetUniformLocation(programId, "light0.coords"), 1, &light0.coords[0]);

   // Obtain global ambient uniform location and set value.
   glUniform4fv(glGetUniformLocation(programId, "globAmb"), 1, &globAmb[0]);

   glUniform4fv(glGetUniformLocation(programId, "woodfloor.ambRefl"), 1, &floorMaterial.ambRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "woodfloor.difRefl"), 1, &floorMaterial.difRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "woodfloor.specRefl"), 1, &floorMaterial.specRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "woodfloor.emitCols"), 1, &floorMaterial.emitCols[0]);
   glUniform1f(glGetUniformLocation(programId, "woodfloor.shininess"), floorMaterial.shininess);

   glUniform4fv(glGetUniformLocation(programId, "wall.ambRefl"), 1, &wallMaterial.ambRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "wall.difRefl"), 1, &wallMaterial.difRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "wall.specRefl"), 1, &wallMaterial.specRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "wall.emitCols"), 1, &wallMaterial.emitCols[0]);
   glUniform1f(glGetUniformLocation(programId, "wall.shininess"), wallMaterial.shininess);

   glUniform4fv(glGetUniformLocation(programId, "tree.ambRefl"), 1, &treeMaterial.ambRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "tree.difRefl"), 1, &treeMaterial.difRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "tree.specRefl"), 1, &treeMaterial.specRefl[0]);
   glUniform4fv(glGetUniformLocation(programId, "tree.emitCols"), 1, &treeMaterial.emitCols[0]);
   glUniform1f(glGetUniformLocation(programId, "tree.shininess"), treeMaterial.shininess);

}











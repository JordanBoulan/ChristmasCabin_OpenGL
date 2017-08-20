/*
Author: Jordan Boulanger - 2017

Description: Drawing a cabin in the snow with icicles on the roof.
             There is a tree and a light inside the cabin. There is a sky box
             to simulate the sky.
Controls:
LEFT Arrow: look left
RIGHT Arrow: look right
UP Arrow: move forward
DOWN Arrow: move back
Spacebar: open door and play music (must be close to the door)

Texture Credits:
http://www.textures.com/category/landscapes/26538
http://www.cssauthor.com/best-collection-free-textures/#Wall
http://www.texturemax.com/
*/

#include <cmath>
#include <iostream>
#include <fstream>

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

#include "mmsystem.h"
#pragma comment( lib, "winmm.lib" )
#include "shader.h"
#include "getbmp.h"
#include "vertex.h"
#include "house.h"
#include "world.h"
#include "icicle.h"
#include "program.h"


using namespace std;
using namespace glm;

static mat4 modelViewMatrix = mat4(1.0);
static mat4 projectionMatrix = mat4(1.0);
static mat3 normalMatrix = mat3(1.0);

static unsigned int buffer[9], vao[8], texture[7];

static BitMapFile *image[7]; // Local storage for bmp image data.

static bool isDoorOpen = false;
static float xPosition = 0;
static float zPosition = 0;
static float lookingX = 0;
static float lookingZ = -1.0;
static float myAngle = 0;
static float icicleAngle = 17.3;

// Initialization routine.
void setup(void)
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
   glEnable(GL_DEPTH_TEST);

   // Create shader program executable.
   vertexShaderId = setShader("vertex", "vertexShader.glsl");
   fragmentShaderId = setShader("fragment", "fragmentShader.glsl");
   programId = glCreateProgram();
   glAttachShader(programId, vertexShaderId);
   glAttachShader(programId, fragmentShaderId);
   glLinkProgram(programId);
   glUseProgram(programId);

   // Create VAOs and VBOs...
   glGenVertexArrays(8, vao);

   glGenBuffers(9, buffer);

   // Obtain projection matrix uniform location and set value.
   projectionMatrixLoc = glGetUniformLocation(programId,"projectionMatrix");
   projectionMatrix = frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
   //projectionMatrix = frustum(-1, 1, -1, 1, 1, 10);
   glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, value_ptr(projectionMatrix));

   // Obtain modelview matrix uniform and object uniform locations.
   modelViewMatrixLoc = glGetUniformLocation(programId,"modelViewMatrix");
   objectLoc = glGetUniformLocation(programId, "object");

   // Load the images.
   image[0] = getbmp("snow.bmp");
   image[1] = getbmp("sky.bmp");
   image[2] = getbmp("brick.bmp");
   image[3] = getbmp("wood.bmp");
   image[4] = getbmp("door.bmp");
   image[5] = getbmp("roof.bmp");
   image[6] = getbmp("tree.bmp");
   // Create texture ids.
   glGenTextures(7, texture);

   loadTextures(image, texture);

   world::fillFieldVertices(vao, buffer);

   normalMatrixLoc = glGetUniformLocation(programId,"normalMatrix");

   loadNormals();
   prepareIcicle();

}

void drawRoofIcicles()
{

   mat4 oldModelView = modelViewMatrix;

   modelViewMatrix = translate(modelViewMatrix, vec3(0.0, 23.0, -9.0));
   modelViewMatrix = scale(modelViewMatrix, vec3(2.0, 2.0, 2.0));
   modelViewMatrix = rotate(modelViewMatrix, icicleAngle, vec3(1.0, 0.0, 0.0));
   glUniformMatrix4fv(modelViewMatrixLoc, 1, GL_FALSE, value_ptr(modelViewMatrix));
   drawIcicle(vao, buffer);

   modelViewMatrix = oldModelView;

   modelViewMatrix = translate(modelViewMatrix, vec3(7.0, 21.5, -9.0));
   modelViewMatrix = scale(modelViewMatrix, vec3(2.0, 2.0, 2.0));
   modelViewMatrix = rotate(modelViewMatrix, icicleAngle, vec3(1.0, 0.0, 0.0));
   glUniformMatrix4fv(modelViewMatrixLoc, 1, GL_FALSE, value_ptr(modelViewMatrix));
   drawIcicle(vao, buffer);

   modelViewMatrix = oldModelView;

   modelViewMatrix = translate(modelViewMatrix, vec3(13.0, 20.5, -9.0));
   modelViewMatrix = scale(modelViewMatrix, vec3(1.5, 1.5, 1.5));
   modelViewMatrix = rotate(modelViewMatrix, icicleAngle, vec3(1.0, 0.0, 0.0));
   glUniformMatrix4fv(modelViewMatrixLoc, 1, GL_FALSE, value_ptr(modelViewMatrix));
   drawIcicle(vao, buffer);

   modelViewMatrix = oldModelView;

   modelViewMatrix = translate(modelViewMatrix, vec3(-7.0, 23.0, -9.0));
   modelViewMatrix = rotate(modelViewMatrix, icicleAngle, vec3(1.0, 0.0, 0.0));
   glUniformMatrix4fv(modelViewMatrixLoc, 1, GL_FALSE, value_ptr(modelViewMatrix));
   drawIcicle(vao, buffer);

   modelViewMatrix = oldModelView;

   modelViewMatrix = translate(modelViewMatrix, vec3(-13.0, 20.5, -9.0));
   modelViewMatrix = scale(modelViewMatrix, vec3(1.5, 1.5, 1.5));
   modelViewMatrix = rotate(modelViewMatrix, icicleAngle, vec3(1.0, 0.0, 0.0));
   glUniformMatrix4fv(modelViewMatrixLoc, 1, GL_FALSE, value_ptr(modelViewMatrix));
   drawIcicle(vao, buffer);

}

// Drawing routine.
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Calculate and update modelview matrix.
   modelViewMatrix = mat4(1.0);


   modelViewMatrix = lookAt(vec3(xPosition, 10.0, zPosition), vec3(lookingX + xPosition, 10.0, lookingZ + zPosition), vec3(0.0, 1.0, 0.0));

   glUniformMatrix4fv(modelViewMatrixLoc, 1, GL_FALSE, value_ptr(modelViewMatrix));

   normalMatrix = transpose(inverse(mat3(modelViewMatrix)));
   glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, value_ptr(normalMatrix));

   world::drawField(vao, buffer);
   world::drawSky(vao, buffer);
   house::drawFloor(vao, buffer);
   house::drawWalls(vao, buffer);
   house::drawRoof(vao, buffer);
   house::drawDoor(vao, buffer, isDoorOpen);
   house::drawTree(vao, buffer);
   drawRoofIcicles();

   glutSwapBuffers();
}



// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
//source for how to play sound:
//http://ntcoder.com/bab/2007/09/13/using-sndplaysound-to-play-a-wave-file/
//source for .wav file:
//http://www.thewavsite.com/christmas.htm

   switch(key)
   {
      case 27:
         exit(0);
         break;
      case ' ':
         if(isDoorOpen == false && (xPosition >= -25.0 && xPosition <= 25.0) && zPosition <= 0)
               {
                   isDoorOpen = true; //open door
                   sndPlaySound("beatles.wav", SND_ASYNC|SND_LOOP);
               }
          else if ((xPosition >= -25.0 && xPosition <= 25.0) && (zPosition <= 0 && zPosition >= -20))
               {
                   isDoorOpen = false; //close door
                   sndPlaySound(NULL, SND_ASYNC);
               }
               glutPostRedisplay();
               break;
      case 'b':
          cout << "z: " << zPosition << endl;
          cout << "x: " << xPosition << endl;
      default:
         break;
   }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{

//source for help with camera movement:
//http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/

    float adjustAmount = 0.5;
    switch(key){
        case GLUT_KEY_LEFT :
            myAngle -= 0.05;
            lookingX = sin(myAngle);
            lookingZ = -cos(myAngle);
			break;
		case GLUT_KEY_RIGHT :
            myAngle += 0.05;
            lookingX = sin(myAngle);
            lookingZ = -cos(myAngle);
			break;
		case GLUT_KEY_UP :
            xPosition += lookingX * adjustAmount;
            zPosition += lookingZ * adjustAmount;
			break;
		case GLUT_KEY_DOWN :
            xPosition -= lookingX * adjustAmount;
            zPosition -= lookingZ * adjustAmount;
			break;
    }
   glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "LEFT Arrow: look left" << endl;
   cout << "RIGHT Arrow: look right" << endl;
   cout << "UP Arrow: move forward" << endl;
   cout << "DOWN Arrow: move back" << endl;
   cout << "Spacebar: open door and play music (must be close to the door)" << endl;
}

// Main routine.
int main(int argc, char **argv)
{
   printInteraction();
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_CORE_PROFILE);
   glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Christmas Cabin");
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);

   glewExperimental = GL_TRUE;
   glewInit();

   setup();

   glutMainLoop();
}


#version 430 core

//These locations don't need to be hard-coded as there is a finate number of buffer locations, but for simplicity. 
layout(location=0) in vec4 fieldCoords;
layout(location=1) in vec2 fieldTexCoords;
layout(location=2) in vec4 skyCoords;
layout(location=3) in vec2 skyTexCoords;
layout(location=4) in vec4 WallCoords;
layout(location=5) in vec2 WallTexCoords;
layout(location=6) in vec4 FloorCoords;
layout(location=7) in vec2 FloorTexCoords;
layout(location=8) in vec4 roofCoords;
layout(location=9) in vec2 roofTexCoords;
layout(location=10) in vec4 doorCoords;
layout(location=11) in vec2 doorTexCoords;
layout(location=12) in vec3 floorNormal;
layout(location=13) in vec3 wallNormal;
layout(location=14) in vec4 treeCoords;
layout(location=15) in vec2 treeTexCoords;


uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
uniform uint object;


struct Light
{
   vec4 ambCols;
   vec4 difCols;
   vec4 specCols;
   vec4 coords;
};

struct Material
{
   vec4 ambRefl;
   vec4 difRefl;
   vec4 specRefl;
   vec4 emitCols;
   float shininess;
};

uniform Light light0;
uniform vec4 globAmb;
uniform Material woodfloor;
uniform Material wall;
uniform Material tree;

out vec2 texCoordsExport;
out vec4 colExport;
out vec4 specExport;

vec4 coords;
vec3 normal, lightDirection, eyeDirection, halfway;
vec4 frontEmit, frontGlobAmb, frontAmb, frontDif, frontSpec;
vec4 wallCoords;

void main(void)
{
   if (object == 0)
   {
       coords = fieldCoords;
       texCoordsExport = fieldTexCoords;
   }
   if (object == 1)
   {
       coords = skyCoords;
       texCoordsExport = skyTexCoords;
   }
   if (object == 2)
   {
       normal = wallNormal;

       normal = normalize(normalMatrix * normal);

       lightDirection = normalize(vec3(light0.coords));
       eyeDirection = -1.0 * normalize(vec3(modelViewMatrix * WallCoords));
       halfway = (length(lightDirection + eyeDirection) == 0.0) ?
                 vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);

       frontEmit = wall.emitCols;
       frontGlobAmb = globAmb * wall.ambRefl;
       frontAmb = light0.ambCols * wall.ambRefl;
       frontDif = max(dot(normal, lightDirection), 0.0) * light0.difCols * wall.difRefl;
       specExport = pow(max(dot(normal, halfway), 0.0), wall.shininess) *
                   light0.specCols * wall.specRefl;

       colExport =  vec4(vec3(min(frontEmit + frontGlobAmb + frontAmb +
                               frontDif, vec4(1.0))), 1.0);

       coords = WallCoords;
       texCoordsExport = WallTexCoords;
   }
   if (object == 3)
   {
       normal = floorNormal;
       normal = normalize(normalMatrix * normal);

       lightDirection = normalize(vec3(light0.coords));
       eyeDirection = -1.0 * normalize(vec3(modelViewMatrix * FloorCoords));
       halfway = (length(lightDirection + eyeDirection) == 0.0) ?
                 vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);

       frontEmit = woodfloor.emitCols;
       frontGlobAmb = globAmb * woodfloor.ambRefl;
       frontAmb = light0.ambCols * woodfloor.ambRefl;
       frontDif = max(dot(normal, lightDirection), 0.0) * light0.difCols * woodfloor.difRefl;
       specExport = pow(max(dot(normal, halfway), 0.0), woodfloor.shininess) *
                   light0.specCols * woodfloor.specRefl;

       colExport =  vec4(vec3(min(frontEmit + frontGlobAmb + frontAmb +
                               frontDif, vec4(1.0))), 1.0);

       coords = FloorCoords;
       texCoordsExport = FloorTexCoords;
   }
   if (object == 4)
   {
       coords = roofCoords;
       texCoordsExport = roofTexCoords;
   }
   if (object == 5)
   {
       coords = doorCoords;
       texCoordsExport = doorTexCoords;
   }
   if (object == 6)
   {
       normal = wallNormal;

       normal = normalize(normalMatrix * normal);

       lightDirection = normalize(vec3(light0.coords));
       eyeDirection = -1.0 * normalize(vec3(modelViewMatrix * treeCoords));
       halfway = (length(lightDirection + eyeDirection) == 0.0) ?
                 vec3(0.0) : (lightDirection + eyeDirection)/length(lightDirection + eyeDirection);

       frontEmit = tree.emitCols;
       frontGlobAmb = globAmb * tree.ambRefl;
       frontAmb = light0.ambCols * tree.ambRefl;
       frontDif = max(dot(normal, lightDirection), 0.0) * light0.difCols * tree.difRefl;
       specExport = pow(max(dot(normal, halfway), 0.0), tree.shininess) *
                   light0.specCols * tree.specRefl;

       colExport =  vec4(vec3(min(frontEmit + frontGlobAmb + frontAmb +
                               frontDif, vec4(1.0))), 1.0);


       coords = treeCoords;
       texCoordsExport = treeTexCoords;
   }

    if (object == 7)
   {
       coords = WallCoords; //ran out of space, used WallCoords location for the icicles
   }


   gl_Position = projectionMatrix * modelViewMatrix * coords;
}

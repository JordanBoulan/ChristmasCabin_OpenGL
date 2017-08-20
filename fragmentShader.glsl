#version 430 core

in vec2 texCoordsExport;
in vec4 colExport;
in vec4 specExport;

uniform sampler2D grassTex;
uniform sampler2D skyTex;
uniform sampler2D brickTex;
uniform sampler2D floorTex;
uniform sampler2D doorTex;
uniform sampler2D roofTex;
uniform sampler2D treeTex;

uniform uint object;

out vec4 colorsOut;

vec4 fieldTexColor, skyTexColor, brickTexColor, floorTexColor, doorTexColor, roofTexColor, treeTexColor, icicleColor;

void main(void)
{
   fieldTexColor = texture(grassTex, texCoordsExport);
   skyTexColor = texture(skyTex, texCoordsExport);
   brickTexColor = texture(brickTex, texCoordsExport);
   floorTexColor = texture(floorTex, texCoordsExport);
   doorTexColor = texture(doorTex, texCoordsExport);
   roofTexColor = texture(roofTex, texCoordsExport);
   treeTexColor = texture(treeTex, texCoordsExport);
   icicleColor = vec4(0.66, 0.85, 0.96, 1.0);

   if (object == 0) colorsOut = fieldTexColor;
   if (object == 1) colorsOut = skyTexColor;
   if (object == 2)
   {
       if (gl_FrontFacing)
           colorsOut = brickTexColor;
       else
           colorsOut = brickTexColor * colExport + specExport;
   }
   if (object == 3 )
   {
       if (gl_FrontFacing)
           colorsOut = floorTexColor * colExport + specExport;
       else
           colorsOut = floorTexColor;
   }
   if (object == 4) colorsOut = roofTexColor;
   if (object == 5) colorsOut = doorTexColor;
   if (object == 6) colorsOut = treeTexColor * colExport + specExport;
   if (object == 7) colorsOut = icicleColor;
}

#include "vertex.h"

#define PI 3.14159265
#define ICE_LONGS 30 // Number of longitudinal slices.
#define ICE_LATS 15 // Number of latitudinal slices.


// Icicle data.
static VertexIce iceVertices[(ICE_LONGS + 1) * (ICE_LATS + 1)];
static unsigned int iceIndices[ICE_LATS][2 * (ICE_LONGS + 1)];
static int iceCounts[ICE_LATS];
static void* iceOffsets[ICE_LATS];

void fillIceVertexArray(VertexIce iceVertices[(ICE_LONGS + 1) * (ICE_LATS + 1)]);
void fillIceIndices(unsigned int iceIndices[ICE_LATS][2 * (ICE_LONGS + 1)]);
void fillIceCounts(int iceCounts[ICE_LATS]);
void fillIceOffsets(void* iceOffsets[ICE_LATS]);

void fillIcicle(VertexIce iceVertices[(ICE_LONGS + 1) * (ICE_LATS + 1)],
	                      unsigned int iceIndices[ICE_LATS][2 * (ICE_LONGS+1)],
                          int iceCounts[ICE_LATS],
			              void* iceOffsets[ICE_LATS]);

void loadIcicleVertices(unsigned int*, unsigned int*);
void drawIcicle(unsigned int*, unsigned int*);
void prepareIcicle();
float changeRadius(float, float);

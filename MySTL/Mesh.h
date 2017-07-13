#ifndef Mesh_H
#define Mesh_H
#include <vector>
#include "SDL.h"
#include "glew.h"

using namespace std;

class Mesh
{
	int id, size;
public:
	Mesh() {}
	Mesh(float* data, int size);
	void draw();
};

#endif

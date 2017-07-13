#ifndef Mesh_H
#define Mesh_H
#include <vector>
#include "SDL.h"
#include "glew.h"

using namespace std;

class Mesh
{
public:
	Mesh();
	Mesh(float* ,int);
	~Mesh();
	int ID;
	int size;
	void draw();
};

#endif

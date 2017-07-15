#pragma once

class Mesh
{
	unsigned int id, size;
public:
	Mesh() {}
	Mesh(float* data, int size);
	void draw();
};

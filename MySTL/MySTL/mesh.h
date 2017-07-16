#pragma once

class Mesh
{
	unsigned int id, size;
public:
	inline Mesh() {}
	Mesh(float* data, int size);
	void draw();
};
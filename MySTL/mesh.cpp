#include "mesh.h"
#include <glew.h>
#include <iostream>

using namespace std;

Mesh::Mesh(float* data, int size) : size(size) {
	cout << data <<endl;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(data[0]), data, GL_STATIC_DRAW);
	cout << "hi";
}

void Mesh::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, id);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 12, 0);

	glDrawArrays(GL_TRIANGLES, 0, size);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
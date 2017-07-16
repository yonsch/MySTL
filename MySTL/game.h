#pragma once

#include "shader.h"
#include "mesh.h"
#include <string>
#include <SDL.h>
#include "math3d.h"

enum class GameState { PLAY, EXIT };

class Game
{
	void initSystems();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	vec3 vertices[8] = {
		vec3(0),
		vec3(1, 0, 0),
		vec3(0, 1, 0),
		vec3(0, 0, 1),
		vec3(1),
		vec3(1, 1, 0),
		vec3(1, 0, 1),
		vec3(0, 1, 1)
	};
#define V(i) vertices[i].x, vertices[i].y, vertices[i].z
#define QUAD(a, b, c, d) V(a), V(b), V(c), V(a), V(c), V(d)
	float data[108] = {
		QUAD(0, 3, 6, 1), //bottom
		QUAD(7, 2, 5, 4), //top
		QUAD(6, 4, 5, 1), //right
		QUAD(0, 2, 7, 3), //left
		QUAD(1, 5, 2, 0), //back
		QUAD(3, 7, 4, 6), //front
	};
#undef V
#undef QUAD
	Mesh mesh;

	mat4 projection, transform, camera;
	std::string vertex = "#version 330"
		"\nin vec3 position;"
		"\nout float depth;"
		"\nuniform mat4 mvp;"
		"\nvoid main() { "
		"\n	gl_Position = mvp * vec4(position, 1.0);"
		"\n	depth = gl_Position.z; "
		"\n}";
	std::string fragment = "#version 330\nin float depth;\n void main() { gl_FragColor = vec4(vec3(depth), 1.0); }";
	Shader shader;

public:
	Game();
	~Game();
	void run();
};
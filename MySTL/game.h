#pragma once

#include "shader.h"
#include "mesh.h"
#include <string>
#include <SDL.h>

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

	float data[9] = { -1, -1, 0, 0, 1, 0, 1, -1, 0 };
	Mesh mesh;

	std::string vertex = "in vec3 position;\nout vec3 pos;\nvoid main() { gl_Position = vec4(position, 1.0); pos = position; }";
	std::string fragment = "in vec3 pos;\n void main() { gl_FragColor = vec4(pos, 1.0); }";
	Shader shader;

public:
	Game();
	~Game();

	void run();
};


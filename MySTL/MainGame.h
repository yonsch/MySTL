#pragma once
#include "SDL.h"
#include "glew.h"
#include "Mesh.h"
#include "Shader.h"
#include <string>

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	

private:

	void initSystems();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	
	//float data[9] = { -1, -1, 0, 0, 1, 0, 1, -1, 0 };
	//Mesh mesh(data, 3);
	float data[9];
	Mesh mesh;

	std::string vertex = "in vec3 position;\nout vec3 pos;\nvoid main { pos = position; }";
	std::string fragment = "in vec3 pos;\nout vec4 color;\n void main() { color = vec4(pos, 1.0); }";
	Shader shader = Shader(vertex, fragment);
};


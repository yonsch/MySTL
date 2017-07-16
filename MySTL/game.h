#pragma once

#include "shader.h"
#include "mesh.h"
#include <string>
#include <SDL.h>
#include "math3d.h"
#include "STLMesh.h"
#include "transform.h"

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

	bool captureMouse = false;

	STLMesh pig = STLMesh("pig.stl");
	Mesh mesh;

	Transform camera = Transform(true), transform;
	mat4 projection;
	std::string vertex = "#version 330"
		"\nin vec3 position;"
		"\nout float depth;"
		"\nuniform mat4 mvp;"
		"\nvoid main() { "
		"\n	gl_Position = mvp * vec4(position, 1.0);"
		"\n	depth = gl_Position.z; "
		"\n}";
	std::string fragment = "#version 330"
		"\nin float depth;"
		"\nvoid main() {"
		"\n	gl_FragColor = vec4(vec3(depth), 1.0);"
		"\n}";
	Shader shader;

public:
	Game();
	~Game();
	void run();
};
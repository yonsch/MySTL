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

	float* data = new float[18] {-1, -1, 0, -1, 1, 0, 1, 1, 0, 1, 1, 0, 1, -1, 0, -1, -1, 0};
	STLMesh pig = STLMesh("pig.stl");
	Mesh mesh, screen;

	Transform camera = Transform(true), transform;
	mat4 projection;
	std::string vertex = "#version 330"
		"\nin vec3 position;"
		"\nuniform mat4 mvp;"
		"\nvoid main() { "
		"\n	gl_Position = mvp * vec4(position, 1.0);"
		"\n}";
	std::string fragment = "#version 330"
		"\nvoid main() {}";

	std::string vertexScreen = "#version 330"
		"\nin vec3 position;"
		"\nout vec2 tex;"
		"\nvoid main() {"
		"\n	gl_Position = vec4(position, 1.0);"
		"\n tex = position.xy / 2.0 + 0.5;"
		"\n}";
	std::string fragmentScreen = "#version 330"
		"\nin vec2 tex;"
		"\nuniform sampler2D diffuse;"
		"\nvoid main() {"
		"\n	gl_FragColor = vec4(vec3(1.0 - texture(diffuse, tex).x) * 5.0, 1.0);"
		"\n}";

	Shader shader, shaderScreen;
	FrameBuffer fbo;
	Texture depthBuffer;

public:
	Game();
	~Game();
	void run();
};
#include "game.h"
#include <iostream>
#include <string>
#include <glew.h>
#include "STLMesh.h"
#include <SDL_image.h>

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "enter any key" << std::endl;
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}

Game::Game()
{
	_window = nullptr;
	_screenHeight = 768;

	_screenWidth = 1024;
	_gameState = GameState::PLAY;
}


Game::~Game()
{
}

void Game::run() {
	initSystems();
	gameLoop();
}

void Game::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Yonsch's Stupid Mess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("window bla bla");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("context");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("glew init");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0, 0, 0, 1);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	mesh = (Mesh) pig;
	screen = Mesh(data, 6);
	shaderScreen = Shader(vertexScreen, fragmentScreen);
	shader = Shader(vertex, fragment);
		
	depthBuffer = Texture(_screenWidth, _screenHeight, 0, GL_RGB16F, GL_RGB, GL_FLOAT);
	fbo = FrameBuffer(_screenWidth, _screenHeight, 1, &depthBuffer);

	float PI = 3.14159265359f;
	camera.move(0, 0, 5);
	projection = mat4::perspective(PI / 2, (float)_screenWidth / _screenHeight, 0.1f, 1000);
	transform.scale(0.5f).rotate(vec3::LEFT, PI/2).rotate(vec3::UP, PI/2);
}

void Game::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_KEYDOWN:
			switch (evnt.button.button)
			{
				//TODO: fix the goddamn camera
			case SDL_SCANCODE_W:
				camera.move(-camera.rot.getForward());
				break;
			case SDL_SCANCODE_A:
				camera.move(-camera.rot.getLeft());
				break;
			case SDL_SCANCODE_S:
				camera.move(-camera.rot.getBack());
				break;
			case SDL_SCANCODE_D:
				camera.move(-camera.rot.getRight());
				break;
			case SDL_SCANCODE_SPACE:
				camera.move(0, 1, 0);
				break;
			case SDL_SCANCODE_LSHIFT:
				camera.move(0, -1, 0);
				break;
			case SDL_SCANCODE_ESCAPE:
				_gameState = GameState::EXIT;
			}
			break;
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			if (!captureMouse) break;
			camera.rotate(vec3::UP, (float)evnt.motion.xrel / 100);
			camera.rotate(camera.rot.getRight(), (float)-evnt.motion.yrel / 100);
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_SetRelativeMouseMode((captureMouse = !captureMouse) ? SDL_TRUE : SDL_FALSE);
		}
	}
}
void Game::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}
void Game::drawGame() {
	fbo.bind();
	shader.bind();
	shader.loadUniform("mvp", projection * ((mat4)camera * transform));
	shader.loadUniform("camPos", camera.pos);
	mat4 m = (mat4)camera;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (!(i != 3 && i == j)) m[i][j] /= 5;
	shader.loadUniform("model", m * transform);
	mesh.draw();
	shader.unbind();
	fbo.unbind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderScreen.bind();
	shaderScreen.loadUniform("diffuse", depthBuffer);
	screen.draw();
	shaderScreen.unbind();

	SDL_GL_SwapWindow(_window);
}
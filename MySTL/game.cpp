#include "game.h"
#include <iostream>
#include <string>
#include <glew.h>
#include "STLMesh.h"

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
	glClearColor(1.f, 1.f, 0.f, 1.f);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	mesh = (Mesh) pig;
	shader = Shader(vertex, fragment);

	float PI = 3.14159265359f;
	projection = mat4::perspective(PI / 2, (float)_screenWidth / _screenHeight, 0.1f, 1000);
	transform.move(0, -2, -5).rotate(vec3::LEFT, PI/2).rotate(vec3::UP, PI/2);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.bind();
	shader.loadUniform("mvp", (mat4)projection * ((mat4)camera * transform));
	vec3 d = camera.rot.getForward();
	glClearColor(d.x, d.y, d.z, 1);
	mesh.draw();
	shader.unbind();

	SDL_GL_SwapWindow(_window);
}
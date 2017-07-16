#include "game.h"
#include <iostream>
#include <string>
#include <glew.h>

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
	_window = SDL_CreateWindow("sdf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
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
	glDisable(GL_CULL_FACE);

	mesh = Mesh(data, 12);
	shader = Shader(vertex, fragment);

	float PI = 3.14159265359f;
	projection = mat4::perspective(PI / 2, _screenWidth / _screenHeight, 0.1f, 1000);
	camera *= mat4::translation(0, 0, -3);
	camera = mat4(camera);
}
void Game::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			camera *= mat4::rotation(vec3::UP, evnt.motion.x / 1000.f);
			camera *= mat4::rotation(vec3::RIGHT, evnt.motion.y / 1000.f);
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
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
	//shader.loadUniform("mvp", transform);
	mesh.draw();
	shader.unbind();

	SDL_GL_SwapWindow(_window);
}
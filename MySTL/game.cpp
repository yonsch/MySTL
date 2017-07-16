#include "MainGame.h"
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

MainGame::MainGame()
{
	_window = nullptr;
	_screenHeight = 768;
	
	_screenWidth = 1024;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}

void MainGame::run() {
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("sdf",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight,SDL_WINDOW_OPENGL);
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
	
	mesh = Mesh(data, 3);
	shader = Shader(vertex, fragment);
}
void MainGame::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y <<std::endl;
		}
	}
}
void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}
void MainGame::drawGame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.bind();
	mesh.draw();
	shader.unbind();

	SDL_GL_SwapWindow(_window);

}

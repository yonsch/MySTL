#include "MainGame.h"
#include <iostream>
#include <string>

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
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex2f(0, 0);
	glVertex2f(500, 0);
	glVertex2f(500, 500);
	glEnd();

	SDL_GL_SwapWindow(_window);

}
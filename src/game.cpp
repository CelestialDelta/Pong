#include "../include/game.h"

Game::Game()
	: _window(), _target(), _player(), _ai(), _running()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	_target = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	_player = Player(_target, glm::vec2(10, 300), glm::vec2(20, 125), 350.0f);
	_ai = AI(_target, glm::vec2(590 - 20, 300), glm::vec2(20, 125), 350.0f);
	_ball = Ball(_target, glm::vec2(300, 300), 16, glm::vec2(50, 50));

	_running = true;
}

void Game::draw()
{
	SDL_SetRenderDrawColor(_target, 255, 255, 255, 255);
	SDL_RenderClear(_target);
	
	_player.draw();
	_ai.draw();
	_ball.draw();
	
	SDL_RenderPresent(_target);
}

void Game::update(float dt)
{
	_player.move(dt);
	_ball.move(dt);
}

void Game::handle()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			_running = false;
		}
	}
	
	//std::cout << _ball.collides(_player) << std::endl;
}

bool Game::is_running() const
{
	return _running;
}

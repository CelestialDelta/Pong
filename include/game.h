#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>

#include "clock.h"
#include "object.h"
#include "common.h"

class Game
{
public:
	Game();
	
	void draw();
	void update(float dt);
	void handle();
	
	bool is_running() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _target;
	Player _player;
	AI _ai;
	Ball _ball;
	bool _running;
};

#include <iostream>
#include <chrono>
#include <stdint.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <glm/glm.hpp>

#include "../include/clock.h"
#include "../include/game.h"

int32_t main()
{		
	Clock clock;
	clock.start();
	
	Game game;
	while(game.is_running())
	{
		float dt = clock.tick();
	
		game.handle();
		game.update(dt);
		game.draw();
	}
	
	return 0;
}

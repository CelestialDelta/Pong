#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <glm/glm.hpp>

#include <iostream>

#include "common.h"

#define ZERO glm::vec2()

class Object
{
public:
	Object(SDL_Renderer* target = nullptr, const glm::vec2& pos = ZERO);
	virtual ~Object();
	virtual void draw() = 0;
	
	void set_position(const glm::vec2& pos);
	const glm::vec2& position() const;
protected:
	SDL_Renderer* _target;
	glm::vec2 _position;
};

//=================================================================================================

class Paddle
	: public Object
{
public:
	Paddle(SDL_Renderer* target = nullptr, const glm::vec2& pos = ZERO, const glm::vec2& size = ZERO, float vel = 0.0f);
	virtual ~Paddle() override;
	
	virtual void draw() override;
	virtual void move(float dt) = 0;
	
	void set_velocity(float vel);
	void set_size(const glm::vec2& size);
	
	const glm::vec2& size() const;
	float velocity() const;
protected:
	glm::vec2 _size;
	float _velocity;
};	

//=================================================================================================

class Player
	: public Paddle
{
public:
	Player(SDL_Renderer* target = nullptr, const glm::vec2& pos = ZERO, const glm::vec2& size = ZERO, float vel = 0.0f);
	virtual ~Player() override;
	
	virtual void move(float dt) override;
};

//=================================================================================================

class AI
	: public Paddle
{
public:
	AI(SDL_Renderer* target = nullptr, const glm::vec2& pos = ZERO, const glm::vec2& size = ZERO, float vel = 0.0f);
	virtual ~AI() override;
	
	void think();
	virtual void move(float dt) override;
};

//=================================================================================================

class Ball
	: public Object
{
public:
	Ball(SDL_Renderer* target = nullptr, const glm::vec2& pos = ZERO, uint16_t radius = 0, const glm::vec2& vel = ZERO);
	virtual ~Ball() override;
	
	virtual void draw() override;
	void move(float dt);
	bool collides(const Paddle& paddle);
	
	void set_radius(float radius);
	uint16_t radius() const;
protected:
	glm::vec2 _velocity;
	float _radius;
};

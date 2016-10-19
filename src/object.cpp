#include "../include/object.h"

Object::Object(SDL_Renderer* target, const glm::vec2& pos)
	: _target(target), _position(pos)
{
}

Object::~Object()
{
}

void Object::set_position(const glm::vec2& pos)
{
	_position = pos;
}

const glm::vec2& Object::position() const
{
	return _position;
}

//=================================================================================================

Paddle::Paddle(SDL_Renderer* target, const glm::vec2& pos, const glm::vec2& size, float vel)
	: Object(target, pos), _size(size), _velocity(vel)
{
}

Paddle::~Paddle()
{
}

void Paddle::draw()
{
	SDL_Rect rect;
	rect.x = _position.x;
	rect.y = _position.y;
	rect.w = _size.x;
	rect.h = _size.y;
	
	SDL_SetRenderDrawColor(_target, 0, 255, 0, 255);
	SDL_RenderFillRect(_target, &rect);
}

void Paddle::set_velocity(float vel)
{
	_velocity = vel;
}

void Paddle::set_size(const glm::vec2& size)
{
	_size = size;
}

float Paddle::velocity() const
{
	return _velocity;
}

const glm::vec2& Paddle::size() const
{
	return _size;
}

//=================================================================================================

Player::Player(SDL_Renderer* target, const glm::vec2& pos, const glm::vec2& size, float vel)
	: Paddle(target, pos, size, vel)
{
}

Player::~Player()
{
}

void Player::move(float dt)
{
	const uint8_t* keyboard = SDL_GetKeyboardState(nullptr);
	if(keyboard[SDL_SCANCODE_W])
	{
		_position.y -= _velocity * dt;
		if(_position.y <= 0)
		{
			_position.y = 0;
		}
	}
	if(keyboard[SDL_SCANCODE_S])
	{
		_position.y += _velocity * dt;
		if(_position.y + _size.y >= WINDOW_HEIGHT)
		{
			_position.y = WINDOW_HEIGHT - _size.y;
		}
	}
}

//=================================================================================================

AI::AI(SDL_Renderer* target, const glm::vec2& pos, const glm::vec2& size, float vel)
	: Paddle(target, pos, size, vel)
{
}

AI::~AI()
{
}

void AI::think()
{
}

void AI::move(float dt)
{
}

//=================================================================================================

Ball::Ball(SDL_Renderer* target, const glm::vec2& pos, uint16_t radius, const glm::vec2& vel)
	: Object(target, pos), _radius(radius), _velocity(vel)
{
}

Ball::~Ball()
{
}

void Ball::draw()
{
	filledCircleRGBA(_target, _position.x, _position.y, _radius, 0, 255, 255, 255);
}

void Ball::move(float dt)
{
	_position.y -= _velocity.y * dt;
	
	std::cout << _velocity.x * dt << std::endl;
	
	if(_position.y - _radius <= 0 || _position.y + _radius >= WINDOW_HEIGHT)
	{
		_velocity.y = -_velocity.y;
	}
	if(_position.x - _radius <= 0 || _position.x + _radius >= WINDOW_WIDTH)
	{
		_velocity.x = -_velocity.x;
	}
}

bool Ball::collides(const Paddle& paddle)
{
	glm::vec2 center(_position + _radius);
	glm::vec2 aabb_half_extents(paddle.size().x / 2, paddle.size().y / 2);
	glm::vec2 aabb_center(
		paddle.position().x + aabb_half_extents.x,
		paddle.position().y + aabb_half_extents.y);
		
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	return glm::length(difference) < _radius;
}



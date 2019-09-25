/**
 * Copyright (c) 2019 Peter Stacey
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "player.h"

#include <cmath>

#include "config.h"

Player::Player(double x, double y)
{
	position = {x, y};
	velocity = {0.0, 0.0};
	acceleration = {0.0, 0.0};
	angle = 0.0;
	lives_ = START_LIVES;
	thrust_ = false;
	rotate_left_ = false;
	rotate_right_ = false;
	time_last_fired_ = SDL_GetTicks();
}

Player::~Player()
{
}

void Player::Reset()
{
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT / 2;
	velocity.x = 0.0;
	velocity.y = 0.0;
	acceleration.x = 0.0;
	acceleration.y = 0.0;
	angle = 0.0;
}

void Player::RotateRight()
{
	angle += PLAYER_ROTATION_AMOUNT;
}

void Player::RotateLeft()
{
	angle -= PLAYER_ROTATION_AMOUNT;
}

void Player::Thrust()
{
	acceleration.x = PLAYER_THRUST_AMOUNT * sin(angle * (M_PI / 180.0f));
	acceleration.y = PLAYER_THRUST_AMOUNT * -cos(angle * (M_PI / 180.0f));
}

bool Player::Fire()
{
	if ((SDL_GetTicks() - time_last_fired_) > PLAYER_FIRE_DELAY)
	{
		time_last_fired_ = SDL_GetTicks();
		return true;
	}
	return false;
}

void Player::GainLife()
{
	lives_++;
}

void Player::LoseLife()
{
	lives_--;
}

int Player::GetLives()
{
	return lives_;
}

void Player::Update()
{
	if (thrust_)
		Thrust();
	if (!thrust_)
	{
		acceleration.Multiply(0.0f);
		velocity.Multiply(PLAYER_DRAG);
	}
	if (rotate_left_)
		RotateLeft();
	if (rotate_right_)
		RotateRight();

	float oldX = velocity.x;
	float oldY = velocity.y;

	velocity.Add(acceleration);

	float magnitude = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (magnitude > PLAYER_MAX_SPEED)
	{
		velocity.x = oldX;
		velocity.y = oldY;
	}

	position.Add(velocity);

	if (position.y < 0.0)
		position.y = SCREEN_HEIGHT;
	if (position.y > SCREEN_HEIGHT)
		position.y = 0.0;
	if (position.x < 0.0)
		position.x = SCREEN_WIDTH;
	if (position.x > SCREEN_WIDTH)
		position.x = 0.0;	
}

void Player::Render(SDL_Renderer * renderer)
{
	float theta = angle * M_PI / 180.0f;

	float cs = cos(theta);
	float sn = sin(theta);

	double x1 = -8 * cs - 15 * sn;
	double y1 = -8 * sn + 15 * cs;
	double x2 = 0 * cs + 15 * sn;
	double y2 = 0 * sn - 15 * cs;
	double x3 = 8 * cs - 15 * sn;
	double y3 = 8 * sn + 15 * cs;
	double x4 = 0 * cs - 8 * sn;
	double y4 = 0 * sn + 8 * cs;

	x1 += position.x;
	y1 += position.y;
	x2 += position.x;
	y2 += position.y;
	x3 += position.x;
	y3 += position.y;
	x4 += position.x;
	y4 += position.y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
	SDL_RenderDrawLine(renderer, x3, y3, x4, y4);
	SDL_RenderDrawLine(renderer, x4, y4, x1, y1);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

Vec2 Player::GetPosition()
{
	return position;
}

float Player::GetAngle()
{
	return angle;
}

bool Player::CollidesWith(GameObject * object)
{
	return this->position.Distance(object->position) <= ASTEROID_BASE_RADIUS;
}

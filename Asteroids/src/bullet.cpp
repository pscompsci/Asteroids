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

#include "bullet.h"

#include <cmath>
#include <iostream>

#include <SDL.h>

#include "config.h"

Bullet::Bullet(double x, double y, double angle)
{
	position.x = x;
	position.y = y;
	this->angle = angle;
	velocity.x = BULLET_SPEED * sin(angle * M_PI / 180.0f);
	velocity.y = BULLET_SPEED * -cos(angle * M_PI / 180.0f);
	flight_time_ = BULLET_FLIGHT_TIME;
	start_time_ = SDL_GetTicks();
	hit_target_ = false;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
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

void Bullet::Render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderSetScale(renderer, 2, 2);
	SDL_RenderDrawPoint(renderer, position.x / 2, position.y / 2);
	SDL_RenderSetScale(renderer, 1, 1);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Bullet::HitAndShouldDie()
{
	hit_target_ = true;
}

bool Bullet::CollidesWith(GameObject * object)
{
	return this->position.Distance(object->position) <= ASTEROID_BASE_RADIUS;
}

bool Bullet::ShouldEnd()
{
	return ((SDL_GetTicks() - start_time_) > flight_time_) || hit_target_;
}

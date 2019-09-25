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

#include "asteroid.h"

#include <iostream>

#include "config.h"

Asteroid::Asteroid(double x, double y, double angle, int size)
{
	position.x = x;
	position.y = y;
	angle = angle;
	acceleration = { 0.0, 0.0 };
	this->size_ = size;
	velocity.x = ASTEROID_BASE_SPEED * size * 0.5 * sin(angle * M_PI / 180.0f);
	velocity.y = ASTEROID_BASE_SPEED * size * 0.5 * -cos(angle * M_PI / 180.0f);
	switch (this->size_)
	{
	case(1):
		points_value_ = LARGE_ASTEROID_SCORE;
		break;
	case(2):
		points_value_ = MEDIUM_ASTEROID_SCORE;
		break;
	case(3):
		points_value_ = SMALL_ASTEROID_SCORE;
		break;
	default:
		points_value_ = 0;
	}
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update()
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

void Asteroid::Render(SDL_Renderer * renderer)
{
	double x1 = position.x - (30.0 * 1 / size_);
	double y1 = position.y + (0.0 * 1 / size_);
	double x2 = position.x - (10.0 * 1 / size_);
	double y2 = position.y - (25.0 * 1 / size_);
	double x3 = position.x + (0.0 * 1 / size_);
	double y3 = position.y - (30.0 * 1 / size_);
	double x4 = position.x + (25.0 * 1 / size_);
	double y4 = position.y - (20.0 * 1 / size_);
	double x5 = position.x + (30.0 * 1 / size_);
	double y5 = position.y + (0.0 * 1 / size_);
	double x6 = position.x + (20.0 * 1 / size_);
	double y6 = position.y + (20.0 * 1 / size_);
	double x7 = position.x + (0.0 * 1 / size_);
	double y7 = position.y + (30.0 * 1 / size_);
	double x8 = position.x - (25.0 * 1 / size_);
	double y8 = position.y + (25.0 * 1 / size_);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
	SDL_RenderDrawLine(renderer, x3, y3, x4, y4);
	SDL_RenderDrawLine(renderer, x4, y4, x5, y5);
	SDL_RenderDrawLine(renderer, x5, y5, x6, y6);
	SDL_RenderDrawLine(renderer, x6, y6, x7, y7);
	SDL_RenderDrawLine(renderer, x7, y7, x8, y8);
	SDL_RenderDrawLine(renderer, x8, y8, x1, y1);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

bool Asteroid::CollidesWith(GameObject * object)
{
	return false;
}

int Asteroid::GetSize()
{
	return size_;
}

int Asteroid::GetPointsValue()
{
	return points_value_;
}

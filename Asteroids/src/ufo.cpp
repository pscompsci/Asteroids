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

#include "ufo.h"

#include <cmath>

#include "config.h"

UFO::UFO(double x, double y)
{
	position = {x, y};
	velocity = {UFO_SPEED, 0.0};
	acceleration = {0.0, 0.0};
	flight_time_ = UFO_FLIGHT_TIME;
	start_time_ = SDL_GetTicks();
	hit_target_ = false;
	points_value_ = UFO_SCORE;
}

UFO::~UFO()
{
}

void UFO::Update()
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

void UFO::Render(SDL_Renderer * renderer)
{
	double x1 = position.x - 10;
	double y1 = position.y;
	double x2 = position.x - 7;
	double y2 = position.y + 7;
	double x3 = position.x + 7;
	double y3 = position.y + 7;
	double x4 = position.x + 10;
	double y4 = position.y;
	double x5 = position.x + 7;
	double y5 = position.y;
	double x6 = position.x;
	double y6 = position.y - 7;
	double x7 = position.x - 7;
	double y7 = position.y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
	SDL_RenderDrawLine(renderer, x3, y3, x4, y4);
	SDL_RenderDrawLine(renderer, x1, y1, x4, y4);
	SDL_RenderDrawLine(renderer, x5, y5, x6, y6);
	SDL_RenderDrawLine(renderer, x6, y6, x7, y7);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

bool UFO::Fire()
{
	if ((SDL_GetTicks() - time_last_fired_) > UFO_FIRE_DELAY)
	{
		time_last_fired_ = SDL_GetTicks();
		return true;
	}
	return false;
}

void UFO::HitAndShouldDie()
{
	hit_target_ = true;
}

bool UFO::CollidesWith(GameObject* object)
{
	return this->position.Distance(object->position) == 0;
}

bool UFO::ShouldEnd()
{
	return ((SDL_GetTicks() - start_time_) > flight_time_) || hit_target_;
}

int UFO::GetPointsValue()
{
	return points_value_;
}
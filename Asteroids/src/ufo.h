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

#ifndef ASTEROIDS_UFO_H_
#define ASTEROIDS_UFO_H_

#include <SDL.h>
#include <vector>

#include "vec2.h"
#include "game_object.h"

 // Defines the attributes and behaviours of UFOs as a sub-class of GameObject.
class UFO : public GameObject
{
public:
	UFO() {};
	UFO(double x, double y);
	~UFO();

	bool Fire();

	void Update();
	void Render(SDL_Renderer* renderer);
	void HitAndShouldDie();

	bool ShouldEnd();
	bool CollidesWith(GameObject* object);
	int GetPointsValue();

private:
	int time_last_fired_;
	unsigned int flight_time_;
	unsigned int start_time_;
	bool hit_target_;
	int points_value_;
};

#endif

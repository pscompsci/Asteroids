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

#ifndef _ASTEROIDS_GAME_H_
#define _ASTEROIDS_GAME_H_

#include <vector>
#include "SDL_ttf.h"
#include "window.h"
#include "timer.h"
#include "player.h"
#include "level.h"
#include "hud.h"

// Provides the overall logic layer of the game and controls the update
// and render cycle.
class Game
{
public:
	Game();
	~Game();
	bool Init();
	void Run();
	void HandleInput();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
	void AddScore(int score);

private:
	SDL_Event event_;
	Window * window_;
	bool running_;
	bool game_over_;
	Timer * timer_;
	Level level_;
	Player player;

	int current_level_;
	int score_;

	void CheckGameOver();
};

#endif
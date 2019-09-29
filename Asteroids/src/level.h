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

#ifndef ASTEROIDS_LEVEL_H_
#define ASTEROIDS_LEVEL_H_

#include <SDL.h>
#include <vector>
#include "game_object.h"
#include "player.h"
#include "bullet.h"
#include "asteroid.h"
#include "ufo.h"
#include "sound.h"
#include "config.h"

// Manages progression in the game and controls the game objects of each level. 
class Level
{
public:
	Level() {};
	Level(int level_number, int score, SoundEffects & sounds);
	~Level();
	void Update(Player & player);
	void Render(SDL_Renderer * renderer, Player & player);
	void Clean();
	
	void AddBullet(Player & player);
	void AddScore(int amount);

	int GetScore();

	bool finished_;

private:
	int level_number_;
	int score_;
	std::vector<Bullet> bullets_;
	std::vector<Asteroid> asteroids_;
	SoundEffects sound_;
	std::vector<UFO> ufos_;

	bool UFOAppears();
};

#endif

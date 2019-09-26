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

#include "level.h"

#include <stdlib.h>
#include <time.h>

Level::Level(int level_number, int score)
{
	level_number_ = level_number;
	score_ = score;
	time_t rawtime;
	srand(time(&rawtime));

	for (int i = 0; i < (MIN_START_ASTEROIDS + 2 * (level_number_ - 1)) && i <= MAX_START_ASTEROIDS; i++)
	{
		double x = rand() % SCREEN_WIDTH;
		double y = rand() % SCREEN_HEIGHT;
		double angle = rand() % 300 + 30.0;
		asteroids_.push_back(Asteroid{x, y, angle, ASTEROID_SIZE::LARGE});

	}
	
	finished_ = false;
}

Level::~Level()
{
}

void Level::Update(Player & player)
{
	player.Update();

	for (unsigned int i = 0; i < bullets_.size(); i++)
	{
		if (bullets_[i].ShouldEnd())
		{
			bullets_.erase(bullets_.begin() + i);
		}
		else
		{
			bullets_[i].Update();
		}
	}

	for (int i = 0; i < ufos_.size(); i++)
	{
		ufos_[i].Update();
	}


	for (unsigned int i = 0; i < asteroids_.size(); i++)
	{
		asteroids_[i].Update();
	}

	for (unsigned int i = 0; i < bullets_.size(); i++)
	{
		for (unsigned int j = 0; j < asteroids_.size(); j++)
		{
			if (bullets_[i].CollidesWith(&asteroids_[j]))
			{
				AddScore(asteroids_[j].GetPointsValue());
				if (asteroids_[j].GetSize() < 3)
				{
					asteroids_.push_back(Asteroid{ asteroids_[j].position.x,
						asteroids_[j].position.y, 45.0, asteroids_[j].GetSize() + 1 });
					asteroids_.push_back(Asteroid{ asteroids_[j].position.x,
						asteroids_[j].position.y, 135.0, asteroids_[j].GetSize() + 1 });
					asteroids_.erase(asteroids_.begin() + j);
				}
				else
				{
					asteroids_.erase(asteroids_.begin() + j);
				}
				bullets_[i].HitAndShouldDie();
				break;
			}
		}
		for (unsigned int k = 0; k < ufos_.size(); k++)
		{
			if (bullets_[i].CollidesWith(&ufos_[k]))
			{
				AddScore(ufos_[k].GetPointsValue());
				ufos_.erase(ufos_.begin() + k);
			}
		}
	}

	for (unsigned int i = 0; i < asteroids_.size(); i++)
	{
		if (player.CollidesWith(&asteroids_[i]))
		{
			asteroids_.erase(asteroids_.begin() + i);
			player.LoseLife();
			player.Reset();
			break;
		}
	}

	if (asteroids_.size() == 0)
	{
		finished_ = true;
	}
}

void Level::Render(SDL_Renderer * renderer, Player & player)
{
	player.Render(renderer);

	for (unsigned int i = 0; i < bullets_.size(); i++)
	{
		bullets_[i].Render(renderer);
	}

	for (int i = 0; i < ufos_.size(); i++)
	{
		ufos_[i].Render(renderer);
	}

	for (unsigned int i = 0; i < asteroids_.size(); i++)
	{
		asteroids_[i].Render(renderer);
	}

}

void Level::Clean()
{
	asteroids_.clear();
	bullets_.clear();
	ufos_.clear();
	level_number_ = NULL;
	finished_ = NULL;
}

void Level::AddBullet(Player & player)
{
	bullets_.push_back(Bullet{ player.GetPosition().x,
					   player.GetPosition().y, player.GetAngle() });
}

void Level::AddScore(int amount)
{
	score_ += amount;
}

int Level::GetScore()
{
	return score_;
}

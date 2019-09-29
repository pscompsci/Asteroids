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

#include "game.h"

#include <iostream>
#include "config.h"

Game::Game()
{
	running_ = Init();
	
	sounds = SoundEffects();
	sounds.LoadResources();

	hud = {"assets/fonts/hyperspace.otf", FONT_SIZE};
	
	current_level_ = 1;
	player = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	level_ = {current_level_, 0, sounds};


	game_over_ = false;
}

Game::~Game()
{
	sounds.Clean();

	delete window_;
	delete timer_;

	window_ = nullptr;
	timer_ = nullptr;
}

bool Game::Init()
{
	timer_ = new Timer();
	window_ = new Window();
	return true;
}

void Game::Run()
{
	while (running_)
	{
		if (!game_over_)
		{
			if (!level_.finished_)
			{
				timer_->Update();
				if (timer_->GetDeltaTime() >= 1.0f / FRAMES_PER_SECOND)
				{
					EarlyUpdate();
					Update();
					LateUpdate();
					Render();
				}
			}
			else
			{
				int current_score = level_.GetScore();
				level_.Clean();
				current_level_++;
				player.Reset();
				level_ = {current_level_, current_score, sounds};
			}
		}
		else
		{
			EarlyUpdate();
		}

		CheckGameOver();
	}

	window_->Clean();
}

void Game::HandleInput()
{
	while (SDL_PollEvent(&event_))
	{
		switch (event_.type)
		{
		case SDL_QUIT:
			running_ = false;
			break;
		case SDL_KEYDOWN:
			if (event_.key.keysym.sym == SDLK_UP)
			{
				sounds.PlayThrust();
				player.thrust_ = true;
			}
			if (event_.key.keysym.sym == SDLK_LEFT)
				player.rotate_left_ = true;
			if (event_.key.keysym.sym == SDLK_RIGHT)
				player.rotate_right_ = true;
			if (event_.key.keysym.sym == SDLK_SPACE)
			{
				if (player.Fire())
				{
					sounds.PlayFire();
					level_.AddBullet(player);
				}
			}
			break;
		case SDL_KEYUP:
			if (event_.key.keysym.sym == SDLK_UP)
				player.thrust_ = false;
			if (event_.key.keysym.sym == SDLK_LEFT)
				player.rotate_left_ = false;
			if (event_.key.keysym.sym == SDLK_RIGHT)
				player.rotate_right_ = false;
			break;
		}
	}
}

void Game::EarlyUpdate()
{
	HandleInput();
}

void Game::Update()
{
	level_.Update(player);
}

void Game::LateUpdate()
{
	timer_->Reset();
}

void Game::Render()
{
	window_->Clear();
	level_.Render(window_->GetRenderer(), player);
	hud.Render(window_->GetRenderer(), 40, 20, level_.GetScore(), player.GetLives(), {255,255,255,255});
	window_->Present();
}

void Game::CheckGameOver()
{
	if (player.GetLives() == 0)
	{
		game_over_ = true;
	}
}
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
	player = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
	level_ = { 1 };
	score_ = 0;
	game_over_ = false;
}

Game::~Game()
{
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

		}
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
				player.thrust_ = true;
			if (event_.key.keysym.sym == SDLK_LEFT)
				player.rotate_left_ = true;
			if (event_.key.keysym.sym == SDLK_RIGHT)
				player.rotate_right_ = true;
			if (event_.key.keysym.sym == SDLK_SPACE)
			{
				if (player.Fire())
				{
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
	
	level_.Render(window_->GetRenderer(), player, score_);

	/** TIDY THIS UP (MEMORY LEAK)
	Text score_text(window_->GetRenderer(), "assets/hyperspace.otf", 28, std::to_string(score_), { 255, 255, 255, 255 });
	score_text.Render(100, 20, window_->GetRenderer());
	Text lives_text(window_->GetRenderer(), "assets/hyperspace.otf", 16, "Lives: " + std::to_string(player.GetLives()), { 255, 255, 255, 255 });
	lives_text.Render(100, 50, window_->GetRenderer());
	*/

	window_->Present();
}

void Game::AddScore(int score)
{
	score_ += score;
}
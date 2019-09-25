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

#include "window.h"

#include <SDL_ttf.h>
#include "config.h"

Window::Window()
{
	Init();
}

Window::~Window()
{
}

void Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL initialization error: " << SDL_GetError();
	}

	if (TTF_Init() == -1)
	{
		std::cout << "TTF initialization error: " << TTF_GetError();
	}

	window_ = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window_ == NULL)
	{
		std::cout << "Window creation error: " << SDL_GetError();
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	if (renderer_ == NULL)
	{
		std::cout << "Renderer creation error: " << SDL_GetError();
	}

	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
}

void Window::Clear()
{
	SDL_RenderClear(renderer_);
}

void Window::Present()
{
	SDL_RenderPresent(renderer_);
}

void Window::Clean()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	TTF_Quit();
	SDL_Quit();

	renderer_ = nullptr;
	window_ = nullptr;
}

SDL_Renderer * Window::GetRenderer()
{
	return renderer_;
}
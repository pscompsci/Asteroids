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

#include "hud.h"
#include <iostream>

HUD::HUD(std::string font_path, int font_size)
{
	game_font_ = TTF_OpenFont(font_path.c_str(), font_size);

	if (game_font_ == NULL)
	{
		std::cout << "Font loading error: " << TTF_GetError() << std::endl;
	}
}

HUD::~HUD()
{
}

void HUD::PrepareText(SDL_Renderer * renderer, std::string message, int value, const SDL_Color & color)
{
	output_ = message + ": " + std::to_string(value);
	text_surface_ = TTF_RenderText_Solid(game_font_, output_.c_str(), color);

	if (text_surface_ == NULL)
	{
		std::cout << "Surface creation error: " << TTF_GetError() << std::endl;
	}

	text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);
	SDL_QueryTexture(text_texture_, nullptr, nullptr, &text_rect_.w, &text_rect_.h);

	if (text_texture_ == NULL)
	{
		std::cout << "Texture creation error: " << TTF_GetError() << std::endl;
	}

	SDL_FreeSurface(text_surface_);
}

void HUD::Render(SDL_Renderer* renderer, double x, double y, int score, int lives, const SDL_Color & color)
{
	text_rect_.x = x;
	text_rect_.y = y;
	PrepareText(renderer, "Score", score, color);
	SDL_RenderCopy(renderer, text_texture_, nullptr, &text_rect_);
	SDL_DestroyTexture(text_texture_);  // Avoid memory leak from created textures not being freed
	text_rect_.y = y + 30;
	PrepareText(renderer, "Lives", lives, color);
	SDL_RenderCopy(renderer, text_texture_, nullptr, &text_rect_);
	SDL_DestroyTexture(text_texture_);
}
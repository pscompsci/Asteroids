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
#include "window.h"

Text::Text(SDL_Renderer* renderer, std::string font_path, int font_size, std::string message, const SDL_Color & color)
{
	text_texture_ = LoadFont(renderer, &font_path, font_size, &message, color);
	SDL_QueryTexture(text_texture_, nullptr, nullptr, &text_rect_.w, &text_rect_.h);
}

Text::~Text() {}

void Text::Render(int x, int y, SDL_Renderer * renderer) const
{
	text_rect_.x = x;
	text_rect_.y = y;
	SDL_RenderCopy(renderer, text_texture_, nullptr, &text_rect_);
}

SDL_Texture* Text::LoadFont(SDL_Renderer * renderer, const std::string * font_path, int font_size, const std::string * message, const SDL_Color & color)
{
	TTF_Font* font = TTF_OpenFont(font_path->c_str(), font_size);

	if (font == NULL)
	{
		std::cout << "Font loading error: " << TTF_GetError() << std::endl;
	}

	SDL_Surface * text_surface = TTF_RenderText_Solid(font, message->c_str(), color);

	if (text_surface == NULL)
	{
		std::cout << "Surface creation error: " << TTF_GetError() << std::endl;
	}

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	if (text_texture == NULL)
	{
		std::cout << "Texture creation error: " << TTF_GetError() << std::endl;
	}

	SDL_FreeSurface(text_surface);

	return text_texture;
}
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

#ifndef ASTEROIDS_HUD_H_
#define ASTEROIDS_HUD_H_

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

// Creates a heads up dsiplay for the game to dislay lives and score
class HUD
{
public:
	HUD() {};
	HUD(std::string font_path, int font_size);
	~HUD();
	void PrepareText(SDL_Renderer * renderer, std::string message, int value, const SDL_Color& color);
	void Render(SDL_Renderer* renderer, double x, double y, int score, int lives, const SDL_Color & color);

private:
	TTF_Font * game_font_;
	std::string output_;
	SDL_Surface * text_surface_ = nullptr;
	SDL_Texture * text_texture_ = nullptr;
	SDL_Rect text_rect_;
};

#endif

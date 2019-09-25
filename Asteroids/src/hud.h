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

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

// Provides the functionality to render the heads up dislay on the screen.
class Text
{
public:
	Text(SDL_Renderer* renderer, std::string font_path, int font_size, std::string message, const SDL_Color & color);
	~Text();

	void Render(int x, int y, SDL_Renderer * renderer) const;

	static SDL_Texture* LoadFont(SDL_Renderer * renderer, const std::string* font_path, int font_size, const std::string* message, const SDL_Color & color);

private:
	SDL_Texture * text_texture_ = nullptr;
	mutable SDL_Rect text_rect_;
};


#endif

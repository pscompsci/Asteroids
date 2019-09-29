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

#ifndef ASTEROIDS_SOUND_H_
#define ASTEROIDS_SOUND_H_

#include <SDL_mixer.h>
#include <iostream>

struct SoundEffects
{
	Mix_Chunk * thrust_sound;
	Mix_Chunk * fire_sound;
	Mix_Chunk * ufo_sound;
	Mix_Chunk * explosion_sound;

	SoundEffects()
	  : thrust_sound(NULL),
		fire_sound(NULL),
		ufo_sound(NULL),
		explosion_sound(NULL) {}

	void LoadResources()
	{
		thrust_sound = Mix_LoadWAV("assets/sounds/thrust.wav");
		fire_sound = Mix_LoadWAV("assets/sounds/fire.wav");
		ufo_sound = Mix_LoadWAV("assets/sounds/saucer_small.wav");
		explosion_sound = Mix_LoadWAV("assets/sounds/bang_medium.wav");

		if (thrust_sound == NULL || fire_sound == NULL || 
			ufo_sound == NULL || explosion_sound == NULL)
		{
			std::cout << "Sound loading error: " << Mix_GetError();
		} 
	}

	void Clean()
	{
		Mix_FreeChunk(explosion_sound);
		Mix_FreeChunk(ufo_sound);
		Mix_FreeChunk(fire_sound);
		Mix_FreeChunk(thrust_sound);

		explosion_sound = nullptr;
		ufo_sound = nullptr;
		fire_sound = nullptr;
		thrust_sound = nullptr;
	}

	void PlayThrust()
	{
		Mix_PlayChannel(-1, thrust_sound, 0);
	}

	void PlayFire()
	{
		Mix_PlayChannel(-1, fire_sound, 0);
	}

	void PlayExplosion()
	{
		Mix_PlayChannel(-1, explosion_sound, 0);
	}

	void PlayUFO()
	{
		Mix_PlayChannel(-1, ufo_sound, 0);
	}
};

#endif
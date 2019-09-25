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

#include "timer.h"

Timer::Timer()
{
	Reset();
	time_scale_ = 1.0f;
}

Timer::~Timer()
{
	time_scale_ = NULL;
}

void Timer::Update()
{
	elapsed_time_ = SDL_GetTicks() - start_ticks_;
	delta_time_ = elapsed_time_ * 0.001f;
}

void Timer::Reset()
{
	start_ticks_ = SDL_GetTicks();
	elapsed_time_ = 0;
	delta_time_ = 0.0f;
}

void Timer::SetTimeScale(float t)
{
	time_scale_ = t;
}

float Timer::GetTimeScale()
{
	return time_scale_;
}

float Timer::GetDeltaTime()
{
	return delta_time_;;
}

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

#ifndef ASTEROIDS_CONFIG_H_
#define ASTEROIDS_CONFIG_H_

#pragma warning (disable : 4305)
#pragma warning (disable: 4244)

const int              SCREEN_WIDTH                  = 900;
const int              SCREEN_HEIGHT                 = 700;
											         
const int              FRAMES_PER_SECOND             = 60;
											         
const int              PLAYER_ROTATION_AMOUNT        = 8;
const float			   PLAYER_THRUST_AMOUNT          = 5.0;
const float            PLAYER_MAX_SPEED              = 10.0f;
const int              PLAYER_FIRE_DELAY             = 300;
const float            PLAYER_DRAG                   = 0.975;
const int			   START_LIVES                   = 3;
											         
const unsigned int     UFO_FLIGHT_TIME               = 2000;
const int              UFO_FIRE_DELAY                = 1200;
											         
const int              BULLET_SPEED                  = 20.0f;
const unsigned int     BULLET_FLIGHT_TIME            = 500;

enum ASTEROID_SIZE     {LARGE = 1, MEDIUM, SMALL};

const int              MAX_LEVEL                     = 10;
const int              MIN_START_ASTEROIDS           = 4;
const int              MAX_START_ASTEROIDS           = 14;
const double           ASTEROID_BASE_SPEED           = 2.0;
const unsigned int     ASTEROID_BASE_RADIUS          = 30;
											         
const int			   LARGE_ASTEROID_SCORE          = 20;
const int              MEDIUM_ASTEROID_SCORE         = 50;
const int              SMALL_ASTEROID_SCORE          = 100;
const int		       UFO_SCORE                     = 200;

#endif

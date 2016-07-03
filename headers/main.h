/*
 * main.h
 *
 *  Created on: Feb 20, 2016
 *      Author: motey
 */

#ifndef HEADERS_MAIN_H_
#define HEADERS_MAIN_H_

#define SDLTWO
#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <GL/GL.h>
#endif
#ifdef LINUX
#ifdef SDLTWO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#endif
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#endif
#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>



#endif /* HEADERS_MAIN_H_ */

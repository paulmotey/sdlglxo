/*
 * sdlmain.c
 *
 *  Created on: Dec 27, 2015
 *      Author: motey
 */
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
extern int GlSdlTest1(	SDL_Renderer *ren , SDL_Window *win ,SDL_GLContext context);

int main(int argc, char** argv) {
	SDL_GLContext context; /* Our opengl context handle */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return 1;
}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_Window *win = SDL_CreateWindow("SDL2 OpenGL WL V2.1", 1200, 200, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (win == nullptr) {		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; return 2;	}
	context = SDL_GL_CreateContext(win);
/* Create a renderer that will draw to the window,-1 specifies that we want to load whichever video driver supports the flags we're passing
Flags:
SDL_RENDERER_ACCELERATED: use hardware accelerated rendering
SDL_RENDERER_PRESENTVSYNC: renderer's present function (update screen) to be synchronized with the monitor's refresh rate */
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 3;
	}
	float m[16];
	if (TTF_Init() < 0) {return 55;}
	glGetFloatv(GL_PROJECTION_MATRIX,m);
	std::cout<<"PROJECTION "<<std::endl<<m[0]<<m[1]<<m[2]<<m[3]<<std::endl;
	std::cout<<m[4]<<m[5]<<m[6]<<m[7]<<std::endl;
	std::cout<<m[8]<<m[9]<<m[10]<<m[11]<<std::endl;
	std::cout<<m[12]<<m[13]<<m[14]<<m[15]<<std::endl;
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	std::cout<<"MODELVIEW "<<std::endl<<m[0]<<m[1]<<m[2]<<m[3]<<std::endl;
	std::cout<<m[4]<<m[5]<<m[6]<<m[7]<<std::endl;
	std::cout<<m[8]<<m[9]<<m[10]<<m[11]<<std::endl;
	std::cout<<m[12]<<m[13]<<m[14]<<m[15]<<std::endl;

	GlSdlTest1(ren, win, context);
	SDL_DestroyRenderer(ren);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

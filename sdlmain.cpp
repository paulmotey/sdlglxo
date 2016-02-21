/*
 * sdlmain.c
 *
 *  Created on: Dec 27, 2015
 *      Author: motey
 */
#include "headers/main.h"
extern int GlSdlTest1(	SDL_Renderer *ren , SDL_Window *win ,SDL_GLContext context);
extern int startSDL (void);
extern int stopSDL (void);
extern int playSound(char playName[],int channel[],int errnum,Mix_Chunk *sound, int SDLvolume,int left, int right);

int main(int argc, char** argv) {
	SDL_GLContext context; /* opengl context handle */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return 1;
}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_Window *win = SDL_CreateWindow("SDL2 OpenGL WL V0.47", 1200, 200, 512,512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; return 2;
	}
	context = SDL_GL_CreateContext(win);
	if (context == nullptr) {
		std::cout << "SDL_CreateWindow context Error: " << SDL_GetError() << std::endl; return 3;
	}
/*
 *  Create a renderer that will draw to the window,
 *  -1 specifies that we want to load whichever video driver
 *   supports the flags we're passing
Flags:
SDL_RENDERER_ACCELERATED: use hardware accelerated rendering
SDL_RENDERER_PRESENTVSYNC: renderer's present function
(update screen) to be synchronized with the monitor's refresh rate
*/
//	char playClick[]="sounds/sine.wav";
//	char playClick[]="sounds/click.wav";
	char playClick[]="sounds/thisme.wav";
	int channel=-1;
	int errnum=0;
	int* channelp=&channel;
	Mix_Chunk *sound = NULL;
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 3;
	}
	if (TTF_Init() < 0) {
		SDL_DestroyRenderer(ren);
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(win);
		return 55;
	}
	startSDL ();
	playSound(playClick,channelp,errnum,sound,18,255,255);//	float m[16];
//	glGetFloatv(GL_PROJECTION_MATRIX,m);
//	std::cout<<"PROJECTION "<<std::endl;
//			std::cout<<m[0]<<" "<<m[1]<<" "<<m[2]<<" "<<m[3]<<std::endl;
//			std::cout<<m[4]<<" "<<m[5]<<" "<<m[6]<<" "<<m[7]<<std::endl;
//			std::cout<<m[8]<<" "<<m[9]<<" "<<m[10]<<" "<<m[11]<<std::endl;
//			std::cout<<m[12]<<" "<<m[13]<<" "<<m[14]<<" "<<m[15]<<std::endl;
	GlSdlTest1(ren, win, context);
	SDL_DestroyRenderer(ren);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	stopSDL();
	SDL_Quit();
	return 0;
}

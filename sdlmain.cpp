/*
 * sdlmain.c
 *
 *  Created on: Dec 27, 2015
 *      Author: motey
 */
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#ifdef _WIN32
#include <windows.h>
#else
//Using X-window context
#endif
#include <GL/GL.h>
#include "Ants2016z.h"

//A triangle and then a texture
int GlSdlTest1(	SDL_Renderer *ren , SDL_Window *win ,SDL_GLContext context){
	double rotation=1.0;
	std::string imagePath = getResourcePath("") + "Five_colors.png";
	std::cout << imagePath <<std::endl;
	SDL_Surface *bmp = IMG_Load(imagePath.c_str());
	if (bmp == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "IMG_Load File Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 4;
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 5;
	}

	/* Clear our buffer with a red background */
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.2, 0.3);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	/* Swap our back buffer to the front */
	SDL_GL_SwapWindow(win);
	/* Wait 2 seconds */
	SDL_Delay(200);

	/* Same as above, but green */
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(win);
	SDL_Delay(600);

	/* Same as above, but blue */
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(win);
	SDL_Delay(200);



	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 70; ++i) {
		//First clear the renderer
		SDL_RenderClear(ren);
		SDL_RenderCopyEx(ren, tex, NULL, NULL,rotation,NULL,SDL_FLIP_NONE);
		SDL_RenderPresent(ren);
		rotation+=10.0;
		SDL_Delay(100);
	}
	SDL_DestroyTexture(tex);
return 0;
}

int main(int argc, char** argv) {
	SDL_GLContext context; /* Our opengl context handle */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	return 1;
}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_Window *win = SDL_CreateWindow("SDL OpenGL V2", 1200, 200, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (win == nullptr) {		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; return 2;	}
	context = SDL_GL_CreateContext(win);
/*
Create a renderer that will draw to the window,
-1 specifies that we want to load whichever video driver supports the flags we're passing
Flags:
SDL_RENDERER_ACCELERATED:
use hardware accelerated rendering
SDL_RENDERER_PRESENTVSYNC:
renderer's present function (update screen) to be synchronized with the monitor's refresh rate
*/
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 3;
	}
	GlSdlTest1(ren, win, context);
	SDL_DestroyRenderer(ren);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
//	std::cout << "SDL_Quit: any ERR ? >>" << SDL_GetError() << "<<" << std::endl;
	return 0;
}

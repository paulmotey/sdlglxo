/*
 * graphics.cpp
 *
 *  Created on: Feb 6, 2016
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
std::string getResourcePath(const std::string &subDir = "") {
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if (baseRes.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

//A triangle and then a texture
int GlSdlTest1(	SDL_Renderer *ren , SDL_Window *win ,SDL_GLContext context){
	double rotation=1.0;
	std::string imagePath = getResourcePath("") + "Five_colors.png";
//	std::cout << imagePath <<std::endl; //Diagnostic
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

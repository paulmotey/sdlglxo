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

void TestText(SDL_Renderer *ren){
try {
	TTF_Font* Sans = TTF_OpenFont("FreeSans.ttf", 24); //this opens a font style and sets a size
	if (Sans == NULL){
		std::cout << "TTF FreeSans failed to load."<<std::endl; //Diagnostic
		return;
	}
	std::cout << "TTF Sans loaded"<<std::endl; //Diagnostic
	SDL_Color White = {255, 255, 255, 255};
	// this is the color in rgb format, maxing out all would give you the color white,
	// and it will be your text's color
	std::cout << "TTF Sans surface create"<<std::endl; //Diagnostic
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "This is TTF text test.", White);
	std::cout << "TTF Sans surface created"<<std::endl; //Diagnostic
	// as TTF_RenderText_Solid could only be used on SDL_Surface
	// then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
	std::cout << "TTF Sans surface created to texture"<<std::endl; //Diagnostic
	//now you can convert it into a texture
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 40;  //controls the rect's x coordinate
	Message_rect.y = 40; // controls the rect's y coordinte
	Message_rect.w = 213; // controls the width of the rect
	Message_rect.h = 27; // controls the height of the rect
	//Mind you that (0,0) is on the top left of the window/screen,
	// think a rect as the text's box, that way it would be very simple to understand
	//Now since it's a texture, you have to put RenderCopy in your game loop area,
	// the area where the whole code executes
	int iW,iH;
	SDL_QueryTexture(Message, NULL, NULL ,&iW, &iH);

	std::cout << "TTF Texture is "<<iW<<"W x "<<iH<<"H"<<std::endl; //Diagnostic
	std::cout << "TTF Sans render"<<std::endl; //Diagnostic
	SDL_RenderCopy(ren, Message, NULL, &Message_rect);
	std::cout << "TTF Sans surface created to texture and rendered"<<std::endl; //Diagnostic
	//you put the renderer's name first, the Message,
	// the crop size(you can ignore this if you don't want to dabble with cropping),
	// and the rect which is the size and coordinate of your texture
	//   std::string("abc").substr(10); // throws std::length_error
	}
//catch( const std::exception& e ) { // reference to the base of a polymorphic object
	 catch( ... ) { // reference to the base of a polymorphic object
	std::cout << "TTF Sans surface created to texture ERROR"<<std::endl; //Diagnostic
//     std::cout << e.what(); // information from length_error printed
     return;
 }
}

void Triangles(){
  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(2.0, 2.5, -1.0);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-3.5, -2.5, -1.0);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(2.0, -4.0, 0.0);
  glEnd();
  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 1.0, 0.0);
  glVertex3f(0.50, 0.5, -1.0);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-0.5, -0.5, 1.0);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.80, -0.70, 0.0);
  glEnd();
  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(-2.0, -2.5, -2.0);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(2.5, 2.5, -1.0);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.80, -0.70, 2.0);
  glEnd();
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
	std::cout << "Start TTF init"<<std::endl; //Diagnostic
	if (TTF_Init() < 0) {
	    return 55;	// Handle error...
	}
	std::cout << "End TTF init"<<std::endl; //Diagnostic
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
	SDL_Delay(2000);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Triangles();
	SDL_GL_SwapWindow(win);
	SDL_Delay(2000);

	glClearColor(0.2, 1.0, 0.4, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	TestText(ren);
	SDL_GL_SwapWindow(win);
	SDL_Delay(4000);


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
	TTF_Quit();
return 0;
}

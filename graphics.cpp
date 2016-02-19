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
#include <iomanip>
#include <locale>
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
GLuint TextureID2 = 0;
GLuint TextureID = 0;
int testErr=0;
int keyScape=0;
double rotation=0.1;

static void process_events( void )
{
    /* Our SDL event placeholder. */
    SDL_Event event;

    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {
    	int value = event.key.keysym.scancode;
        if (value == SDLK_ESCAPE) {	testErr=3; }//Not sure about this TEST IT!

        switch( event.type ) {
        case SDL_KEYDOWN:
//    		std::cout << "KEY pressed down " << std::endl;
    		keyScape=1;
            /* Handle key presses. */
            //handle_key_down( &event.type );
            break;
        case SDL_QUIT:
    		keyScape=1;
            /* Handle quit requests (like Ctrl-c). */
            //quit_tutorial( 0 );
            break;
        }

    }

}

int Triangles(SDL_Renderer *ren, SDL_Window *win, int howLong){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
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
	SDL_RenderPresent(ren);
	SDL_GL_SwapWindow(win);
	SDL_Delay(2000);
	return 0;
}
float sizew,sizeh;

SDL_Surface* CS(Uint32 flags,int width,int height,const SDL_Surface* display)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& fmt = *(display->format);
  return SDL_CreateRGBSurface(flags,width,height,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}
Uint8 get_pixel32(SDL_Surface *surface, int x, int y){
	//Convert pixels to 32 bits
	Uint8 *pixels = (Uint8*)surface->pixels;

	return pixels[(3*y*surface->w) + x];
}
int TestText(SDL_Renderer *ren,SDL_Window *win, std::string text,int howLong){
	glColor4f(1.0,1.0,1.0,1.0);
//	int iW,iH;
	SDL_Color White = {255, 255, 255, 255}; //Text color
//    SDL_Color foregroundColor = { 255, 255, 255 ,255};
    SDL_Color backgroundColor = { 155, 155, 255 ,255};
//    SDL_Color backgroundColor2 = { 255, 255, 255 ,255};

	glClearColor(0.0, 0.00, 0.0, 1.0);
//	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_RenderClear(ren);
	if (TextureID2==0){
		TTF_Font* Sans = TTF_OpenFont("FreeSans.ttf",24);
		if (Sans == NULL){
			std::cout << "TTF FreeSans failed to load."<<std::endl; //Diagnostic
			return 1;
		}
		std::cout<<" 1 "<< std::endl;
		SDL_Surface* sSans = TTF_RenderText_Shaded(Sans,text.c_str(), White,backgroundColor);
//		SDL_Surface* sSans = TTF_RenderText_Solid(Sans,text.c_str(), White);
		std::cout<<" 2 "<< std::endl;
//		SDL_Surface* sSans2 = CS(0,128,128,sSans);
		SDL_Surface* sSans2 = SDL_CreateRGBSurface( 0,1024,32,24,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		std::cout<<" 3 "<<sSans->format->Rmask<<std::dec<<static_cast<int>(sSans2->format->BytesPerPixel)<<std::dec<<std::endl;
//		int Width=256;
//		int Height=256;
//		SDL_Surface* sSans2;
//		SDL_Rect srcrect;
		SDL_Rect dstrect;
//		srcrect.x=0;
//		srcrect.y=0;
//		srcrect.w=sSans->w;
//		srcrect.h=sSans->h;
		dstrect.x=0;
		dstrect.y=0;
		dstrect.w=sSans2->w;//256;
		dstrect.h=sSans2->h;//256;
//		Uint8 * pixel = (Uint8*)sSans->pixels;
		for (int i =0; i<12; i++){
			for (int j =0; j<10; j++){
			std::cout <<"-"<<static_cast<int>(get_pixel32(sSans,j,i))<<std::hex<<"-";
			}
			std::cout<< std::endl;
		}
//		SDL_BlitSurface
//		SDL_BlitScaled(sSans,&srcrect,sSans2,&dstrect);
		int foo=SDL_BlitSurface(sSans,NULL,sSans2,&dstrect);

		std::cout<<" 4 "<<dstrect.w<<" x "<<dstrect.h<<" foo "<<foo<< std::endl;
		for (int i =0; i<10; i++){
			for (int j =0; j<10; j++){
			std::cout <<"-"<<static_cast<int>(get_pixel32(sSans2,j,i))<<std::hex<<"-";
			}
			std::cout<< std::endl;
		}
		glGenTextures(1, &TextureID2);
		glBindTexture(GL_TEXTURE_2D, TextureID2);
		int Mode = GL_RGB;
		if(sSans2->format->BytesPerPixel == 4) {
			Mode = GL_RGBA;
			std::cout <<sSans->w<<" RGBAx "<<sSans->h<<"  "<<glGetError()<<" "<< std::endl;
		}
		if(sSans->format->BytesPerPixel == 4) {
			std::cout <<sSans2->w<<" SANS RGBA "<<sSans2->h<<"  "<<glGetError()<<" "<< std::endl;
		}
		std::cout<<" 5 "<< std::endl;
		std::cout <<sSans2->w<<" x "<<sSans2->h<<"  "<<glGetError()<<" "<< std::endl;
		std::cout <<sSans->w<<" x "<<sSans->h<<"  "<<glGetError()<<" "<< std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, sSans2->w, sSans2->h, 0, Mode, GL_UNSIGNED_BYTE, sSans2->pixels);
	 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		std::cout<<" 6 "<< std::endl;
		sizew=sSans2->w;
		sizeh=sSans2->h;
		SDL_FreeSurface(sSans);
		std::cout <<sizew<<" x "<<sizeh<<" "<<TextureID2<<" "<<glGetError()<< std::endl;
	}
//	0.0,-0.20,-0.50	//Any other glTex* stuff here
	float originx,originy,originz,delta;
	originx=-0.0;
	originy=0.0;
	originz=-0.50;
	delta=0.0;
	sizew=2.0;
	sizeh=0.1061250;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureID2);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
/*
	glBegin(GL_QUADS);
	//side F
	    glTexCoord2f(0.0,0.0);
	glVertex3f(originx,originy,originz+delta);
	    glTexCoord2f(1.0,0.0);
	glVertex3f(originx+sizew,originy,originz+delta);
	    glTexCoord2f(1.0,1.0);
	glVertex3f(originx+sizew,originy+sizeh,originz+delta);
	    glTexCoord2f(0.0,1.0);
	glVertex3f(originx,originy+sizeh,originz+delta);
	glEnd();
*/
//	glRotatef(180.0,1.0,0.0,0.0);
/*
	glBegin(GL_QUADS);
	//side F
	    glTexCoord2f(0.0,0.0);
	glVertex3f(originx,originy,originz+delta);
	    glTexCoord2f(1.0,0.0);
	glVertex3f(originx+sizew,originy,originz+delta);
	    glTexCoord2f(1.0,1.0);
	glVertex3f(originx+sizew,originy+sizeh,originz+delta);
	    glTexCoord2f(0.0,1.0);
	glVertex3f(originx,originy+sizeh,originz+delta);
	glEnd();
*/
	originy=01.0;
	originx=-1.0;
	glBindTexture(GL_TEXTURE_2D, TextureID2);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//	glRotatef(180,1.0,0.0,0.0);

	glBegin(GL_QUADS);
	//side F
	    glTexCoord2f(0.0,0.0);
	glVertex3f(originx,originy,originz+delta);
	    glTexCoord2f(1.0,0.0);
	glVertex3f(originx+sizew,originy,originz+delta);
	    glTexCoord2f(1.0,1.0);
	glVertex3f(originx+sizew,originy-sizeh,originz+delta);
	    glTexCoord2f(0.0,1.0);
	glVertex3f(originx,originy-sizeh,originz+delta);
	glEnd();

//	glRotatef(180,0.0,1.0,0.0);
/*
	glBegin(GL_QUADS);
	//side F
	    glTexCoord2f(0.0,0.0);
	glVertex3f(originx,originy,originz+delta);
	    glTexCoord2f(1.0,0.0);
	glVertex3f(originx+sizew,originy,originz+delta);
	    glTexCoord2f(1.0,1.0);
	glVertex3f(originx+sizew,originy+sizeh,originz+delta);
	    glTexCoord2f(0.0,1.0);
	glVertex3f(originx,originy+sizeh,originz+delta);
	glEnd();
*/
//	SDL_RenderCopy(ren, Message, NULL, &Message_rect);
	SDL_RenderPresent(ren);
#ifdef _WIN32
	SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
	SDL_Delay(howLong);
	glColor4f(1.0,1.0,1.0,1.0);
	glClearColor(1.0,1.0,1.0,1.0);
//		SDL_DestroyTexture(Message);
		return 0;
}
//Rotating Texture
int Rotex(SDL_Renderer *ren, SDL_Window *win, int howLong) {
	double rotation=1.0;
	std::string imagePath = getResourcePath("") + "Five_colors.png";
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_RenderClear(ren);
	SDL_Surface *bmp = IMG_Load(imagePath.c_str());
	if (bmp == nullptr) {
//		SDL_DestroyRenderer(ren);
//		SDL_DestroyWindow(win);
		std::cout << "IMG_Load File Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
		return 4;
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
//		SDL_DestroyRenderer(ren);
//		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
		return 5;
	}
	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < howLong; ++i) {
		//First clear the renderer
		SDL_RenderClear(ren);
		SDL_RenderCopyEx(ren, tex, NULL, NULL,rotation,NULL,SDL_FLIP_NONE);
		SDL_RenderPresent(ren);
//		SDL_GL_SwapWindow(win);
		rotation+=1.0;
		SDL_Delay(10);
	}
	SDL_RenderCopyEx(ren, tex, NULL, NULL,0.0,NULL,SDL_FLIP_NONE);
	SDL_DestroyTexture(tex);
	return 0;

}
int blackTriangle(SDL_Renderer *ren, SDL_Window *win, int howLong){
	/* Clear our buffer with a red background */
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_RenderClear(ren);
	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.2, 0.3);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();	/* Swap our back buffer to the front */
	SDL_RenderPresent(ren);
	SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
	SDL_Delay(howLong);
	return 0;

}

int drawLine1(SDL_Renderer *ren, SDL_Window *win, int howLong){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(3.0);
	SDL_RenderClear(ren);
	  glBegin(GL_LINES);
	  glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	  glVertex3f(-1.0f, -1.0f, -1.0f);
	  glVertex3f(1.0f, 1.0f, 1.0f);
	  glEnd();
	  glBegin(GL_LINES);
	  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	  glVertex3f(-1.0f, 1.0f, -1.0f);
	  glVertex3f(1.0f, -1.0f, 1.0f);
	  glEnd();
	  glBegin(GL_LINES);
	  glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	  glVertex3f(-1.0f, 0.0f, -1.0f);
	  glVertex3f(1.0f, 0.0f, 1.0f);
	  glEnd();
	SDL_RenderPresent(ren);
	SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
	SDL_Delay(howLong);
	return 0;

}
void drawLine2(){
  glColor4f(0.80f, 0.80f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  glVertex3f(-10.0f, -10.0f, -10.0f);
  glVertex3f(10.0f, 10.0f, 10.0f);
  glEnd();

}
int drawBoxPLS(SDL_Renderer *ren, SDL_Window *win, int howLong,float size, int faces, int types, float originx, float originy , float originz){
/*
 * rotation of points for texture matching
 * 1--------2
 * |        |
 * |        |
 * |        |
 * |        |
 * 4--------3
 */
	glClearColor(0.30, 0.30, 0.30, 1.0);
	float delta=0.03;
	glLineWidth(3.0);
	glPointSize(4.0);
	if (types & 1){
		for (int i = 0; i < howLong; ++i) {
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_RenderClear(ren);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glBegin(GL_POINTS);
			//side F
			glVertex3f(originx,originy,originz+delta);
			glVertex3f(originx+size,originy,originz+delta);
			glVertex3f(originx+size,originy+size,originz+delta);
			glVertex3f(originx,originy+size,originz+delta);

			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			//side R
			glVertex3f(originx+size+delta,originy,originz);
			glVertex3f(originx+size+delta,originy,originz+size);
			glVertex3f(originx+size+delta,originy+size,originz+size);
			glVertex3f(originx+size+delta,originy+size,originz);

			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			//side L
			glVertex3f(originx+delta,originy,originz+size);
			glVertex3f(originx+delta,originy,originz);
			glVertex3f(originx+delta,originy+size,originz);
			glVertex3f(originx+delta,originy+size,originz+size);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			//side B
			glVertex3f(originx+size,originy,originz+size+delta);
			glVertex3f(originx,originy,originz+size+delta);
			glVertex3f(originx,originy+size,originz+size+delta);
			glVertex3f(originx+size,originy+size,originz+size+delta);

			glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
			//side D
			glVertex3f(originx,originy+size+delta,originz);
			glVertex3f(originx+size,originy+size+delta,originz);
			glVertex3f(originx+size,originy+size+delta,originz+size);
			glVertex3f(originx,originy+size+delta,originz+size);

			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			//side U
			glVertex3f(originx,originy+delta,originz+size);
			glVertex3f(originx+size,originy+delta,originz+size);
			glVertex3f(originx+size,originy+delta,originz);
			glVertex3f(originx,originy+delta,originz);


			glEnd();
			//  		SDL_RenderCopyEx(ren, tex, NULL, NULL,rotation,NULL,SDL_FLIP_NONE);
			//  		SDL_RenderPresent(ren);
			//		SDL_GL_SwapWindow(win);
//			rotation+=0.010;
			glRotatef(rotation,1.0,0.5,0.3);
			SDL_RenderPresent(ren);
#ifdef _WIN32
			SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
			SDL_Delay(10);
			process_events();
			if (keyScape>0){break;}
		}
	}
	rotation=0.05;
	delta=0.0;
	if (types & 2){
		for (int i = 0; i < howLong; ++i) {
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_RenderClear(ren);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(rotation,1.0,0.5,0.25);
			glBegin(GL_LINES);
			//side F
			glVertex3f(originx,originy,originz+delta);
			glVertex3f(originx+size,originy,originz+delta);
			glVertex3f(originx+size,originy,originz+delta);
			glVertex3f(originx+size,originy+size,originz+delta);
			glVertex3f(originx+size,originy+size,originz+delta);
			glVertex3f(originx,originy+size,originz+delta);
			glVertex3f(originx,originy+size,originz+delta);
			glVertex3f(originx,originy,originz+delta);

			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			//side R
			glVertex3f(originx+size+delta,originy,originz);
			glVertex3f(originx+size+delta,originy,originz+size);
			glVertex3f(originx+size+delta,originy,originz+size);
			glVertex3f(originx+size+delta,originy+size,originz+size);
			glVertex3f(originx+size+delta,originy+size,originz+size);
			glVertex3f(originx+size+delta,originy+size,originz);
			glVertex3f(originx+size+delta,originy+size,originz);
			glVertex3f(originx+size+delta,originy,originz);

			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			//side L
			glVertex3f(originx+delta,originy,originz+size);
			glVertex3f(originx+delta,originy,originz);
			glVertex3f(originx+delta,originy,originz);
			glVertex3f(originx+delta,originy+size,originz);
			glVertex3f(originx+delta,originy+size,originz);
			glVertex3f(originx+delta,originy+size,originz+size);
			glVertex3f(originx+delta,originy+size,originz+size);
			glVertex3f(originx+delta,originy,originz+size);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			//side B
			glVertex3f(originx+size,originy,originz+size+delta);
			glVertex3f(originx,originy,originz+size+delta);
			glVertex3f(originx,originy,originz+size+delta);
			glVertex3f(originx,originy+size,originz+size+delta);
			glVertex3f(originx,originy+size,originz+size+delta);
			glVertex3f(originx+size,originy+size,originz+size+delta);
			glVertex3f(originx+size,originy+size,originz+size+delta);
			glVertex3f(originx+size,originy,originz+size+delta);

			glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
			//side D
			glVertex3f(originx,originy+size+delta,originz);
			glVertex3f(originx+size,originy+size+delta,originz);
			glVertex3f(originx+size,originy+size+delta,originz);
			glVertex3f(originx+size,originy+size+delta,originz+size);
			glVertex3f(originx+size,originy+size+delta,originz+size);
			glVertex3f(originx,originy+size+delta,originz+size);
			glVertex3f(originx,originy+size+delta,originz+size);
			glVertex3f(originx,originy+size+delta,originz);

			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			//side U
			glVertex3f(originx,originy+delta,originz+size);
			glVertex3f(originx+size,originy+delta,originz+size);
			glVertex3f(originx+size,originy+delta,originz+size);
			glVertex3f(originx+size,originy+delta,originz);
			glVertex3f(originx+size,originy+delta,originz);
			glVertex3f(originx,originy+delta,originz);
			glVertex3f(originx,originy+delta,originz);
			glVertex3f(originx,originy+delta,originz+size);


			glEnd();
			//  		SDL_RenderCopyEx(ren, tex, NULL, NULL,rotation,NULL,SDL_FLIP_NONE);
			//  		SDL_RenderPresent(ren);
			//		SDL_GL_SwapWindow(win);
//			rotation+=0.010;
			glRotatef(rotation,1.0,0.5,0.3);
			SDL_RenderPresent(ren);
#ifdef _WIN32
			SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
			SDL_Delay(10);
			process_events();
			if (keyScape>0){break;}
		}
	}
	rotation=0.05;
	if (types & 4){
//		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CW);
		glEnable(GL_CULL_FACE);
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_TEXTURE_2D);
		for (int i = 0; i < howLong; ++i) {
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_RenderClear(ren);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(rotation,1.0,0.5,0.3);
			glBegin(GL_QUADS);
			//side F
			glVertex3f(originx,originy,originz+delta);
			glVertex3f(originx+size,originy,originz+delta);
			glVertex3f(originx+size,originy+size,originz+delta);
			glVertex3f(originx,originy+size,originz+delta);

			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			//side R
			glVertex3f(originx+size+delta,originy,originz);
			glVertex3f(originx+size+delta,originy,originz+size);
			glVertex3f(originx+size+delta,originy+size,originz+size);
			glVertex3f(originx+size+delta,originy+size,originz);

			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			//side L
			glVertex3f(originx+delta,originy,originz+size);
			glVertex3f(originx+delta,originy,originz);
			glVertex3f(originx+delta,originy+size,originz);
			glVertex3f(originx+delta,originy+size,originz+size);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			//side B
			glVertex3f(originx+size,originy,originz+size+delta);
			glVertex3f(originx,originy,originz+size+delta);
			glVertex3f(originx,originy+size,originz+size+delta);
			glVertex3f(originx+size,originy+size,originz+size+delta);

			glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
			//side D
			glVertex3f(originx,originy+size+delta,originz);
			glVertex3f(originx+size,originy+size+delta,originz);
			glVertex3f(originx+size,originy+size+delta,originz+size);
			glVertex3f(originx,originy+size+delta,originz+size);

			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			//side U
			glVertex3f(originx,originy+delta,originz+size);
			glVertex3f(originx+size,originy+delta,originz+size);
			glVertex3f(originx+size,originy+delta,originz);
			glVertex3f(originx,originy+delta,originz);


			glEnd();
			//  		SDL_RenderCopyEx(ren, tex, NULL, NULL,rotation,NULL,SDL_FLIP_NONE);
			//  		SDL_RenderPresent(ren);
			//		SDL_GL_SwapWindow(win);
//			rotation+=0.010;
//			glRotatef(rotation,1.0,0.5,0.3);
			SDL_RenderPresent(ren);
#ifdef _WIN32
			SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
			SDL_Delay(10);
			process_events();
			if (keyScape>0){break;}
		}
	}
	rotation=0.5;
	delta=0.0;
	if (types & 8){
		std::string imagePath = getResourcePath("") + "Five_colors.png";
		SDL_Surface *bmp = IMG_Load(imagePath.c_str());
		if (bmp == nullptr) {
			std::cout << "IMG_Load File Error: " << SDL_GetError() << std::endl;
			return 4;
		}

//		GLuint TextureID = 0;

		// You should probably use CSurface::OnLoad ... ;)
		//-- and make sure the Surface pointer is good!

		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		int Mode = GL_RGB;

		if(bmp->format->BytesPerPixel == 4) {
		    Mode = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, Mode, bmp->w, bmp->h, 0, Mode, GL_UNSIGNED_BYTE, bmp->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SDL_FreeSurface(bmp);

		//Any other glTex* stuff here
//		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_COLOR_MATERIAL);
		glFrontFace(GL_CW);
//		glDisable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
//		float tw=1.0;
//		float th=1.0;
        glBindTexture(GL_TEXTURE_2D, TextureID);
//        SDL_GL_BindTexture(tex, &tw, &th);
		for (int i = 0; i < howLong; ++i) {
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_RenderClear(ren);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
//			glRotatef(rotation,1.0,0.5,0.3);
			glBegin(GL_QUADS);
			//side F
 		    glTexCoord2f(0.0,0.0);
			glVertex3f(originx,originy,originz+delta);
 		    glTexCoord2f(1.0,0.0);
			glVertex3f(originx+size,originy,originz+delta);
 		    glTexCoord2f(1.0,1.0);
			glVertex3f(originx+size,originy+size,originz+delta);
 		    glTexCoord2f(0.0,1.0);
			glVertex3f(originx,originy+size,originz+delta);

			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			//side R
 		    glTexCoord2f(0.0,0.0);
			glVertex3f(originx+size+delta,originy,originz);
 		    glTexCoord2f(1.0,0.0);
			glVertex3f(originx+size+delta,originy,originz+size);
 		    glTexCoord2f(1.0,1.0);
			glVertex3f(originx+size+delta,originy+size,originz+size);
 		    glTexCoord2f(0.0,1.0);
			glVertex3f(originx+size+delta,originy+size,originz);

			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			//side L
		    glTexCoord2f(0.0,0.0);
			glVertex3f(originx+delta,originy,originz+size);
		    glTexCoord2f(1.0,0.0);
			glVertex3f(originx+delta,originy,originz);
		    glTexCoord2f(1.0,1.0);
			glVertex3f(originx+delta,originy+size,originz);
		    glTexCoord2f(0.0,1.0);
			glVertex3f(originx+delta,originy+size,originz+size);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			//side B
		    glTexCoord2f(0.0,0.0);
			glVertex3f(originx+size,originy,originz+size+delta);
		    glTexCoord2f(1.0,0.0);
			glVertex3f(originx,originy,originz+size+delta);
		    glTexCoord2f(1.0,1.0);
			glVertex3f(originx,originy+size,originz+size+delta);
		    glTexCoord2f(0.0,1.0);
			glVertex3f(originx+size,originy+size,originz+size+delta);

			glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
			//side D
		    glTexCoord2f(0.0,0.0);
			glVertex3f(originx,originy+size+delta,originz);
		    glTexCoord2f(1.0,0.0);
			glVertex3f(originx+size,originy+size+delta,originz);
		    glTexCoord2f(1.0,1.0);
			glVertex3f(originx+size,originy+size+delta,originz+size);
		    glTexCoord2f(0.0,1.0);
			glVertex3f(originx,originy+size+delta,originz+size);

			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			//side U
		    glTexCoord2f(0.0,0.0);
			glVertex3f(originx,originy+delta,originz+size);
		    glTexCoord2f(1.0,0.0);
			glVertex3f(originx+size,originy+delta,originz+size);
		    glTexCoord2f(1.0,1.0);
			glVertex3f(originx+size,originy+delta,originz);
		    glTexCoord2f(0.0,1.0);
			glVertex3f(originx,originy+delta,originz);


			glEnd();
			//  		SDL_RenderCopyEx(ren, tex, NULL, NULL,rotation,NULL,SDL_FLIP_NONE);
			//  		SDL_RenderPresent(ren);
			//		SDL_GL_SwapWindow(win);
			rotation+=0.010;
			glRotatef(rotation,1.0,0.50,0.0);
			SDL_RenderPresent(ren);
#ifdef _WIN32
			SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
			SDL_Delay(10);
			process_events();
			if (keyScape>0){break;}
		}
//		rotation=0.0;
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_RenderClear(ren);
		glRotatef(0.0,0.0,0.0,0.0);
		SDL_RenderPresent(ren);
#ifdef _WIN32
		SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
//	    if (tex) {
//	        SDL_GL_UnbindTexture(tex);
//	    }
//		SDL_DestroyTexture(tex);
		glDisable(GL_TEXTURE_2D);

	}
	return 0;
}

//A triangle, text and then a texture
int GlSdlTest1(	SDL_Renderer *ren , SDL_Window *win ,SDL_GLContext context){
	float m[16];
	if (TTF_Init() < 0) {return 55;}
	glGetFloatv(GL_PROJECTION_MATRIX,m);
	std::cout<<"PROJECTION "<<std::endl;
	std::cout<<std::setw(2)<<m[0]<<"\t "<<std::setw(2)<<m[1]<<"\t "<<m[2]<<"\t "<<m[3]<<std::endl;
	std::cout<<m[4]<<"\t "<<m[5]<<"\t "<<m[6]<<"\t "<<m[7]<<std::endl;
	std::cout<<m[8]<<"\t "<<m[9]<<"\t "<<m[10]<<"\t "<<m[11]<<std::endl;
	std::cout<<m[12]<<"\t "<<m[13]<<"\t "<<m[14]<<"\t "<<m[15]<<std::endl;
//	glGetFloatv(GL_MODELVIEW_MATRIX,m);
//	std::cout<<m[0]<<m[1]<<m[2]<<m[3]<<std::endl;
//	std::cout<<m[4]<<m[5]<<m[6]<<m[7]<<std::endl;
//	std::cout<<m[8]<<m[9]<<m[10]<<m[11]<<std::endl;
//	std::cout<<m[12]<<m[13]<<m[14]<<m[15]<<std::endl;

	while ((keyScape == 0) && (testErr ==0)){
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
		testErr=blackTriangle(ren,win,200);
		testErr=drawLine1(ren,win,400);
		testErr=Triangles(ren, win,  200);
		testErr=TestText(ren, win, "Simple variable size TTF text Version 0.46 24pt (16/17 px)",2000);
		testErr=drawBoxPLS(ren, win,100,0.5,6,8,0.0,-0.20,-0.50);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
		testErr=Rotex(ren, win, 100);
		testErr=TestText(ren, win, "Simple variable size TTF text Version 0.45 14pt (16/17 px)",2000);
glPopMatrix();
		process_events();
	}
	TTF_Quit();
	return 0;
}

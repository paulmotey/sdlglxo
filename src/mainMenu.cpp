/*
 * mainMenu.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: motey
 */




/*
*/

#include "../headers/main.h"
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


Uint8 get_pixel32b(SDL_Surface *surface, int x, int y){	//Convert pixels to 32 bits
	Uint8 *pixels = (Uint8*)surface->pixels;
	return pixels[(3*y*surface->w) + x];
}


int TestMenu(SDL_Renderer *ren,SDL_Window *win, std::string text,int howLong){
	std::string font ("FreeSans.ttf");
	int fontSize=20;
	float sizew,sizeh;
	GLuint TextureID3 = 0;

	SDL_Color TextBackgroundColor = {255, 255, 255, 255}; //Text color
    SDL_Color TextColor = { 188, 0, 22 ,255};
	SDL_Rect dstrect;

	glClearColor(0.50, 0.50, 0.50, 1.0);
	glColor4f(1.0,1.0,1.0,1.0);

	float originx,originy,originz,delta;
	int Mode = GL_RGB;
	float Twidth=1.0;
	float TQwidth=1.0;



	glClear(GL_COLOR_BUFFER_BIT);
	SDL_RenderClear(ren);

	if (TextureID3==0){
		TTF_Font* Sans = TTF_OpenFont(font.c_str(),fontSize);
		if (Sans == NULL){
			std::cout << "TTF FreeSans failed to load."<<std::endl; //Diagnostic
			return 1;
		}
		SDL_Surface* sSans = TTF_RenderText_Shaded(Sans,text.c_str(), TextColor,TextBackgroundColor);
//		SDL_Surface* sSans = TTF_RenderText_Solid(Sans,text.c_str(), White);
		SDL_Surface* sSans2 = SDL_CreateRGBSurface( 0,1024,32,24,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		dstrect.x=2;
		dstrect.y=2;
		dstrect.w=sSans2->w-4;
		dstrect.h=sSans2->h-4;
		SDL_BlitSurface(sSans,NULL,sSans2,&dstrect);
		glGenTextures(1, &TextureID3);
		glBindTexture(GL_TEXTURE_2D, TextureID3);
		if(sSans2->format->BytesPerPixel == 4) {
			Mode = GL_RGBA;
			std::cout <<sSans->w<<" RGBAx "<<sSans->h<<"  "<<glGetError()<<" "<< std::endl;
		}
		if(sSans->format->BytesPerPixel == 4) {
			std::cout <<sSans2->w<<" SANS RGBA "<<sSans2->h<<"  "<<glGetError()<<" "<< std::endl;
		}
		Twidth=1.01*((float)(sSans->w)/(float)(sSans2->w));
		TQwidth=1.0*((float)(sSans->w)/(float)(512));
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, sSans2->w, sSans2->h, 0, Mode, GL_UNSIGNED_BYTE, sSans2->pixels);
	 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		sizew=sSans2->w;
		sizeh=sSans2->h;
		SDL_FreeSurface(sSans);
	}
	originz=-0.50;
	delta=0.0;
	sizew=TQwidth;	// or 2.0;
	sizeh=(float)(60.0/512.0);	//0.1061250;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TextureID3);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	originy=1.0;
	originx=-1.0;
	glBindTexture(GL_TEXTURE_2D, TextureID3);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	    glTexCoord2f(0.0,0.0);
	glVertex3f(originx,originy,originz+delta);
	    glTexCoord2f(Twidth,0.0);
	glVertex3f(originx+sizew,originy,originz+delta);
	    glTexCoord2f(Twidth,1.0);
	glVertex3f(originx+sizew,originy-sizeh,originz+delta);
	    glTexCoord2f(0.0,1.0);
	glVertex3f(originx,originy-sizeh,originz+delta);
	glEnd();
	SDL_RenderPresent(ren);
#ifdef _WIN32
	SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
	SDL_Delay(howLong);
	glColor4f(1.0,1.0,1.0,1.0);
	glClearColor(1.0,1.0,1.0,1.0);
	glDeleteTextures(1,&TextureID3);
	TextureID3=0;
	return 0;
}


/*
 * mainMenu.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: motey
 */




/*
 * Menu text for each item
 * Pointer to code to execute
 * Which is selected
 * Escape exits sub task and returns to main task
 * Select by position on screen
 * Map screen to element
 * Basic screen is 512x512
*/

#include "../headers/main.h"
extern unsigned int texture[256];

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


Uint8 get_pixel32b(SDL_Surface *surface, int x, int y){	//Convert pixels to 32 bits
	Uint8 *pixels = (Uint8*)surface->pixels;
	return pixels[(3*y*surface->w) + x];
}

struct menuItem
{
	int swidth;
	int w;
    int h;
    float sizew;
    std::string name;
    std::string item;
};

menuItem menuItems[16];
int menuTextures=84; //84-99 =16
std::string menuFont ("FreeSans.ttf");
//std::string menuFont ("FreeMono.ttf");

int menuFontSize=20;
int borderSize=0;

SDL_Color menuTextBackgroundColor = {255, 255, 255, 255}; //Text color
SDL_Color menuTextColor = { 8, 10, 22 ,255};

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int buildMenu(){
	menuItems[0].name="Item 1";
	int sizew,sizeh;
	int i;
	std::string mi;
	const char *mi6;
	SDL_Rect dstrect;
	for (i=0;i<16;i++){
		mi="  [ "+patch::to_string(i+1)\
				+" ] Test "
				+patch::to_string(i)+std::string(i*6, '*')+"  ["+patch::to_string(i)+"] end .";
		menuItems[i].name=mi;
		mi6=mi.c_str();
		menuItems[i].swidth=strlen(mi6);
//		mi.std::string::c_str().length;

	}
	int Mode = GL_RGB;
//	float Twidth=1.0;
//	float TQwidth=1.0;
	for ( i=0; i<16; i++){
		TTF_Font* Sans = TTF_OpenFont(menuFont.c_str(),menuFontSize);
			if (Sans == NULL){
				std::cout << "Menu font "<<menuFont.c_str()<<" failed to load."<<std::endl;
				return 1;
			}
		SDL_Surface* sSans = TTF_RenderText_Shaded(Sans,menuItems[i].name.c_str(), menuTextColor,menuTextBackgroundColor);
//		SDL_Surface* sSans = TTF_RenderText_Solid(Sans,text.c_str(), White);
		SDL_Surface* sSans2 = SDL_CreateRGBSurface( 0,1024,32,24,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		dstrect.x=borderSize;
		dstrect.y=borderSize;
		dstrect.w=sSans2->w;
		dstrect.h=sSans2->h;
		SDL_BlitSurface(sSans,NULL,sSans2,&dstrect);
		glBindTexture(GL_TEXTURE_2D, texture[i+menuTextures]);
		if(sSans2->format->BytesPerPixel == 4) {
			Mode = GL_RGBA;
			std::cout <<sSans->w<<" RGBAx "<<sSans->h<<"  "<<glGetError()<<" "<< std::endl;
		}
		if(sSans->format->BytesPerPixel == 4) {
			std::cout <<sSans2->w<<" SANS RGBA "<<sSans2->h<<"  "<<glGetError()<<" "<< std::endl;
		}

		menuItems[i].sizew=1.02*((float)(sSans->w)/(float)(sSans2->w));

//		TQwidth=1.0*((float)(sSans->w)/(float)(512));
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, sSans2->w, sSans2->h, 0, Mode, GL_UNSIGNED_BYTE, sSans2->pixels);
	 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		sizew=sSans2->w;
		sizeh=sSans2->h;

		menuItems[i].w = sizew;
		menuItems[i].h = sizeh;
		SDL_FreeSurface(sSans);
	}
	return 0;
}


int TestMenu(SDL_Renderer *ren,SDL_Window *win, std::string text,int howLong){
//	std::string font ("FreeSans.ttf");
	float sizew,sizeh;
	int i=0;

	glClearColor(0.50, 0.50, 0.50, 1.0);
	glColor4f(1.0,1.0,1.0,1.0);

	float originx,originy,originz,delta;
//	int Mode = GL_RGB;
	float Twidth=menuItems[i].sizew;
//	float TQwidth=1.0;



	glClear(GL_COLOR_BUFFER_BIT);
	SDL_RenderClear(ren);

//	TQwidth=1.0*((float)(sSans->w)/(float)(512));
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	originy=1.0;
	originx=-1.0;
	originz=-0.50;
	delta=0.0;
	sizeh=(float)(menuFontSize/256.0);	//0.1061250;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
float H=menuFontSize/(25.0-borderSize);
	for (i=0;i<16;i++){
		sizew=1.0*((float)menuItems[i].swidth/60.0);	//TQwidth;	// or 2.0;
//		std::cout<<((float)menuItems[i].swidth/50.0)<<std::endl;	//TQwidth;	// or 2.0;
		originy=1.0-i*sizeh;
		Twidth=1.0*menuItems[i].sizew;
		glBindTexture(GL_TEXTURE_2D, texture[84+i]);
		glBegin(GL_QUADS);
		    glTexCoord2f(0.0,0.0);
		glVertex3f(originx,originy,originz+delta);
		    glTexCoord2f(Twidth,0.0);
		glVertex3f(originx+sizew,originy,originz+delta);
		    glTexCoord2f(Twidth,H);
		glVertex3f(originx+sizew,originy-sizeh,originz+delta);
		    glTexCoord2f(0.0,H);
		glVertex3f(originx,originy-sizeh,originz+delta);
		glEnd();
	}


	SDL_RenderPresent(ren);
#ifdef _WIN32
	SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
	SDL_Delay(howLong);
	glColor4f(1.0,1.0,1.0,1.0);
	glClearColor(1.0,1.0,1.0,1.0);
	return 0;
}


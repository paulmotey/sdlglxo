/*
 * graphics.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: motey
 */
#include "headers/main.h"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

GLuint TextureID2 = 0;
GLuint TextureID = 0;
int testErr=0;
int keyScape=0;
double rotation=0.1;
int debug=0;
float sizew,sizeh;
std::string font ("FreeMono.ttf");
//char font="FreeSans.ttf";
int fontSize=26;
int VersionMajor=0;
int VersionMinor=51;

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

static void process_events( void ){
    SDL_Event event;
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ){
            	case SDLK_ESCAPE:
            		keyScape=1; //EXIT
            		break;
            	case SDLK_LEFT:
            		std::cout << "<Left" << std::endl;
            		break;
                case SDLK_RIGHT:
            		std::cout << "Right> " << std::endl;
                    break;
                case SDLK_UP:
            		std::cout << "^Up^" << std::endl;
                    break;
                case SDLK_DOWN:
            		std::cout << "\\Down/" << std::endl;
                    break;
                default:
                    break;
            }
            break;
        case SDL_QUIT:
    		keyScape=1;
            /* Handle quit requests (like Ctrl-c). */
            break;
        case SDL_MOUSEBUTTONDOWN:
//            std::cout<<"Mouse button pressed"<<std::endl;
            break;
        case SDL_MOUSEMOTION:
//            std::cout<<"Mouse move to "<<event.motion.x<<" "<<event.motion.y <<std::endl;
            break;
        }
    }
}

int Triangles(SDL_Renderer *ren, SDL_Window *win, int howLong){
	glDisable(GL_BLEND);
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
#ifdef _WIN32
	SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
	SDL_Delay(howLong);
	return 0;
}

/*
 * reference code 'create sdl surface'
SDL_Surface* CS(Uint32 flags,int width,int height,const SDL_Surface* display)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& fmt = *(display->format);
  return SDL_CreateRGBSurface(flags,width,height,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}
*/
Uint8 get_pixel32(SDL_Surface *surface, int x, int y){	//Convert pixels to 32 bits
	Uint8 *pixels = (Uint8*)surface->pixels;
	return pixels[(3*y*surface->w) + x];
}


static int TestText(SDL_Renderer *ren,SDL_Window *win, std::string text,int howLong){
	SDL_Color White = {255, 255, 255, 255}; //Text color
    SDL_Color backgroundColor = { 55, 55, 55 ,255};
	SDL_Rect dstrect;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor4f(1.0,1.0,1.0,1.0);

	float originx,originy,originz,delta;
	int Mode = GL_RGB;
	int i,j;
	float Twidth=1.0;
	float TQwidth=1.0;



	glClear(GL_COLOR_BUFFER_BIT);
	SDL_RenderClear(ren);

	if (TextureID2==0){
		TTF_Font* Sans = TTF_OpenFont(font.c_str(),fontSize);
		if (Sans == NULL){
			std::cout << "TTF FreeSans failed to load."<<std::endl; //Diagnostic
			return 1;
		}
		SDL_Surface* sSans = TTF_RenderText_Shaded(Sans,text.c_str(), White,backgroundColor);
//		SDL_Surface* sSans = TTF_RenderText_Solid(Sans,text.c_str(), White);
		SDL_Surface* sSans2 = SDL_CreateRGBSurface( 0,1024,32,24,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		dstrect.x=2;
		dstrect.y=2;
		dstrect.w=sSans2->w-4;
		dstrect.h=sSans2->h-4;
		if(debug>0){
			for ( i =0; i<12; i++){
				for ( j =0; j<10; j++){
					std::cout <<"-"<<static_cast<int>(get_pixel32(sSans,j,i))<<std::hex<<"-";
				}
				std::cout<< std::endl;
			}
		}
		SDL_BlitSurface(sSans,NULL,sSans2,&dstrect);
		if(debug>0){
			for (i =0; i<10; i++){
				for ( j =0; j<10; j++){
					std::cout <<"-"<<static_cast<int>(get_pixel32(sSans2,j,i))<<std::hex<<"-";
				}
				std::cout<< std::endl;
			}
		}
		glGenTextures(1, &TextureID2);
		glBindTexture(GL_TEXTURE_2D, TextureID2);
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
	glBindTexture(GL_TEXTURE_2D, TextureID2);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	originy=1.0;
	originx=-1.0;
	glBindTexture(GL_TEXTURE_2D, TextureID2);
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
	glDeleteTextures(1,&TextureID2);
	TextureID2=0;
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
		std::cout << "IMG_Load File Error: " << SDL_GetError() << std::endl;
		return 4;
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 5;
	}
	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < howLong; ++i) {
		//First clear the renderer
		SDL_RenderClear(ren);
		SDL_RenderCopyEx(ren, tex, NULL, NULL,rotation,NULL,SDL_FLIP_NONE);
		SDL_RenderPresent(ren);
#ifdef _WIN32
//	SDL_GL_SwapWindow(win);	/* This does something odd in this case? */
#endif
		rotation+=1.0;
		SDL_Delay(10);
	}
	SDL_RenderCopyEx(ren, tex, NULL, NULL,0.0,NULL,SDL_FLIP_NONE);
	SDL_DestroyTexture(tex);
	return 0;

}
int blackTriangle(SDL_Renderer *ren, SDL_Window *win, int howLong){
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glClearColor(0.30, 0.20, 0.10, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_RenderClear(ren);
	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0.2, 0.3);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	SDL_RenderPresent(ren);
#ifdef _WIN32
	SDL_GL_SwapWindow(win);
#endif
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
#ifdef _WIN32
	SDL_GL_SwapWindow(win);
#endif
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
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
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

//		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_COLOR_MATERIAL);
		glFrontFace(GL_CW);
//		glDisable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureID);
		for (int i = 0; i < howLong; ++i) {
			glClear(GL_COLOR_BUFFER_BIT);
			SDL_RenderClear(ren);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
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
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_RenderClear(ren);
		glRotatef(0.0,0.0,0.0,0.0);
		SDL_RenderPresent(ren);
#ifdef _WIN32
		SDL_GL_SwapWindow(win);	/* Wait 2 seconds =2000 */
#endif
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);

	}
	return 0;
}

//A triangle, text and then a texture
int GlSdlTest1(	SDL_Renderer *ren , SDL_Window *win ,SDL_GLContext context){
//	float m[16];
//	glGetFloatv(GL_PROJECTION_MATRIX,m);
//	std::cout<<"PROJECTION "<<std::endl;
//	std::cout<<std::setw(2)<<m[0]<<"\t "<<std::setw(2)<<m[1]<<"\t "<<m[2]<<"\t "<<m[3]<<std::endl;
//	std::cout<<m[4]<<"\t "<<m[5]<<"\t "<<m[6]<<"\t "<<m[7]<<std::endl;
//	std::cout<<m[8]<<"\t "<<m[9]<<"\t "<<m[10]<<"\t "<<m[11]<<std::endl;
//	std::cout<<m[12]<<"\t "<<m[13]<<"\t "<<m[14]<<"\t "<<m[15]<<std::endl;
	if (TTF_Init() < 0) {return 55;}
	while ((keyScape == 0) && (testErr ==0)){
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
		testErr=blackTriangle(ren,win,200);
		process_events();if(keyScape==1){break;}
		testErr=drawLine1(ren,win,200);
		process_events();if(keyScape==1){break;}
		testErr=Triangles(ren, win,  200);
#ifdef LINUX
		testErr=TestText(ren, win, " Esc exit - Version "+SSTR(VersionMajor)+"."+SSTR(VersionMinor)+" Linux "+font+" "+SSTR(fontSize)+" GL ",1000);
#endif
#ifdef _WIN32
		testErr=TestText(ren, win, " Esc exit - Version "+SSTR(VersionMajor)+"."+SSTR(VersionMinor)+" Windows "+font+" "+SSTR(fontSize)+" GL ",1000);
#endif
		process_events();if(keyScape==1){break;}
		testErr=drawBoxPLS(ren, win,50,0.5,6,15,0.0,-0.20,-0.50);
		process_events();if(keyScape==1){break;}
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
#ifdef _WIN32
		testErr=Rotex(ren, win, 30);
		process_events();if(keyScape==1){break;}
		testErr=TestText(ren, win, " Esc exit - Version "+SSTR(VersionMajor)+"."+SSTR(VersionMinor)+" Windows "+font+" "+SSTR(fontSize)+" GLSDL ",1000);
#endif
glPopMatrix();
		process_events();if(keyScape==1){break;}
	}
	TTF_Quit();
	return 0;
}

/*
 * textureLoad.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: motey
 */



#define MAXTEX 255
unsigned int texture[256];
void *envFiles[256];
int actual_textures;
int empty_texture;
int texture_count=256;

#include "../headers/main.h"
#include <fstream>

int ImageLoadSdl(GLenum target, const char *filename, int verbose) {
//unsigned int i,j,rc1,gc2,bc3;
SDL_Surface  *image;
GLenum texture_format;
GLint  nOfColors;
image=IMG_Load(filename);
if( verbose==1){
	printf("IMG_Load_SDL: %s %d\n",filename,target);
}
if(!image){
	std::cout<<"IMG_Load_SDL: "<<IMG_GetError()<<filename<<target<<std::endl;
	return 1;
}
/*After load it needs to be in a format for OpenGL textures */
nOfColors = image->format->BytesPerPixel;
	if (nOfColors == 4) {
		texture_format = GL_RGBA;
	}
	if (nOfColors == 3){
		texture_format = GL_RGB;
	}
if( verbose==1){
	std::cout<<" Colors "<<nOfColors<<" "<<filename<<" W x H "<<image->w<<" x "<<image->h<<std::endl;
}
glBindTexture(GL_TEXTURE_2D, texture[target]);
glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, image->w, image->h, 0, texture_format, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

SDL_FreeSurface(image);
return 0;
}

void createTextures(char *texture_list) {
int i;
std::string texture_name;
int a,b;
std::fstream fs;
std::string each_line;
std::cout<<"No problem yet with ["<<texture_list<<"]"<<std::endl;
glGenTextures(texture_count, &texture[0]);
for(i=0;i<MAXTEX;i++){envFiles[i]=NULL;} //Clear environment textures
fs.open (texture_list, std::fstream::in | std::fstream::out | std::fstream::app);
if (fs.is_open()) {
    while (std::getline(fs,each_line)){
    	std::istringstream iss(each_line);
    	if (!(iss >> texture_name >> a >> b)) { break; } // error
    	std::cout<<texture_name<<" is texture # "<<a<<" absolute defined as "<<b<<std::endl;
    	ImageLoadSdl(a,texture_name.c_str(),0);
    }
  fs.close();
}else{
    std::cout<<"Problem with "<<texture_list<<std::endl;
}
	actual_textures=50;
	empty_texture=1;
}

void destroyTextures() {
glDeleteTextures(texture_count,&texture[0]);
}





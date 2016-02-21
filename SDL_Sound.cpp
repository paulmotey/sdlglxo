/**
 * Contributors: Motey, Alice
 FIXME the channel stuff is really a silly implementation
 FIXME So who is supposed to do the FIXME?
 It would seem that it is either worthy of fixing or not
What needs to be "fixed" specifically?
*/
#include "headers/main.h"

int sprintfCPP(std::string text1,std::string text2,std::string text3,std::string text4)
{
  std::ostringstream out;
  out << text1 << text2 << text3 << text4 <<std::endl;
  std::cout << out.str();
  return 0;
}
int SDL_available=0;
int Err_Print_SDL( int  errno2, char *namish ) {
	switch (errno2) {
		case 1:
			sprintfCPP( "Unable to initialize SDL: [", Mix_GetError(),"]","");break;
		case 2:
			sprintfCPP("Unable to initialize audio: [", Mix_GetError(),"]","");break;
		case 3:
			sprintfCPP("Unable to load WAV file: ",namish,"","");
			sprintfCPP("SDL err = [ ",Mix_GetError() ,"] ","");break;
		case 4:
			sprintfCPP("Unable to play WAV file: [", Mix_GetError(),"]","");break;
		case 5:
			sprintfCPP("Error cases test: [", Mix_GetError(),"] sound=",namish);break;
		default :
		break;
	}
	return 0;
}

int playSound(char playName[],int channel[],int errnum,Mix_Chunk *sound, int SDLvolume,int left, int right) {
int SDL_err=3;
	if  ( SDL_available!=0){return 10;}
	sound = Mix_LoadWAV(playName);

	if(sound == NULL) {	Err_Print_SDL(SDL_err,playName);}

	channel[0] = Mix_PlayChannel(-1, sound, 0);
	SDL_err=4;if(channel[0] == -1) {Err_Print_SDL(SDL_err,playName);}

	/*volume = MIX_MAX_VOLUME;*/
	Mix_Volume(channel[0], SDLvolume);
	Mix_SetPanning(channel[0],left,right);
	Mix_Playing(-1);
	Mix_VolumeMusic(SDLvolume);
//	Err_Print_SDL(5,playName); //diagnostic
	return errnum;
}

int SDL_Sound_stop(void) {
	if  ( SDL_available!=0){return 1;}
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}

int SDL_Sound_start (void) {
int errState=0;
int audio_rate = 22050;
Uint16 audio_format = AUDIO_S16SYS;
int audio_channels = 2;
int audio_buffers = 4096;

	if (SDL_Init( SDL_INIT_AUDIO) != 0){errState=1;}

	if (errState==0){
		if(Mix_OpenAudio(audio_rate,
			 audio_format,
			 audio_channels,
			 audio_buffers) != 0)
		{errState=2;}
	}
	SDL_available=errState;	//audio_channels=Mix_AllocateChannels(32);
	return errState;
}


/**
 * Contributor: Motey
 FIXME the channel stuff is really a silly implementation
*/
#include "headers/main.h"
int startSDL (void);
int stopSDL (void);
int playSound (char * playName,int channel[],int errnum,Mix_Chunk *sound, int volume, int left, int right);

int SDL_available=0;

int Err_Print_SDL( int  errno2, char *namish ) {

	char errString[200];

	switch (errno2) {
	case 1:
		std::cout<<errString<<std::endl;
		break;
//	sprintf(errString, "Unable to initialize SDL: [%s]\n", Mix_GetError());break;
	case 2:
//	sprintf(errString, "Unable to initialize audio: [%s]\n", Mix_GetError());break;
	case 3:
//	sprintf(errString, "Unable to load WAV file: %s SDL err = [ %s ]\n",namish, Mix_GetError());break;
	case 4:
//	sprintf(errString, "Unable to play WAV file: [%s]\n", Mix_GetError());break;
	default :
		break;
//	sprintf(errString, "Unable to even make a simple err display work! DOH! \n");break;
	}
//fprintf(stderr,"%s",errString);
return 0;
//This doesn't really return, I just did it this way so I can use the return value later.
}
/* Test code----
int mainly() {
int channel,errnum;
int *channelp=&channel;
char playName[]="res/applause.wav";
Mix_Chunk *sound = NULL;
int quitty=1;
errnum=startSDL();if(errnum>0){errPrint(errnum,playName);}
playSound(playName,channelp,errnum,sound);
if ((Mix_Playing(channel) == 0) && quitty==0){Mix_FreeChunk(sound);quitty=1;}
stopSDL();
return errnum;
}
*/
/*
Volume is 0-128
*/
/* The internal format for an audio chunk */
//typedef struct Mix_Chunk {
//	int allocated;
//	Uint8 *abuf;
//	Uint32 alen;
//	Uint8 volume;		/* Per-sample volume, 0-128 */
//} Mix_Chunk;
//const uint8_t *buf, int buf_size
int Rawdio(uint8_t *buf, int buf_size) {
return 0;
// //int playStat=0;
// //Mix_Chunk *sounds;
// Mix_Chunk sound;
// //sounds=&sound;
// sound.allocated=0;
// sound.abuf=buf;
// sound.alen=buf_size;
// sound.volume=128;
// //playStat=Mix_PlayChannel(-1, sounds, 0);
}

int playSound(char playName[],int channel[],int errnum,Mix_Chunk *sound, int SDLvolume,int left, int right) {
int SDL_err;
//int playing=0;
SDL_err=3;
if  ( SDL_available!=0){return 10;}
sound = Mix_LoadWAV(playName);
if(sound == NULL) {
	Err_Print_SDL(SDL_err,playName);}
channel[0] = Mix_PlayChannel(-1, sound, 0);
SDL_err=4;
if(channel[0] == -1) {
	Err_Print_SDL(SDL_err,playName);}
/*
volume = MIX_MAX_VOLUME;
printf("Sound Level: %d\n", volume);
*/
Mix_Volume(channel[0], SDLvolume);
Mix_SetPanning(channel[0],left,right);
//playing=
Mix_Playing(-1);
//printf ("Channel is %d of %d err %d\n",channel[0],playing,errnum);
Mix_VolumeMusic(SDLvolume);
return errnum;
}

int stopSDL(void) {
if  ( SDL_available!=0){return 1;}
Mix_CloseAudio();
SDL_Quit();
return 0;
}

int startSDL (void) {
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
SDL_available=errState;
//audio_channels=Mix_AllocateChannels(32);
//printf("Channels %d\n",audio_channels);
return errState;
}


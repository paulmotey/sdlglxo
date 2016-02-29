/*
select position and return
*/

#include "../headers/main.h"
extern int keyScape;
int mousex;
int mousey;
/*
SDL_Event -- General event structure
Structure Definition

typedef union{
  Uint8 type;
  SDL_ActiveEvent active;
  SDL_KeyboardEvent key;
  SDL_MouseMotionEvent motion;
  SDL_MouseButtonEvent button;
  SDL_JoyAxisEvent jaxis;
  SDL_JoyBallEvent jball;
  SDL_JoyHatEvent jhat;
  SDL_JoyButtonEvent jbutton;
  SDL_ResizeEvent resize;
  SDL_ExposeEvent expose;
  SDL_QuitEvent quit;
  SDL_UserEvent user;
  SDL_SysWMEvent syswm;
} SDL_Event;


*/
/*
SDL_MouseButtonEvent -- Mouse button event structure
Structure Definition

typedef struct{
  Uint8 type;
  Uint8 button;
  Uint8 state;
  Uint16 x, y;
} SDL_MouseButtonEvent;

Structure Data

type	SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP
button	The mouse button index (SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT)
state	SDL_PRESSED or SDL_RELEASED
x, y	The X/Y coordinates of the mouse at press/release time

Description

SDL_MouseButtonEvent is a member of the SDL_Event union and is used when an event 
of type SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP is reported.

When a mouse button press or release is detected then number of the button pressed
 (from 1 to 255, with 1 usually being the left button and 2 the right)
  is placed into button, the position of the mouse when this event occurred
   is stored in the x and the y fields. Like SDL_KeyboardEvent, 
   information on whether the event was a press or a release event
    is stored in both the type and state fields, but this should be obvious.
*/
void process_events( void ){
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
            mousex=event.motion.x;
            mousey=event.motion.y;
            break;
        }
    }
}


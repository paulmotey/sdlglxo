/*
select position and return
*/

#include "../headers/main.h"
extern int keyScape;
int mousex;
int mousey;

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


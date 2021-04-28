#include <SDL2/SDL.h>
#include <bits/stdc++.h>
using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
Uint32* pixel;
int frame = 0;
void render(){
	frame++;
	double s = sin(frame);
	double c = cos(frame);
	int distance = 2;
	double x[8] = {-1,1,1,-1,-1,1,1,-1};
	double y[8] = {1,1,1,1,-1,-1,-1,-1};
	double z[8] = {-1,-1,1,1,-1,-1,1,1};
	for( int i = 0; i != 8; i++ ) {
		int xx = x[i];
		int yy = y[i];
		int zz = z[i];
		x[i] = xx*(c*c) + yy*(s*c) - zz*(s);
		y[i] = xx*(c*s*s-s*c) + yy*(s*s*s+c+c) + zz*(c*s);
		z[i] = xx*(c*s*c+s*s) + yy*(s*s*c-c*s) + zz*(c*c);
	}
	
}

int main( int argc, char** argv )
{
	if( SDL_Init( SDL_INIT_VIDEO) < 0 )
	{
		printf( "SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError() );
		return -1;
	}

	SDL_Window* window = NULL;
	const auto UD = SDL_WINDOWPOS_UNDEFINED;
	window = SDL_CreateWindow( "wow", UD, UD, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if( window == NULL ) {
		printf("Window could be not be created! SDL_ERROR: %s\n", SDL_GetError() );
		return -1;
	}

	SDL_Surface* screenSurface = NULL;
	screenSurface = SDL_GetWindowSurface( window );
	pixel = (Uint32*)screenSurface->pixels;
	SDL_Event event;
	while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
       	render();
       	SDL_UpdateWindowSurface( window );
       	SDL_Delay(100);
    }
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}
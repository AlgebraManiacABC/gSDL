#include <stdio.h>
#include <gSDL.h>

int main()
{
	//SDL_Window * w;
	//SDL_Renderer * r;
	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr,"SDL_Init fail! [%s]\n",SDL_GetError());
		return EXIT_FAILURE;
	}
	/*
	if(gSDL_Init(SDL_INIT_EVERYTHING,&w,640,400,SDL_WINDOW_BORDERLESS,"Test",&r))
	{
		fprintf(stderr,"Initialization failure: %s\n",SDL_GetError());
		return EXIT_FAILURE;
	}
	*/
	printf("Initialization success!\n");
	//gSDL_Close(LEVEL_REND,&r,&w);
	//SDL_DestroyRenderer(r);
	//SDL_DestroyWindow(w);
	SDL_Quit();
	return EXIT_SUCCESS;
}
#include <stdio.h>
#include <gSDL.h>
#include <stdbool.h>

void RenderFrame(SDL_Renderer *r, gIMG *g);

int main(int argc, char *argv[])
{
	SDL_Window * w;
	SDL_Renderer * r;
	//if(SDL_Init(SDL_INIT_VIDEO))
	//{
	//	fprintf(stderr,"SDL_Init fail! [%s]\n",SDL_GetError());
	//	return EXIT_FAILURE;
	//}
	if(gSDL_Init(SDL_INIT_EVERYTHING,&w,640,400,SDL_WINDOW_RESIZABLE,"Test",&r,
		SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC,IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP))
	{
		fprintf(stderr,"Initialization failure: %s\n",SDL_GetError());
		return EXIT_FAILURE;
	}
	printf("Initialization success!\n");

	SDL_Color red = {0xff,0x00,0x00,0x00};
	Button butt = CreateSolidButton(r,red,640/2,400/2,640/10,400/10);

	bool close = false;
	while(!close)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			int ww, wh;
			switch(event.type)
			{
				case SDL_QUIT:
					close = true;
					break;
				case SDL_KEYDOWN:
					SDL_GetWindowSize(w,&ww,&wh);
					printf("Window w.h: %d.%d\n",ww,wh);
					printf("Button: %d.%d @ %d,%d\n",butt.rect.w,butt.rect.h,butt.rect.x,butt.rect.y);
					break;
				case SDL_WINDOWEVENT:
					switch(event.window.event)
					{
						case SDL_WINDOWEVENT_RESIZED:
							int new_ww = event.window.data1;
							int new_wh = event.window.data2;
							printf("Window was resized! New w.h: %d.%d\n",new_ww,new_wh);
							gIMG_Resize(&butt,new_ww/10,new_wh/10);
							gIMG_Move(&butt,new_ww/2,new_wh/2);
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
		SDL_Delay(1000/60);
		RenderFrame(r,&butt);
	}

	gSDL_Close(LEVEL_REND,&r,&w);
	return EXIT_SUCCESS;
}

void RenderFrame(SDL_Renderer *r, gIMG *g)
{
	SDL_RenderClear(r);
	gIMG_RenderCopy(r,g);
	SDL_RenderPresent(r);
}
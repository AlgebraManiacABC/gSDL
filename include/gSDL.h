#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define LEVEL_REND 2
#define LEVEL_WIN 1
#define LEVEL_INIT 0

#define PT_DEFAULT 200

typedef struct
{
    SDL_Texture *tx;
    SDL_Rect rect;

}   myIMG;

typedef myIMG Button;

int mySDL_Init(Uint32 init_flags, SDL_Window ** w, int win_w, int win_h,
    Uint32 win_flags, char * win_name, SDL_Renderer ** r);

//HWND mySDL_Get_WinHandle(SDL_Window * w);

//WINBOOL mySDL_Create_Menu(HWND hwnd, char * str);

int mySDL_MaximizeWindow(SDL_Window ** w, SDL_Renderer ** r);

Button CreateSolidButton(SDL_Renderer *r, SDL_Color color, int x_center, int y_center, int w, int h);

int Button_AddText(SDL_Renderer *r, Button but, TTF_Font *font, char *txt, SDL_Color color, int pt);

bool isMouseOverRect(int mx, int my, SDL_Rect rect);

bool isMouseOverButton(int mx, int my, Button but);

myIMG CreateImgFromFile(SDL_Renderer *, const char *);

int myIMG_Resize(myIMG *img, int w, int h);

int myIMG_RenderCopy(SDL_Renderer *r, myIMG *img);

SDL_Rect myTTF_CreateRectFromTexture(SDL_Texture *text, int x, int y, int pt);

int myTTF_RenderText(SDL_Renderer * r, SDL_Texture *text, int x, int y, int pt);

SDL_Texture * CreateSolidTextureFromText
    (SDL_Renderer * r, TTF_Font * font, char * text, SDL_Color color);

int mySDL_Close(int level, ...);
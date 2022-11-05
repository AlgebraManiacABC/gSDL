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

}   gIMG;

typedef gIMG Button;

int gSDL_Init(Uint32 init_flags, SDL_Window ** w, int win_w, int win_h,
    Uint32 win_flags, char * win_name, SDL_Renderer ** r);

//HWND gSDL_Get_WinHandle(SDL_Window * w);

//WINBOOL gSDL_Create_Menu(HWND hwnd, char * str);

int gSDL_MaximizeWindow(SDL_Window ** w, SDL_Renderer ** r);

Button CreateSolidButton(SDL_Renderer *r, SDL_Color color, int x_center, int y_center, int w, int h);

int Button_AddText(SDL_Renderer *r, Button but, TTF_Font *font, char *txt, SDL_Color color, int pt);

bool isMouseOverRect(int mx, int g, SDL_Rect rect);

bool isMouseOverButton(int mx, int g, Button but);

gIMG CreateImgFromFile(SDL_Renderer *, const char *);

int gIMG_Resize(gIMG *img, int w, int h);

int gIMG_RenderCopy(SDL_Renderer *r, gIMG *img);

SDL_Rect gTTF_CreateRectFromTexture(SDL_Texture *text, int x, int y, int pt);

int gTTF_RenderText(SDL_Renderer * r, SDL_Texture *text, int x, int y, int pt);

SDL_Texture * CreateSolidTextureFromText
    (SDL_Renderer * r, TTF_Font * font, char * text, SDL_Color color);

int gSDL_Close(int level, ...);
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

#ifndef GIMG
#define GIMG
typedef struct
{
    SDL_Texture *tx;
    SDL_Rect rect;

}   gIMG;

typedef gIMG Button;
#endif

/**
 * @brief 
 * 
 * Initializes SDL, and creates a Window and Renderer with the given information.
 * Will print an error message on failure.
 * 
 * @param init_flags SDL_Init flags
 * @param w A pointer to a Window pointer which will be set to the created window on success
 * @param win_w The starting window width
 * @param win_h The starting window height
 * @param win_flags SDL_CreateWindow flags
 * @param win_name The name of the Window
 * @param r A pointer to a Renderer pointer which will be set to the created renderer on success
 * @param rend_flags SDL_CreateRenderer flags
 * @param img_flags IMG_Init flags
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on fail.
 */
int gSDL_Init(Uint32 init_flags, SDL_Window ** w, int win_w, int win_h,
    Uint32 win_flags, char * win_name, SDL_Renderer ** r, Uint32 rend_flags, Uint32 img_flags);

//HWND gSDL_Get_WinHandle(SDL_Window * w);

//WINBOOL gSDL_Create_Menu(HWND hwnd, char * str);

int gSDL_MaximizeWindow(SDL_Window ** w, SDL_Renderer ** r, const char * windowName);

Button CreateSolidButton(SDL_Renderer *r, SDL_Color color, int x_center, int y_center, int w, int h);

int Button_AddText(SDL_Renderer *r, Button but, TTF_Font *font, char *txt, SDL_Color color, int pt);

bool isMouseOverRect(int mx, int g, SDL_Rect rect);

bool isMouseOverButton(int mx, int g, Button but);

gIMG CreateImgFromFile(SDL_Renderer *, const char *);

int gIMG_Resize(gIMG *img, int w, int h);

int gIMG_Move(gIMG *img, int x, int y);

int gIMG_RenderCopy(SDL_Renderer *r, gIMG *img);

SDL_Rect gTTF_CreateRectFromTexture(SDL_Texture *text, int x, int y, int pt);

int gTTF_RenderText(SDL_Renderer * r, SDL_Texture *text, int x, int y, int pt);

SDL_Texture * CreateSolidTextureFromText
    (SDL_Renderer * r, TTF_Font * font, char * text, SDL_Color color);

int gSDL_Close(int level, ...);
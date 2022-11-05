#include "mysdl.h"

int mySDL_Init(Uint32 init_flags, SDL_Window ** w, int win_w, int win_h,
    Uint32 win_flags, char * win_name, SDL_Renderer ** r)
{
    if(SDL_Init(init_flags))
    {
        fprintf(stderr,"Initialization failure: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    *w = SDL_CreateWindow(win_name,
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          win_w,win_h,win_flags);
    if(!(*w))
    {
        fprintf(stderr,"Window creation failure: %s\n",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    *r = SDL_CreateRenderer(*w,-1,
                SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(!(*r))
    {
        fprintf(stderr,"Renderer creation failure: %s\n",SDL_GetError());
        mySDL_Close(LEVEL_WIN,*w);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
HWND mySDL_Get_WinHandle(SDL_Window * w)
{
    SDL_SysWMinfo winfo;
    SDL_VERSION(&winfo.version);
    if(!SDL_GetWindowWMInfo(w,&winfo))
    {
        return NULL;
    }
    return winfo.info.win.window;
}

WINBOOL mySDL_Create_Menu(HWND hwnd, char * str)
{
    HMENU menu = CreateMenu();

    AppendMenu(menu,MF_STRING,(UINT_PTR)NULL,str);

    return SetMenu(hwnd,menu);
}
*/

int mySDL_MaximizeWindow(SDL_Window ** w, SDL_Renderer ** r)
{
    SDL_DisplayMode disp;
    if(SDL_GetDesktopDisplayMode(0,&disp))
    {
        fprintf(stderr,"Couldn't get display mode! %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_DestroyWindow(*w);
    *w = SDL_CreateWindow("Betrayal at House on the Hill",
                SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                disp.w,disp.h,
                SDL_WINDOW_MAXIMIZED | SDL_WINDOW_BORDERLESS);
    if(!(*w))
    {
        fprintf(stderr,"Window could not be resized! %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_DestroyRenderer(*r);
    *r = SDL_CreateRenderer(*w,-1,
                SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(!(*r))
    {
        fprintf(stderr,"Window could not be resized! %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

Button CreateSolidButton(SDL_Renderer *r, SDL_Color color, int xc, int yc, int w, int h)
{
    Button but;
    but.tx = SDL_CreateTexture(r,SDL_PIXELFORMAT_UNKNOWN,SDL_TEXTUREACCESS_TARGET,w,h);
    SDL_SetRenderTarget(r,but.tx);
    SDL_Color before;
    SDL_GetRenderDrawColor(r,&before.r,&before.g,&before.b,&before.a);
    SDL_SetRenderDrawColor(r,color.r,color.g,color.b,color.a);
    SDL_RenderFillRect(r,NULL);
    SDL_SetRenderDrawColor(r,before.r,before.g,before.b,before.a);
    SDL_SetRenderTarget(r,NULL);

    but.rect.h = h;
    but.rect.w = w;
    but.rect.x = xc-(w/2);
    but.rect.y = yc+(h/2);

    return but;
}

int Button_AddText(SDL_Renderer *r, Button but, TTF_Font *font, char *text, SDL_Color color, int pt)
{
    SDL_Texture *temp = CreateSolidTextureFromText(r,font,text,color);
    if(!temp) return EXIT_FAILURE;

    if(SDL_SetRenderTarget(r,but.tx))       return EXIT_FAILURE;
    SDL_Rect box = myTTF_CreateRectFromTexture(temp,0,0,pt);
    box.x = (but.rect.w / 2) - (box.w/2);
    box.y = (but.rect.h / 2) - (box.h/2);
    if(SDL_RenderCopy(r,temp,NULL,&box))    return EXIT_FAILURE;
    if(SDL_SetRenderTarget(r,NULL))         return EXIT_FAILURE;
    SDL_DestroyTexture(temp);
    return EXIT_SUCCESS;
}

bool isMouseOverRect(int mx, int my, SDL_Rect rect)
{
    if(mx > (rect.x+rect.w) || mx < (rect.x))
        return false;
    if(my > (rect.y+rect.h) || my < (rect.y))
        return false;
    return true;
}

bool isMouseOverButton(int mx, int my, Button but)
{
    if(mx > (but.rect.x+but.rect.w) || mx < (but.rect.x))
        return false;
    if(my > (but.rect.y+but.rect.h) || my < (but.rect.y))
        return false;
    return true;
}

myIMG CreateImgFromFile(SDL_Renderer *r, const char *file)
{
    SDL_Surface *temp = IMG_Load(file);
    myIMG img = {NULL,{0,0,0,0}};
    img.tx = SDL_CreateTextureFromSurface(r,temp);
    SDL_QueryTexture(img.tx,NULL,NULL,&img.rect.w,&img.rect.h);
    return img;
}

int myIMG_Resize(myIMG *img, int w, int h)
{
    if(!img) return EXIT_FAILURE;
    img->rect.h = h;
    img->rect.w = w;
    return EXIT_SUCCESS;
}

int myIMG_RenderCopy(SDL_Renderer *r, myIMG *img)
{
    return SDL_RenderCopy(r,img->tx,NULL,&img->rect);
}

SDL_Rect myTTF_CreateRectFromTexture(SDL_Texture *text, int x, int y, int pt)
{
    SDL_Rect box = {x,y,0,0};
    SDL_QueryTexture(text,NULL,NULL,&box.w,&box.h);
    float ratio = (float)pt/PT_DEFAULT;
    box.h *= ratio;
    box.w *= ratio;
    return box;
}

int myTTF_RenderText(SDL_Renderer * r, SDL_Texture * text, int x, int y, int pt)
{
    SDL_Rect box = {x,y,0,0};
    SDL_QueryTexture(text,NULL,NULL,&box.w,&box.h);
    float ratio = (float)pt/PT_DEFAULT;
    box.h *= ratio;
    box.w *= ratio;
    return SDL_RenderCopy(r,text,NULL,&box);
}

SDL_Texture * CreateSolidTextureFromText
    (SDL_Renderer * r, TTF_Font * font, char * text, SDL_Color color)
{
    SDL_Surface * temp = TTF_RenderText_Solid(font,text,color);
    if(!temp) return NULL;
    SDL_Texture * tex = SDL_CreateTextureFromSurface(r,temp);
    SDL_FreeSurface(temp);
    return tex;
}

int mySDL_Close(int level, ...)
{
    va_list vars;
    va_start(vars,level);
    switch(level)
    {
        case LEVEL_REND:
            SDL_DestroyRenderer(va_arg(vars,SDL_Renderer*));
        case LEVEL_WIN:
            SDL_DestroyWindow(va_arg(vars,SDL_Window*));
        case LEVEL_INIT:
            SDL_Quit();
            break;
        default:
            fprintf(stderr,"Unknown mySDL_Close level!\n");
            va_end(vars);
            return EXIT_FAILURE;
            break;
    }
    va_end(vars);
    return EXIT_SUCCESS;
}
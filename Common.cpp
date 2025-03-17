#include "Common.h"
#include "BaseObjects.h"

SDL_Window* g_window = NULL;
SDL_Renderer* g_screen = NULL;
SDL_Event g_event;

BaseObject g_background;  // Định nghĩa

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret<0)
    {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("JELLYFISH GAME <3", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else{
        g_screen = SDL_CreateRenderer(g_window, -1 , SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
        {
            success = false;
        }
        else{
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_JPG; //CHÚ Ý KIỂU ẢNH CHỖ NÀY LÀ JPG NHÉ!!!!!!!!!!!!//
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("IMG//background.jpg", g_screen);
    if (ret == false)
    {
        return false;
    }
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

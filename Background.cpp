#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

SDL_Window* g_windows = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* g_background = NULL;

bool loadMedia()
{
    bool success = true;
    // Load ảnh background
    g_background = IMG_Load("D:\\Trang\\LEARNC++\\CODEBLOCK\\GAME\\Jellyfish_game\\background.jpg");
    if (g_background == NULL)
    {
        cout << "Failed to load image! SDL_image Error: " << IMG_GetError() << endl;
        success = false;
    }

    return success;
}


void close()
{
    SDL_FreeSurface(g_background);
    g_background = NULL;
    SDL_DestroyWindow(g_windows);
    g_windows = NULL;
    SDL_Quit();
}

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        g_windows = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 700, SDL_WINDOW_SHOWN);
        if (g_windows == NULL)
        {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(g_windows);
        }
    }
    return success;
}


int main(int argc, char* argv[])
{
    if (init() == true)
    {
        if (loadMedia())
        {
            SDL_BlitSurface(g_background , NULL , gScreenSurface , NULL);
            SDL_UpdateWindowSurface(g_windows);
            SDL_Delay (2000);
        }
    }
    close();
    return 0;
}

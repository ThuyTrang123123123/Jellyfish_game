#include "Common.h"
#include "BaseObjects.h"

extern BaseObject g_background;

int main(int argc, char* argv[])
{
    if (InitData() == false)
    {
        return -1;
    }
    if (LoadBackground() == false)
    {
        return -1;
    }
    bool is_quit = false;
    while (!is_quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}

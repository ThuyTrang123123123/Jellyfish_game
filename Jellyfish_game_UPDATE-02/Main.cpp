#include "Common.h"
#include "BaseObjects.h"
#include "game_map.h"

extern BaseObject g_background;

int main(int argc, char* argv[])
{
    if (InitData() == false)
    {
        return -1;
    }
    if (LoadBackground() == false)
    {
        printf("Error: Failed to load background image!\n");
        return -1;
    }

    GameMap game_map;
    game_map.LoadMap((char*)"map/map01.dat");
    game_map.LoadTiles(g_screen);

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
        game_map.DrawMap(g_screen);

        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}

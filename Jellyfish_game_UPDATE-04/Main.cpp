#include "Common.h"
#include "BaseObjects.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTime.h"

extern BaseObject g_background;

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
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
    game_map.LoadMap((char*)"map/map01.dat"); //map01 viết còn sai, cái ảnh 3 oke rồi, cần chỉnh lại 0- ô trống//
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("character//jellyfish.png", g_screen);
    p_player.set_clips();

    bool is_quit = false;
    while (!is_quit)
    {
        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandelInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getMap();

        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap (map_data);
        game_map.DrawMap (g_screen);

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; // ms

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
    }

    close();
    return 0;
}

#include "Common.h"
#include "BaseObjects.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTime.h"
#include "ThreatsObject.h"

extern BaseObject g_background;

std::vector<ThreatsObject*> MakeThreadList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for (int i=0; i<20 ; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats + i);
        if (p_threat != NULL)
        {
            p_threat -> LoadImg ("character//threat_left.png", g_screen);
            p_threat -> set_clips();
            p_threat -> set_type_move (ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat -> set_x_pos (670+i*700);
            p_threat -> set_y_pos (200);

            int pos1 = p_threat -> get_x_pos() - 60;
            int pos2 = p_threat -> get_x_pos() + 60;
            p_threat -> SetAnimationPos(pos1 , pos2);

            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject* threats_objs = new ThreatsObject[20];

    for (int i=0 ; i<20 ; i++)
    {
        ThreatsObject* p_threat = (threats_objs + i);
        if (p_threat != NULL)
        {
            p_threat -> LoadImg ("character/threat_level.png", g_screen);
            p_threat -> set_clips();
            p_threat -> set_x_pos(700 + i*1300);
            p_threat -> set_y_pos(250);
            p_threat -> set_type_move (ThreatsObject::STATIC_THREAT);
            p_threat -> set_input_left (18);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

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
    //p_player.LoadImg ("character//consua_right.png" , g_screen);
    p_player.set_clips();

    std::vector<ThreatsObject*> threats_list = MakeThreadList();

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

        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap (map_data);
        game_map.DrawMap (g_screen);

        for (int i=0 ; i<threats_list.size() ; i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat -> SetMapXY (map_data.start_x_, map_data.start_y_);
                p_threat -> ImpMoveType(g_screen);
                p_threat -> DoPlayer (map_data);
                p_threat -> Show (g_screen);

            }
        }

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

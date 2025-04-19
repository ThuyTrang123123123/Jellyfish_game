#include "Common.h"
#include "BaseObjects.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTime.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"

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
            p_threat -> set_input_left (0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
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

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("IMG/explosion.png", g_screen);
    if (!tRet) return -1;
    exp_threat.set_clip();

    ExplosionObject exp_main;
    bool mRet = exp_main.LoadImg("IMG/explosion.png", g_screen);
    if (!mRet) return -1;
    exp_main.set_clip();

    int num_die = 0;

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
                p_threat -> MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat -> Show (g_screen);

                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int j=0 ; j<tBullet_list.size() ; j++)
                {
                    BulletObject* pt_bullet = tBullet_list.at(j);
                    if (pt_bullet)
                    {
                        bCol1 = SDLCommon::CheckCollision(pt_bullet->GetRect(), rect_player);
                        if (bCol1)
                        {
                            p_threat->RemoveBullet(j);
                            break;
                        }
                    }
                }
                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommon::CheckCollision(rect_player, rect_threat);
                if (bCol1 || bCol2)
                {
                    int width_exp_frame = exp_main.get_frame_width();
                    int height_exp_frame = exp_main.get_frame_height();
                    for (int ex = 0; ex<4 ; ex++)
                    {
                        int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                        int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - height_exp_frame*0.5;

                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                    }

                    num_die ++;
                    if (num_die <= 3)
                    {
                        p_player.SetRect(0,0);
                        p_player.set_comback_time(60);
                        SDL_Delay(1000);
                        continue;
                    }
                    else{

                        if (MessageBox(NULL, "GAME OVER", "Info" , MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
                }
            }
        }

        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();
        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r=0 ; r<bullet_arr.size(); r++)
        {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL)
            {
                for (int t=0; t<threats_list.size(); t++)
                {
                    ThreatsObject* obj_threat = threats_list.at(t);
                    if (obj_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_high_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommon::CheckCollision(bRect, tRect);

                        if (bCol)
                        {
                            for (int ex=0 ; ex < NUM_FRAME_EXP; ++ex)
                            {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                            }


                            p_player.RemoveBullet(r);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }
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

    for (int i=0; i<threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list.at(i);
        if (p_threat)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }

    threats_list.clear();

    close();
    return 0;
}

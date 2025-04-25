#include "Common.h"
#include "BaseObjects.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTime.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "BossObject.h"
#include "SoundManager.h"

extern BaseObject g_background;
extern TTF_Font* font_time;

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

    BaseObject castle;

    BaseObject winImage;

    // 1. Init SDL, IMG, TTF, audio…
    if (InitData() == false)
    {
        SDL_Log("Failed to initialize SDL");
        return -1;
    }

    // 2. Load Start Screen
    BaseObject startScreen;
    if (!startScreen.LoadImg("IMG/startgame.png", g_screen)) {
        SDL_Log("Failed to load start screen image");
        return -1;
    }

    // 3. Vòng lặp chờ bấm Start
    bool start = false;
    while (!start) {
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) {
                // bấm đóng cửa sổ thì exit luôn
                SoundManager::Instance().clean();
                SDL_Quit();
                return 0;
            }
            if (g_event.type == SDL_MOUSEBUTTONDOWN) {
                // bấm chuột bất kỳ (hoặc kiểm tra vùng nút nếu cần)
                start = true;
            }
        }
        SDL_RenderClear(g_screen);
        // vẽ full-screen startgame.png
        startScreen.Render(g_screen, nullptr);
        SDL_RenderPresent(g_screen);
    }

    if (LoadBackground() == false)
    {
        SDL_Log("Failed to load background image");
        return -1;
    }

    if (!winImage.LoadImg("IMG/win.png", g_screen)) {
    SDL_Log("Failed to load win image");
    return -1;
    }

    castle.LoadImg("character//castle.png", g_screen);

    if (!SoundManager::Instance().init()) {
    SDL_Log("SDL_mixer init failed: %s", Mix_GetError());
    return -1;
    }

    GameMap game_map;
    game_map.LoadMap((char*)"map/map01.dat"); //map01 viết còn sai, cái ảnh 3 oke rồi, cần chỉnh lại 0- ô trống//
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("character//jellyfish.png", g_screen);
    //p_player.LoadImg ("character//consua_right.png" , g_screen);
    p_player.set_clips();

    PlayerPower player_power;
    player_power.Init(g_screen);

    PlayerDonut player_donut;
    player_donut.Init(g_screen);
    player_donut.SetPos(SCREEN_WIDTH*0.5 - 295, 6);

    std::vector<ThreatsObject*> threats_list = MakeThreadList();

    //BOSS THREAT
    BossObject bossObject;
    bool ret = bossObject.LoadImgFrames(g_screen);;
    if (!ret) {
    SDL_Log("Failed to load boss frames!");
    return -1;
    }
    int xPosBoss = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6;
    int yPosBoss = SCREEN_HEIGHT - castle.GetRect().h - 165;
    bossObject.set_xpos(xPosBoss);
    bossObject.set_ypos(yPosBoss);

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("IMG/explosion.png", g_screen);
    if (!tRet) return -1;
    exp_threat.set_clip();

    ExplosionObject exp_main;
    bool mRet = exp_main.LoadImg("IMG/explosion.png", g_screen);
    if (!mRet) return -1;
    exp_main.set_clip();

    int num_die = 0;

    //TIME TEXT
    TextObject time_game;
    time_game.SetColor(TextObject::BLANK_TEXT);

    TextObject mark_game;
    mark_game.SetColor(TextObject::BLANK_TEXT);
    UINT mark_value = 0;

    TextObject donut_game;
    donut_game.SetColor(TextObject::BLANK_TEXT);


    //*************************************
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

        int castle_x_pos = map_data.max_x_ - castle.GetRect().w;  // đặt gần cuối bản đồ
        int castle_y_pos = SCREEN_HEIGHT - castle.GetRect().h - 248;   // đặt trên nền đất

        SDL_Rect castle_rect;
        castle_rect.x = castle_x_pos - map_data.start_x_;  // điều chỉnh theo camera
        castle_rect.y = castle_y_pos;
        castle_rect.w = castle.GetRect().w;
        castle_rect.h = castle.GetRect().h;

        castle.SetRect(castle_rect.x, castle_rect.y);
        castle.Render(g_screen);

        SDL_Rect playerRect = p_player.GetRectFrame();
        if (SDLCommon::CheckCollision(playerRect, castle_rect))
        {
        // Hiển thị ảnh WIN full‐screen
            winImage.SetRect(0, 0);
            winImage.Render(g_screen, nullptr);
            SDL_RenderPresent(g_screen);
            SDL_Delay(5000);
            is_quit = true;
            break;
        }

        //DRAW GEOMETRIC
        GeometricFormat rectangle_size(0,0, SCREEN_WIDTH, 40);
        ColorData color_data(85,189,124);
        Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

        GeometricFormat outLineSize(1, 1, SCREEN_WIDTH-1, 40);
        ColorData color_data2 (255, 255, 255);

        Geometric::RenderOutline(outLineSize, color_data2, g_screen);


        player_power.Show(g_screen);
        player_donut.Show(g_screen);

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
                        SDL_Delay(15);
                    }

                    num_die ++;
                    if (num_die < 3)
                    {
                        p_player.SetRect(0,0);
                        p_player.set_comback_time(60);
                        SDL_Delay(700);
                        player_power.Decrease();
                        player_power.Render(g_screen);
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
                SDL_Rect bRect = p_bullet->GetRect();

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
                            mark_value++;
                            for (int ex=0 ; ex < NUM_FRAME_EXP; ++ex)
                            {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                                SDL_RenderPresent(g_screen);
                            }


                            p_player.RemoveBullet(r);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }

                if (bossObject.GetIsAlive())
                {
                    SDL_Rect boss_rect = bossObject.GetRect();
                    bool boss_hit = SDLCommon::CheckCollision(bRect, boss_rect);

                    if (boss_hit)
                    {
                    // Hiệu ứng nổ boss
                        ExplosionObject boss_exp;
                        boss_exp.LoadImg("IMG/explosion.png", g_screen);
                        boss_exp.set_clip();

                        int frame_w = boss_exp.get_frame_width();
                        int frame_h = boss_exp.get_frame_height();
                        int exp_x = boss_rect.x + bossObject.get_width_frame() / 2 - frame_w / 2;
                        int exp_y = boss_rect.y + bossObject.get_height_frame() / 2 - frame_h / 2;

                        for (int ex = 0; ex < NUM_FRAME_EXP; ++ex)
                        {
                        boss_exp.set_frame(ex);
                        boss_exp.SetRect(exp_x, exp_y);
                        boss_exp.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                        SDL_Delay(80);
                        }

                        // Boss die
                        bossObject.SetDie();
                        mark_value += 5;
                        p_player.RemoveBullet(r);
                        break; // Không cần xét tiếp viên đạn này
                    }
                }
            }
        }

        //SHOW GAME TIME
        std::string str_time = "TIME: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 400 - time_val;
        if (val_time <= 0)
        {
            if (MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
            }
        }
        else{
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 6);
        }

        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Mark: ");
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 6);

        int donut_count = p_player.GetDonutCount();
        std::string donut_str = std::to_string(donut_count);

        donut_game.SetText(donut_str);
        donut_game.LoadFromRenderText(font_time, g_screen);
        donut_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 6);

        //SHOW BOSS
        int val = MAX_MAP_X*TILE_SIZE - (map_data.start_x_ + p_player.GetRect().x);
        if (val <= SCREEN_WIDTH && bossObject.GetIsAlive())
        {
            bossObject.SetMapXY(map_data.start_x_, map_data.start_y_);
            bossObject.DoPlayer(map_data);
            bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            bossObject.Show(g_screen);

            // ====== VA CHẠM GIỮA MAIN VỚI BOSS =======
            SDL_Rect rect_player = p_player.GetRectFrame();
            SDL_Rect rect_boss = bossObject.GetRect();

            bool boss_col = SDLCommon::CheckCollision(rect_player, rect_boss);

            // ====== VA CHẠM GIỮA MAIN VỚI ĐẠN CỦA BOSS =======
            std::vector<BulletObject*> boss_bullets = bossObject.get_bullet_list();
            bool boss_bullet_col = false;

            for (int bb = 0; bb < boss_bullets.size(); bb++)
            {
                BulletObject* p_bullet = boss_bullets.at(bb);
                if (p_bullet)
                {
                    SDL_Rect bullet_rect = p_bullet->GetRect();
                    if (SDLCommon::CheckCollision(bullet_rect, rect_player))
                    {
                        boss_bullet_col = true;
                        // Xoá viên đạn gây va chạm
                        boss_bullets.erase(boss_bullets.begin() + bb);
                        break;
                    }
                }
            }

            // ✅ Nếu va chạm với Boss hoặc Bullet → gây nổ, trừ mạng
            if (boss_col || boss_bullet_col)
            {
                int width_exp_frame = exp_main.get_frame_width();
                int height_exp_frame = exp_main.get_frame_height();

                for (int ex = 0; ex < 4; ++ex)
                {
                    int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame * 0.5;
                    int y_pos = (p_player.GetRect().y + p_player.get_frame_height() * 0.5) - height_exp_frame * 0.5;

                    exp_main.set_frame(ex);
                    exp_main.SetRect(x_pos, y_pos);
                    exp_main.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                    SDL_Delay(15);
                }

                num_die++;
                if (num_die < 3)
                {
                    p_player.SetRect(0, 0);
                    p_player.set_comback_time(60);
                    SDL_Delay(700);
                    player_power.Decrease();
                    player_power.Render(g_screen);
                }
                else
                {
                    if (MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK)
                    {
                        close();
                        SDL_Quit();
                        return 0;
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

    SoundManager::Instance().clean();
    close();
    return 0;
}

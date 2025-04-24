#include "BossObject.h"

BossObject::BossObject()
{
    frame_ = 0;
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    think_time_ = 0;
    map_x_ = 0;
    map_y_ = 0;
    last_fire_time_ = 0;
}

BossObject::~BossObject()
{

}

bool BossObject::LoadImg(std::string path, SDL_Renderer* screen)
{

    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w / FRAME_NUM_16;
        height_frame_ = rect_.h;
    }

    return ret;
}

void BossObject::Show(SDL_Renderer* des)
{
    if (think_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        frame_++;
        if (frame_ >= 4) frame_ = 0;

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

        SDL_RenderCopy(des, frame_images_[frame_], NULL, &renderQuad);
    }
}

void BossObject::DoPlayer(Map& g_map)
{
    if(think_time_ == 0)
    {
    x_val_ = 0;
    y_val_ += GRAVITY_SPEED;

    if (y_val_ >= MAX_FALL_SPEED)
    {
        y_val_ = MAX_FALL_SPEED;
    }

    if (input_type_.left_ == 1)
    {
        x_val_ -= PLAYER_SPEED;
    }
    else if (input_type_.right_ == 1)
    {
        x_val_ += PLAYER_SPEED;
    }

    if (input_type_.jump_ == 1)
    {
        if (on_ground_ == true)
        {
            y_val_ = - PLAYER_HIGHT_VAL;
        }

        input_type_.jump_ = 0;
    }

    CheckToMap(g_map);
    }

    if (think_time_ > 0)
    {
        think_time_ --;
        if (think_time_ == 0)
        {
            InitPlayer();
        }
    }
}

void BossObject::InitPlayer()
{
    x_val_ = 0;
    y_val_ = 0;

    if (x_pos_ > 280)
    {
        x_pos_ -= 280;
    }
    else{
        x_pos_ = 0;
        y_pos_ = 0;
        think_time_ = 0;
        input_type_.left_ = 1;
    }
}

void BossObject::CenterEntityOnMap(Map& g_map)
{
    g_map.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
    if (g_map.start_x_ < 0)
    {
        g_map.start_x_ = 0;
    }
    else if (g_map.start_x_ + SCREEN_WIDTH >= g_map.max_x_)
    {
        g_map.start_x_ = g_map.max_x_ - SCREEN_WIDTH;
    }

    g_map.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
    if (g_map.start_y_ < 0)
    {
        g_map.start_y_ = 0;
    }
    else if (g_map.start_y_ + SCREEN_HEIGHT >= g_map.max_y_)
    {
        g_map.start_y_ = g_map.max_y_ - SCREEN_HEIGHT;
    }
}

void BossObject::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    on_ground_ = 0;

    //check chieu ngang
    int height_min = height_frame_;

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (x1 >=0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // di chuyen sang phai
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if ((val1 != BLANK_TILE ) || (val2 != BLANK_TILE))
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if ((val1 != BLANK_TILE ) || (val2 != BLANK_TILE ))
            {
                x_pos_ = (x1 + 1)* TILE_SIZE;
                x_val_ = 0;

            }
        }
    }

    // check chieu doc
    int width_min = width_frame_;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];


            if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE ))
            {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;

            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if ((val1 != BLANK_TILE ) || (val2 != BLANK_TILE ))
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0 )
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_ )
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }
    if (y_pos_ > map_data.max_y_)
    {

    }
}

void BossObject::InitBullet(SDL_Renderer* screen)
{
    BulletObject* p_bullet = new BulletObject();
    p_bullet->set_bullet_type(BulletObject::STORM_BULLET);
    bool ret = p_bullet->LoadImgBullet(screen);

    if (ret)
        {
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->set_is_move(true);

            // Canh giữa chiều ngang và đặt ở tầm 2/3 chiều cao của boss
            int bullet_x = rect_.x + width_frame_ / 2 - 20;
            int bullet_y = rect_.y + height_frame_ * 2 / 3;

            p_bullet->SetRect(bullet_x, bullet_y);
            p_bullet->set_x_val(15);

            // NEW: chuẩn bị animation 4 frame
            p_bullet->set_clips();

            bullet_list_.push_back(p_bullet);
        }
}

void BossObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_fire_time_ >= 3000)  // Mỗi 3000 ms = 3 giây
    {
        InitBullet(des);
        last_fire_time_ = current_time;
    }
    for (int i=0; i<bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(des);
            }
            else{
                    p_bullet->Free();
                    bullet_list_.erase(bullet_list_.begin() + i);
            }
        }
    }
}

bool BossObject::LoadImgFrames(SDL_Renderer* screen)
{
    for (int i = 0; i < 4; i++)
    {
        std::string path = "character//Giant//" + std::to_string(i + 1) + ".png";
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load %s: %s", path.c_str(), IMG_GetError());
            return false;
        }
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        frame_images_[i] = SDL_CreateTextureFromSurface(screen, surface);

        if (!frame_images_[i])
        {
            SDL_Log("Failed to create texture from %s: %s", path.c_str(), SDL_GetError());
            return false;
        }

        SDL_FreeSurface(surface);
    }

    // Giả sử mọi ảnh có cùng kích thước
    SDL_QueryTexture(frame_images_[0], NULL, NULL, &width_frame_, &height_frame_);
    return true;
}


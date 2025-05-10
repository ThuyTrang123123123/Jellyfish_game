#include "BulletObject.h"

BulletObject::BulletObject()
{
    bullet_type_ = SPHERE_BULLET;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;

    frame_ = 0;
    animation_count_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
}

BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;

    if (bullet_type_ == LASER_BULLET)
    {
        ret = LoadImg("character//laser.png", des);
    }
    else if (bullet_type_ == STORM_BULLET)
    {
        ret = LoadImg("character//storm.png", des);
        if (ret)
        {
            width_frame_ = rect_.w / 4;
            height_frame_ = rect_.h;
            set_clips();
        }
    }
    else // SPHERE_BULLET mặc định
    {
        ret = LoadImg("character//sphere.png", des);
    }

    return ret;
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
    }
}


void BulletObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i=0; i<4 ; i++)
        {
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void BulletObject::Render(SDL_Renderer* des)
{
    if (p_object_ != nullptr)
    {
        if (bullet_type_ == STORM_BULLET)
        {
            animation_count_++;
            if (animation_count_ >= 6)
            {
                frame_++;
                if (frame_ >= 4) frame_ = 0;
                animation_count_ = 0;
            }

            SDL_Rect* current_clip = &frame_clip_[frame_];
            SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
            SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
        }
        else
        {
            // Các loại đạn không animation
            SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h };
            SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
        }
    }
}

#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = SPHERE_BULLET;
}

BulletObject::~BulletObject()
{

}

void BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    if (bullet_type_ == LASER_BULLET)
    {
        LoadImg("character//laser.png", des);
    }
    else{
        LoadImg("character//sphere.png", des);
    }
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

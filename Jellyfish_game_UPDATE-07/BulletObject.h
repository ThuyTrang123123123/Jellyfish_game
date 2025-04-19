
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObjects.h"
#include "Common.h"

class BulletObject : public BaseObject
{

public:
    BulletObject();
    ~BulletObject();

    enum BulletDir
    {
        DIR_RIGHT = 20,

        DIR_LEFT = 21,
    };

    //luu tru dan
    enum BulletType
    {
        SPHERE_BULLET = 50,
        LASER_BULLET = 51,
    };

    void set_x_val (const int& xVal) {x_val_ = xVal;}
    void set_y_val (const int& yVal) {y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move (const bool& isMove) {is_move_ = isMove;}
    bool get_is_move() const {return is_move_;}

    void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir_ = bulletDir;}
    int get_bullet_dir() const {return bullet_dir_;}

    void HandleMove(const int& x_border, const int& y_border);

    //luu tru loai dan:
    void set_bullet_type(const unsigned int& bulletType) {bullet_type_ = bulletType;}
    unsigned int get_bullet_type() const {return bullet_type_;}

    bool LoadImgBullet(SDL_Renderer* des);

private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int bullet_dir_;

    //Lưu trữ các loại đạn:
    unsigned int bullet_type_;

};

#endif

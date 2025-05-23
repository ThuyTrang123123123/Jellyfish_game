#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

extern SDL_Window* g_window;
extern SDL_Renderer* g_screen;
extern SDL_Event g_event;

//Screen
const int FRAME_PER_SECOND = 25; // fps
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 0
bool InitData();
bool LoadBackground();
void close();

#define TILE_SIZE 70

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    std::string file_name_;
};

#endif

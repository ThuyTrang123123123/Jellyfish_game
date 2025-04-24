#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <string>
#include <iostream>

class SoundManager {
public:
    // Lấy instance đơn (singleton)
    static SoundManager& Instance();

    // Khởi tạo SDL_mixer
    bool init(int frequency = 44100,
              Uint16 format = MIX_DEFAULT_FORMAT,
              int channels = 2,
              int chunksize = 2048);

    // Phát nhạc nền (path tới file, -1 lặp vô hạn)
    bool playMusic(const std::string& path, int loops = -1);

    // Phát hiệu ứng bắn súng mỗi lần main player bắn
    void playShot();

    // Dừng nhạc và giải phóng tài nguyên
    void clean();

private:
    SoundManager();
    ~SoundManager();

    Mix_Music* music_;  // Con trỏ tới nhạc nền
    Mix_Chunk* shotEffect_; // Hiệu ứng bắn súng
};

#endif // SOUNDMANAGER_H

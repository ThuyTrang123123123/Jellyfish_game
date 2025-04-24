#include "SoundManager.h"

SoundManager::SoundManager()
  : music_(nullptr) {}

SoundManager::~SoundManager() {
    clean();
}

SoundManager& SoundManager::Instance() {
    static SoundManager instance;
    return instance;
}

bool SoundManager::init(int freq, Uint16 format, int channels, int chunksize) {
    // Khởi tạo hỗ trợ định dạng OGG
    int flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(flags) & flags) != flags) {
        std::cerr << "SDL_mixer OGG init failed! Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(freq, format, channels, chunksize) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: "
                  << Mix_GetError() << std::endl;
        return false;
    }

     // Tự động load và play nhạc nền sea.mp3
    music_ = Mix_LoadMUS("audio/sea.mp3");
    if (!music_) {
        std::cerr << "Failed to load background music sea.mp3: " << Mix_GetError() << std::endl;
    } else {
        Mix_PlayMusic(music_, -1);
    }
    // Load hiệu ứng bắn súng
    shotEffect_ = Mix_LoadWAV("audio/laserfire02.ogg");
    if (!shotEffect_) {
        std::cerr << "Failed to load shot effect: " << Mix_GetError() << std::endl;
    }
    return true;
}

bool SoundManager::playMusic(const std::string& path, int loops)
{
    if (music_) {
        Mix_HaltMusic();
        Mix_FreeMusic(music_);
        music_ = nullptr;
    }

    music_ = Mix_LoadMUS(path.c_str());
    if (!music_) {
        std::cerr << "Failed to load music '" << path << "'! SDL_mixer Error: "
                  << Mix_GetError() << std::endl;
        return false;
    }
    if (Mix_PlayMusic(music_, loops) < 0) {
        std::cerr << "Failed to play music! SDL_mixer Error: "
                  << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void SoundManager::playShot() {
    if (shotEffect_) {
        Mix_PlayChannel(-1, shotEffect_, 0);
    }
}

void SoundManager::clean() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
    if (music_) {
        Mix_FreeMusic(music_);
        music_ = nullptr;
    }
    if (shotEffect_) { Mix_FreeChunk(shotEffect_); shotEffect_ = nullptr; }
    Mix_CloseAudio();
    Mix_Quit();
}

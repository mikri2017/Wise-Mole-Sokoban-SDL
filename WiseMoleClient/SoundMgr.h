#pragma once

#include <SDL3_mixer/SDL_mixer.h>

enum class SndType
{
    MoveBox
};

class Mix_Chunk;

class SoundMgr
{
private:
    MIX_Mixer* m_mxr{ nullptr };

    MIX_Audio* move_box{ nullptr };

public:
    SoundMgr();
    ~SoundMgr();

    void play_sound(SndType snd_type);
};

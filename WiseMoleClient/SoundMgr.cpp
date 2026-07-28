#include "SoundMgr.h"
#include <iostream>

SoundMgr::SoundMgr()
{
    MIX_Init();

    m_mxr = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!m_mxr)
        std::cout << SDL_GetError() << std::endl;

    move_box = MIX_LoadAudio(m_mxr, "assets/sounds/move_box.mp3", true);
    if (!move_box)
        std::cout << SDL_GetError() << std::endl;
}

SoundMgr::~SoundMgr()
{
    MIX_DestroyAudio(move_box);

    MIX_DestroyMixer(m_mxr);

    MIX_Quit();
}

void SoundMgr::play_sound(SndType snd_type)
{
    if (snd_type == SndType::MoveBox)
        if (!MIX_PlayAudio(m_mxr, move_box))
            std::cout << SDL_GetError() << std::endl;
}

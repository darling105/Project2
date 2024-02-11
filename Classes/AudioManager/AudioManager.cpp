#include "AudioManager.h"
#include "AudioEngine.h"

AudioManager* AudioManager::_instance;

AudioManager* AudioManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new AudioManager();
    }
    return _instance;
}

void AudioManager::playMusic(std::string fileName)
{
    AudioEngine::stop(_bgmID);
    _bgmID = AudioEngine::play2d("Audio/Music/" + fileName, true, _musicVolume);
}

void AudioManager::playSFX(std::string fileName)
{
    AudioEngine::play2d("Audio/SFX/" + fileName, false, _sfxVolume);
}

void AudioManager::setMusicVolume(float newVolume)
{
    _musicVolume = newVolume;

    AudioEngine::setVolume(_bgmID, _musicVolume);
}

void AudioManager::setSFXVolume(float newVolume)
{
    _sfxVolume = newVolume;
}
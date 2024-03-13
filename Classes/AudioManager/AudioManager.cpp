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

AudioManager::AudioManager()
{
    _musicVolume = UserDefault::getInstance()->getFloatForKey("MusicVolume", 0.0f);
    _sfxVolume = UserDefault::getInstance()->getFloatForKey("SfxVolume", 0.0f);
}

void AudioManager::init()
{
    _musicVolume = UserDefault::getInstance()->getFloatForKey("MusicVolume", 0.0f);
    _sfxVolume = UserDefault::getInstance()->getFloatForKey("SfxVolume", 0.0f);
}
void AudioManager::playMusic(std::string fileName)
{
    AudioEngine::stop(_bgmID);
    _bgmID = AudioEngine::play2d("Audio/Music/" + fileName, true, _musicVolume);
}

void AudioManager::playSFX(std::string fileName)
{
    AudioEngine::stop(_sfxID);
    _sfxID = AudioEngine::play2d("Audio/SFX/" + fileName, false, _sfxVolume);
}

void AudioManager::setMusicVolume(float newVolume)
{
    _musicVolume = newVolume;

    AudioEngine::setVolume(_bgmID, _musicVolume);
}

void AudioManager::setSFXVolume(float newVolume)
{
    _sfxVolume = newVolume;

    AudioEngine::setVolume(_sfxID, _sfxVolume);
}

float AudioManager::getMusicVolume()
{
    return _musicVolume;
}
float AudioManager::getSFXVolume()
{
    return _sfxVolume;
}

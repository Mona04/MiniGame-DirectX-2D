#pragma once
#include "IResource.h"

enum class AudioType : uint
{
    Sound, Stream
};

class AudioClip final : public IResource
{
private:
	friend class ResourceManager;

private:
    AudioClip(class Context* context);
    ~AudioClip();

    AudioClip(const AudioClip& rhs); // 복사 생성자
    AudioClip& operator=(const AudioClip&) = delete;

    void SaveToFile(const std::string & path) override;
    void LoadFromFile(const std::string & path) override;

public:
    void Play();
    void Pause();
    void Stop();

    void SetLoop(bool bLoop);
    void SetMute(bool bMute);
    void SetPriority(int priority);
    void SetVolume(float volume);
    void SetPitch(float pitch);
    void SetPan(float pan);

    auto IsPlaying() -> const bool;

private:
    void CreateSound(const std::string& path);
    void CreateStream(const std::string& path);

    auto GetSoundMode() const -> const int;
    auto IsChannelValid() const -> const bool;

private:
    FMOD::System* system;
    FMOD::Sound* sound; //음원 객체
    FMOD::Channel* channel; //재생중인 음원

    AudioType audioType;
    float minDistance;
    float maxDistance;
    float volume = 0.3f;

    int loopMode;
    int rolloffMode;
    int result;
};
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

    void SetLoop(const bool& bLoop);
    void SetMute(const bool& bMute);
    void SetPriority(const int& priority);
    void SetVolume(const float& volume);
    void SetPitch(const float& pitch);
    void SetPan(const float& pan);

    auto IsPlaying() -> const bool;

    void Update();

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
    int loopMode;
    int rolloffMode;
    int result;
};
#pragma once
#include "IComponent.h"

class AudioSource : public IComponent
{
public:
    AudioSource(class Context* context);
    ~AudioSource();

	void SetAudioClip(const std::string& path, const std::string& name) { audioClip = resourceMgr->Load<AudioClip>(path, name); }
    void SetAudioClip(class AudioClip* audioClip) { this->audioClip = audioClip; }

    void Play();
    void Stop();
    void Pause();

    auto IsLoop() const -> const bool& { return bLoop; }
    void SetIsLoop(const bool& bLoop);

    auto IsMute() const -> const bool& { return bMute; }
    void SetIsMute(const bool& bMute);

    auto GetPriority() const -> const int& { return priority; }
    void SetPriority(const int& priority);

    auto GetVolume() const -> const float& { return volume; }
    void SetVolume(const float& volume);

    auto GetPitch() const -> const float& { return pitch; }
    void SetPitch(const float& pitch);

    auto GetPan() const -> const float& { return pan; }
    void SetPan(const float& pan);

	void Update() override {}
	void Render() override {}

private:
	class ResourceManager* resourceMgr;

    class AudioClip* audioClip;
    std::string path;
    bool bMute;
    bool bLoop;
    int priority;
    float volume;
    float pitch;
    float pan;
};
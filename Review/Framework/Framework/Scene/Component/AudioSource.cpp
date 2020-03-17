#include "Framework.h"
#include "AudioSource.h"
#include "Framework/Resource/AudioClip.h"

AudioSource::AudioSource(Context * context)
    : IComponent(context)
    , audioClip(nullptr)
    , path("")
    , bMute(false)
    , bLoop(false)
    , priority(128)
    , volume(1.0f)
    , pitch(1.0f)
    , pan(0.0f)
{
    resourceMgr = context->GetSubsystem<ResourceManager>();
	IComponent::type = ComponentType::AudioResource;
}

AudioSource::~AudioSource()
{
}

void AudioSource::Play()
{
    if (!audioClip)
        return;

    audioClip->Play();
    audioClip->SetLoop(bLoop);
    audioClip->SetMute(bMute);
    audioClip->SetPriority(priority);
    audioClip->SetVolume(volume);
    audioClip->SetPitch(pitch);
    audioClip->SetPan(pan);
}

void AudioSource::Stop()
{
    if (!audioClip)
        return;

    audioClip->Stop();
}

void AudioSource::Pause()
{
    if (!audioClip)
        return;

    audioClip->Pause();
}

void AudioSource::SetIsLoop(const bool & bLoop)
{
    if (!audioClip)
        return;

    if (this->bLoop == bLoop)
        return;

    this->bLoop = bLoop;
    audioClip->SetLoop(this->bLoop);
}

void AudioSource::SetIsMute(const bool & bMute)
{
    if (!audioClip)
        return;

    if (this->bMute == bMute)
        return;

    this->bMute = bMute;
    audioClip->SetMute(this->bMute);
}

void AudioSource::SetPriority(const int & priority)
{
    if (!audioClip)
        return;

    if (this->priority == priority)
        return;

    //Channel priority
    //0     : 가장 중요
    //255   : 가장 덜중요
    //128   : 기본값

    this->priority = Math::Clamp(priority, 0, 255);
    audioClip->SetPriority(this->priority);
}

void AudioSource::SetVolume(const float & volume)
{
    if (!audioClip)
        return;

    if (this->volume == volume)
        return;

    this->volume = Math::Clamp(volume, 0.0f, 1.0f);
    audioClip->SetVolume(this->volume);
}

void AudioSource::SetPitch(const float & pitch)
{
    if (!audioClip)
        return;

    if (this->pitch == pitch)
        return;

    this->pitch = Math::Clamp(pitch, 0.0f, 3.0f);
    audioClip->SetPitch(this->pitch);
}

void AudioSource::SetPan(const float & pan)
{
    if (!audioClip)
        return;

    if (this->pan == pan)
        return;

    this->pan = Math::Clamp(pan, -1.0f, 1.0f);
    audioClip->SetPan(this->pan);
}

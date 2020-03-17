#include "Framework.h"
#include "AudioClip.h"

AudioClip::AudioClip(Context * context)
    : IResource(context)
    , sound(nullptr)
    , channel(nullptr)
    , audioType(AudioType::Sound)
    , loopMode(FMOD_LOOP_OFF)
    , rolloffMode(FMOD_3D_LINEARROLLOFF)
    , minDistance(1.0f)
    , maxDistance(1000.0f)
{
    system = context->GetSubsystem<Audio>()->GetFMODSystem();
}

AudioClip::~AudioClip()
{
    if (!sound)
        return;

	result = sound->release();
    
	assert(result == FMOD_OK);
}

AudioClip::AudioClip(const AudioClip & rhs)
    : IResource(rhs.context)
    , sound(nullptr)
    , channel(nullptr)
    , audioType(rhs.audioType)
    , loopMode(rhs.loopMode)
    , rolloffMode(rhs.rolloffMode)
    , minDistance(rhs.minDistance)
    , maxDistance(rhs.maxDistance)
{
    system = rhs.system;

    LoadFromFile("../../_Assets/Audio/" + rhs.resourcePath);
}

void AudioClip::SaveToFile(const std::string & path)
{
}

void AudioClip::LoadFromFile(const std::string & path)
{
    switch (audioType)
    {
    case AudioType::Sound:
        CreateSound(path);
        break;

    case AudioType::Stream:
        CreateStream(path);
        break;

    default:
        break;
    }
}

void AudioClip::Play()
{
    //사운드가 플레이중인지 체크
    //현재 재생중이면 리턴
    if (IsChannelValid())
    {
        bool bPaused = false;
        result = channel->getPaused(&bPaused);
        assert(result == FMOD_OK);

        if (bPaused)
        {
            result = channel->setPaused(false);
            assert(result == FMOD_OK);
            return;
        }
    }
	if (IsPlaying())
        return;

    //사운드 플레이
    result = system->playSound(sound, nullptr, false, &channel);
    assert(result == FMOD_OK);
}

void AudioClip::Pause()
{
    if (!IsChannelValid())
        return;

    //사운드가 일시정지 상태인지 체크
    bool bPaused = false;
    result = channel->getPaused(&bPaused);
    assert(result == FMOD_OK);

    //사운드가 일시정지 상태이면 리턴
    if (bPaused)
        return;

    //사운드 일시정지
    result = channel->setPaused(true);
    assert(result == FMOD_OK);
}

void AudioClip::Stop()
{
    //사운드가 플레이중인지 체크
    //사운드가 플레이중이 아니면 리턴
    if (!IsPlaying())
        return;

    //사운드 중지
    result = channel->stop();
    assert(result == FMOD_OK);

    channel = nullptr;
}

void AudioClip::SetLoop(const bool & bLoop)
{
    loopMode = bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

    if (!sound)
        return;

    if (bLoop)
    {
        result = sound->setLoopCount(-1);
        assert(result == FMOD_OK);
    }

    result = sound->setMode(GetSoundMode());
    assert(result == FMOD_OK);
}

void AudioClip::SetMute(const bool & bMute)
{
    if (!IsChannelValid())
        return;

    result = channel->setMute(bMute);
    assert(result == FMOD_OK);
}

void AudioClip::SetPriority(const int & priority)
{
    if (!IsChannelValid())
        return;

    result = channel->setPriority(priority);
    assert(result == FMOD_OK);
}

void AudioClip::SetVolume(const float & volume)
{
    if (!IsChannelValid())
        return;

    result = channel->setVolume(volume);
    assert(result == FMOD_OK);
}

void AudioClip::SetPitch(const float & pitch)
{
    if (!IsChannelValid())
        return;

    result = channel->setPitch(pitch);
    assert(result == FMOD_OK);
}

void AudioClip::SetPan(const float & pan)
{
    if (!IsChannelValid())
        return;

    result = channel->setPan(pan);
    assert(result == FMOD_OK);
}

auto AudioClip::IsPlaying() -> const bool
{
    if (!IsChannelValid())
        return false;

    bool bPlaying = false;
    result = channel->isPlaying(&bPlaying);
    assert(result == FMOD_OK);

    return bPlaying;
}

void AudioClip::Update()
{
    //TODO :
}

void AudioClip::CreateSound(const std::string & path)
{
    result = system->createSound
    (
        path.c_str(),
        GetSoundMode(),
        nullptr,
        &sound
    );

    assert(result == FMOD_OK);

    result = sound->set3DMinMaxDistance(minDistance, maxDistance);
    assert(result == FMOD_OK);
}

void AudioClip::CreateStream(const std::string & path)
{
    result = system->createStream
    (
        path.c_str(),
        GetSoundMode(),
        nullptr,
        &sound
    );
    assert(result == FMOD_OK);

    result = sound->set3DMinMaxDistance(minDistance, maxDistance);
    assert(result == FMOD_OK);
}

auto AudioClip::GetSoundMode() const -> const int
{
    return FMOD_3D | loopMode | rolloffMode;
}

auto AudioClip::IsChannelValid() const -> const bool
{
    if (!channel)
        return false;

    bool dummy;
    return channel->isPlaying(&dummy) == FMOD_OK;
}

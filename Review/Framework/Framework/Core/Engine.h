#pragma once
#include <atomic>

enum EngineFlags : ulong
{
	ENGINEFLAGS_UPDATE = 1UL << 0,
	ENGINEFLAGS_RENDER = 1UL << 1,
	ENGINEFLAGS_GAME = 1UL << 2,
	ENGINEFLAGS_EDITOR = 1UL << 3,
	ENGINEFLAGS_PLAY = 1UL << 4,
};


class Engine final
{
public:
	Engine();
	~Engine();

	class Context* GetContext() const { return context; }

	void Initialize();
	void Update();
	void Render();
	void Resize(const uint& width, const uint& height);

public:
	static const ulong& GetEngineFlags() { return engineFlags; }
	static void SetEngineFlags(const ulong& flags) { engineFlags = flags; }
	static void OnEngineFlags(const EngineFlags& flags) { engineFlags |= flags; }
	static void OffEngineFlags(const EngineFlags& flags) { engineFlags &= ~flags; }
	static const bool IsOnEngineFlags(const EngineFlags& flags) { return (engineFlags & flags) > 0UL; }
	static void ToggleEngineFlags(const EngineFlags& flags) { IsOnEngineFlags(flags) ? OffEngineFlags(flags) : OnEngineFlags(flags); }

	bool DoesUpdateEnd() { return updateEnd; }

	void Destroy() { bDestroy = true; }
	bool IsDestroy() { return bDestroy; }

	class UI_Component_Frame* GetFrame() { return frame; }

private:
	class Context* context;
	class Timer* timer;
	class UI_Component_Frame* frame;

	static ulong engineFlags;
	std::atomic_bool updateEnd = false;
	std::atomic_bool bDestroy = false;
};
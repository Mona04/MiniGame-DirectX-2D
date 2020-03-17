#pragma once
#include "../ISubsystem.h"

// ������ ���ĸ� class Thread �� std::thread �� �ִ� ������ŭ �ְ� ������Ų��.
// �׸��� Task �� �־ �׶����� std::thread �� Ǯ���ش�.

class Task final
{
public:
	typedef std::function<void()> Process;
	
public:
	Task(Process&& process) { this->process = std::forward<Process>(process); };
	~Task() = default;

	void Execute() { process();}

private:
	Process process;
};

class Thread final : public ISubsystem
{
public:
	Thread(class Context* context);
	~Thread();

	const bool Initialize() override;

	void Invoke();
	int LeftJobs() { return nRunningTask; }

	template <typename Process> void AddTask(Process&& process);

private:
	std::vector<std::thread> threads;
	std::queue<std::shared_ptr<Task>> tasks;
	std::mutex taskMutex;
	std::condition_variable conditionVar;
	uint threadCount;
	uint nRunningTask = 0;
	bool bStopping;
};

// thread ���� �θ��� thread �� ȣ�� �Ұ�����
template<typename Process>
inline void Thread::AddTask(Process&& process)
{
	if (threads.empty())
	{
		LOG_WARNING("No available thread");
		process();
		return;
	}

	std::unique_lock<std::mutex> lock(taskMutex);
	{
		tasks.push(std::make_shared<Task>(std::bind(std::forward<Process>(process))));
		nRunningTask++;
	}
	lock.unlock();

	conditionVar.notify_one();
}

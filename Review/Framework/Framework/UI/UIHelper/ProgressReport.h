#pragma once

struct Progress final
{
	Progress() { Clear(); }

	void Clear() 
	{
		status.clear(); 
		numDone = 0;
		numTotal = 0;
		bLoading = false;
	}

	std::string status;
	uint numDone;
	uint numTotal;
	bool bLoading;
};

class ProgressReport final
{
public:
	static constexpr uint Scene = 1;  // 애 아이디임 ㅋㅋ

public:
	static ProgressReport* Get() { static ProgressReport instance; return &instance; }

public:
	void SetDefault(const uint& progressID, const uint& total, class ProgressBar* bar);
	void OneStepForward(const uint& progressID);
	const bool& GetIsLoadingOfReport(const uint& progressID);

private:
	const std::string GetStatus(const uint& progressID)
	{
		return reports[progressID].status;
	}

	void SetStatus(const uint& progressID, const std::string& status) 
	{
		reports[progressID].status = status;
	}

	void SetNumDoneOfReport(const uint& progressID, const uint& numDone)
	{
		Progress& report = reports[progressID];
		report.numDone = numDone;
		if (report.numDone >= report.numTotal)
		{
			report.numDone = report.numTotal;
			report.bLoading = false;
		}
	}

	void SetNumTotalOfReport(const uint& progressID, const uint& numTotal)
	{
		Progress& report = reports[progressID];
		report.numTotal = numTotal;
	}

	void SetIsLoadingOfReport(const uint& progressID, const bool& bLoading)
	{
		reports[progressID].bLoading = bLoading;
	}

	const float GetPercentageOfReport(const uint& progressID)
	{
		Progress& report = reports[progressID];
		return static_cast<float>(report.numDone) / static_cast<float>(report.numTotal);
	}

	void ClearReport(const uint& progressID) { reports[progressID].Clear(); progressBar = nullptr; }

private:
	ProgressReport() { reports[Scene] = Progress(); }
	~ProgressReport() = default;
	
private:
	std::map<uint, Progress> reports;
	class ProgressBar* progressBar = nullptr;
};
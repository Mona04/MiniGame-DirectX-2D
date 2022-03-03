#include "Framework.h"
#include "ProgressReport.h"


void ProgressReport::SetDefault(const uint& progressID, const uint& total, ProgressBar* bar)
{
	std::lock_guard<std::mutex> lock(mutex);

	ClearReport(progressID);
	SetIsLoadingOfReport(progressID, true);
	SetNumTotalOfReport(progressID, total);
	SetNumDoneOfReport(progressID, 0);
	progressBar = bar;
	progressBar->SetProgress(reports[progressID].numDone, reports[progressID].numTotal);
}

void ProgressReport::OneStepForward(const uint& progressID)
{
	std::lock_guard<std::mutex> lock(mutex);

	SetNumDoneOfReport(progressID, reports[progressID].numDone + 1);
	progressBar->SetProgress(reports[progressID].numDone, reports[progressID].numTotal);
}

const bool& ProgressReport::GetIsLoadingOfReport(const uint& progressID)
{
	std::lock_guard<std::mutex> lock(mutex);

	return reports[progressID].bLoading;
}


#include "ui.h"
#include "timer.h"
#include "trace.h"

UI::UI()
{
	controls["TotalProgressBar"] = NULL;
	controls["FileProgressBar"]  = NULL;
	controls["TotalDownloaded"]	 = NULL;
	controls["FileDownloaded"]   = NULL;
	controls["FileName"]         = NULL;
	controls["Speed"]            = NULL;
	controls["Status"]           = NULL;
	controls["ElapsedTime"]      = NULL;
	controls["RemainingTime"]    = NULL;
	controls["NextButton"]		 = NULL;
	controls["WizardForm"]		 = NULL;

	detailed = false;
}

UI::~UI()
{
}

void UI::connectControl(tstring name, HWND handle)
{
	controls[toansi(name)] = handle;
}

void UI::setFileName(tstring filename)
{
	setLabelText(controls["FileName"], filename);
}

void UI::setProgressInfo(DWORDLONG totalSize, DWORDLONG totalDownloaded, DWORDLONG fileSize, DWORDLONG fileDownloaded)
{
	int filePercents  = (int)(100.0 / ((double)fileSize  / (double)fileDownloaded));
	int totalPercents = (int)(100.0 / ((double)totalSize / (double)totalDownloaded));

	setProgressBarPos(controls["TotalProgressBar"], totalPercents);
	setProgressBarPos(controls["FileProgressBar"],  filePercents);
}

void UI::setSpeedInfo(DWORD speed, DWORD remainingTime)
{
	setLabelText(controls["RemainingTime"], Timer::msecToStr(remainingTime, _T("%02u:%02u:%02u")));
	setLabelText(controls["Speed"],         itotstr((int)((double)speed / 1024.0 * 1000.0)) + _T("KB/s"));
}

void UI::setSizeTimeInfo(DWORDLONG totalSize, DWORDLONG totalDownloaded, DWORDLONG fileSize, DWORDLONG fileDownloaded, DWORD elapsedTime)
{
	setLabelText(controls["ElapsedTime"],     Timer::msecToStr(elapsedTime, _T("%02u:%02u:%02u")));
	setLabelText(controls["TotalDownloaded"], itotstr(totalDownloaded/1024) + _T(" of ") + itotstr(totalSize/1024) + _T("KB"));
	setLabelText(controls["FileDownloaded"],  itotstr(fileDownloaded/1024)  + _T(" of ") + itotstr(fileSize/1024)  + _T("KB"));
}

void UI::setLabelText(HWND l, tstring text)
{
	if(l)
		SendMessage(l, WM_SETTEXT, 0, (LPARAM)text.c_str());
}

void UI::setProgressBarPos(HWND pb, int pos)
{
	if(pb)
		PostMessage(pb, PBM_SETPOS, (int)((65535.0 / 100.0) * pos), 0);
}

int UI::messageBox(tstring text, tstring caption, DWORD type)
{
	return MessageBox(controls["WizardForm"], text.c_str(), caption.c_str(), type);
}
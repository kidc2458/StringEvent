/*
	프로그램 설명: event,mutex 동시 사용 사례
*/

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

using namespace std;

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

typedef struct _SynchString {
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex;
}SynchString;

SynchString gSynString;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThreads[2];
	DWORD dwThreadIDs[2];

	gSynString.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	gSynString.hMutex = CreateMutex(NULL, FALSE, NULL);

	//귀찮으니 에러 메세지 생략

	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadIDs[0]);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, CountThreadFunction, NULL, 0, (unsigned*)&dwThreadIDs[1]);

	_fputts(_T("Insert string: "), stdout);
	_fgetts(gSynString.string, 30, stdin);

	SetEvent(gSynString.hEvent);

	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	CloseHandle(gSynString.hEvent);
	CloseHandle(gSynString.hMutex);
	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(gSynString.hEvent, INFINITE);
	WaitForSingleObject(gSynString.hMutex, INFINITE);

	_fputts(_T("Output string: "), stdout);
	_fputts(gSynString.string, stdout);

	ReleaseMutex(gSynString.hMutex);
	return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(gSynString.hEvent, INFINITE);
	WaitForSingleObject(gSynString.hMutex, INFINITE);

	_tprintf(_T("Output string length: %d\n"), _tcsclen(gSynString.string) - 1);

	ReleaseMutex(gSynString.hMutex);
	return 0;
}
/*
프로그램 설명: 수동 리셋 모드 동기화 적용 사례
*/


#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define TRREADCOUNT 2

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

TCHAR str[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread[TRREADCOUNT];
	DWORD dwThreadID[TRREADCOUNT];

	hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	if (hEvent == nullptr)
	{
		_fputts(_T("Event object create error\n"), stdout);
		return -1;
	}


	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadID[0]);
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, CountThreadFunction, NULL, 0, (unsigned*)&dwThreadID[1]);
	if (hThread[0] == nullptr || hThread[1] == nullptr)
	{
		_fputts(_T("Thread create error\n"), stdout);
		return -1;
	}


	_fputts(_T("Insert sting: "), stdout);
	_fgetts(str, 30, stdin);
	SetEvent(hEvent);

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);


	CloseHandle(hEvent);

	for (int i = 0; i < TRREADCOUNT; ++i)
	{
		CloseHandle(hThread[i]);
	}

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);
	_fputts(_T("output strng: "), stdout);
	_fputts(str, stdout);
	return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);
	_tprintf(_T("output string length: %d \n"), _tcslen(str) - 1);
	return 0;
}
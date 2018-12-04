/*
	프로그램 설명: 1. 생산자/소비자 모델의 이해
				   2. 동기화 event에 대한 이해
*/

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <process.h>	/* _ beginthreadex, _endthreadex*/
#include "StringEvent.h"

using namespace std;

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR str[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread;
	DWORD dwThreadID;

	hEvent = CreateEvent(
		NULL,	//lpEventAttributes : 보안 속성을 지정할때 사용. 핸들을 자식 프로세스에게 상속하고자 할 경우 NULL이 아닌 다른 값
		TRUE,	//bManualReset : 수동 리셋(True) / 자동 리셋 모드(False)를 결정.
		FALSE,	//이벤트 오브젝트의 초기 상태. True(Signaled), False(None-Signaled)
		NULL	//이벤트 오브젝트에 이름을 줄 경우. NULL은 이름 없는 오브젝트
	);

				if (hEvent == NULL)
				{
					_fputts(_T("Event object creation error \n"), stdout);
					return -1;
				}

	hThread = (HANDLE)_beginthreadex(
		NULL, 0,
		OutputThreadFunction,
		NULL, 0,
		(unsigned*)&dwThreadID
	);

				if (hThread == 0)
				{
					_fputts(_T("Thread create error \n"), stdout);
					return -1;
				}

	_fputts(_T("Insert string: "), stdout);
	_fgetts(str, 30, stdin);

	SetEvent(hEvent);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hEvent);
	CloseHandle(hThread);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	//이벤트가 Signaled 상태가 되기를 기다린다.
	WaitForSingleObject(hEvent, INFINITE);
	_fputts(_T("Output string : "), stdout);
	_fputts(str, stdout);

	return 0;
}
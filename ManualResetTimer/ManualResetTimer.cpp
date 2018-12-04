/*
	프로그램 설명: 수동 리셋 타이머 오브젝트에 대한 이해
*/

#define _WIN32_WINNT	0x0501

#include <iostream>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	//타이머 오브젝트 생성
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds...\n"));

	SetWaitableTimer(
		hTimer,			//hTimer: 알림을 설정할 타이머 오브젝트 핸들
		&liDueTime,		//pDueTime: 알림이 울리는 시간
		5000,				//lPeriod: 타이머가 주기적으로 알람을 울리게 할때 사용하는 전달 인자. 밀리세컨드, 0은 주기적인 알람을 사용 안함.
		NULL,			//
		NULL,			//
		FALSE			//전원 관리 매개변수
	);
	while (true)
	{
		WaitForSingleObject(hTimer, INFINITE);
		_tprintf(_T("Timer was singnaled.\n"));
		MessageBeep(MB_ICONEXCLAMATION);
	}

	return 0;
}
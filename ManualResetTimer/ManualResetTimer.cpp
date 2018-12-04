/*
	���α׷� ����: ���� ���� Ÿ�̸� ������Ʈ�� ���� ����
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

	//Ÿ�̸� ������Ʈ ����
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds...\n"));

	SetWaitableTimer(
		hTimer,			//hTimer: �˸��� ������ Ÿ�̸� ������Ʈ �ڵ�
		&liDueTime,		//pDueTime: �˸��� �︮�� �ð�
		5000,				//lPeriod: Ÿ�̸Ӱ� �ֱ������� �˶��� �︮�� �Ҷ� ����ϴ� ���� ����. �и�������, 0�� �ֱ����� �˶��� ��� ����.
		NULL,			//
		NULL,			//
		FALSE			//���� ���� �Ű�����
	);
	while (true)
	{
		WaitForSingleObject(hTimer, INFINITE);
		_tprintf(_T("Timer was singnaled.\n"));
		MessageBeep(MB_ICONEXCLAMATION);
	}

	return 0;
}
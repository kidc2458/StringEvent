/*
	���α׷� ����: 1. ������/�Һ��� ���� ����
				   2. ����ȭ event�� ���� ����
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
		NULL,	//lpEventAttributes : ���� �Ӽ��� �����Ҷ� ���. �ڵ��� �ڽ� ���μ������� ����ϰ��� �� ��� NULL�� �ƴ� �ٸ� ��
		TRUE,	//bManualReset : ���� ����(True) / �ڵ� ���� ���(False)�� ����.
		FALSE,	//�̺�Ʈ ������Ʈ�� �ʱ� ����. True(Signaled), False(None-Signaled)
		NULL	//�̺�Ʈ ������Ʈ�� �̸��� �� ���. NULL�� �̸� ���� ������Ʈ
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
	//�̺�Ʈ�� Signaled ���°� �Ǳ⸦ ��ٸ���.
	WaitForSingleObject(hEvent, INFINITE);
	_fputts(_T("Output string : "), stdout);
	_fputts(str, stdout);

	return 0;
}
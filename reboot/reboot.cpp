// reboot.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "reboot.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//�ϐ�
	HANDLE hToken;
	TOKEN_PRIVILEGES tokenPriv;
	BOOL bRet;



	//�A�N�Z�X�g�[�N�����J��
	bRet = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	//�V���b�g�_�E��������LUID���擾����
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &(tokenPriv.Privileges[0].Luid));
	tokenPriv.PrivilegeCount = 1;
	tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;


	//�V���b�g�_�E��������LUID�ŁA�V���b�g�_�E��������L���ɂ���
	bRet = AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, 0, NULL, NULL);


	ExitWindowsEx(EWX_REBOOT, 0);

	return (int)1;
}


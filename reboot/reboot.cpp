// reboot.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "reboot.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//変数
	HANDLE hToken;
	TOKEN_PRIVILEGES tokenPriv;
	BOOL bRet;



	//アクセストークンを開く
	bRet = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	//シャットダウン権限のLUIDを取得する
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &(tokenPriv.Privileges[0].Luid));
	tokenPriv.PrivilegeCount = 1;
	tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;


	//シャットダウン権限のLUIDで、シャットダウン権限を有効にする
	bRet = AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, 0, NULL, NULL);


	ExitWindowsEx(EWX_REBOOT, 0);

	return (int)1;
}


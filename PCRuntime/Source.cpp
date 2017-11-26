#include<iostream>
#include<string>
#include<regex>
#include<chrono>
#include<thread>
#include<Windows.h>
#include<AccCtrl.h>
#include<Aclapi.h>
using namespace std;

DWORD ProtectProcess(void)
{
	HANDLE hProcess = GetCurrentProcess();
	PACL pEmptyDacl;
	DWORD dwErr;

	// using malloc guarantees proper alignment
	pEmptyDacl = (PACL)malloc(sizeof(ACL));

	if (!InitializeAcl(pEmptyDacl, sizeof(ACL), ACL_REVISION))
	{
		dwErr = GetLastError();
	}
	else
	{
		dwErr = SetSecurityInfo(hProcess, SE_KERNEL_OBJECT,
			DACL_SECURITY_INFORMATION, NULL, NULL, pEmptyDacl, NULL);
	}

	free(pEmptyDacl);
	return dwErr;
}

int main(void)
{
	ProtectProcess();
	int time=0;
	string str;
	regex regex_pattern("^([1-9][0-9]*)$");
	while(1)
	{
		cout << "Insert time till shutdown (minutes): ";
		cin >> str;
		if (regex_match(str, regex_pattern)) break;
		cout << "Incorect data. Try again." << endl;
	} 
	time = stoi(str);
	chrono::minutes duration(time);
	chrono::seconds message(600);
	string cmd = "c:\\windows\\system32\\shutdown.exe /s /t 0";
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	this_thread::sleep_for(duration-message);
	MessageBoxA(NULL,"10 minutes left untill shutdown","INFO", MB_ICONWARNING);
	this_thread::sleep_for(message);
	system(cmd.c_str());
}

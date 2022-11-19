#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <tlhelp32.h>


using namespace std;


BOOL ThreadFunction(DWORD ProcPID, bool ThreadContinuation) 
{ 
	BOOL          BooleanResult = FALSE;
	HANDLE        ThreadHandler = NULL; 
    THREADENTRY32 TEBAddress        = {0}; 
 

    ThreadHandler = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); 
    if (ThreadHandler == INVALID_HANDLE_VALUE) 
        return (FALSE);     

    TEBAddress.dwSize = sizeof(THREADENTRY32); 
  
    if (Thread32First(ThreadHandler, &TEBAddress)) 
    { 
        do 
        { 
            if (TEBAddress.th32OwnerProcessID == ProcPID) 
            {
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, TEBAddress.th32ThreadID);
				if (ThreadContinuation)
				{
					ResumeThread(hThread);
				}
				else
				{
					SuspendThread(hThread);
				}
				
				CloseHandle(hThread);
            } 
        }
        while (Thread32Next(ThreadHandler, &TEBAddress)); 
		cout << "\n[INFO] PROC PID " << ProcPID << " Operation Has Been Successful.\n";
        BooleanResult = TRUE; 
    } 
	else
	{
		cout << "[INFO] Unsuccessful Attempt!";
		BooleanResult = FALSE;
	}

    CloseHandle (ThreadHandler); 
 
    return (BooleanResult); 
} 



int _tmain(int argc, TCHAR* argv[], TCHAR*)
{
	if (argc <= 1)
	{
		cerr << _T("Usage:\n    suspex.exe PID </resume>\n");
		cerr << _T("/continue: resumes the execution of PID\n");
		return 1;
	}
	else
	{
		DWORD pid = _ttoi(argv[1]);
		if (pid == 0)
		{
			return 1;
		}
		else
			ThreadFunction(pid, (argc > 2) && (!_tcsicmp(argv[2], _T("/continue"))));
	}

	return 0;
}

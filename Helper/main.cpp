#include <iostream>
#include "windows.h"
#include "../entry/entry.h"

#define INITIAL_STRING "TRY_TO_CHANGE_ME"
#define END_STRING "WELL_DONE"

typedef char* (*Func)(pid_t, std::string, std::string);

bool InjectDLL(DWORD pid, char *dllName);
bool StaticInjection(DWORD pid);
bool DynamicInjection(DWORD pid, char *dllName);

int main() {
    pid_t pid = 3532;
    char *s;
    s = (char *)calloc(1024, sizeof(char ));
    strcpy(s, "C:\\Users\\shine\\Desktop\\Dev\\DLLInjection\\entry\\cmake-build-debug\\libentry.dll");
//    StaticInjection(pid);
    DynamicInjection(pid, s);
//    InjectDLL(pid, s);
    return 0;
}

bool StaticInjection(DWORD pid) {
    Injection(pid, INITIAL_STRING, END_STRING);
    return true;
}

bool DynamicInjection(DWORD pid, char *dllName) {
    bool result = false;
    HMODULE hInstance = LoadLibraryA(dllName);
    if (hInstance !=  nullptr) {
        Func func = (Func) GetProcAddress(hInstance, "Injection");
        if (func != nullptr) {
            func(pid, INITIAL_STRING, END_STRING);
            result = true;
        }
        FreeLibrary(hInstance);
    }
    return result;
}

bool InjectDLL(DWORD pid, char *dllName)
{
    HMODULE hdll = LoadLibraryA("Kernel32.dll");
	auto LoadLibraryA = (LPVOID)GetProcAddress(hdll, "LoadLibraryA");
	HANDLE handle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_VM_WRITE |
                                PROCESS_CREATE_THREAD | PROCESS_CREATE_PROCESS,
                                FALSE, pid);
	if (handle) {
        LPVOID memAlloc = VirtualAllocEx(handle, nullptr, strlen(dllName) + 1, MEM_RESERVE | MEM_COMMIT,
                                         PAGE_READWRITE);
        WriteProcessMemory(handle, memAlloc, dllName, strlen(dllName) + 1, nullptr);

        HANDLE HThread = CreateRemoteThread(handle, nullptr, 0,
                                                    (LPTHREAD_START_ROUTINE) LoadLibraryA, (LPVOID) memAlloc, 0, nullptr);

        if (HThread == nullptr) {
            printf("error\n");
        } else {
            WaitForSingleObject(HThread, INFINITE);
            CloseHandle(HThread);
        }
        FreeLibrary(hdll);
    }
	CloseHandle(handle);
}
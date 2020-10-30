#include "entry.h"

#include <windows.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define INITIAL_STRING "TRY_TO_CHANGE_ME"
#define END_STRING "WELL_DONE"

void Injection(pid_t pid, std::string pattern, std::string newData) {
    bool stringFound = false;
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (handle) {
        unsigned char *p = nullptr;
        MEMORY_BASIC_INFORMATION info;

        for (p = nullptr; VirtualQueryEx(handle, p, &info, sizeof(info)) == sizeof(info); p += info.RegionSize) {
            std::vector<char> buffer;

            if (info.State == MEM_COMMIT && (info.Type == MEM_MAPPED || info.Type == MEM_PRIVATE)) {
                SIZE_T bytes_read;
                std::vector<char>::iterator offset;

                buffer.resize(info.RegionSize);
                ReadProcessMemory(handle, p, buffer.data(), info.RegionSize, &bytes_read);

                offset = std::search(buffer.begin(), buffer.end(), pattern.begin(), pattern.end());

                if (offset != buffer.end()) {
                    LPVOID addr = p + std::distance(buffer.begin(), offset);

                    std::cout << addr << std::endl;

                    if (WriteProcessMemory(handle, addr, newData.data(), newData.length() + 1, NULL)) {
                        std::cout << "String Changed to " + newData  << std::endl;
                        stringFound = true;
                    }
                }
            }
        }
        if (!stringFound) {
            std::cout << "String not FOUND!" << std::endl;
        }
        CloseHandle(handle);
    } else {
        std::cout << "handle not FOUND!" << std::endl;
    }
}

BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            Injection(getpid(), INITIAL_STRING, END_STRING);
            break;
        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}
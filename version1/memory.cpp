#include "includes.h"


static int pID{};


namespace memory
{
	
    //Opening Handle   
    DWORD GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
    {
        DWORD modBaseAddr = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 modEntry;
            modEntry.dwSize = sizeof(modEntry);

            if (Module32First(hSnap, &modEntry)) {
                do {
                    if (!_wcsicmp(modEntry.szModule, modName)) {
                        modBaseAddr = (DWORD)modEntry.modBaseAddr;
                        break;
                    }


                } while (Module32Next(hSnap, &modEntry));
            }
        }

        CloseHandle(hSnap);
        return modBaseAddr;
    }
    
    
    
    
    template <typename T>
    T read(HANDLE process, LPCVOID address)
	{
        LPVOID buffer{};
        ReadProcessMemory(process, address, &buffer, sizeof(T), 0);
        std::cout << &buffer << ' \n';
        Sleep(50);
        system("cls");
        return &buffer;
     

	}

    auto write(HANDLE process, LPVOID address, LPCVOID value)
    {
       //WriteProcessMemory(process, address, value, sizeof(address), NULL);
    }
    

    DWORD GPID(const std::wstring& processName) {
        DWORD processID = 0;  // Default to 0, which means process not found
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hSnapshot != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32);

            // Get the first process
            if (Process32First(hSnapshot, &pe32)) {
                do {
                    if (std::wstring(pe32.szExeFile) == processName) {
                        processID = pe32.th32ProcessID;
                        break;
                    }
                } while (Process32Next(hSnapshot, &pe32));
            }

            CloseHandle(hSnapshot); // Clean up the snapshot object
        }
        else {
            std::cerr << "Failed to create snapshot of processes" << std::endl;
        }

        return processID;
    }

    //Opening the handle
    
 }

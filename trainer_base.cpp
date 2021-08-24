#include "trainer_base.h"
#include <iostream>

uintptr_t GetModuleBaseAddress(DWORD procId, std::wstring modName, BOOL isWOW64) {
    uintptr_t modBaseAddr = 0;
    DWORD dwFlag = isWOW64 ? TH32CS_SNAPMODULE32 : TH32CS_SNAPMODULE;

    HANDLE hSnap = CreateToolhelp32Snapshot(dwFlag, procId);

    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!_wcsicmp(modEntry.szModule, modName.c_str())) {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    } else {
        std::cout << "oops: " << GetLastError() << std::endl;
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

TrainerBase::TrainerBase() : hProcess(NULL), processID(0), isWOW64(FALSE), window_name(L"") { }

TrainerBase::TrainerBase(const wchar_t* window_name) : hProcess(NULL), processID(0), isWOW64(FALSE), window_name(window_name) { }

int TrainerBase::scan_process_mem(int mod_addr_n, std::wstring mod_addr_names[]) {
    mod_addr = std::map<std::wstring, uintptr_t>();
    handle = FindWindow(nullptr, window_name);

    if (!handle) {
        std::wcout << "Window " << window_name << " not found" << std::endl;
        return 0;
    }

    GetWindowThreadProcessId(handle, &processID);
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    IsWow64Process(hProcess, &isWOW64);

    for (int i = 0; i < mod_addr_n; i++) {
        mod_addr.emplace(mod_addr_names[i], GetModuleBaseAddress(processID, mod_addr_names[i], isWOW64));
        std::wcout << "Base address of " << mod_addr_names[i] << ": 0x" << std::hex << mod_addr[mod_addr_names[i]] << std::endl;
    }

    return 1;
}

uint8_t TrainerBase::read_mem_byte(uintptr_t address) {
    uint8_t result = 0x0;

    ReadProcessMemory(hProcess, LPVOID(address), &result, sizeof(result), NULL);

    return result;
}

uint16_t TrainerBase::read_mem_double_byte(uintptr_t address) {
    uint16_t result = 0x0;

    ReadProcessMemory(hProcess, LPVOID(address), &result, sizeof(result), NULL);

    return result;
}

uint32_t TrainerBase::read_mem_word(uintptr_t address) {
    uint32_t result = 0x0;

    ReadProcessMemory(hProcess, LPVOID(address), &result, sizeof(result), NULL);

    return result;
}

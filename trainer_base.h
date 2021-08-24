#ifndef TRAINER_BASE_H
#define TRAINER_BASE_H

#include <Windows.h> // OS functions
#include <Psapi.h> // To get process info
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <map>
#include <memory>

class TrainerBase {
protected:
    // Win32 API variables
    HANDLE hProcess;
    HWND handle;
    DWORD processID;
    BOOL isWOW64;

    // Other variables
    const wchar_t* window_name;
    std::map<std::wstring, uintptr_t> mod_addr;

public:
    TrainerBase();
    TrainerBase(const wchar_t* window_name);

    int scan_process_mem(int mod_addr_n = 0, std::wstring mod_addr_names[] = {});
    uint8_t read_mem_byte(uintptr_t address);
    uint16_t read_mem_double_byte(uintptr_t address);
    uint32_t read_mem_word(uintptr_t address);
};

#endif // TRAINER_BASE_H

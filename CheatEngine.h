// CheatEngine.h - 通用Hook引擎
#pragma once
#include "CheatItem.h"
#include <atlstr.h>

class CListBox;

class CCheatEngine
{
public:
    CCheatEngine(HANDLE hProcess, CListBox* pLog = nullptr);
    ~CCheatEngine();

    void SetModuleBase(DWORD_PTR dwModuleBase);
    void SetProcess(HANDLE hProcess);
    void SetLogControl(CListBox* pLog);

    BOOL EnableCheatItem(CheatItem& item);
    BOOL DisableCheatItem(CheatItem& item);
    BOOL ToggleCheatItem(CheatItem& item, BOOL enable);

    DWORD_PTR GetModuleBase() const { return m_dwModuleBase; }
    BOOL AllocateMemory(DWORD_PTR& outAddress, SIZE_T size = 2048);
    void FreeMemory(DWORD_PTR address);
    BOOL WriteBytes(DWORD_PTR address, const BYTE* bytes, size_t size);
    BOOL ReadBytes(DWORD_PTR address, BYTE* buffer, size_t size);
    BOOL ChangeMemoryProtection(DWORD_PTR address, size_t size, DWORD newProtect, DWORD& oldProtect);

    void Log(const TCHAR* format, ...);

private:
    BOOL CalculateJmpOffset(DWORD_PTR fromAddr, DWORD_PTR toAddr, DWORD& outOffset);
    BOOL WriteHookInstruction(DWORD_PTR targetAddr, DWORD_PTR jumpToAddr, int hookSize);
    BOOL BuildFullCode(const CheatItem& item, BYTE* outCode, size_t& outSize);
    void LogBytes(const TCHAR* prefix, const BYTE* bytes, size_t size);

    HANDLE m_hProcess;
    CListBox* m_pLog;
    DWORD_PTR m_dwModuleBase;
};

// CheatEngine.cpp - 通用Hook引擎实现
#include "pch.h"
#include "CheatEngine.h"
#include <stdarg.h>

CCheatEngine::CCheatEngine(HANDLE hProcess, CListBox* pLog)
    : m_hProcess(hProcess)
    , m_pLog(pLog)
    , m_dwModuleBase(0)
{
}

CCheatEngine::~CCheatEngine()
{
}

void CCheatEngine::SetModuleBase(DWORD_PTR dwModuleBase)
{
    m_dwModuleBase = dwModuleBase;
}

void CCheatEngine::SetProcess(HANDLE hProcess)
{
    m_hProcess = hProcess;
}

void CCheatEngine::SetLogControl(CListBox* pLog)
{
    m_pLog = pLog;
}

void CCheatEngine::Log(const TCHAR* format, ...)
{
    if (!m_pLog)
        return;

    CString strLog;
    va_list args;
    va_start(args, format);
    strLog.FormatV(format, args);
    va_end(args);

    CTime time = CTime::GetCurrentTime();
    CString strTime = time.Format(_T("[%H:%M:%S] "));

    m_pLog->AddString(strTime + strLog);

    int nCount = m_pLog->GetCount();
    if (nCount > 0)
        m_pLog->SetCurSel(nCount - 1);
}

void CCheatEngine::LogBytes(const TCHAR* prefix, const BYTE* bytes, size_t size)
{
    if (!m_pLog)
        return;

    CString strBytes;
    for (size_t i = 0; i < size; i++)
    {
        strBytes.AppendFormat(_T("%02X "), bytes[i]);
    }
    Log(_T("%s: %s"), prefix, strBytes);
}

BOOL CCheatEngine::CalculateJmpOffset(DWORD_PTR fromAddr, DWORD_PTR toAddr, DWORD& outOffset)
{
    outOffset = (DWORD)(toAddr - (fromAddr + 5));
    return TRUE;
}

BOOL CCheatEngine::AllocateMemory(DWORD_PTR& outAddress, SIZE_T size)
{
    if (!m_hProcess)
        return FALSE;

    outAddress = (DWORD_PTR)VirtualAllocEx(
        m_hProcess, NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (!outAddress)
    {
        Log(_T("[CheatEngine] 分配内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    Log(_T("[CheatEngine] 内存分配成功: 0x%08X"), outAddress);
    return TRUE;
}

void CCheatEngine::FreeMemory(DWORD_PTR address)
{
    if (m_hProcess && address)
    {
        VirtualFreeEx(m_hProcess, (LPVOID)address, 0, MEM_RELEASE);
        Log(_T("[CheatEngine] 内存已释放: 0x%08X"), address);
    }
}

BOOL CCheatEngine::WriteBytes(DWORD_PTR address, const BYTE* bytes, size_t size)
{
    if (!m_hProcess)
        return FALSE;

    SIZE_T bytesWritten = 0;
    BOOL bResult = WriteProcessMemory(m_hProcess, (LPVOID)address, bytes, size, &bytesWritten);

    if (!bResult || bytesWritten != size)
    {
        Log(_T("[CheatEngine] 写入内存失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    return TRUE;
}

BOOL CCheatEngine::ReadBytes(DWORD_PTR address, BYTE* buffer, size_t size)
{
    if (!m_hProcess)
        return FALSE;

    SIZE_T bytesRead = 0;
    return ReadProcessMemory(m_hProcess, (LPCVOID)address, buffer, size, &bytesRead)
        && bytesRead == size;
}

BOOL CCheatEngine::ChangeMemoryProtection(DWORD_PTR address, size_t size, DWORD newProtect, DWORD& oldProtect)
{
    if (!m_hProcess)
        return FALSE;
    return VirtualProtectEx(m_hProcess, (LPVOID)address, size, newProtect, &oldProtect);
}

BOOL CCheatEngine::WriteHookInstruction(DWORD_PTR targetAddr, DWORD_PTR jumpToAddr, int hookSize)
{
    DWORD jmpOffset = 0;
    CalculateJmpOffset(targetAddr, jumpToAddr, jmpOffset);

    BYTE jmpInstruction[7] = { 0 };
    jmpInstruction[0] = 0xE9;
    jmpInstruction[1] = (BYTE)(jmpOffset & 0xFF);
    jmpInstruction[2] = (BYTE)((jmpOffset >> 8) & 0xFF);
    jmpInstruction[3] = (BYTE)((jmpOffset >> 16) & 0xFF);
    jmpInstruction[4] = (BYTE)((jmpOffset >> 24) & 0xFF);

    for (int i = 5; i < hookSize; i++)
        jmpInstruction[i] = 0x90;

    DWORD oldProtect = 0;
    if (!ChangeMemoryProtection(targetAddr, hookSize, PAGE_EXECUTE_READWRITE, oldProtect))
    {
        Log(_T("[Hook] 修改内存保护失败，错误码: %d"), GetLastError());
        return FALSE;
    }

    BOOL bResult = WriteBytes(targetAddr, jmpInstruction, hookSize);
    ChangeMemoryProtection(targetAddr, hookSize, oldProtect, oldProtect);

    if (bResult)
        Log(_T("[Hook] Hook指令写入成功"));

    return bResult;
}

BOOL CCheatEngine::BuildFullCode(const CheatItem& item, BYTE* outCode, size_t& outSize)
{
    DWORD_PTR returnAddress = *item.pTargetAddress + item.returnOffset;
    DWORD_PTR jmpPosition = *item.pAllocatedAddress + item.newSize - 1;
    DWORD jmpOffset = (DWORD)(returnAddress - (jmpPosition + 5));

    memcpy(outCode, item.newBytes, item.newSize);

    size_t jmpPos = item.newSize - 1;
    outCode[jmpPos] = 0xE9;
    outCode[item.newSize] = (BYTE)(jmpOffset & 0xFF);
    outCode[item.newSize + 1] = (BYTE)((jmpOffset >> 8) & 0xFF);
    outCode[item.newSize + 2] = (BYTE)((jmpOffset >> 16) & 0xFF);
    outCode[item.newSize + 3] = (BYTE)((jmpOffset >> 24) & 0xFF);

    outSize = item.newSize + 4;
    return TRUE;
}

BOOL CCheatEngine::EnableCheatItem(CheatItem& item)
{
    CString strItemName(item.name);

    if (!m_hProcess)
    {
        Log(_T("[%s] 错误: 未附加进程"), strItemName);
        return FALSE;
    }

    if (*item.pEnabled)
    {
        Log(_T("[%s] 已经启用"), strItemName);
        return TRUE;
    }

    Log(_T("[%s] 正在启用..."), strItemName);

    if (*item.pTargetAddress == 0)
    {
        *item.pTargetAddress = m_dwModuleBase + item.offset;
        Log(_T("[%s] 目标地址: 0x%08X"), strItemName, *item.pTargetAddress);
    }

    if (item.originalSize <= 16)
    {
        BYTE currentBytes[16] = { 0 };
        if (ReadBytes(*item.pTargetAddress, currentBytes, item.originalSize))
            LogBytes(strItemName + _T(" 当前字节码"), currentBytes, item.originalSize);
    }

    if (item.hookType == HookType::NOP_REPLACE)
    {
        DWORD oldProtect = 0;
        if (!ChangeMemoryProtection(*item.pTargetAddress, item.originalSize,
            PAGE_EXECUTE_READWRITE, oldProtect))
            return FALSE;

        BYTE* nopBytes = new BYTE[item.originalSize];
        memset(nopBytes, 0x90, item.originalSize);
        BOOL bResult = WriteBytes(*item.pTargetAddress, nopBytes, item.originalSize);
        delete[] nopBytes;
        ChangeMemoryProtection(*item.pTargetAddress, item.originalSize, oldProtect, oldProtect);

        if (bResult)
        {
            *item.pEnabled = TRUE;
            Log(_T("[%s] 成功启用！"), strItemName);
        }
        return bResult;
    }
    else
    {
        if (!AllocateMemory(*item.pAllocatedAddress))
            return FALSE;
        *item.pMemoryAllocated = TRUE;

        size_t fullCodeSize = 0;
        BYTE* fullCode = new BYTE[2048];

        if (!BuildFullCode(item, fullCode, fullCodeSize))
        {
            delete[] fullCode;
            return FALSE;
        }

        LogBytes(strItemName + _T(" 自定义代码"), fullCode, fullCodeSize);

        if (!WriteBytes(*item.pAllocatedAddress, fullCode, fullCodeSize))
        {
            delete[] fullCode;
            return FALSE;
        }
        delete[] fullCode;

        if (!WriteHookInstruction(*item.pTargetAddress, *item.pAllocatedAddress, item.hookInstructionSize))
        {
            FreeMemory(*item.pAllocatedAddress);
            *item.pAllocatedAddress = 0;
            *item.pMemoryAllocated = FALSE;
            return FALSE;
        }

        *item.pEnabled = TRUE;
        Log(_T("[%s] 成功启用！"), strItemName);
        return TRUE;
    }
}

BOOL CCheatEngine::DisableCheatItem(CheatItem& item)
{
    CString strItemName(item.name);

    if (!m_hProcess)
    {
        Log(_T("[%s] 错误: 未附加进程"), strItemName);
        return FALSE;
    }

    if (!*item.pEnabled)
    {
        Log(_T("[%s] 已经禁用"), strItemName);
        return TRUE;
    }

    Log(_T("[%s] 正在禁用..."), strItemName);

    if (*item.pTargetAddress == 0)
        *item.pTargetAddress = m_dwModuleBase + item.offset;

    if (item.hookType == HookType::NOP_REPLACE)
    {
        DWORD oldProtect = 0;
        if (!ChangeMemoryProtection(*item.pTargetAddress, item.originalSize,
            PAGE_EXECUTE_READWRITE, oldProtect))
            return FALSE;

        BOOL bResult = WriteBytes(*item.pTargetAddress, item.originalBytes, item.originalSize);
        ChangeMemoryProtection(*item.pTargetAddress, item.originalSize, oldProtect, oldProtect);

        if (bResult)
        {
            *item.pEnabled = FALSE;
            Log(_T("[%s] 成功禁用！"), strItemName);
        }
        return bResult;
    }
    else
    {
        DWORD oldProtect = 0;
        if (!ChangeMemoryProtection(*item.pTargetAddress, item.originalSize,
            PAGE_EXECUTE_READWRITE, oldProtect))
            return FALSE;

        BOOL bResult = WriteBytes(*item.pTargetAddress, item.originalBytes, item.originalSize);
        ChangeMemoryProtection(*item.pTargetAddress, item.originalSize, oldProtect, oldProtect);

        if (bResult)
        {
            *item.pEnabled = FALSE;
            if (*item.pMemoryAllocated && *item.pAllocatedAddress)
            {
                FreeMemory(*item.pAllocatedAddress);
                *item.pAllocatedAddress = 0;
                *item.pMemoryAllocated = FALSE;
            }
            Log(_T("[%s] 成功禁用！"), strItemName);
        }
        return bResult;
    }
}

BOOL CCheatEngine::ToggleCheatItem(CheatItem& item, BOOL enable)
{
    return enable ? EnableCheatItem(item) : DisableCheatItem(item);
}

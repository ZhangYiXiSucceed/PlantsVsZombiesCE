// CheatItem.h - 修改器项结构体定义
#pragma once
#include <windows.h>

enum class HookType {
    NOP_REPLACE,
    JMP_HOOK,
};

struct CheatItem {
    const char* name;
    DWORD offset;
    HookType hookType;
    const BYTE* originalBytes;
    size_t originalSize;
    const BYTE* newBytes;
    size_t newSize;
    int hookInstructionSize;
    int returnOffset;
    BOOL* pEnabled;
    DWORD_PTR* pTargetAddress;
    DWORD_PTR* pAllocatedAddress;
    BOOL* pMemoryAllocated;
};

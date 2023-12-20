#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "proc.h"

extern HWND hwnd;
extern HANDLE pHandle;
extern DWORD baseAddress;

class memory
{
public:
	static void write(DWORD offset, std::vector<DWORD> offsets, void* input, size_t size);
	static void read(DWORD offset, std::vector<DWORD> offsets, void* output, size_t size);

	static void setHWDN(HWND* _hwnd);
	static void setpHandle(HANDLE* _pHandle);
	static void setBaseAddress(DWORD _baseAddress);
private:
	static DWORD ResolvePointerChain(DWORD offset, std::vector<DWORD> offsets);
};


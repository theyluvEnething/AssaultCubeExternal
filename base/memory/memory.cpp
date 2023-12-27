#include "memory.h"

HWND hwnd;
HANDLE pHandle;
DWORD baseAddress;

void memory::setHWDN(HWND* _hwnd) { hwnd = *_hwnd; }
void memory::setpHandle(HANDLE* _pHandle) { pHandle = *_pHandle; }
void memory::setBaseAddress(DWORD _baseAddress) { baseAddress = _baseAddress; }
HANDLE memory::getpHandle() { return pHandle; }
HWND memory::getHWND() { return hwnd; }

DWORD memory::ResolvePointerChain(DWORD offset, std::vector<DWORD> offsets) {
	if (!hwnd || !pHandle) {
		std::cout << "HWND or pHandle not initialized." << std::endl;
		return -1;
	}

	DWORD address = NULL;
	ReadProcessMemory(pHandle, (LPVOID*)(baseAddress + offset), &address, sizeof(address), 0);

	for (int i = 0; i < offsets.size() - 1; i++) {
		ReadProcessMemory(pHandle, (LPVOID*)(address + offsets[i]), &address, sizeof(address), 0);
	}
	return address + offsets[offsets.size() - 1];
}

void memory::write(DWORD offset, std::vector<DWORD> offsets, void* value, size_t size) {
	DWORD address = ResolvePointerChain(offset, offsets);
	WriteProcessMemory(pHandle, (LPVOID*)address, value, size, 0);
}

void memory::read(DWORD offset, std::vector<DWORD> offsets, void* output, size_t size) {
	DWORD address = ResolvePointerChain(offset, offsets);
	ReadProcessMemory(pHandle, (LPVOID*)(address), output, size, 0);
}

void memory::read(DWORD address, void* output, size_t size) {
	ReadProcessMemory(pHandle, (LPVOID*)(address), output, size, 0);
}
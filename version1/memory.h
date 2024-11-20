#pragma once


namespace memory
{

	template <typename T>
	T read(HANDLE process, LPCVOID address);
	//auto write(HANDLE process, LPVOID address, LPCVOID value);
	DWORD GPID(const std::wstring& processName);

	DWORD GetModuleBaseAddress(DWORD procID, const wchar_t* modName);
	
}
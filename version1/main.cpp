#include "includes.h"

//DWORD *buffer {};





int main()
{
	SetConsoleTitleA("AssaultCubeTrainer");

	
	std::cout << "debug or nah???\n\n1 = YES\n2 = NO\n\n";
	bool debug{};
	std::cin >> debug;
	
	int buffer{};


	HWND hWnd = FindWindowA(0, ("AssaultCube"));
	
	//HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	DWORD pID{};
	GetWindowThreadProcessId(hWnd, &pID);
	HANDLE AssaultCube = nullptr;
	AssaultCube = OpenProcess(PROCESS_ALL_ACCESS, NULL, pID);
	DWORD baseModule = memory::GetModuleBaseAddress(pID, L"ac_client.exe"); //getting base address 
	
	/*std::cout << "[1] - ReadProcessMemory\n[2] - WriteProcessMemory\n\n";
	int choice{};
	std::cin >> choice;
	if (choice == 1)
	{
		system("cls");
		ReadProcessMemory(AssaultCube, (LPCVOID)(0x0781B44), &buffer, sizeof(buffer), NULL);
		//ac_client.exe+ 0x18AC00 = offset of health
		std::cout << buffer << std::endl;
		Sleep(5000);
	}
	else if (choice == 2)
	{
		
		int newValue{2000};
		
		
		system("cls");
		WriteProcessMemory(AssaultCube, (LPVOID)(baseModule + 0x18AC00),  &newValue, sizeof(newValue), NULL);
		std::cout << "\n\n WRITTEN";
	}
	*/
	/*int LocalHealthPTR{};
	ReadProcessMemory(AssaultCube, (LPCVOID)(0x006C2514), &LocalHealthPTR, sizeof(LocalHealthPTR), NULL);
	system("cls");
	ReadProcessMemory(AssaultCube, (LPCVOID)(baseModule + 0x18AC00), &buffer, sizeof(buffer), NULL);
	//ac_client.exe+ 0x18AC00 = local player address
	std::cout << "Static HP value " << LocalHealthPTR << std::endl;
	std::cout << "Static HP address " << &LocalHealthPTR << std::endl;
	std::cout << "Pointer address " <<  &buffer << std::endl;
	std::cout << "Pointer value " << buffer << std::endl;
	
	Sleep(5000);			
	*/
	using localOffset = int;
	localOffset healthptr{ 0xEC };
	localOffset ammoptr{ 0x140 };
	int localPlayer{};
	int localHealth{};
	int localAmmo{};
	ReadProcessMemory(AssaultCube, (LPCVOID)(baseModule + 0x18AC00), &localPlayer, sizeof(localPlayer), NULL);
	ReadProcessMemory(AssaultCube, (LPCVOID)(localPlayer + healthptr), &localHealth, sizeof(localHealth), NULL);

	
	while (true)
	{
		int newHealth{ localHealth + 20 };
		int newAmmo{ localAmmo + 20 };


		WriteProcessMemory(AssaultCube, LPVOID(localPlayer + healthptr), &newHealth, sizeof(newHealth), NULL);
		ReadProcessMemory(AssaultCube, (LPCVOID)(localPlayer + healthptr), &localHealth, sizeof(localHealth), NULL);
		std::cout << "\nHP: " << localHealth;

		ReadProcessMemory(AssaultCube, (LPCVOID)(localPlayer + ammoptr), &localAmmo, sizeof(localAmmo), NULL);
		WriteProcessMemory(AssaultCube, LPVOID(localPlayer + ammoptr), &newAmmo, sizeof(newAmmo), NULL);
		std::cout << "\nAmmo: " << localAmmo;
	}
	
	
}
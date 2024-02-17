#include "folderOperation.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <string>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /*time*/
using namespace std;

const string strLocalDirectory = pathToFolder;
string filePath;


//shouldItBeRenamed(); jest wylaczone
//minimize wylaczone


bool setBackground(int i)
{
	stringstream ssFilePath;

	ssFilePath << strLocalDirectory << setfill('0') << setw(2) << to_string(i) << ".jpg";

	//Returns true on success, false otherwise. 
	if (SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)ssFilePath.str().c_str(),
		SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != 0)
	{
		filePath = ssFilePath.str();
		return true;
	}
	return false;
}

void randomWallpaper(int max)		
{
	int time = 20, x = 0;
	int const maxSkip = 10;
	int skip[maxSkip];	//don't repeat at least [m] times

//	while (true)																		
	{
		int i = rand() % (max);
		for (int a = 0; a < maxSkip; a++)
		{
			if (skip[a] == i) {
				i = rand() % (max);
				a = 0;
			}
		}
		skip[x] = i;

		if (setBackground(i)) {
			cout << "Tapeta nr " << i << endl;
		}
		else { //print error type
			DWORD DWLastError = GetLastError();
			cout << "\nError: " << std::hex << DWLastError;
		}

		//its used in loop version
		x++; //Przed if aby nie wyszlo od [0] do [maxSkip - 1]
		if (x == maxSkip) {
			x = 1;
		}

		//cooldown
	//	Sleep(1000 * 60 * time); //co min minut
	}

}


void programLoop()
{
	int max = howManyFiles();
	cout << "Tapet bedzie " << max << endl;

	randomWallpaper(max);
}


void shouldItBeRenamed()
{
	bool wola;
	cout << "Uzywaj kopii zapasowej na wszelki wypadek.\nChcesz zmienic nazwy plikow w F:/TBB/? \n\n0 - nie \n1 - tak \n";
	cin >> wola;
	if (wola)
	{
		if (renameFiles() == 0)		cout << "\nPliki zyskaly nowa tozsamosc. Juz ich nie znajda!\n\n";
		else						cout << "\nMoj Panie, pliki sie buntuja!\n\n";
	}
}

void minimize()
{
	HWND handle = GetConsoleWindow();
	ShowWindow(handle, SW_MINIMIZE);
}

void close() {
	HWND handle = GetConsoleWindow();
	PostMessage(handle, WM_CLOSE, 0, 0);
}

int main()
{
	setlocale(LC_CTYPE, "Polish");
	srand(time(NULL));

	struct tm* ptr;
	struct hourAndMin
	{
		char min;
		char hour;
	};
	time_t now;


	now = time(NULL);
	ptr = localtime(&now);

	cout << "Poczatek o " << (*ptr).tm_hour << ':' << ptr->tm_min << endl;
	//shouldItBeRenamed();	
	renameFiles();
	//minimize();
	programLoop(); //petla wylaczona
//	close();

}






//
//int main()
//{
//	const wchar_t* path = L"F:\\WALLPAPER_ENGINE\\meve2";
//
//	//for (int i = 0; i < 10; i++)
//	{
//		/*Sleep(1000);
//		if (i % 2 == 0)
//			path = L"F:\\WALLPAPER_ENGINE\\meve2";
//		else
//			path = L"F:\\WALLPAPER_ENGINE\\meve1";*/
//
//		int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)path, SPIF_UPDATEINIFILE);
//
//		cout << result << endl;
//	}
//}

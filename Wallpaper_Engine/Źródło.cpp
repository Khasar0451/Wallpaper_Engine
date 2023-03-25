#include "folderOperation.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <string>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /*time*/
using namespace std;

const string strLocalDirectory = pathToFolder;// "R:/Wallpapers/DeathStrandingWallpapers";
string filePath;


//shouldItBeRenamed(); jest wylaczone
//minimize wy���zone


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

void randomWallpaper(int max)		//dodaj co� w styl ze 5 pod rzad nie bedzie takich samych, czyli array 
{
	int time = 20, x = 0;
	int const maxSkip = 10;
	int skip[maxSkip];	//don't repeat at least [m] times

//	while (true)																		<---------- dzialanie w petli wylczone (sleep tez, uruchom go bo cos sie rozwali bez sleepa w petli)
	{
		int i = rand() % (max); //+1 by od 1 do max
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
	//		saveToTxt(i, max);										<--------- zapis do txt (statystyki)
		}
		else { //print error type
			DWORD DWLastError = GetLastError();
			cout << "\nError: " << std::hex << DWLastError;
		}

		x++; //Przed if aby nie wyszlo od [0] do [maxSkip - 1]
		if (x == maxSkip) {
			x = 1;
		}


		//cooldown
	//	Sleep(1000 * 60 * time); //co min minut
	}

}

void inOrderWallpaper(int max)
{
	for (int i = rand() % max; i <= max; i++)
	{
		if (setBackground(i)) {
			cout << "Tapeta nr " << i << "\n";
		}
		else { //print error type
			DWORD DWLastError = GetLastError();
			cout << "\nError: " << std::hex << DWLastError;
		}
		//cooldown
		Sleep(1000 * 60 * 10); //co 20 minut

		//repeat
		if (i == max) i = -1;
	}
}

void programLoop()
{
	int max = howManyFiles();
	cout << "Tapet b�dzie " << max << endl;

	randomWallpaper(max);
}



void shouldItBeRenamed()
{
	bool wola;
	cout << "Uzywaj kopii zapasowej na wszelki wypadek.\nChcesz zmienic nazwy plikow w F:/TBB/? \n\n0 - nie \n1 - tak \n";
	cin >> wola;
	if (wola)
	{
		if (renameFiles() == 0)		cout << "\nPliki zyska�y now� to�samo��. Ju� ich nie znajd�!\n\n";
		else						cout << "\nM�j Panie, pliki si� buntuj�!\n\n";
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

	cout << "Zacz��e� o " << (*ptr).tm_hour << ':' << ptr->tm_min << endl;
	//shouldItBeRenamed();	
	renameFiles();
	//minimize();
	//	saveTime(struct hourAndMin);
	programLoop(); //petla wylaczona
	close();

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

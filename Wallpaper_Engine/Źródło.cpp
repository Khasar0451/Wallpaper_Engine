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

void setWallpaper(int number) {
	if (setBackground(number)) {
		cout << "Tapeta nr " << number << endl;
	}
	else { //print error type
		DWORD DWLastError = GetLastError();
		cout << "\nError: " << std::hex << DWLastError;
	}

}

void loopSetWallpaper(int max)
{
	int time = 20;

	while (true)																	
	{
		int i = rand() % (max);
		setWallpaper(i);

		//cooldown
		Sleep(1000 * 60 * time); //co min minut
	}

}


void programLoop()
{
	int max = howManyFiles();
	cout << "Tapet bedzie " << max << endl;
	
	loopSetWallpaper(max);
	setWallpaper(rand() % (max));

	//randomWallpaper(max);
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

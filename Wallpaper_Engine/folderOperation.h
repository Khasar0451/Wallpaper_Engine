#pragma once
#pragma warning(disable : 4996)
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <filesystem>
#include <errno.h>
#include <iomanip> //setfill, setw
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

const string pathToFolder = "R:/Wallpapers/GeneralWallpapers/";

int renameFiles();
int howManyFiles();

#include "folderOperation.h"
using namespace std;
namespace fs = std::filesystem;

int renameFiles()
{

    string oldName, newName;
    stringstream ssOldName, ssNewName;
    int result = 0, i = 0;

    for (const auto& entry : fs::directory_iterator(pathToFolder))
    {
        ssOldName << entry.path().string();
        oldName = ssOldName.str();
        ssNewName << pathToFolder << setfill('0') << setw(2) << i << ".jpg"; 
        newName = ssNewName.str();

        result = rename(oldName.c_str(), newName.c_str());

        if (result != 0) cout << "Error when renaming " << strerror(errno) << endl;

        //make stringstreams empty, ready for a new directory
        ssOldName.str("");
        ssNewName.str("");
        i++;
    }
    return result;
}

int howManyFiles()
{
    int i = 0;
    for (const auto& entry : fs::directory_iterator(pathToFolder))
    {
        i++;
    }
    return i;
}
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
        ssNewName << pathToFolder << setfill('0') << setw(2) << i << ".jpg"; //dont forget to add .jpg
        newName = ssNewName.str();

        //rename; change string for const char* with .c_str(), because yes
        result = rename(oldName.c_str(), newName.c_str());

        //if error              /*Z jakiegoœ powodu zawsze printuje, nawet jesli success ("File exists")*/
       // if (result != 0) cout << strerror(errno) << endl;

        //make stringstreams empty, ready for a new directory
        ssOldName.str("");
        ssNewName.str("");
        i++;

    }
    return result;
}

int howManyFiles()
{
    int i = 0; //BY£O "-1, by zaczê³o liczyæ od 0". nwm czemu, zmieni³em na i = 0 (a z max usun¹³em +1 w ProgramLoop())
    for (const auto& entry : fs::directory_iterator(pathToFolder))
    {
        i++;
    }
    return i;
}
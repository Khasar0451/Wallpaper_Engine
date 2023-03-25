#include "folderOperation.h"
using namespace std;
namespace fs = std::filesystem;

//string pathToFolder = "R:/Wallpapers/DeathStrandingWallpapers";

//DAJ WARNING, ZATRZYMUJ¥CY PROGRAM I PROSZ¥CY BY U¯YWAÆ GO TYLKO NA KOPII ZAPasowej
//
//void saveTime(struct hourAndMin)
//{
//    fstream timeStats;
//    timeStats.open("F:/statystyki_czasu.txt");
//
//}

void saveToTxt(int nr, int max)
{
    int all = 0;
    fstream stats;
    stats.open("R:/statystyki.txt", ios::in | ios::out | ios::binary);

    //vector<int> line; Nie potrzbuje wektora jesli uda mi sie skocz do linii zrobic
    if (stats.is_open())
    {
        int score = 0;
        //  Resetowanie pliku do 000
/*        for (int i = 1; i <= howManyFiles(); i++)
        {

            stats << setfill('0') << setw(2) << i << ". " << setfill('0') << setw(3) << score << endl;
        }
            stats << "Iloœæ cykli: " << setfill('0') << setw(6) << all << endl << endl;    */
            //    for (int i = 1; i <= howManyFiles(); i++)
            //    {

            //        stats << setfill('0') << setw(2) << i << ". " << ""<<setfill('0') << setw(3) << score << endl;
            //    }

          //  stats.clear();*/



            //seekg szuka kursorem w pliku otworzonym binarnie miejsca z wynikiem, wczytuje go, inkrementuje i wpisuje (znowu
            // seek, ale teraz seekp bo do pisania). setfill aby seekg mia³ sta³¹ odleg³oœæ do szukania, zdefiniowan¹ ni¿ej:
            //-1 -> bo numery tapet s¹ od 01 (-2 naprawi³o, nie wiem czemu --- chyab przez to +9.0)
            //*8 -> bo 8 znaków ma jeden wiersz w notatniku
            //+3 -> bo od 4 znaku jest szukana liczba (wynik)
            //+9 -> Pomija tytu³ dla Excela (nr, wynik)
        stats.seekg((nr - 2.0) * 8.0 + 3.0 + 9.0, ios::beg);
        stats >> score;
        score++;
        cout << " po raz " << score << endl;
        stats.seekp((nr - 2.0) * 8.0 + 3.0 + 9.0, ios::beg);
        stats << setfill('0') << setw(3) << score;

        stats.seekg((max - 2.0) * 8.0 + 20.0 + 9.0, ios::beg);
        stats >> all;
        all++;

        stats.close();
        stats.open("R:/statystyki.txt", ios::in | ios::out | ios::binary);  //otwieram ejszcze raz bo coœ nie tak z seekp, bez tego aint workin

        stats.seekp((max - 2.0) * 8.0 + 20.0 + 9.0, ios::beg);   //"Iloœæ cykli: " == 13 znaków 
        stats << setfill('0') << setw(6) << all;

        cout << score * 100 / all << "%" << endl << endl;
        //stats.close();
        //stats.open("F:/statystyki.txt", ios::in | ios::out | ios::binary);  //otwieram ejszcze raz bo coœ nie tak z seekp, bez tego aint workin

        //
        //stats.seekp((nr + max) * 8.0 + 8.0 + 9.0, ios::beg);
        //stats << setfill('0') << setw(3) << score / all * 100;
        //cout << endl << fixed << setprecision(2) << score / all * 100 << "%" << endl;
    }
    else cout << "FAILURE. *pew*";

    stats.close();
}

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
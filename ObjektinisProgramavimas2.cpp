#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;
using std::setw;
using std::left;
using std::setprecision;
using std::fixed;
using std::ifstream;

struct stud{
string vardas;
string pavarde;
int egz;
vector<int> nd;
double vidurkis;
double mediana;
};

void nuskaitymasFaile(int&, stud*&);
void nuskaitymasKonsoleje(int&, stud*&);
void nuskaitymasGeneruojant(int&, stud*&);
void rikiavimas(int&, stud*&);
void vidurkisFormatavimas(int, stud*&, int&, int&);


void nuskaitymas(int& sk, stud*& studentai, int& vilgis, int& pilgis){

    string pasirinkimas;
    do{
    cout << "Pasirinkite duomenu ivedimo buda: " << endl;
    cout << "1. Ivedimas per konsole" << endl;
    cout << "2. Ivedimas generuojant atsitiktines reiksmes" << endl;
    cout << "3. Ivedimas is tekstinio failo" << endl;
    cin >> pasirinkimas;
    if(pasirinkimas == "1") nuskaitymasKonsoleje(sk, studentai);
    else if(pasirinkimas == "2") nuskaitymasGeneruojant(sk, studentai);
    else if(pasirinkimas == "3") nuskaitymasFaile(sk, studentai);
    else{
        pasirinkimas = "0";
        cout << "Klaida. Neteisingas pasirinkimas, iveskite skaicius 1-3" << endl;
    }
    }while(pasirinkimas == "0");

    rikiavimas(sk, studentai);
    vidurkisFormatavimas(sk, studentai, vilgis, pilgis);

}


void spausdinimas(int sk, stud* studentai, int vilgis, int pilgis){
    cout << setw(pilgis+4) << left << "Pavarde";
    cout << setw(vilgis+4) << left << "Vardas";
    cout << "VidGalutinis MedGalutinis" << endl;
    cout << "-------------------------";
    string eilute(pilgis+vilgis+8, '-');
    cout << eilute << endl;
    for(int i = 0; i < sk; i++){
        cout << setw(pilgis+4) << left << studentai[i].pavarde;
        cout << setw(vilgis+4) << left << studentai[i].vardas;
        cout << setw(13) << left << fixed << setprecision(2) << studentai[i].vidurkis;
        cout << setw(13) << left << fixed << setprecision(2) << studentai[i].mediana << endl;
    }
}

int ivedimas(){
    int k;
    cin >> k;
        if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Klaida. Ivestas simbolis nera skaitmuo" << endl;
            return 0;
        }
    else return k;
}

int main(){
    stud* studentai;
    int sk = -1, vilgis = 10, pilgis = 10;
    nuskaitymas(sk, studentai, vilgis, pilgis);
    spausdinimas(sk, studentai, vilgis, pilgis);
}

void nuskaitymasKonsoleje(int& sk, stud*& studentai) {
    int k = 1;
    cout << "Pasibaigus namu darbu eilutei iveskite neigiama skaiciu (pvz. -1)" << endl;
    cout << "Iveskite studentu skaiciu: ";
    while(sk <= 0) sk = ivedimas();
    studentai = new stud[sk];
    for(int i = 0; i < sk; i++){
        cout << "Iveskite " << i+1 << " studento varda: ";
        cin >> studentai[i].vardas;
        cout << "Pavarde: ";
        cin >> studentai[i].pavarde;
        cout << "Namu darbu rezultatus:" << endl;
        studentai[i].vidurkis = 0;

        while(k >= 0){
            k = ivedimas();
            if(k > 0){
                studentai[i].nd.push_back(k);
                studentai[i].vidurkis += k;
            }
        }
        cout << "Egzamino ivertinima: ";
        studentai[i].egz = 0;
        while(studentai[i].egz <= 0) studentai[i].egz = ivedimas();
    }
}

void nuskaitymasGeneruojant(int& sk, stud*& studentai){
    char eil;
    int ndk, temp;
        cout << "Iveskite studentu skaiciu: ";
        cin >> sk;
        cout << "Iveskite namu darbu kieki: ";
        cin >> ndk;
        studentai = new stud[sk];
        srand(time(NULL));

        for(int i = 0; i < sk; i++){
            studentai[i].vardas = "Vardas" + std::to_string(i+1);
            studentai[i].pavarde = "Pavarde" + std::to_string(i+1);
            studentai[i].vidurkis = 0;
            for(int j = 0; j < ndk; j++){
                temp = 1.0*rand()/RAND_MAX*10+1;
                studentai[i].nd.push_back(temp);
                studentai[i].vidurkis += temp;
            }
            studentai[i].egz = 1.0*rand()/RAND_MAX*10+1;
        }
}

void nuskaitymasFaile(int& sk, stud*& studentai){
    ifstream in("kursiokai.txt");
    int ndk, temp;
    in >> sk >> ndk;
        studentai = new stud[sk];
        for(int i = 0; i < sk; i++){
            studentai[i].vidurkis = 0;
            in >> studentai[i].vardas >> studentai[i].pavarde;
            for(int j = 0; j < ndk; j++){
                in >> temp;
                studentai[i].nd.push_back(temp);
                studentai[i].vidurkis += temp;
            }
            in >> studentai[i].egz;
        }
        in.close();
}

void vidurkisFormatavimas(int sk, stud*& studentai, int& vilgis, int& pilgis){
    for(int i = 0; i < sk; i++){
        if(vilgis < studentai[i].vardas.size()) vilgis = studentai[i].vardas.size();
        if(pilgis < studentai[i].pavarde.size()) pilgis = studentai[i].pavarde.size();
        studentai[i].vidurkis = studentai[i].vidurkis/studentai[i].nd.size()*0.4 + studentai[i].egz*0.6;

            std::sort(studentai[i].nd.begin(), studentai[i].nd.end());

        if(studentai[i].nd.size()%2 > 0){
            studentai[i].mediana = studentai[i].nd[studentai[i].nd.size()/2];
        }
        else studentai[i].mediana = (studentai[i].nd[studentai[i].nd.size()/2] + studentai[i].nd[studentai[i].nd.size()/2-1])/2.0;
    }
}

void rikiavimas(int& sk, stud*& studentai){
    stud temp;
    for(int i = 0; i < sk-1; i++){
       for(int j = 0; j < sk-i-1; j++){
            if(studentai[j].pavarde > studentai[j+1].pavarde){
                temp = studentai[j];
                studentai[j] = studentai[j+1];
                studentai[j+1] = temp;
            }
       }
    }
}

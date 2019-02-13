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
void vidurkis(int, stud*&);

void nuskaitymas(int& sk, stud*& studentai){
    int pasirinkimas;
    do{
    cout << "Pasirinkite duomenu ivedimo buda: " << endl;
    cout << "1. Ivedimas per konsole" << endl;
    cout << "2. Ivedimas generuojant atsitiktines reiksmes" << endl;
    cout << "3. Ivedimas is tekstinio failo" << endl;
    cin >> pasirinkimas;

    switch(pasirinkimas){

    case 1 :
        nuskaitymasKonsoleje(sk, studentai);
    break;

    case 2 :
        nuskaitymasGeneruojant(sk, studentai);
    break;
    case 3 :
        nuskaitymasFaile(sk, studentai);
    break;
    default :
        cout << "Klaida. Neatpazinta ivedimo reiksme" << endl;
        pasirinkimas = 0;
        }
    }while(pasirinkimas == 0);

    vidurkis(sk, studentai);
    rikiavimas(sk, studentai);

}


void spausdinimas(int sk, stud* studentai){
    cout << "Pavarde      Vardas       VidGalutinis MedGalutinis" << endl;
    cout << "---------------------------------------------------" << endl;
    for(int i = 0; i < sk; i++){
        cout << setw(13) << left << studentai[i].pavarde;
        cout << setw(13) << left << studentai[i].vardas;
        cout << setw(13) << left << fixed << setprecision(2) << studentai[i].vidurkis;
        cout << setw(13) << left << fixed << setprecision(2) << studentai[i].mediana << endl;
    }
}

int main(){
    stud* studentai;
    int sk;
    nuskaitymas(sk, studentai);
    spausdinimas(sk, studentai);
}

void nuskaitymasKonsoleje(int& sk, stud*& studentai) {
    int k;
    cout << "Pasibaigus namu darbu eilutei iveskite neigiama skaiciu (pvz. -1)" << endl;
    cout << "Iveskite studentu skaiciu: ";
    cin >> sk;
    studentai = new stud[sk];
    for(int i = 0; i < sk; i++){
        cout << "Iveskite " << i+1 << " studento varda: ";
        cin >> studentai[i].vardas;
        cout << "Pavarde: ";
        cin >> studentai[i].pavarde;
        cout << "Namu darbu rezultatus:" << endl;
        studentai[i].vidurkis = 0;
        k = 1;
        while(k >= 0){
            cin >> k;
            if(k >= 0){
                studentai[i].nd.push_back(k);
                studentai[i].vidurkis += k;
            }
        }
        cout << "Egzamino ivertinima: ";
        cin >> studentai[i].egz;
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

void vidurkis(int sk, stud*& studentai){
    for(int i = 0; i < sk; i++){
        studentai[i].vidurkis = studentai[i].vidurkis/studentai[i].nd.size()*0.4 + studentai[i].egz*0.6;

            std::sort(studentai[i].nd.begin(), studentai[i].nd.end());
            for(int j = 0; j < studentai[i].nd.size(); j++) cout << studentai[i].nd[j] << " ";
            cout << endl;

        if(studentai[i].nd.size()%2 > 0){
            studentai[i].mediana = studentai[i].nd[studentai[i].nd.size()/2+1];
        }
        else studentai[i].mediana = (studentai[i].nd[studentai[i].nd.size()/2]+studentai[i].nd[studentai[i].nd.size()/2-1])/2.0;
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

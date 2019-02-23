#include "Funkcijos.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string>


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
using std::cerr;

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
        cerr << "Klaida. Neteisingas pasirinkimas, iveskite skaicius 1-3" << endl;
    }
    }while(pasirinkimas == "0");

    rikiavimas(sk, studentai);
    try{
    vidurkisFormatavimas(sk, studentai, vilgis, pilgis);
    } catch(const char* msg) {
        cerr << msg << endl;
        exit(1);
    }

}


void spausdinimas(int sk, stud* studentai, int vilgis, int pilgis){
    string pasirinkimas;
    do{
    cout << "Naudoti 1.vidurki ar 2.mediana? ";
    cin >> pasirinkimas;
    if(pasirinkimas == "1"){
        cout << setw(pilgis+4) << left << "Pavarde";
        cout << setw(vilgis+4) << left << "Vardas";
        cout << "VidGalutinis" << endl;
    }
    else if(pasirinkimas == "2"){
        cout << setw(pilgis+4) << left << "Pavarde";
        cout << setw(vilgis+4) << left << "Vardas";
        cout << "MedGalutinis" << endl;
    }
    else{
        pasirinkimas = "0";
        cerr << "Klaida. Neteisingas pasirinkimas, iveskite skaicius 1-2" << endl;
        }
    }while(pasirinkimas == "0");

    cout << "-------------";
    string eilute(pilgis+vilgis+8, '-');
    cout << eilute << endl;
    for(int i = 0; i < sk; i++){
        cout << setw(pilgis+4) << left << studentai[i].pavarde;
        cout << setw(vilgis+4) << left << studentai[i].vardas;
        if(pasirinkimas == "1") cout << setw(13) << left << fixed << setprecision(2) << studentai[i].vidurkis << endl;
        else if(pasirinkimas == "2") cout << setw(13) << left << fixed << setprecision(2) << studentai[i].mediana << endl;
    }
}

int ivedimas(){
    int k = 0;
    cin >> k;
        if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cerr << "Klaida. Ivestas simbolis nera skaitmuo" << endl;
            return 0;
        }
    else return k;
}

void nuskaitymasKonsoleje(int& sk, stud*& studentai) {
    int k;
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
        k=1;
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
    int ndk = -1, temp;
        cout << "Iveskite studentu skaiciu: ";
        while(sk <= 0) sk = ivedimas();
        cout << "Iveskite namu darbu kieki: ";
        while(ndk <= 0) ndk = ivedimas();
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
    if(!in.good()){
        cerr << "Klaida. Toks failas neegzistuoja" << endl;
        exit(1);
    }
    string eilute;
    int temp, ndk;
    in >> sk >> ndk;
    if(in.fail() || sk <= 0){
        cerr << "Klaida. Neteisingai ivestas studentu arba namu darbu skaicius" << endl;
        exit(1);
        }
        studentai = new stud[sk];
        for(int i = 0; i < sk; i++){
            studentai[i].vidurkis = 0;
            in >> studentai[i].vardas >> studentai[i].pavarde;
            for(int j = 0; j < ndk; j++){
                in >> temp;
                if(in.fail() || temp <= 0) {
                    cerr << "Klaida. Neteisingai ivesti namu darbu ivertinimai" << endl;
                    exit(1);
                }
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
        if(studentai[i].nd.size() == 0) throw "Klaida. Mokinys neturi nei vieno namu darbo. Dalyba is 0 negalima";
        studentai[i].vidurkis = studentai[i].vidurkis/studentai[i].nd.size()*0.4 + studentai[i].egz*0.6;

            std::sort(studentai[i].nd.begin(), studentai[i].nd.end());

        if(studentai[i].nd.size()%2 > 0){
            studentai[i].mediana = studentai[i].nd[studentai[i].nd.size()/2];
        }
        else studentai[i].mediana = (studentai[i].nd[studentai[i].nd.size()/2] + studentai[i].nd[studentai[i].nd.size()/2-1])/2.0;
        studentai[i].mediana = studentai[i].mediana*0.4 + studentai[i].egz*0.6;
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

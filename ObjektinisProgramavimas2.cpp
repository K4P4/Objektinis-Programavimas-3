#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;
using std::setw;
using std::left;
using std::setprecision;
using std::fixed;

struct stud{
string vardas;
string pavarde;
int egz;
vector<int> nd;
double vidurkis;
double mediana;
};

void nuskaitymas(int& sk, stud*& studentai){
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
        int k = 1;
        while(k >= 0){
            cin >> k;
            if(k >= 0){
                studentai[i].nd.push_back(k);
                studentai[i].vidurkis += k;
            }
        }
        cout << "Egzamino ivertinima: ";
        cin >> studentai[i].egz;

        studentai[i].vidurkis = studentai[i].vidurkis/studentai[i].nd.size()*0.4 + studentai[i].egz*0.6;

        for(int k = 0; k < studentai[i].nd.size(); k++){
            for(int j = i; j < studentai[i].nd.size()-1; j++){
                if(studentai[i].nd[k] < studentai[i].nd[j]){
                    int temp = studentai[i].nd[k];
                    studentai[i].nd[k] = studentai[i].nd[j];
                    studentai[i].nd[j] = temp;
                }
            }
        }

        if(studentai[i].nd.size()%2 > 0){
            studentai[i].mediana = studentai[i].nd[studentai[i].nd.size()/2+1];
        }
        else studentai[i].mediana = (studentai[i].nd[studentai[i].nd.size()/2]+studentai[i].nd[studentai[i].nd.size()/2-1])/2.0;
    }
}

void spausdinimas(int sk, stud* studentai){
    cout << "Pavarde      Vardas       VidGalutinis MedGalutinis" << endl;
    cout << "---------------------------------------------------" << endl;
    for(int i = 0; i < sk; i++){
        cout << setw(13) << left << studentai[i].pavarde;
        cout << setw(13) << left << studentai[i].vardas;
        cout << setw(13) << left << fixed << setprecision(3) << studentai[i].vidurkis;
        cout << setw(13) << left << fixed << setprecision(3) << studentai[i].mediana << endl;
    }
}

int main(){
    stud* studentai;
    int sk;
    nuskaitymas(sk, studentai);
    spausdinimas(sk, studentai);
}

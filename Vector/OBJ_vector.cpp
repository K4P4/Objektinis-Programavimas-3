#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using std::string;
using std::vector;
using std::cerr;
using std::endl;
using namespace std::chrono;

struct stud{
string vardas;
string pavarde;
int egz;
vector<int> nd;
double vidurkis;
double mediana;
};

void nuskaitymasFaile(int& sk, vector<stud>& studentai){
    std::ifstream in("sugeneruota100000.txt");
    string eil;
    if(!in.good()){
        cerr << "Klaida. Toks failas neegzistuoja" << endl;
        exit(1);
    }
    int temp;
    sk = 0;
        while(in >> eil){
            stud studentas;
            studentas.vidurkis = 0;
            studentas.vardas = eil;
            in >> studentas.pavarde;
            while(in.peek()!='\n' && in >> temp){
                if(in.fail() || temp <= 0) {
                    cerr << "Klaida. Patikrinkite faila" << endl;
                    exit(1);
                }
                studentas.nd.push_back(temp);
                studentas.vidurkis += temp;
            }
            studentas.egz = studentas.nd[studentas.nd.size()-1];
            studentas.nd.pop_back();
            studentai.push_back(studentas);
            sk++;
        }
        in.close();
}

int main(){
    vector<stud> studentai;
    int sk = -1;
    auto start = high_resolution_clock::now();

    nuskaitymasFaile(sk, studentai);
    vector<stud> vargs;

    for(int i = 0; i < studentai.size(); i++){
        studentai[i].vidurkis = studentai[i].vidurkis/studentai[i].nd.size()*0.4 + studentai[i].egz*0.6;
        if(studentai[i].vidurkis < 5.0){
            vargs.push_back(studentai[i]);
            studentai.erase(studentai.begin()+i);
            i--;
        }
    }

    auto ending = high_resolution_clock::now();
    duration<double> diff = ending-start;
    std::cout << sk << " studentu isskirstymas uztruko: " << diff.count() << "s" << endl;
}

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>

using std::string;
using std::vector;
using std::cerr;
using std::endl;
using namespace std::chrono;


class stud{
private:
    string vardas;
    string pavarde;
    int egz;
    vector<int> nd;
    double vidurkis;
public:
    stud() : vidurkis(0){}
    stud(std::istream& is);
    inline string getVardas() const { return vardas;}
    inline string getPavarde() const { return pavarde;}
    inline double getVidurkis() const { return vidurkis;}
    void setVardas(string vard) { vardas = vard;}
	void setPavarde(string pav) { pavarde = pav;}
	void pushNd(int pazymys) { nd.push_back(pazymys);}
	void setEgzaminas();
	void apskVidurki();
	void addVidurkis(int pazymys);
};

void stud::setEgzaminas(){
    egz = nd[nd.size()-1];
    nd.pop_back();
}

void stud::apskVidurki(){
    vidurkis = vidurkis/nd.size()*0.4 + egz*0.6;
}

void stud::addVidurkis(int pazymys){
    vidurkis += pazymys;
}

bool maziau(const stud& esm){
return (esm.getVidurkis() < 5.0);
}

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
            studentas.setVardas(eil);
            in >> eil;
            studentas.setPavarde(eil);
            while(in.peek()!='\n' && in >> temp){
                if(in.fail() || temp <= 0) {
                    cerr << "Klaida. Patikrinkite faila" << endl;
                    exit(1);
                }
                studentas.pushNd(temp);
                studentas.addVidurkis(temp);
            }
            studentas.setEgzaminas();
            studentas.apskVidurki();
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

    vector<stud>::iterator it = studentai.begin();

    it = std::partition(studentai.begin(), studentai.end(), maziau);
    vector<stud> kieti(it, studentai.end());

    studentai.erase(it, studentai.end());
    studentai.shrink_to_fit();

    auto ending = high_resolution_clock::now();

    duration<double> diff = ending-start;
    std::cout << sk << " studentu isskirstymas uztruko: " << diff.count() << "s" << endl;
}

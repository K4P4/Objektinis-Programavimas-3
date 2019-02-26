#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <vector>
#include <string>

using std::string;
using std::vector;

struct stud{
string vardas;
string pavarde;
int egz;
vector<int> nd;
double vidurkis;
double mediana;
};

void generavimasFaile(int&, vector<stud>&);
void nuskaitymasFaile(int&, vector<stud>&);
void nuskaitymasKonsoleje(int&, vector<stud>&);
void nuskaitymasGeneruojant(int&, vector<stud>&);
void rikiavimas(int&, vector<stud>&);
void vidurkisFormatavimas(int, vector<stud>&, int&, int&);
void nuskaitymas(int&, vector<stud>&, int&, int&);
void spausdinimas(int, vector<stud>, int, int);
int ivedimas();

#endif

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

void nuskaitymasFaile(int&, stud*&);
void nuskaitymasKonsoleje(int&, stud*&);
void nuskaitymasGeneruojant(int&, stud*&);
void rikiavimas(int&, stud*&);
void vidurkisFormatavimas(int, stud*&, int&, int&);
void nuskaitymas(int&, stud*&, int&, int&);
void spausdinimas(int, stud*, int, int);
int ivedimas();

#endif

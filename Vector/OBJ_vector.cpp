#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <gtest/gtest.h>

using std::string;
using std::vector;
using std::cerr;
using std::endl;
using std::cout;
using std::cin;
using namespace std::chrono;

class zmogus {
protected:
	string vardas;
	string pavarde;
public:
	zmogus(string defv = "", string defp = "") : vardas{ defv }, pavarde{ defp }{}
	virtual void setEgzaminas() = 0;
	void setVardas(string vard) { vardas = vard; }
	void setPavarde(string pav) { pavarde = pav; }
	inline string getVardas() const { return vardas; }
	inline string getPavarde() const { return pavarde; }
};

class stud : public zmogus {
protected:
	int egz;
	vector<int> nd;
	double vidurkis;
public:
	stud() : vidurkis(0), egz(0) {}
	stud(std::istream& is);
	double getVidurkis() const { return vidurkis; }
	void pushNd(int pazymys) { nd.push_back(pazymys); }
	void setEgzaminas();
	void apskVidurki();
	void addVidurkis(int pazymys);
	friend bool operator == (const stud &st1, const stud& st2) { return st1.vidurkis == st2.vidurkis; }
	friend bool operator != (const stud &st1, const stud& st2) { return st1.vidurkis != st2.vidurkis; }
	friend std::istream & operator >> (std::istream & in, stud & st);
	friend std::ostream & operator << (std::ostream & out, const stud &st);
	stud(const stud& a);
	stud& operator=(const stud& st);
	stud(stud&& st) : zmogus{ st.vardas,st.pavarde }, egz{ st.egz }, vidurkis{ st.vidurkis }, nd{ std::move(st.nd) } {};
	friend bool operator < (const stud &st1, const stud &st2) { return st1.vidurkis < st2.vidurkis; }
	friend bool operator > (const stud &st1, const stud &st2) { return st1.vidurkis > st2.vidurkis; }
};

int ivedimas();

std::istream& operator >> (std::istream & in, stud & st) {
	cout << "Pasibaigus namu darbu eilutei iveskite neigiama skaiciu (pvz. -1)" << endl;
	cout << "Iveskite studento varda: ";
	cin >> st.vardas;
	cout << "Pavarde: ";
	cin >> st.pavarde;
	cout << "Namu darbu rezultatus:" << endl;
	st.vidurkis = 0;
	int k = 1;
	while (k >= 0) {
		k = ivedimas();
		if (k > 0) {
			st.nd.push_back(k);
			st.vidurkis += k;
		}
	}
	cout << "Egzamino ivertinima: ";
	st.egz = 0;
	while (st.egz <= 0) st.egz = ivedimas();
	return in;
}

std::ostream & operator << (std::ostream & out, const stud &st) {
	out << "Vardas: " << st.vardas << endl;
	out << "Pavarde: " << st.pavarde << endl;
	out << "Vidurkis: " << st.vidurkis << endl;
	return out;
}

stud& stud::operator=(const stud& st) {
	if (&st == this) return *this;
	vardas = st.vardas;
	pavarde = st.pavarde;
	egz = st.egz;
	nd = st.nd;
	vidurkis = st.vidurkis;
	return *this;
}

stud::stud(const stud& st) {
	vardas = st.vardas;
	pavarde = st.pavarde;
	egz = st.egz;
	nd = st.nd;
	vidurkis = st.vidurkis;
}

void stud::setEgzaminas() {
	egz = nd[nd.size() - 1];
	nd.pop_back();
}

void stud::apskVidurki() {
	if(nd.size() > 0) vidurkis = vidurkis / nd.size()*0.4 + egz * 0.6;
	else vidurkis = 0;
}

void stud::addVidurkis(int pazymys) {
	vidurkis += pazymys;
}

bool maziau(const stud& esm) {
	return (esm.getVidurkis() < 5.0);
}

int ivedimas() {
	int k = 0;
	cin >> k;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cerr << "Klaida. Ivestas simbolis nera skaitmuo" << endl;
		return 0;
	}
	else return k;
}

void nuskaitymasFaile(int& sk, vector<stud>& studentai) {
	std::ifstream in("sugeneruota1000.txt");
	string eil;
	if (!in.good()) {
		cerr << "Klaida. Toks failas neegzistuoja" << endl;
		exit(1);
	}
	int temp;
	sk = 0;
	while (in >> eil) {
		stud studentas;
		studentas.setVardas(eil);
		in >> eil;
		studentas.setPavarde(eil);
		while (in.peek() != '\n' && in >> temp) {
			if (in.fail() || temp <= 0) {
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

TEST(StudentClassTests, VidurkisLyguNuliui) {
	stud Student;
	EXPECT_EQ(0, Student.getVidurkis());
}

TEST(StudentClassTests, VardasTuriReiksme) {
	stud Student;
	EXPECT_EQ("", Student.getVardas());
}

TEST(StudentClassTests, PavardeTuriReiksme) {
	stud Student;
	EXPECT_EQ("", Student.getPavarde());
}

TEST(StudentClassTests, VektoriusTuscias) { //Ğis testas padëjo rasti klaidà: neturëdami paşymiø skaièiuojam vidurká ir gauname -nan, nes vyksta dalyba iğ nulio
	stud Student;
	Student.apskVidurki();
	EXPECT_EQ(0, Student.getVidurkis());
}



int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
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

	duration<double> diff = ending - start;
	std::cout << sk << " studentu isskirstymas uztruko: " << diff.count() << "s" << endl;
	return RUN_ALL_TESTS();
}

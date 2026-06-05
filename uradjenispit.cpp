#include <iostream>
using namespace std;



class Predmet {
public:
	char* _naziv;
	int _ocjena;
	int* _ECTS;
	// Kreirati i implementirati
	// 1. Defaultni konstruktor (default constructor)
	// 2. Konstruktor koji prima parametre (user-defined constructor)
	// 3. Konstruktor kopije (copy constructor)
	// 4. Operator dodjele (operator =)
	// 5. Dealokacija (destructor)
	// 6. Ispis ili operator ispisa (operator <<) 
	Predmet() {
		const char* dftnaziv = "Nema predmeta";
		int vel = strlen(dftnaziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, dftnaziv);

		_ocjena = 5;

		_ECTS = new int(0);
	}
	Predmet(const char* naziv, int ocjena, int ects)
	{
		_ocjena = ocjena;
		_ECTS = new int(ects);

		int vel = strlen(naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, naziv);
	}

	Predmet(const Predmet& predmet) {
		
		_ocjena = predmet._ocjena;
		_ECTS = new int(*predmet._ECTS);

		int vel = strlen(predmet._naziv) + 1;
		_naziv = new char[vel];
		strcpy_s(_naziv, vel, predmet._naziv);
	}

	Predmet& operator = (const Predmet& predmet)
	{
		if (this != &predmet) {

			delete[] _ECTS;
			delete[]_naziv;

			_ocjena = predmet._ocjena;
			_ECTS = new int(*predmet._ECTS);

			int vel = strlen(predmet._naziv) + 1;
			_naziv = new char[vel];
			strcpy_s(_naziv, vel, predmet._naziv);
		}
		return *this;
	}

	~Predmet() {
		delete _ECTS;
		_ECTS = nullptr;

		delete[]_naziv;
		_naziv = nullptr;

	}

	void Ispis() {
		cout << "Naziv predmeta: " << _naziv << endl;
		cout << "ECTS: " << _ECTS << endl;
		cout << "Ocjena: " << _ocjena << endl;
	}
};





class Student {
	char* _imePrezime;
	Predmet* _polozeni;
	int _trenutno;
	int _max;
public:
	// Kreirati i implementirati
	// 1. Defaultni konstruktor (default constructor)
	// 2. Konstruktor koji prima parametre (user-defined constructor)
	// 3. Konstruktor kopije (copy constructor)
	// 4. Operator dodjele (operator =)
	// 5. Dealokacija (destructor)
	// 6. Ispis ili operator ispisa (operator <<) 
	// 7. Dodatne funkcije

	Student() {
		const char* dftImePrezime = "Nema Ime prezime";
		int vel = strlen(dftImePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, dftImePrezime);

		_trenutno = 0;
		_max = 3;
		_polozeni = new Predmet[_max];
	}

	Student(const char* imeprezime, int max) {
		int vel = strlen(imeprezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imeprezime);

		_max = max;
		_trenutno = 0;

		_polozeni = new Predmet[_max];
	}

	Student(const Student& obj) {
		int vel = strlen(obj._imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, obj._imePrezime);

		_max = obj._max;
		_trenutno = obj._trenutno;

		_polozeni = new Predmet[_max];

		for (int i = 0; i < _trenutno; i++)
		{
			_polozeni[i] = obj._polozeni[i];
		}
	}
	Student& operator = (const Student & obj){
		if (this != &obj)
		{
			delete[] _imePrezime;
			delete[]_polozeni;
			int vel = strlen(obj._imePrezime) + 1;
			_imePrezime = new char[vel];
			strcpy_s(_imePrezime, vel, obj._imePrezime);

			_max = obj._max;
			_trenutno = obj._trenutno;

			_polozeni = new Predmet[_max];

			for (int i = 0; i < _trenutno; i++)
			{
				_polozeni[i] = obj._polozeni[i];
			}
		}
		return *this;
	}
	~Student() {
		delete[] _imePrezime;
		delete[]_polozeni;

		_imePrezime = nullptr;
		_polozeni = nullptr;

	}
	void Ispis() {
		cout << "Ime i prezime: " << _imePrezime << endl;
		cout << "Polozeni predmeti studenta: " << endl;
		
	}
	void AddPolozeniPredmet(Predmet predmet) {
		// Dodaje novi polozeni predmet u niz
		// Voditi računa da se ne može prekoračiti kapacitet niza
		// Voditi računa da se ne moze dodavati isti predmet (istog naziva)		        
		if (_trenutno == _max)
		{
			cout << "Preko kapaciteta " << endl;
			return;
		}
		for (int i = 0; i < _trenutno; i++)
		{
			if (strcmp(predmet._naziv, _polozeni[i]._naziv) == 0)
			{
				cout << "Odabrano vec" << endl;
				return;
			}
		}
		_polozeni[_trenutno] = predmet;
		_trenutno++;

	}

};



void main() {

	/* -- PREDMET TESTIRANJE -- */

	Predmet predmet0; // dft constr.

	Predmet predmet1("Programiranje II", 9, 7); // user-def constr. (naziv, ocjena, ects)
	Predmet predmet2("Matematika II", 6, 4); // user-def constr. (naziv, ocjena, ects)
	Predmet predmet3("Operativni sistemi", 7, 4); // user-def constr. (naziv, ocjena, ects)
	Predmet predmet4("Web razvoj i dizajn", 7, 5); // user-def constr. (naziv, ocjena, ects)

	Predmet predmetKopija = predmet1; // copy constr.

	Predmet predmetOperatorDodjele;
	predmetOperatorDodjele = predmet1; // operator = 

	/* Metoda Ispisa ili operator ispisa (operator <<) - Dovoljno implementirati jedno */

	predmet1.Ispis();
	

	/* -- STUDENT TESTIRANJE -- */


	Student student0; // dft constr.

	Student student1("Vedad Keskin", 3); // user-def constr. (imeprezime, max)

	student1.AddPolozeniPredmet(predmet1); // Dodavanje predmeta PRII
	student1.AddPolozeniPredmet(predmet2); // Dodavanje predmeta MATII
	student1.AddPolozeniPredmet(predmet2); // Dodavanje predmeta MATII - Duplikat (potrebno zabraniti)
	student1.AddPolozeniPredmet(predmet3); // Dodavanje predmeta OS
	student1.AddPolozeniPredmet(predmet4); // Dodavanje predmeta WRD - Prekoračenje niza (potrebno zabraniti)


	Student studentKopija = student1; // copy constr.

	Student studentOperatorDodjele;
	studentOperatorDodjele = student1; // operator = 

	/* Metoda Ispisa ili operator ispisa (operator <<) - Dovoljno implementirati jedno */

	student1.Ispis();
	

	system("pause>0");
}
#include <iostream>
using namespace std;

class Datum {
public:
	int* _dan, * _mjesec, * _godina;
	// Kreirati i implementirati
	// 1. Defaultni konstruktor (default constructor)
	// 2. Konstruktor koji prima parametre (user-defined constructor)
	// 3. Konstruktor kopije (copy constructor)
	// 4. Operator dodjele (operator =)
	// 5. Dealokacija (destructor)
	// 6. Ispis ili operator ispisa (operator <<) 

	Datum()
	{
		_dan = new int(0);
		_mjesec = new int(0);
		_godina = new int(0);
	}

	Datum(int dan,int  mjesec, int godina)
	{
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);

	}
	Datum(const Datum& datum)
	{
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
	}

	Datum& operator =(const Datum& datum) {
		if (this !=&datum)
		{
			_dan = new int(*datum._dan);
			_mjesec = new int(*datum._mjesec);
			_godina = new int(*datum._godina);
		}
		return *this;
	}

	~Datum() {
		delete _dan;
		delete _mjesec;
		delete _godina;

		_dan = nullptr;
		_mjesec = nullptr;
		_godina = nullptr;
	}
	void Ispis()
	{
		cout << "Datum: " << *_dan << "." << *_mjesec << "." <<*_godina << endl;
		cout << "----------------------------------------------------" << endl;
	}
};

class Kandidat {
public:
	char* _imePrezime;
	char* _JMBG;
	// Kreirati i implementirati
	// 1. Defaultni konstruktor (default constructor)
	// 2. Konstruktor koji prima parametre (user-defined constructor)
	// 3. Konstruktor kopije (copy constructor)
	// 4. Operator dodjele (operator =)
	// 5. Dealokacija (destructor)
	// 6. Ispis ili operator ispisa (operator <<) 

	Kandidat() {
		const char* dftimeprezime = "Nema";
		int vel = strlen(dftimeprezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, dftimeprezime);

		const char* dftjmbg = "----";
		int vel2 = strlen(dftjmbg) + 1;
		_JMBG = new char[vel2];
		strcpy_s(_JMBG, vel2, dftjmbg);
	}


	Kandidat(const char* imeprezime, const char* jmbg)
	{
		int vel = strlen(imeprezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imeprezime);

		int vel2 = strlen(jmbg) + 1;
		_JMBG= new char[vel2];
		strcpy_s(_JMBG, vel2, jmbg);
	}

	Kandidat(const Kandidat& kandidat) 
	{
		int vel = strlen(kandidat._imePrezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, kandidat._imePrezime);

		int vel2 = strlen(kandidat._JMBG) + 1;
		_JMBG = new char[vel2];
		strcpy_s(_JMBG, vel2, kandidat._JMBG);
	}

	Kandidat& operator =(const Kandidat& kandidat)
	{
		if (this != &kandidat)
		{
			int vel = strlen(kandidat._imePrezime) + 1;
			_imePrezime = new char[vel];
			strcpy_s(_imePrezime, vel, kandidat._imePrezime);

			int vel2 = strlen(kandidat._JMBG) + 1;
			_JMBG = new char[vel2];
			strcpy_s(_JMBG, vel2, kandidat._JMBG);
		}
		return *this;
	}

	~Kandidat() {
		delete[]_imePrezime;
		delete[]_JMBG;

		_imePrezime = nullptr;
		_JMBG = nullptr;

	}
	void Ispis() {
		cout << "Ime i Prezime kandidata: " << _imePrezime << endl;
		cout << "JMBG: " << _JMBG << endl;
		cout << "----------------------------------------------------" << endl;
	}
};

class Glasac {
public:
	Datum _datumRodjenja;
	char* _imePrezime;
	char* _JMBG;
	char* _prebivaliste;
	// Kreirati i implementirati
	// 1. Defaultni konstruktor (default constructor)
	// 2. Konstruktor koji prima parametre (user-defined constructor)
	// 3. Konstruktor kopije (copy constructor)
	// 4. Operator dodjele (operator =)
	// 5. Dealokacija (destructor)
	// 6. Ispis ili operator ispisa (operator <<) 
	Glasac() {
		const char* dftimeprezime = "Nema";
		int vel = strlen(dftimeprezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, dftimeprezime);

		const char* dftjmbg = "----";
		int vel2 = strlen(dftjmbg) + 1;
		_JMBG = new char[vel2];
		strcpy_s(_JMBG, vel2, dftjmbg);

		const char* dftprebivaliste = "----";
		int vel3 = strlen(dftprebivaliste) + 1;
		_prebivaliste = new char[vel3];
		strcpy_s(_prebivaliste, vel3, dftprebivaliste);
	}

	Glasac(Datum datum, const char* imeprezime, const char* jmbg, const char* prebivaliste)
	{
		_datumRodjenja = datum;

		int vel = strlen(imeprezime) + 1;
		_imePrezime = new char[vel];
		strcpy_s(_imePrezime, vel, imeprezime);

		int vel2 = strlen(jmbg) + 1;
		_JMBG = new char[vel2];
		strcpy_s(_JMBG, vel2, jmbg);

		int vel3 = strlen(prebivaliste) + 1;
		_prebivaliste = new char[vel3];
		strcpy_s(_prebivaliste, vel3, prebivaliste);
	}

	Glasac(Glasac& glasac)
	{
		_datumRodjenja = glasac._datumRodjenja;

		int vel1 = strlen(glasac._imePrezime) + 1;
		_imePrezime = new char[vel1];
		strcpy_s(_imePrezime, vel1, glasac._imePrezime);

		int vel2 = strlen(glasac._JMBG);
		_JMBG = new char[vel2];
		strcpy_s(_JMBG, vel2, glasac._JMBG);

		int vel3 = strlen(glasac._prebivaliste) + 1;
		_prebivaliste = new char[vel3];
		strcpy_s(_prebivaliste, vel3, glasac._prebivaliste);
	}

	Glasac& operator =(const Glasac& glasac) {

		if (this != &glasac)
		{
			_datumRodjenja = glasac._datumRodjenja;

			int vel1 = strlen(glasac._imePrezime) + 1;
			_imePrezime = new char[vel1];
			strcpy_s(_imePrezime, vel1, glasac._imePrezime);

			int vel2 = strlen(glasac._JMBG);
			_JMBG = new char[vel2];
			strcpy_s(_JMBG, vel2, glasac._JMBG);

			int vel3 = strlen(glasac._prebivaliste) + 1;
			_prebivaliste = new char[vel3];
			strcpy_s(_prebivaliste, vel3, glasac._prebivaliste);
		}
		return *this;
	}

	~Glasac() {
		delete[]_imePrezime;
		delete[]_JMBG;
		delete[]_prebivaliste;

		_imePrezime = nullptr;
		_JMBG = nullptr;
		_prebivaliste = nullptr;
	}
	void Ispis() {
		cout << "Ime prezime glasaca: " << _imePrezime << endl;
		cout << "JMBG: " << *_JMBG << endl;
		cout << "Prebivaliste " << _prebivaliste << endl;
		cout << "Datum rodjenja glasaca ";
		_datumRodjenja.Ispis();
		cout << endl;
		cout << "----------------------------------------------------" << endl;

	}
};

class GlasackiListic {
public:
	Glasac* _glasac;
	Kandidat* _kandidat;
	// Kreirati i implementirati
	// 1. Defaultni konstruktor (default constructor)
	// 2. Konstruktor koji prima parametre (user-defined constructor)
	// 3. Konstruktor kopije (copy constructor)
	// 4. Operator dodjele (operator =)
	// 5. Dealokacija (destructor)
	// 6. Ispis ili operator ispisa (operator <<) 


};


class Izbori {
public:
	char* _glasackoMjesto;
	GlasackiListic* _glasovi;
	int _trenutnoGlasova;
	int _maxBrojGlasova;
	// Kreirati i implementirati
	// 1. Defaultni konstruktor (default constructor)
	// 2. Konstruktor koji prima parametre (user-defined constructor)
	// 3. Konstruktor kopije (copy constructor)
	// 4. Operator dodjele (operator =)
	// 5. Dealokacija (destructor)
	// 6. Ispis ili operator ispisa (operator <<) 
	// 7. Dodatne funkcije


	bool AddGlasackiListic(GlasackiListic listic)
	{
		/*funkcija treba da omoguci dodavanje informacija o novom glasu i tom prilikom:
		-     onemoguciti da se doda vise listica nego sto je dozvoljeno
		-     onemoguciti da ista osoba glasa vise puta
		-     onemoguciti glasanje osobama mladjim od 18 godina (uzeti u obzir godinu rodjenja)
		-     onemoguciti glasanje osobama iz drugih opstina
		-     u zavisnosti od uspjesnosti operacije funkcija vraca true ili false
		*/
	}


};



void main() {

	/* -- DATUM TESTIRANJE -- */

	Datum datumPunoljetni(12, 12, 1998); // user-def constr. (dan, mjesec, godina)
	Datum datumMaloljetni(1, 3, 2012); // user-def constr. (dan, mjesec, godina)
	datumPunoljetni.Ispis();
	datumMaloljetni.Ispis();
	/* -- KANDIDAT TESTIRANJE -- */

	Kandidat kandidat1("Denis Music", "0407003154765"); // user-def constr. (imeprezime, jmbg)
	Kandidat kandidat2("Elmir Babovic", "1354365135322"); // user-def constr. (imeprezime, jmbg)
	kandidat1.Ispis();
	kandidat2.Ispis();

	/* -- GLASAC TESTIRANJE -- */

	/* user-def constr. (datum, imeprezime, jmbg, prebivaliste) */
	Glasac glasac1(datumPunoljetni, "Sara Delic", "0407003154578", "Gorazde"); // nece moci glasati jer nije iz Jablanice
	Glasac glasac2(datumPunoljetni, "Kerim Dziho", "1501003124589", "Mostar"); // nece moci glasati jer nije iz Jablanice
	Glasac glasac3(datumPunoljetni, "Tarik Dzino", "1208003235689", "Jablanica");
	Glasac glasac4(datumPunoljetni, "Vedad Keskin", "1212998150001", "Jablanica");
	Glasac glasac5(datumMaloljetni, "Iman Bejana Keskin", "1208003235689", "Jablanica"); // nece moci glasati jer nije punoljetna

	glasac1.Ispis();
	glasac2.Ispis();
	/* -- GLASACKI LISTICI TESTIRANJE -- */

	/* user - def constr. (osoba, kandidat) */
	//GlasackiListic listic1(glasac1, kandidat1); // nece moci glasati jer nije iz Jablanice
	//GlasackiListic listic2(glasac2, kandidat2); // nece moci glasati jer nije iz Jablanice
	//GlasackiListic listic3(glasac3, kandidat1);
	//GlasackiListic listic4(glasac4, kandidat2);
	//GlasackiListic listic5(glasac5, kandidat1); // nece moci glasati jer nije punoljetna

	/* -- IZBORI TESTIRANJE -- */

	//Izbori izbori("Jablanica", 3); // user-def constr. (glasackomjesto, max)

	//izbori.AddGlasackiListic(listic1); // nece moci glasati jer nije iz Jablanice
	//izbori.AddGlasackiListic(listic2); // nece moci glasati jer nije iz Jablanice
	//izbori.AddGlasackiListic(listic2); // nece moci glasati jer nije iz Jablanice
	//izbori.AddGlasackiListic(listic3);
	//izbori.AddGlasackiListic(listic4);
	//izbori.AddGlasackiListic(listic5); // nece moci glasati jer nije punoljetna


	//Izbori izboriKopija = izbori; // copy constr.
	//Izbori izboriOperatorDodjele;
	//izboriOperatorDodjele = izbori; // operator =

	//cout << izboriOperatorDodjele;


	system("pause>0");
}


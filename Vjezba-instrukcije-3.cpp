#include <iostream>
using namespace std;
char* getnizkaraktera(const char* sadrzaj)
{
	int vel = strlen(sadrzaj) + 1;
	char* novi = new char[vel];
	strcpy_s(novi,vel,sadrzaj);
	return novi;
}
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

	Datum() {
		_dan = new int(0);
		_mjesec = new int(0);
		_godina = new int(0);
	}

	Datum(int dan, int mjesec, int godina)
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

	Datum& operator =(const Datum& datum)
	{
		if (this != &datum)
		{
			delete _dan;
			delete _mjesec;
			delete _godina;

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
	void Ispis() {

		cout << *_dan << "." << *_mjesec << "." << *_godina << endl;

	}
	friend ostream& operator << (ostream& COUT, const Datum& obj) {

		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << endl;

		return COUT;

	}
};

	class Kandidat {
	public:
		char* _imePrezime;
		char* _JMBG;
	
		

			Kandidat() {
				_imePrezime = getnizkaraktera("Nema imena");
				_JMBG = getnizkaraktera("nema");
			}
		
		Kandidat(const char* imeprezime, const char* jmbg)
		{
			_imePrezime = getnizkaraktera(imeprezime);
			_JMBG = getnizkaraktera(jmbg);

		}
		Kandidat(const Kandidat& kandidat)
		{
			_imePrezime = getnizkaraktera(kandidat._imePrezime);
			_JMBG = getnizkaraktera(kandidat._JMBG);
		}
		Kandidat& operator =(const Kandidat& kandidat)
		{
			if (this != &kandidat)
			{
				delete[]_imePrezime;
				delete[]_JMBG;
				_imePrezime = getnizkaraktera(kandidat._imePrezime);
				_JMBG = getnizkaraktera(kandidat._JMBG);
			}
			return *this;
		}
		~Kandidat()
		{
			delete[]_imePrezime; _imePrezime = nullptr;
			delete[]_JMBG; _JMBG = nullptr;
		}
		void Ispis() {

			cout << "ime kandidata: " << _imePrezime << endl;
			cout << "JMBG kandidata: " << _JMBG << endl << endl;
			cout << "======================================" << endl << endl;

		}

		friend ostream& operator <<(ostream& COUT, const Kandidat& obj)
		{
			COUT << obj._imePrezime << " [" << obj._JMBG << "]" << endl;

			return COUT;
		}

	};
	class Osoba {
	public:
		Datum _datumRodjenja; // maloljetna osoba ne smije glasati
		char* _imePrezime;
		char* _JMBG;
		char* _prebivaliste; // ne moze glasati osoba koja nije iz prebivalista gdje se glasanje nalazi


		Osoba(Datum datumRodjenja = Datum(), const char* imePrezime = "Nema imena", const char* JMBG = "Nema JMBG", const char* prebivaliste = "Nema prebivalista")
		{
			_imePrezime = getnizkaraktera(imePrezime);
			_JMBG = getnizkaraktera(JMBG);
			_prebivaliste = getnizkaraktera(prebivaliste);
			_datumRodjenja = datumRodjenja;
		}
		Osoba(const Osoba& osoba)
		{
			_imePrezime = getnizkaraktera(osoba._imePrezime);
			_JMBG = getnizkaraktera(osoba._JMBG);
			_prebivaliste = getnizkaraktera(osoba._prebivaliste);
			_datumRodjenja = osoba._datumRodjenja;
		}
		Osoba& operator =(const Osoba& osoba)
		{
			if (this != &osoba)
			{
				delete[]_imePrezime;
				delete[]_JMBG;
				delete[]_prebivaliste;

				_imePrezime = getnizkaraktera(osoba._imePrezime);
				_JMBG = getnizkaraktera(osoba._JMBG);
				_prebivaliste = getnizkaraktera(osoba._prebivaliste);
				_datumRodjenja = osoba._datumRodjenja; // FALI
			}
			return *this;
		}

		~Osoba()
		{
			delete[]_imePrezime; _imePrezime = nullptr;
			delete[]_JMBG; _JMBG = nullptr;
			delete[]_prebivaliste; _prebivaliste = nullptr;
		}
		void Ispis() {

			cout << "Ime: " << _imePrezime << endl;
			cout << "JMBG: " << _JMBG << endl;
			cout << "Prebivaliste: " << _prebivaliste << endl << endl;
			cout << "Datum: " << _datumRodjenja << endl;
			cout << "======================================" << endl << endl;

		}
		friend ostream& operator <<(ostream& COUT, const Osoba& osoba)
		{
			COUT << osoba._imePrezime << " [" << osoba._JMBG << "] rodjen u " << osoba._prebivaliste << ", datuma " << osoba._datumRodjenja << endl;

			return COUT;
		}
	};

	

	class GlasackiListic {
	public:
		Osoba* _glasac;
		Kandidat* _kandidat;
		
		GlasackiListic(Osoba glasac = Osoba(), Kandidat kandidat = Kandidat()) {

			_glasac = new Osoba(glasac);
			_kandidat = new Kandidat(kandidat);

		}

		GlasackiListic(const GlasackiListic& obj)
		{
			_glasac = new Osoba(*obj._glasac);
			_kandidat = new Kandidat(*obj._kandidat);
		}

		GlasackiListic& operator = (const GlasackiListic& obj)
		{
			if (this != &obj)
			{
				delete _glasac;
				delete _kandidat;
				_glasac = new Osoba(*obj._glasac);
				_kandidat = new Kandidat(*obj._kandidat);
			}
			return *this;
		}
		~GlasackiListic()
		{
			delete _glasac; _glasac = nullptr;
			delete _kandidat; _kandidat = nullptr;
		}
		friend ostream& operator << (ostream& COUT, const GlasackiListic& obj) {

			COUT << "============= GLASACKI LISTIC ===============" << endl;
			COUT << "Glasac:" << endl;
			COUT << *obj._glasac;
			COUT << "Glasa za:" << endl;
			COUT << *obj._kandidat;
			COUT << "=============================================" << endl;

			return COUT;

		}

	};


	class Izbori {
	public:
		char* _glasackoMjesto;    // niz karaktera
		GlasackiListic* _glasovi; // niz GlasackiListic
		int _trenutnoGlasova;
		int _maxBrojGlasova;



		Izbori(const char* glasackoMjesto = "Sarajevo", int max = 3) {

			_glasackoMjesto = getnizkaraktera(glasackoMjesto);

			_maxBrojGlasova = max;
			_trenutnoGlasova = 0;

			_glasovi = new GlasackiListic[_maxBrojGlasova];


		}

		Izbori(const Izbori& obj) {

			_glasackoMjesto = getnizkaraktera(obj._glasackoMjesto);

			_trenutnoGlasova = obj._trenutnoGlasova;
			_maxBrojGlasova = obj._maxBrojGlasova;

			_glasovi = new GlasackiListic[_maxBrojGlasova];

			for (int i = 0; i < _trenutnoGlasova; i++)
			{
				_glasovi[i] = obj._glasovi[i];
			}

		}

		Izbori& operator = (const Izbori& obj) {

			if (this != &obj) {

				delete[] _glasackoMjesto;
				delete[] _glasovi;


				_glasackoMjesto = getnizkaraktera(obj._glasackoMjesto);

				_trenutnoGlasova = obj._trenutnoGlasova;
				_maxBrojGlasova = obj._maxBrojGlasova;

				_glasovi = new GlasackiListic[_maxBrojGlasova];

				for (int i = 0; i < _trenutnoGlasova; i++)
				{
					_glasovi[i] = obj._glasovi[i];
				}
			}
			return *this;

		}

		~Izbori() {

			delete[] _glasackoMjesto;
			_glasackoMjesto = nullptr;
			delete[] _glasovi;
			_glasovi = nullptr;


		}




		friend ostream& operator << (ostream& COUT, const Izbori& obj) {

			COUT << "Izbori u " << obj._glasackoMjesto << endl;

			for (int i = 0; i < obj._trenutnoGlasova; i++)
			{
				COUT << obj._glasovi[i] << endl;
			}


			return COUT;

		}




		bool AddGlasackiListic(GlasackiListic listic)
		{
			/*funkcija treba da omoguci dodavanje informacija o novom glasu i tom prilikom:
			-     onemoguciti da se doda vise listica nego sto je dozvoljeno
			-     onemoguciti da ista osoba glasa vise puta
			-     onemoguciti glasanje osobama mladjim od 18 godina (uzeti u obzir godinu rodjenja)
			-     onemoguciti glasanje osobama iz drugih opstina
			-     u zavisnosti od uspjesnosti operacije funkcija vraca true ili false
			*/


			if (_maxBrojGlasova == _trenutnoGlasova) {
				cout << "Niz je popunjen" << endl;
				return false;
			}

			for (int i = 0; i < _trenutnoGlasova; i++)
			{

				// strcmp( naziv1 , naziv2 ) == 0
				if (strcmp(_glasovi[i]._glasac->_imePrezime, listic._glasac->_imePrezime) == 0) {
					cout << "Osoba je vec glasala" << endl;
					return false;
				}
			}

			//   2025 - 2012 < 18
			//if ( 2025 - *listic._glasac->_datumRodjenja._godina < 18 ) {

			//	cout << "Osoba je maloljetna" << endl;
			//	return false;

			//}

			if (*listic._glasac->_datumRodjenja._godina > 2007) {
				cout << "Osoba je maloljetna" << endl;
				return false;
			}

			//                               Mostar != Jabalnica
			if (strcmp(listic._glasac->_prebivaliste, _glasackoMjesto) != 0) {

				cout << "Osoba nije iz grada prebivalista" << endl;
				return false;

			}


			_glasovi[_trenutnoGlasova] = listic;

			_trenutnoGlasova++;

			return true;

		}


	};



	void main() {

		/* -- DATUM TESTIRANJE -- */

		Datum datumPunoljetni(12, 12, 1998); // user-def constr. (dan, mjesec, godina)
		Datum datumMaloljetni(1, 3, 2012); // user-def constr. (dan, mjesec, godina)

		/* -- KANDIDAT TESTIRANJE -- */

		Kandidat kandidat1("Denis Music", "0407003154765"); // user-def constr. (imeprezime, jmbg)
		Kandidat kandidat2("Elmir Babovic", "1354365135322"); // user-def constr. (imeprezime, jmbg)

		/* -- GLASAC TESTIRANJE -- */

		/* user-def constr. (datum, imeprezime, jmbg, prebivaliste) */
		Osoba glasac1(datumPunoljetni, "Sara Delic", "0407003154578", "Gorazde"); // nece moci glasati jer nije iz Jablanice
		Osoba glasac2(datumPunoljetni, "Kerim Dziho", "1501003124589", "Mostar"); // nece moci glasati jer nije iz Jablanice
		Osoba glasac3(datumPunoljetni, "Tarik Dzino", "1208003235689", "Jablanica");
		Osoba glasac4(datumPunoljetni, "Vedad Keskin", "1212998150001", "Jablanica");
		Osoba glasac5(datumMaloljetni, "Iman Bejana Keskin", "1208003235689", "Jablanica"); // nece moci glasati jer nije punoljetna

		/* -- GLASACKI LISTICI TESTIRANJE -- */

		/* user - def constr. (osoba, kandidat) */
		GlasackiListic listic1(glasac1, kandidat1); // nece moci glasati jer nije iz Jablanice
		GlasackiListic listic2(glasac2, kandidat2); // nece moci glasati jer nije iz Jablanice
		GlasackiListic listic3(glasac3, kandidat1);
		GlasackiListic listic4(glasac4, kandidat2);
		GlasackiListic listic5(glasac5, kandidat1); // nece moci glasati jer nije punoljetna

		/* -- IZBORI TESTIRANJE -- */

		Izbori izbori("Jablanica", 3); // user-def constr. (glasackomjesto, max)

		izbori.AddGlasackiListic(listic1); // nece moci glasati jer nije iz Jablanice
		izbori.AddGlasackiListic(listic2); // nece moci glasati jer nije iz Jablanice
		izbori.AddGlasackiListic(listic2); // nece moci glasati jer nije iz Jablanice
		izbori.AddGlasackiListic(listic3);
		izbori.AddGlasackiListic(listic4);
		izbori.AddGlasackiListic(listic5); // nece moci glasati jer nije punoljetna


		Izbori izboriKopija = izbori; // copy constr.
		Izbori izboriOperatorDodjele;
		izboriOperatorDodjele = izbori; // operator =

		cout << izboriOperatorDodjele;


		system("pause>0");
	}


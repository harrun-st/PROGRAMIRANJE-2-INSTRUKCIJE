#include<iostream>
using namespace std;
char* getnizKaraktera(const char* tekst)
{
	if (tekst == nullptr)
	{
		return nullptr;

	}
	int vel = strlen(tekst) + 1;
	char* kopija = new char[vel];
	strcpy_s(kopija, vel, tekst);
	return kopija;
}

class Artikal {
	char* _sifra;
	char* _naziv;
	double _cijena;
	int _kolicinaNaSkladistu;
public:
	Artikal(const char* sifra = "----", const char* naziv = "Nema naziv", double cijena = 0.0, int kolicina = 0)
	{

		_sifra = getnizKaraktera(sifra);
		_naziv = getnizKaraktera(naziv);

		_cijena = cijena;

		_kolicinaNaSkladistu = kolicina;
	}

	Artikal(const Artikal& obj)
	{
		_sifra = getnizKaraktera(obj._sifra);
		_naziv = getnizKaraktera(obj._naziv);
		_cijena = obj._cijena;
		_kolicinaNaSkladistu = obj._kolicinaNaSkladistu;

	}

	Artikal& operator =(const Artikal& obj)
	{
		if (this != &obj)
		{
			delete[]_sifra;
			delete[]_naziv;
			_sifra = getnizKaraktera(obj._sifra);
			_naziv = getnizKaraktera(obj._naziv);
			_cijena = obj._cijena;
			_kolicinaNaSkladistu = obj._kolicinaNaSkladistu;
		}
		return *this;
	}

	~Artikal()
	{
		delete[]_sifra;
		delete[]_naziv;
		_sifra = nullptr;
		_naziv = nullptr;
	}

	friend ostream& operator <<(ostream& COUT, const Artikal& obj)
	{
		COUT << obj._naziv << " [" << obj._sifra << "] " << obj._cijena << "KM " << endl;

		COUT << "Kolicina u skladistu: " << obj._kolicinaNaSkladistu << endl;

		return COUT;
	}
	// Operator -= na na?in da se stanje na skladištu artikla promijeni za proslije?enu vrijednost
	// Voditi raCuna da se ne može iCi u negativnu vrijednost
	Artikal& operator -=(int kolicina)
	{
		if (_kolicinaNaSkladistu < kolicina)
		{
			return *this;
		}
		_kolicinaNaSkladistu -= kolicina;

		return *this;
	}

	// Operator += na na?in da se stanje na skladištu artikla promijeni za proslije?enu vrijednost
	Artikal& operator +=(int kolicina)
	{
		_kolicinaNaSkladistu += kolicina;

		return *this;
	}
	// Operator ++ na na?in da se cijena artikla uve?a za 1
	Artikal& operator ++() {
		_cijena++;
		return *this;
	}
	// Operator -- na na?in da se cijena artikla umanji za 1
	// Voditi ra?una da se ne može i?i u negativnu vrijednost
	Artikal& operator --()
	{
		if (_cijena < 1)
		{
			return *this;
		}
		_cijena--;

		return *this;
	}
	// Operator == koji poredi artikle na osnovu sifre
	bool operator ==(const Artikal& obj)
	{
		return strcmp(_sifra, obj._sifra) == 0;
	}

	int GetKolicinaNaSkladistu() { return _kolicinaNaSkladistu; }
	double GetCijena() { return _cijena; }
	char* GetSifra() { return _sifra; }
};

class StavkaRacuna {
	Artikal* _artikal;
	int* _kupljenaKolicina;
public:
	StavkaRacuna(Artikal artikal=Artikal(),int kolicina=0)
	{
		_artikal = new Artikal(artikal);
		_kupljenaKolicina = new int(kolicina);
	}

	StavkaRacuna(const StavkaRacuna& obj)
	{
		_artikal = new Artikal(*obj._artikal);
		_kupljenaKolicina = new int(*obj._kupljenaKolicina);

	}

	StavkaRacuna& operator =(const StavkaRacuna& obj)
	{
		if (this != &obj)
		{
			delete _artikal;
			delete _kupljenaKolicina;
			_artikal = new Artikal(*obj._artikal);
			_kupljenaKolicina = new int(*obj._kupljenaKolicina);
		}

		return *this;
	}
	~StavkaRacuna() {
		delete _artikal;
		delete _kupljenaKolicina;
		_artikal = nullptr;
		_kupljenaKolicina = nullptr;
	}
	friend ostream& operator <<(ostream& COUT, const StavkaRacuna& obj)
	{
		COUT << *obj._artikal << endl;
		COUT << "Kupljena kolicina: " << *obj._kupljenaKolicina;
		return COUT;
	}



	// Operator += koji uve?ava stanje kupljene koli?ine
	StavkaRacuna& operator +=(int kolicina)
	{
		*_kupljenaKolicina += kolicina;
		return *this;
	}
	// Operator -= koji umanjuje stanje kupljene koli?ine
	// Voditi ra?una da se ne može i?i u negativnu vrijednost
	StavkaRacuna& operator -=(int kolicina)
	{
		if (*_kupljenaKolicina < kolicina)
		{
			return *this;
		}
		*_kupljenaKolicina -= kolicina;
		return *this;
	}
	// Operator == koji poredi stavke na osnovu sifre

	bool operator ==(const StavkaRacuna& obj)
	{
		return *_artikal == *obj._artikal;
	}

	double GetUkupnaCijena() { // vra?a cijenu stavke racuna (kolicina * cijena artikla) 
		return *_kupljenaKolicina * _artikal->GetCijena();
	}

	double GetKolicina() { // vra?a koli?inu stavke ra?una 
		return *_kupljenaKolicina;
	}

	Artikal& GetArtikal() { // vra?a originalni artikal
		return *_artikal;
	}

};


class Racun {
	static int _id; // unikatni identifikator, koristi se za pove?anje broja ra?una uz osiguravanje unikatnosti 
	int _brojRacuna;
	StavkaRacuna* _stavke;
	int _trenutno;
	int _max;
	double _iznosBezPDV;
	double _iznosSaPDV;
	bool _naplaceno;
public:
	Racun(int max = 5)
	{
		_brojRacuna = _id;
		_id++;

		_trenutno = 0;
		_max = max;

		_iznosBezPDV = 0.0;
		_iznosSaPDV = 0.0;

		_naplaceno = false;

		_stavke = new StavkaRacuna[_max];
	}

	Racun(const Racun& obj)
	{
		_brojRacuna = obj._brojRacuna;
		_trenutno = obj._trenutno;
		_max = obj._max;

		for (int i = 0; i < _trenutno; i++)
		{
			_stavke[i] = obj._stavke[i];
		}

		_iznosBezPDV = obj._iznosBezPDV;
		_iznosSaPDV = obj._iznosSaPDV;

		_naplaceno = obj._naplaceno;
	}

	Racun& operator =(const Racun& obj)
	{
		if (this != &obj)
		{
			delete[]_stavke;

			_brojRacuna = obj._brojRacuna;
			_trenutno = obj._trenutno;
			_max = obj._max;


			_stavke = new StavkaRacuna[_max];
			for (int i = 0; i < _trenutno; i++)
			{
				_stavke[i] = obj._stavke[i];
			}

			_iznosBezPDV = obj._iznosBezPDV;
			_iznosSaPDV = obj._iznosSaPDV;

			_naplaceno = obj._naplaceno;
		}
		return *this;
	}

	~Racun() {
		delete[]_stavke;
		_stavke = nullptr;
	}
	// Operator () - Dodaje nove artikle u _stavke (ulazni parametri su Artikal i kolicina)
	// // Voditi ra?una da nema prekora?enja niza
	// Prilikom svakog dodavanja artikla, ažurirati vrijednosti iznosBezPDV i iznosSaPDV
	// Voditi ra?una da prilikom dodavanja duplikata ažuriramo kupljenu koli?inu, koli?inu na skladištu i iznose bez i sa PDV ili samo zabraniti unos duplikata
	// Ažurirati koli?inu na skladištu artikla nakon svake kupovine
	Racun& operator ()(Artikal artikal,int kolicina)
	{
		if (_max == _trenutno)
		{
			return *this;
		}

		StavkaRacuna stavka(artikal, kolicina);


		for (int i = 0; i < _trenutno; i++)
		{
			if (stavka == _stavke[i])
			{
				return *this;
			}

		}

		_stavke[_trenutno] = stavka;
		_stavke[_trenutno].GetArtikal().operator-=(kolicina);
		_trenutno++;
		// Prilikom svakog dodavanja artikla, ažurirati vrijednosti iznosBezPDV i iznosSaPDV
		_iznosBezPDV += stavka.GetUkupnaCijena();

		//               stavka.GetUkupnaCijena(); + stavka.GetUkupnaCijena() od 17% 
		//_iznosSaPDV += stavka.GetUkupnaCijena() + stavka.GetUkupnaCijena() * 0.17;
		_iznosSaPDV += stavka.GetUkupnaCijena() * 1.17;

		return *this;
	}
	


	void PrintRacun() {
		// Ispisuje sve stavke ra?una zajedno sa iznosom za pla?anje sa i bez PDV-a i brojem ra?una
		// Voditi ra?una da se jedan ra?un ne može dva puta isprintati (paziti na bool _naplaceno)
		if (_naplaceno == true)
		{
			cout << "Racun je vec naplacen" << endl;
			return;
		}

		cout << "====== Br. racuna " << _brojRacuna << " ======" << endl << endl;
		for (int i = 0; i < _trenutno; i++)
		{
			cout << _stavke[i] << endl;
			cout << "================" << endl <<endl;
		}

		cout << "Iznos sa PDV: " << _iznosSaPDV <<"KM"<< endl;
		cout << "Iznos bez PDV: " << _iznosBezPDV << "KM" << endl;

		_naplaceno = true;
	}


};
int Racun::_id = 1;


void main() {

	/* -- ARTIKAL TESTIRANJE -- */


	Artikal artikal1("SIF001", "Hljeb", 1.2, 30);
	Artikal artikal2("SIF002", "Sok", 2.3, 20);
	Artikal artikal3("SIF003", "Cips", 3.5, 10);


	/* -- STAVKA RACUNA TESTIRANJE -- */


	StavkaRacuna stavka1(artikal1, 3);
	StavkaRacuna stavka2(artikal2, 3);

	stavka1 += 1;

	cout << stavka1;

	cout << "Ukupna cijena stavke je " << stavka1.GetUkupnaCijena() << endl;

	if (stavka1 == stavka1) {
		cout << "Stavke su iste" << endl;
	}
	else {
		cout << "Stavke nisu iste" << endl;

	}

	/* -- RACUN TESTIRANJE -- */


	Racun racun1;
	Racun racun2;
	Racun racun3;


	racun1(artikal1, 5);
	racun1(artikal2, 2);
	racun1(artikal2, 2);
	racun1(artikal3, 1);



	racun1.PrintRacun();



	system("pause>0");


	system("pause>0");
}

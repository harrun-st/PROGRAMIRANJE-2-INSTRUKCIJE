#include <iostream>
using namespace std;

char* GetNizKaraktera(const char* tekst)
{
    int vel = strlen(tekst) + 1;
    char* kopija = new char[vel];
    strcpy_s(kopija, vel, tekst);
    return kopija;
}
class Media { // BAZNA KLASA
public: // Nije obavezno da bazna klasa koristi protected način pristupa iako je preporučeno, na ispitu i na vježbama način pristupa nikad ne mijenjanti
    char* _naslov;
    char* _zanr;
    int _godinaObjavljivanja;
    float _ocjena;
    // Kreirati i implementirati
    // 1. Defaultni konstruktor (default constructor)
    // 2. Konstruktor koji prima parametre (user-defined constructor)
    // 3. Konstruktor kopije (copy constructor)
    // 4. Operator dodjele (operator =)
    // 5. Dealokacija (destructor)
    // 6. Operator ispisa (operator <<) 
    // 7. Čista virtuelna funkcija (apstrakcija) npr. void Info()

    Media(const char* naslov ="Nema naslov", const char* zanr = "---", int godina = 20000, float ocjena = 0)
    {
        _naslov = GetNizKaraktera(naslov);
        _zanr = GetNizKaraktera(zanr);
        _godinaObjavljivanja = godina;
        _ocjena = ocjena;
    }

    Media(const Media& obj)
    {
        _naslov = GetNizKaraktera(obj._naslov);
        _zanr = GetNizKaraktera(obj._zanr);
        _godinaObjavljivanja = obj._godinaObjavljivanja;
        _ocjena = obj._ocjena;
    }

    Media& operator =(const Media& obj)
    {
        if (this != &obj)
        {
            delete[]_naslov;
            delete[]_zanr;

            _naslov = GetNizKaraktera(obj._naslov);
            _zanr = GetNizKaraktera(obj._zanr);
            _godinaObjavljivanja = obj._godinaObjavljivanja;
            _ocjena = obj._ocjena;
        }
        return *this;
    }
    ~Media() {

        delete[]_naslov;
        _naslov = nullptr;
        delete[]_zanr;
        _zanr = nullptr;

    }

    friend ostream& operator <<(ostream& COUT, const Media& obj)
    {
        COUT << obj._naslov << " (" << obj._godinaObjavljivanja << ") [" << obj._ocjena << "] - " << obj._zanr << endl;
        return COUT;
    }
};

class Serija : public Media { // IZVEDENA KLASA
public:
    int _brojEpizoda;
    int _brojSezona;
    // Kreirati i implementirati
    // 1. Defaultni konstruktor (default constructor)
    // 2. Konstruktor koji prima parametre (user-defined constructor)
    // 3. Konstruktor kopije (copy constructor)
    // 4. Operator dodjele (operator =)
    // 5. Dealokacija (destructor)
    // 6. Operator ispisa (operator <<) 
    // 7. Override čiste virtuelne funkcije npr. void Info()

    Serija(const char* naziv = "Nema ga", const char* zanr = "Nema zanr", int godina = 2000, int ocjena = 0, int brepiz = 0, int brsez = 0) :Media(naziv, zanr, godina, ocjena) {

        _brojEpizoda = brepiz;
        _brojSezona = brsez;
    }
    Serija(const Serija& obj):Media(obj)
    {
        _brojEpizoda = obj._brojEpizoda;
        _brojSezona = obj._brojEpizoda;
    }
    Serija& operator =(const Serija& obj)
    {
        if (this != &obj)
        {
            Media::operator=(obj);
            _brojEpizoda = obj._brojEpizoda;
            _brojSezona = obj._brojEpizoda;
        }
        return *this;
    }
    friend ostream& operator <<(ostream& COUT, const Serija& obj) {
        COUT << obj._naslov << " (" << obj._godinaObjavljivanja << ") [" << obj._ocjena << "] - " << obj._zanr << endl;
        COUT << "Broj sezona : " << obj._brojSezona << endl;
        COUT << "Broj epizoda : " << obj._brojEpizoda << endl;
        return COUT;
    }

};

class Film : public Media { // IZVEDENA KLASA
public:
    int _trajanje; // Trajanje u minutama
    // Kreirati i implementirati
    // 1. Defaultni konstruktor (default constructor)
    // 2. Konstruktor koji prima parametre (user-defined constructor)
    // 3. Konstruktor kopije (copy constructor)
    // 4. Operator dodjele (operator =)
    // 5. Dealokacija (destructor)
    // 6. Operator ispisa (operator <<) 
    // 7. Override čiste virtuelne funkcije npr. void Info()
    Film(const char* naziv = "Nenma", const char* zanr = "nema", int godina = 2000, int ocjena = 0, int trajanje = 0) :Media(naziv, zanr, godina, ocjena) {
        _trajanje = trajanje;
    }

    Film(const Film& obj):Media(obj)
    {
        _trajanje = obj._trajanje;
    }

    Film& operator =(const Film& obj)
    {
        if (this != &obj)
        {

            Film::operator=(obj);
            _trajanje = obj._trajanje;
        }
        return *this;
   }

    friend ostream& operator <<(ostream& COUT, const Film& obj)
    {
        COUT << obj._naslov << " (" << obj._godinaObjavljivanja << ") [" << obj._ocjena << "] - " << obj._zanr << endl;
        COUT << "Trajanje : " << obj._trajanje << "min" << endl;
        return COUT;
    }
};

class Korisnik {
public:
    char* _korisnickoIme;
    char* _lozinka;

    Film* _pregledaniFilmovi;
    int _maxPregledanihFilmova;
    int _trenutnoPregledanihFilmova;

    Serija* _pregledaneSerije;
    int _maxPregledanihSerija;
    int _trenutnoPregledanihSerija;
    // Kreirati i implementirati
    // 1. Defaultni konstruktor (default constructor)
    // 2. Konstruktor koji prima parametre (user-defined constructor)
    // 3. Konstruktor kopije (copy constructor)
    // 4. Operator dodjele (operator =)
    // 5. Dealokacija (destructor)
    // 6. Operator ispisa (operator <<) 
    // 7. Potrebne funkcije
    Korisnik(const char* korisnikime = "nema", const char* lozinka = "----", int maxPF = 3, int maxPS = 3)
    {
        _korisnickoIme = GetNizKaraktera(korisnikime);
        _lozinka = GetNizKaraktera(lozinka);

        _maxPregledanihFilmova = maxPF;
        _trenutnoPregledanihFilmova = 0;
        _pregledaniFilmovi = new Film[_maxPregledanihFilmova];


        _trenutnoPregledanihSerija = 0;
        _maxPregledanihSerija = maxPS;
        _pregledaneSerije = new Serija[_maxPregledanihSerija];


    }

    Korisnik(const Korisnik& obj)
    {
        _korisnickoIme = obj._korisnickoIme;
        _lozinka = obj._lozinka;

        _maxPregledanihFilmova = obj._maxPregledanihFilmova;
        _trenutnoPregledanihFilmova = obj._trenutnoPregledanihFilmova;
        _pregledaniFilmovi = new Film[_maxPregledanihFilmova];
        for (int i = 0; i < _trenutnoPregledanihFilmova; i++)
        {
            _pregledaniFilmovi[i] = obj._pregledaniFilmovi[i];
        }
        _maxPregledanihSerija = obj._maxPregledanihSerija;
        _trenutnoPregledanihSerija = obj._trenutnoPregledanihSerija;
        _pregledaneSerije = new Serija[_maxPregledanihSerija];
        for (int j = 0; j < _trenutnoPregledanihSerija; j++)
        {
            _pregledaneSerije[j] = obj._pregledaneSerije[j];
        }
    }

    Korisnik& operator=(const Korisnik& obj) {
        if (this != &obj)
        {
            delete[] _korisnickoIme;
            delete[] _lozinka;
            delete[] _pregledaniFilmovi;
            delete[] _pregledaneSerije;

            _korisnickoIme = GetNizKaraktera(obj._korisnickoIme);
            _lozinka = GetNizKaraktera(obj._lozinka);

            _maxPregledanihFilmova = obj._maxPregledanihFilmova;
            _trenutnoPregledanihFilmova = obj._trenutnoPregledanihFilmova;
            _pregledaniFilmovi = new Film[_maxPregledanihFilmova];

            for (int i = 0; i < _trenutnoPregledanihFilmova; i++)
            {
                _pregledaniFilmovi[i] = obj._pregledaniFilmovi[i];
            }

            _trenutnoPregledanihSerija = obj._trenutnoPregledanihSerija;
            _maxPregledanihSerija = obj._maxPregledanihSerija;
            _pregledaneSerije = new Serija[_maxPregledanihSerija];
            for (int i = 0; i < _trenutnoPregledanihSerija; i++)
            {
                _pregledaneSerije[i] = obj._pregledaneSerije[i];
            }
        }
        return *this;
    }
    ~Korisnik() {
        delete[] _korisnickoIme; _korisnickoIme = nullptr;
        delete[] _lozinka; _lozinka = nullptr;
        delete[] _pregledaniFilmovi; _pregledaniFilmovi = nullptr;
        delete[] _pregledaneSerije; _pregledaneSerije = nullptr;
    }

    bool IsUserDataValid(const char* username, const char* password)
    {
        // Funkcija vraca true ili false u zavisnosti od toga da li su proslijedjeni podaci tačni
        if (strcmp(username, _korisnickoIme) == 0 && strcmp(password, _lozinka) == 0) {
            return true;
        }
        return false;

    }

    bool DodajFilm(Film film)
    {
        // Funkcija ima za cilj dodavanje novog filma u niz pregldanih.
        // Voditi računa da se ne prekorači kapacitet niza
        // Voditi računa da se ne mogu dodati dva ista filma (to su filmovi koji imaju isti naziv i godinu izdavanja)
        if (_maxPregledanihFilmova == _trenutnoPregledanihFilmova)
        {
            return false;

        }
        for (int i = 0; i < _trenutnoPregledanihFilmova; i++)
        {
            if (strcmp(film._naslov, _pregledaniFilmovi[i]._naslov) == 0 && film._godinaObjavljivanja == _pregledaniFilmovi[i]._godinaObjavljivanja)
            {
                cout << "Film je pregledan" << endl;
                return false;
            }
        }
        _pregledaniFilmovi[_trenutnoPregledanihFilmova] = film;
        _trenutnoPregledanihSerija++;
        return true;
    }

    bool DodajSeriju(Serija serija)
    {
        // Funkcija ima za cilj dodavanje nove serije u niz pregldanih.
        // Voditi računa da se ne prekorači kapacitet niza
        // Voditi racuna da se ne mogu dodati dvije iste serije (to su serije koje imaju isti naziv i godinu izdavanja)
        if (_maxPregledanihSerija == _trenutnoPregledanihSerija)
        {
            return false;

        }
        for (int i = 0; i < _trenutnoPregledanihSerija; i++)
        {
            if (strcmp(serija._naslov, _pregledaneSerije[i]._naslov) == 0 && serija._godinaObjavljivanja == _pregledaniFilmovi[i]._godinaObjavljivanja)
            {
                cout << "Film je pregledan" << endl;
                return false;
            }
        }
        _pregledaneSerije[_trenutnoPregledanihSerija] = serija;
        _trenutnoPregledanihSerija++;
        return true;

    }

    Film* GetNajnovijiFilm()
    {
        // Funkcija kao rezultat vraća pokazivač na najnoviji film kojeg je korisnik odgledao
        if (_trenutnoPregledanihFilmova == 0) {
            return nullptr;
        }

        int najvecaGodina = INT_MIN;  // 2011
        int pozicija = 0;

        for (int i = 0; i < _trenutnoPregledanihFilmova; i++)// 2011 2023 2007 2013 1231 123 123 213 123 123 1231231 
        {
            if (_pregledaniFilmovi[i]._godinaObjavljivanja > najvecaGodina) { // 2007 > 2023
                najvecaGodina = _pregledaniFilmovi[i]._godinaObjavljivanja; // 2023
                pozicija = i;                                              // 1
            }
        }

        return new Film(_pregledaniFilmovi[pozicija]);


    }

    Serija* GetNajboljaSerija()
    {
        // Funkcija kao rezultat vraća pokazivač na seriju sa najvećom ocjenom koju je korisnik odgledao
        if (_trenutnoPregledanihSerija == 0) {
            return nullptr;
        }

        int najboljaSerija = INT_MIN;
        int pozicija = 0;

        for (int i = 0; i < _trenutnoPregledanihSerija; i++)
        {
            if (_pregledaneSerije[i]._ocjena > najboljaSerija) { // 9 > 9
                najboljaSerija = _pregledaneSerije[i]._ocjena;
                pozicija = i;
            }
        }
        return new Serija(_pregledaneSerije[pozicija]);


    }
};

void main()
{
  

    Serija serija("Kill Bill", "Akcija", 2020, 5,54,3);
    cout << serija;
    system("PAUSE>0");
}


#include <iostream>
#include<vector>
#include<sstream>
#include<regex>
#include<iomanip>
#include<string>


using namespace std;

string crt = "\n---------------------------------------------------------------------------------\n";

string PORUKA_TELEFON = crt +
"TELEFONE ISKLJUCITE I ODLOZITE U TORBU, DZEP ILI DRUGU LOKACIJU VAN " +
"DOHVATA.\n" +
"CESTO SE NA TELEFONIMA (PRO)NALAZE PROGRAMSKI KODOVI KOJI MOGU BITI " +
"ISKORISTENI ZA\n" +
"RJESAVANJE ISPITNOG ZADATKA, STO CE, U SLUCAJU PRONALASKA, BITI " +
"SANKCIONISANO.\n\n" +
"SVI KOD KOJIH BUDE PRONADJEN TELEFON ILI NEKI DRUGI UREDJAJ KOJI MOZE " +
"SADRZAVATI\n" +
"MATERIJAL ILI RJESENJA ISPITNIH ZADATAKA CE BITI UDALJENI SA ISPITA I " +
"BIT CE POKRENUT\n" +
"POSTUPAK PROTIV NJIH" + crt;

string PORUKA_ISPIT = crt +
"0. PROVJERITE DA LI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n" +
"1. SVE KLASE SA DINAMICKOM ALOKACIJOM MORAJU IMATI ISPRAVAN " +
"DESTRUKTOR\n" +
"2. IZOSTAVLJANJE DESTRUKTORA ILI NJEGOVIH DIJELOVA BIT CE OZNACENO " +
"KAO TM\n" +
"3. ATRIBUTI, METODE I PARAMETRI MORAJU BITI IDENTICNI ONIMA U TESTNOJ " +
"MAIN FUNKCIJI,\n" +
" OSIM AKO POSTOJI JASNO OPISAN RAZLOG ZA MODIFIKACIJU\n" +
"4. IZUZETKE BACAJTE SAMO TAMO GDJE JE IZRICITO NAGLASENO\n" +
"5. SVE METODE KOJE SE POZIVAJU U MAIN-U MORAJU POSTOJATI.\n" +
" AKO NEMATE ZELJENU IMPLEMENTACIJU, OSTAVITE PRAZNO TIJELO ILI " +
"VRATITE DEFAULT VRIJEDNOST\n" +
"6. U MAIN FUNKCIJI MOZETE DODAVATI TESTNE PODATKE I POZIVE PO " +
"VLASTITOM IZBORU\n" +
"7. TESTIRAJTE PROGRAM U OBA MODA (F5 i Ctrl+F5)" + crt;


char* AlocirajTekst(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;

    size_t velicina = strlen(tekst) + 1;
    char* noviTekst = new char[velicina];

    strcpy_s(noviTekst, velicina, tekst);

    return noviTekst;
}



enum VrstaDostave {
    STANDARDNA,
    BRZA,
    MEDJUNARODNA
};

const char* VrstaDostaveOznake[] = {
    "ST",
    "BR",
    "MD"
};

const char* VrstaDostaveNazivi[] = {
    "STANDARDNA",
    "BRZA",
    "MEDJUNARODNA"
};


enum StatusPosiljke {
    KREIRANA,
    PREUZETA,
    U_TRANZITU,
    ISPORUCENA,
    OTKAZANA
};

const char* StatusPosiljkeNazivi[] = {
    "KREIRANA",
    "PREUZETA",
    "U TRANZITU",
    "ISPORUCENA",
    "OTKAZANA"
};
ostream& operator <<(ostream& COUT, const StatusPosiljke& obj)
{
    COUT << StatusPosiljkeNazivi[obj];
    return COUT;
}

/*
   Funkcija GenerisiOznaku generise oznaku posiljke u formatu: BH-VD-BBBB-IN
   Potpis funkcije treba biti:
   string GenerisiOznaku(const char* imePrezime, int redniBroj,
   VrstaDostave vrstaDostave)
   BH -> fiksna oznaka drzave,
   VD -> vrsta dostave: ST (standardna), BR (brza), MD (medjunarodna),
   BBBB -> redni broj posiljke popunjen nulama na slobodnim mjestima,
   IN -> inicijali imena i prezimena primaoca.
   Kod imena koje sadrzi vise rijeci koriste se inicijal prve i posljednje
   rijeci. Redni broj mora biti u rasponu 1-9999.
   Za neispravne podatke funkcija vraca "BH-XX-0000-XX".
   */

string GenerisiOznaku(const char* imePrezime, int redniBroj, VrstaDostave vrstaDostave)
{
    ostringstream ss;
    

    char ime = imePrezime[0];
    string prezime = imePrezime;
    ss << "BH-" << VrstaDostaveOznake[vrstaDostave] << "-";
    ss << setfill('0') << setw(4) << redniBroj << "-";
    ss << ime << prezime[prezime.rfind(' ') + 1]<<"";
    
    return ss.str();
}


/*
Koristeci regex, funkcija ValidirajOznaku provjerava da li je oznaka
zapisana u prethodno definisanom formatu. Dozvoljene su iskljucivo oznake
vrsta ST, BR i MD, redni broj mora imati cetiri cifre i ne moze biti 0000,
a inicijali moraju biti zapisani velikim slovima.
Potpis funkcije treba biti:
bool ValidirajOznaku(const string& oznaka)
*/

bool ValidirajOznaku(const string& oznaka) {
    regex sifra("BH-(ST|BR|MD)-(?!0000)([0-9]{4})-([A-Z]{2})");
    return regex_match(oznaka, sifra);
}
template<class T1, class T2, int max>
class Kolekcija {
    T1* _elementi1[max];
    T2* _elementi2[max];
    int _trenutno;

public:
    Kolekcija() : _trenutno(0) {
        for (int i = 0; i < max; i++) {
            _elementi1[i] = nullptr;
            _elementi2[i] = nullptr;
        }
    }
    Kolekcija(const Kolekcija& obj)
    {
        for (int i = 0; i < _trenutno; i++) 
        {
            _elementi1[i] = nullptr;
            _elementi2[i] = nullptr;


           
        }

        _trenutno = obj._trenutno;

        for (int i = 0; i < _trenutno; i++)
        {
            _elementi1[i] = new T1(*obj._elementi1[i]);
            _elementi2[i] = new T2(*obj._elementi2[i]);
        }
    }
    Kolekcija& operator =(const Kolekcija& obj)
    {
        if (this != &obj)
        {
            for (int i = 0; i < _trenutno; i++) {
                delete _elementi1[i];
                delete _elementi2[i];

                _elementi1[i] = nullptr;
                _elementi2[i] = nullptr;
            }


            _trenutno = obj._trenutno;
            for (int i = 0; i < _trenutno; i++)
            {
                _elementi1[i] = new T1(*obj._elementi1[i]);
                _elementi2[i] = new T2(*obj._elementi2[i]);
            }
        }
        return *this;
    }
    int GetTrenutno() const {
        return _trenutno;
    }

    T1& GetElement1(int indeks) {
        return *_elementi1[indeks];
    }

    T2& GetElement2(int indeks) {
        return *_elementi2[indeks];
    }

    const T1& GetElement1(int indeks) const {
        return *_elementi1[indeks];
    }

    const T2& GetElement2(int indeks) const {
        return *_elementi2[indeks];
    }

    T1& operator[](int indeks) {
        return *_elementi1[indeks];
    }

    friend ostream& operator<<(ostream& COUT, const Kolekcija& obj) {
        for (int i = 0; i < obj.GetTrenutno(); i++)
            COUT << obj.GetElement1(i) << " "
            << obj.GetElement2(i) << endl;

        return COUT;
    }

    ~Kolekcija() {
        for (int i = 0; i < _trenutno; i++) {
            delete _elementi1[i];
            delete _elementi2[i];

            _elementi1[i] = nullptr;
            _elementi2[i] = nullptr;
        }

        _trenutno = 0;
    }

    void Dodaj(T1 el1, T2 el2)
    {
        if (_trenutno >= max)
        {
            return;
        }
        _elementi1[_trenutno] = new T1(el1);
        _elementi2[_trenutno] = new T2( el2);

        _trenutno++;
    }

    /*
   DodajNaPoziciju dodaje novi par na lokaciju/indeks definisanu
   prvim parametrom,
   pomjera postojece pokazivace udesno i vraca trenutno stanje
   kolekcije (izmijenjeni tj. prosireni objekat).
   U slucaju popunjene kolekcije ili neispravne lokacije potrebno je
   baciti izuzetak.
   */

    Kolekcija& DodajNaPoziciju(int pozicija, T1 el1, T2 el2)
    {
        if (_trenutno >= max || pozicija < 0 || pozicija > _trenutno)
            throw exception("Kolekcija je puna ili je pozicija nevalidna.");
        

        for (int i = _trenutno; i >pozicija; i--)
        {
            _elementi1[i] = _elementi1[i - 1];
            _elementi2[i] = _elementi2[i - 1];
        }
        _elementi1[pozicija] = new T1(el1);
        _elementi2[pozicija] = new T2(el2);

        _trenutno++;
        return *this;
    }

    /*
   UkloniSaPozicije uklanja par sa proslijedjene pozicije/indeksa,
   preostale elemente
   pomjera ulijevo i vraca uklonjeni par u obliku pair<T1, T2>.
   Za poziciju izvan opsega baca se izuzetak.
   */

    pair<T1, T2> UkloniSaPozicije(int pos)
    {
        pair<T1, T2> par;
        if (pos < 0 || pos >= _trenutno)
            throw exception("invalid pos");


        par.first = *_elementi1[pos];
        par.second = *_elementi2[pos];

        delete _elementi1[pos];
        delete _elementi2[pos];

        for (int i = pos; i < _trenutno-1; i++)
        {
            _elementi1[i] = _elementi1[i + 1];
            _elementi2[i] = _elementi2[i + 1];
        }

        _elementi1[_trenutno - 1] = nullptr;
        _elementi2[_trenutno - 1] = nullptr;
        _trenutno--;

        return par;
    }
};


class DatumVrijeme {
    int* _dan, * _mjesec, * _godina, * _sati, * _minute;

public:
    DatumVrijeme(
        int dan = 1,
        int mjesec = 1,
        int godina = 2000,
        int sati = 0,
        int minute = 0) {

        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
        _sati = new int(sati);
        _minute = new int(minute);
    }


    DatumVrijeme(const DatumVrijeme& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
        _sati = new int(*obj._sati);
        _minute = new int(*obj._minute);
    }

    DatumVrijeme& operator=(const DatumVrijeme& obj) {
        if (this == &obj) return *this;
        delete _dan;
        delete _mjesec;
        delete _godina;
        delete _sati;
        delete _minute;

        _dan = _mjesec = _godina = _sati = _minute = nullptr;

        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
        _sati = new int(*obj._sati);
        _minute = new int(*obj._minute);
        return *this;
    }

    friend ostream& operator<<(ostream& COUT, const DatumVrijeme& obj) {
        //ToString vraca datum i vrijeme u formatu DD.MM.GGGG HH:MM,
        COUT << obj.ToString();

        return COUT;
    }

    ~DatumVrijeme() {
        delete _dan;
        delete _mjesec;
        delete _godina;
        delete _sati;
        delete _minute;

        _dan = _mjesec = _godina = _sati = _minute = nullptr;
    }


    string ToString() const {
        ostringstream buffer;

        buffer << setfill('0') << setw(2) << *_dan << ".";
        buffer << setfill('0') << setw(2) << *_mjesec << ".";
        buffer << setfill('0') << setw(4) << *_godina << " ";

        buffer << setfill('0') << setw(2) << *_sati << ":";
        buffer << setfill('0') << setw(2) << *_minute;


        return buffer.str();
    }

    bool operator>(const DatumVrijeme& obj) const {
        if (*_godina != *obj._godina)
            return *_godina > *obj._godina;

        if (*_mjesec != *obj._mjesec)
            return *_mjesec > *obj._mjesec;

        if (*_dan != *obj._dan)
            return *_dan > *obj._dan;

        if (*_sati != *obj._sati)
            return *_sati > *obj._sati;

        return *_minute > *obj._minute;
    }

    bool operator==(const DatumVrijeme& obj) const 
    {
        return (*_godina == *obj._godina && *_mjesec == *obj._mjesec && *_dan == *obj._dan && *_sati == *obj._sati && *_minute == *obj._minute);
    }
};


class Posiljka {
    char* _oznaka;
    char* _sadrzaj;
    char* _imePrezimePrimaoca;
    char* _emailPrimaoca;
    VrstaDostave _vrstaDostave;
    int _redniBroj;

    Kolekcija<StatusPosiljke, DatumVrijeme, 10> _statusi;

    void Dealociraj() {
        delete[] _oznaka;
        delete[] _sadrzaj;
        delete[] _imePrezimePrimaoca;
        delete[] _emailPrimaoca;

        _oznaka = _sadrzaj = _imePrezimePrimaoca =
            _emailPrimaoca = nullptr;
    }

public:
    Posiljka(const char* sadrzaj,const char* imeprezime,const char* email,VrstaDostave vrstadostave,int rednibroj,const DatumVrijeme& vrijeme)
    {
        _oznaka = AlocirajTekst(GenerisiOznaku(imeprezime, rednibroj, vrstadostave).c_str());
        _sadrzaj = AlocirajTekst(sadrzaj);
        _imePrezimePrimaoca = AlocirajTekst(imeprezime);
        _emailPrimaoca = AlocirajTekst(email);
        _vrstaDostave = vrstadostave;
        _redniBroj = rednibroj;
        _statusi.Dodaj(KREIRANA, vrijeme);
    }

    Posiljka(const Posiljka& obj)
    {
        _oznaka = AlocirajTekst(obj._oznaka);
        _sadrzaj = AlocirajTekst(obj._sadrzaj);
        _imePrezimePrimaoca = AlocirajTekst(obj._imePrezimePrimaoca);
        _emailPrimaoca = AlocirajTekst(obj._emailPrimaoca);
        _vrstaDostave = obj._vrstaDostave;
        _redniBroj = obj._redniBroj;
        _statusi = obj._statusi;
    }
    Posiljka& operator=(const Posiljka& obj) {
        if (this != &obj) {

            delete[] _oznaka;
            delete[] _sadrzaj;
            delete[] _imePrezimePrimaoca;
            delete[] _emailPrimaoca;


            _oznaka = AlocirajTekst(obj._oznaka);
            _sadrzaj = AlocirajTekst(obj._sadrzaj);
            _imePrezimePrimaoca = AlocirajTekst(obj._imePrezimePrimaoca);
            _emailPrimaoca = AlocirajTekst(obj._emailPrimaoca);
            _vrstaDostave = obj._vrstaDostave;
            _redniBroj = obj._redniBroj;
            _statusi = obj._statusi;
        }
        return *this;
    }

    const char* GetOznaka() const {
        return _oznaka;
    }

    const char* GetSadrzaj() const {
        return _sadrzaj;
    }

    const char* GetImePrezimePrimaoca() const {
        return _imePrezimePrimaoca;
    }

    const char* GetEmailPrimaoca() const {
        return _emailPrimaoca;
    }

    VrstaDostave GetVrstaDostave() const {
        return _vrstaDostave;
    }

    int GetRedniBroj() const {
        return _redniBroj;
    }

    Kolekcija<StatusPosiljke, DatumVrijeme, 10>& GetStatusi() {
        return _statusi;
    }

    StatusPosiljke GetTrenutniStatus() const {
        return _statusi.GetElement1(_statusi.GetTrenutno() - 1);
    }

    friend ostream& operator<<(ostream& COUT, const Posiljka& obj) {
         /*ToString vraca podatke u formatu:
         oznaka | ime i prezime | vrsta dostave | sadrzaj | trenutni status
         BH-BR-0042-AB | Amina Buric | BRZA | Dokumenti | KREIRANA*/

        COUT << obj.ToString();

        return COUT;
    }
    string ToString()const
    {
        ostringstream ss;

        ss << _oznaka << " | " << _imePrezimePrimaoca << " | " << VrstaDostaveNazivi[_vrstaDostave] << " | " << _sadrzaj << " | " << GetTrenutniStatus();

        return ss.str();
    }

    ~Posiljka() {
        Dealociraj();
    }
    ///*
   //DodajStatus dodaje status samo ako je vrijeme vece od vremena
   //posljednjeg statusa i ako je promjena statusa dozvoljena.
   //Dozvoljen slijed statusa je: KREIRANA -> PREUZETA -> U_TRANZITU ->
   //ISPORUCENA
   //OTKAZANA se moze evidentirati iz bilo kojeg statusa koji nije zavrsni.
   //Nakon statusa ISPORUCENA ili OTKAZANA nisu dozvoljene nove promjene.
   //Preskakanje, ponavljanje statusa i hronoloski neispravno vrijeme vracaju
   //false, bez izmjene kolekcije statusa.
   //*/

    bool DodajStatus(StatusPosiljke novistatus, DatumVrijeme datumvrijeme)
    {
        StatusPosiljke trenutniStatus = GetTrenutniStatus();
        DatumVrijeme trenutnoDatumVrijeme = _statusi.GetElement2(_statusi.GetTrenutno()-1);


        if (!(datumvrijeme > trenutnoDatumVrijeme))
        {
            return false;
        }

        if (trenutniStatus == ISPORUCENA || trenutniStatus == OTKAZANA)
        {
            return false;
        }

        // 4) OTKAZANA se smije dodati iz bilo kojeg NEZAVRSNOG statusa
        if (novistatus == OTKAZANA) {
            _statusi.Dodaj(novistatus, datumvrijeme);
            return true;
        }

        if (trenutniStatus == KREIRANA && novistatus == PREUZETA) {

            _statusi.Dodaj(novistatus, datumvrijeme);
            return true;

        }
        else if (trenutniStatus == PREUZETA && novistatus == U_TRANZITU) {

            _statusi.Dodaj(novistatus, datumvrijeme);
            return true;

        }
        else if (trenutniStatus == U_TRANZITU && novistatus == ISPORUCENA) {

            _statusi.Dodaj(novistatus, datumvrijeme);
            return true;

        }
        else {

            return false;
        }
    }
};


class DostavnaSluzba {
    char* _naziv;
    vector<Posiljka> _posiljke;

public:
    DostavnaSluzba(const char* naziv = "") {
        _naziv = AlocirajTekst(naziv);
    }
    DostavnaSluzba(const DostavnaSluzba& obj)
    {
        _naziv = AlocirajTekst(obj._naziv);
        _posiljke = obj._posiljke;
    }
    DostavnaSluzba& operator = (const DostavnaSluzba& obj) {
        if (this != &obj) {

            delete[] _naziv;


            _naziv = AlocirajTekst(obj._naziv);
            _posiljke = obj._posiljke;

        }
        return *this;
    }

    const char* GetNaziv() const {
        return _naziv;
    }

    vector<Posiljka>& GetPosiljke() {
        return _posiljke;
    }

    ~DostavnaSluzba() {
        delete[] _naziv;
        _naziv = nullptr;
    }
    /*
   DodajPosiljku dodaje posiljku u dostavnu sluzbu. Nije dozvoljeno dodati
   dvije posiljke sa istim rednim brojem ili istom oznakom. U slucaju
   duplikata metoda baca izuzetak.
   */

    void DodajPosiljku(Posiljka posiljka)
    {
        
        for (auto& p : _posiljke)
        {
            if (p.GetRedniBroj() == posiljka.GetRedniBroj() || strcmp(p.GetOznaka(),posiljka.GetOznaka())==0)
            {
                throw exception("ne mozeeeeee");
            }
        }

        _posiljke.push_back(posiljka);
    }

    ///*
    //PronadjiPosiljku vraca pokazivac na posiljku sa proslijedjenom oznakom.
    //Ako posiljka nije pronadjena, metoda vraca nullptr.
    //*/

    Posiljka* PronadjiPosiljku(string oznaka)
    {
        Posiljka* posiljka;

        for (auto& p : _posiljke)
        {
            if (oznaka== p.GetOznaka())
            {
                return new Posiljka(p);
            }
        }

        return nullptr;
    }

    ///*
     //PosiljkePoStatusu vraca vector pokazivaca na sve posiljke ciji trenutni
     //status odgovara proslijedjenom statusu.
     //*/

    vector<Posiljka*> PosiljkePoStatusu(StatusPosiljke statusposiljke)
    {
        vector<Posiljka*> posiljka;

        for (auto& p : _posiljke)
        {
            if (statusposiljke == p.GetTrenutniStatus())
            {
                posiljka.push_back(&p);
            }
        }

        return posiljka;
    }
    ///*
    //StatistikaPoStatusu vraca kolekciju koja za svaki status,
    //redoslijedom
    //definisanim enumom StatusPosiljke, sadrzi status i broj posiljki koje se
    //trenutno nalaze u tom statusu. U rezultat se dodaje svih pet statusa,
    //ukljucujuci i one za koje je broj posiljki jednak nuli.
    //*/

    Kolekcija<StatusPosiljke, int, 5> StatistikaPoStatusu()
    {
        Kolekcija<StatusPosiljke, int, 5> kolekcija;

        for (int i = 0; i < 5; i++)
        {
            StatusPosiljke status = (StatusPosiljke)i;
            int brojposiljki = 0;

            for (int i = 0; i < _posiljke.size(); i++)
            {
                if (_posiljke[i].GetTrenutniStatus() == status)
                {
                    brojposiljki++;
                }
            }
            kolekcija.Dodaj(status, brojposiljki);
        }
        return kolekcija;
    }
};


const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite da li se svako nasljedjivanje moze "
        << "posmatrati kao polimorfizam i obrnuto? Navedite konkretne "
        << "primjere.\n";

    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}


const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasnite razloge kojima bi se implementator "
        << "klase mogao voditi pri donosenju odluke da sve metode u klasi "
        << "(ne)proglasi virtualnim?\n";

    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}


int main() {
    cout << PORUKA_TELEFON;
    cin.get();

    cout << PORUKA_TELEFON;
    cin.get();

    cout << PORUKA_ISPIT;
    cin.get();

    system("cls");

    cout << GetOdgovorNaPrvoPitanje() << crt;
    cin.get();

    cout << GetOdgovorNaDrugoPitanje() << crt;
    cin.get();


    /*
    Funkcija GenerisiOznaku generise oznaku posiljke u formatu: BH-VD-BBBB-IN
    Potpis funkcije treba biti:
    string GenerisiOznaku(const char* imePrezime, int redniBroj,
    VrstaDostave vrstaDostave)
    BH -> fiksna oznaka drzave,
    VD -> vrsta dostave: ST (standardna), BR (brza), MD (medjunarodna),
    BBBB -> redni broj posiljke popunjen nulama na slobodnim mjestima,
    IN -> inicijali imena i prezimena primaoca.
    Kod imena koje sadrzi vise rijeci koriste se inicijal prve i posljednje
    rijeci. Redni broj mora biti u rasponu 1-9999.
    Za neispravne podatke funkcija vraca "BH-XX-0000-XX".
    */

    if (GenerisiOznaku("Amina Buric", 42, BRZA) == "BH-BR-0042-AB")
        cout << "Oznaka OK" << crt;

    if (GenerisiOznaku("Goran Skondric", 7, STANDARDNA) ==
        "BH-ST-0007-GS")
        cout << "Oznaka OK" << crt;

    if (GenerisiOznaku("Ana Marija Kovac", 156, MEDJUNARODNA) ==
        "BH-MD-0156-AK")
        cout << "Oznaka OK" << crt;

    if (GenerisiOznaku("Amina", 42, BRZA) == "BH-XX-0000-XX" &&
        GenerisiOznaku("Amina Buric", 0, BRZA) == "BH-XX-0000-XX" &&
        GenerisiOznaku("Amina Buric", 10000, BRZA) == "BH-XX-0000-XX" &&
        GenerisiOznaku("Amina Buric", 42, (VrstaDostave)99) ==
        "BH-XX-0000-XX")
        cout << "Neispravni podaci za oznaku OK" << crt;


    /*
    Koristeci regex, funkcija ValidirajOznaku provjerava da li je oznaka
    zapisana u prethodno definisanom formatu. Dozvoljene su iskljucivo oznake
    vrsta ST, BR i MD, redni broj mora imati cetiri cifre i ne moze biti 0000,
    a inicijali moraju biti zapisani velikim slovima.
    Potpis funkcije treba biti:
    bool ValidirajOznaku(const string& oznaka)
    */

    if (ValidirajOznaku("BH-BR-0042-AB"))
        cout << "OZNAKA VALIDNA" << crt;

    if (!ValidirajOznaku("BH-EX-0042-AB") &&
        !ValidirajOznaku("BH-BR-042-AB") &&
        !ValidirajOznaku("BH-BR-0042-Ab") &&
        !ValidirajOznaku("BH-BR-0000-AB") &&
        !ValidirajOznaku("bh-BR-0042-AB"))
        cout << "OZNAKA NIJE VALIDNA" << crt;

    if (ValidirajOznaku(GenerisiOznaku("Maid Ramic", 284, BRZA)))
        cout << "GENERISANA OZNAKA VALIDNA" << crt;


    Kolekcija<int, string, 5> brojevi;

    brojevi.Dodaj(10, "Deset");
    brojevi.Dodaj(20, "Dvadeset");
    brojevi.Dodaj(30, "Trideset");

    cout << brojevi << crt;


    /*
    DodajNaPoziciju dodaje novi par na lokaciju/indeks definisanu
    prvim parametrom,
    pomjera postojece pokazivace udesno i vraca trenutno stanje
    kolekcije (izmijenjeni tj. prosireni objekat).
    U slucaju popunjene kolekcije ili neispravne lokacije potrebno je
    baciti izuzetak.
    */

    Kolekcija<int, string, 5> prosireniBrojevi =
        brojevi.DodajNaPoziciju(1, 15, "Petnaest");

    cout << prosireniBrojevi << crt;


    /*
    UkloniSaPozicije uklanja par sa proslijedjene pozicije/indeksa,
    preostale elemente
    pomjera ulijevo i vraca uklonjeni par u obliku pair<T1, T2>.
    Za poziciju izvan opsega baca se izuzetak.
    */

    pair<int, string> uklonjeni =prosireniBrojevi.UkloniSaPozicije(2);

    cout << "Uklonjeno: " << uklonjeni.first << " "
        << uklonjeni.second << crt;

    cout << "Preostali elementi:" << crt
        << prosireniBrojevi;

    try {
        prosireniBrojevi.UkloniSaPozicije(10);
    }
    catch (exception& e) {
        cout << "Exception: " << e.what() << crt;
    }


    try {
        Kolekcija<int, string, 3> punaKolekcija;

        punaKolekcija.Dodaj(1, "Jedan");
        punaKolekcija.Dodaj(2, "Dva");
        punaKolekcija.Dodaj(3, "Tri");

        punaKolekcija.DodajNaPoziciju(1, 4, "Cetiri");
    }
    catch (exception& e) {
        cout << "Exception: " << e.what() << crt;
    }


    Kolekcija<int, string, 5> kopijaBrojeva = brojevi;

    kopijaBrojeva[0] = 100;

    Kolekcija<int, string, 5> dodijeljeniBrojevi;

    dodijeljeniBrojevi = brojevi;

    dodijeljeniBrojevi[1] = 200;

    cout << "Original:" << crt << brojevi;
    cout << "Kopija:" << crt << kopijaBrojeva;
    cout << "Dodijeljeni objekat:" << crt << dodijeljeniBrojevi;


    DatumVrijeme kreirana(1, 7, 2026, 8, 0);
    DatumVrijeme preuzeta(1, 7, 2026, 9, 0);
    DatumVrijeme tranzit(1, 7, 2026, 10, 0);
    DatumVrijeme isporucena(1, 7, 2026, 11, 0);


    ///*
    //ToString vraca datum i vrijeme u formatu DD.MM.GGGG HH:MM,
    //ukljucujuci
    //pocetne nule.
    //*/

    cout << kreirana.ToString() << crt; //01.07.2026 08:00

    if (preuzeta > kreirana)
        cout << "Vrijeme preuzimanja je nakon vremena kreiranja" << crt;

    DatumVrijeme kopijaPreuzeta(preuzeta);

    if (kopijaPreuzeta == preuzeta && !(kreirana == preuzeta))
        cout << "Provjera vremena, OK." << crt;


    /*
    Konstruktor Posiljke generise oznaku i evidentira pocetni status
    KREIRANA
    sa proslijedjenim vremenom kreiranja.
    */

    Posiljka dokumenti(
        "Dokumenti",
        "Amina Buric",
        "amina@fit.ba",
        BRZA,
        42,
        kreirana
    );

    Posiljka knjige(
        "Knjige",
        "Goran Skondric",
        "goran@fit.ba",
        STANDARDNA,
        7,
        kreirana
    );

    Posiljka oprema(
        "Oprema",
        "Ana Marija Kovac",
        "ana@fit.ba",
        MEDJUNARODNA,
        156,
        kreirana
    );


    ///*
    //ToString vraca podatke u formatu:
    //oznaka | ime i prezime | vrsta dostave | sadrzaj | trenutni status
    //BH-BR-0042-AB | Amina Buric | BRZA | Dokumenti | KREIRANA
    //*/

    cout << dokumenti.ToString() << crt;

    if (dokumenti.ToString() ==
        "BH-BR-0042-AB | Amina Buric | BRZA | Dokumenti | KREIRANA")
        cout << "Posiljka ToString OK" << crt;


    ///*
    //DodajStatus dodaje status samo ako je vrijeme vece od vremena
    //posljednjeg statusa i ako je promjena statusa dozvoljena.
    //Dozvoljen slijed statusa je: KREIRANA -> PREUZETA -> U_TRANZITU ->
    //ISPORUCENA
    //OTKAZANA se moze evidentirati iz bilo kojeg statusa koji nije zavrsni.
    //Nakon statusa ISPORUCENA ili OTKAZANA nisu dozvoljene nove promjene.
    //Preskakanje, ponavljanje statusa i hronoloski neispravno vrijeme vracaju
    //false, bez izmjene kolekcije statusa.
    //*/

    if (dokumenti.DodajStatus(PREUZETA, preuzeta))
        cout << "Status PREUZETA dodan" << crt;

    if (dokumenti.DodajStatus(U_TRANZITU, tranzit))
        cout << "Status U TRANZITU dodan" << crt;

    if (dokumenti.DodajStatus(ISPORUCENA, isporucena))
        cout << "Status ISPORUCENA dodan" << crt;

    if (!dokumenti.DodajStatus(OTKAZANA, isporucena))
        cout << "Promjena zavrsnog statusa nije dozvoljena" << crt;

    if (!knjige.DodajStatus(U_TRANZITU, preuzeta))
        cout << "Preskakanje statusa nije dozvoljeno" << crt;

    if (oprema.DodajStatus(OTKAZANA, preuzeta))
        cout << "Posiljka otkazana" << crt;


    Posiljka kopijaDokumenata = dokumenti;

    cout << kopijaDokumenata << crt;


    DostavnaSluzba brzaPosta("Brza posta");


    /*
    DodajPosiljku dodaje posiljku u dostavnu sluzbu. Nije dozvoljeno dodati
    dvije posiljke sa istim rednim brojem ili istom oznakom. U slucaju
    duplikata metoda baca izuzetak.
    */

    brzaPosta.DodajPosiljku(knjige);
    brzaPosta.DodajPosiljku(oprema);

    try {
        brzaPosta.DodajPosiljku(knjige);
    }
    catch (exception& e) {
        cout << "Exception: " << e.what() << crt;
    }


    ///*
    //PronadjiPosiljku vraca pokazivac na posiljku sa proslijedjenom oznakom.
    //Ako posiljka nije pronadjena, metoda vraca nullptr.
    //*/

    string oznakaKnjige = knjige.GetOznaka();

    Posiljka* pronadjena =
        brzaPosta.PronadjiPosiljku(oznakaKnjige);

    if (pronadjena != nullptr)
        cout << "Pronadjena posiljka: "
        << pronadjena->GetOznaka() << crt;

    if (brzaPosta.PronadjiPosiljku("BH-ST-9999-XX") == nullptr)
        cout << "Nepostojeca posiljka nije pronadjena" << crt;


    ///*
    //EvidentirajStatus pronalazi posiljku na osnovu oznake i pokusava
    //dodati
    //novi status koristeci pravila metode DodajStatus.
    //Nakon svakog uspjesno evidentiranog statusa potrebno je u zasebnom
    //threadu
    //poslati obavijest primaocu. Obavijest se ne salje ako posiljka ne
    //postoji ili status nije dodan, te u tim slucajevima metoda vraca
    //false.
    //Primjer sadrzaja obavijesti:
    //------------------------------------------------------------------
    //---------------
    //To: goran@fit.ba
    //From: info@brzaposta.ba
    //Subject: Promjena statusa posiljke
    //Postovani Goran Skondric,
    //Posiljka BH-ST-0007-GS je promijenila status u PREUZETA.
    //Vrijeme evidentiranja: 01.07.2026 09:00
    //Hvala sto koristite nase usluge.
    //BrzaPosta Tim
    //------------------------------------------------------------------
    //---------------
    //*/

    ////if (brzaPosta.EvidentirajStatus(
    //    oznakaKnjige,
    //    PREUZETA,
    //    preuzeta))
    //    cout << "Status evidentiran i obavijest poslana" << crt;

    //if (!brzaPosta.EvidentirajStatus(
    //    oznakaKnjige,
    //    ISPORUCENA,
    //    isporucena))
    //    cout << "Obavijest nije poslana za neispravnu promjenu "
    //    << "statusa" << crt;

    //if (!brzaPosta.EvidentirajStatus(
    //    "NEPOSTOJECA",
    //    PREUZETA,
    //    preuzeta))
    //    cout << "Obavijest nije poslana za nepostojecu posiljku"
    //    << crt;


    ///*
    //PosiljkePoStatusu vraca vector pokazivaca na sve posiljke ciji trenutni
    //status odgovara proslijedjenom statusu.
    //*/

    vector<Posiljka*> preuzetePosiljke =
        brzaPosta.PosiljkePoStatusu(PREUZETA);

    for (auto posiljka : preuzetePosiljke)
        cout << posiljka->GetOznaka() << " -> "
        << StatusPosiljkeNazivi[
            (int)posiljka->GetTrenutniStatus()
        ]
        << crt;


    ///*
    //StatistikaPoStatusu vraca kolekciju koja za svaki status,
    //redoslijedom
    //definisanim enumom StatusPosiljke, sadrzi status i broj posiljki koje se
    //trenutno nalaze u tom statusu. U rezultat se dodaje svih pet statusa,
    //ukljucujuci i one za koje je broj posiljki jednak nuli.
    //*/

    Kolekcija<StatusPosiljke, int, 5> statistika =
        brzaPosta.StatistikaPoStatusu();

    for (int i = 0; i < statistika.GetTrenutno(); i++)
        cout << StatusPosiljkeNazivi[
            (int)statistika.GetElement1(i)
        ]
        << " -> "
        << statistika.GetElement2(i)
        << crt;


    DostavnaSluzba kopijaSluzbe = brzaPosta;

    cout << kopijaSluzbe.GetNaziv() << " ima "
        << kopijaSluzbe.GetPosiljke().size()
        << " posiljki" << crt;

    cin.get();

    return 0;
}
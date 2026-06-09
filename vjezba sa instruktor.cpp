#include <iostream>
using namespace std;
char* getNizKaraktera(const char* predmet)
{
    if (predmet == nullptr)
    {
        return nullptr;
    }
    int vel = strlen(predmet) + 1;
    char* kopija = new char[vel];
    strcpy_s(kopija, vel, predmet);
    return kopija;
}
class Osoba {
protected:
    char* _imePrezime;
    char* _JMBG;
public:
    Osoba(const char* imeprezime = "---", const char* jmbg = "---")
    {
       
        _imePrezime = getNizKaraktera(imeprezime);
        _JMBG = getNizKaraktera(jmbg);
    }
    Osoba(const Osoba& obj) {
        _imePrezime = getNizKaraktera(obj._imePrezime);
        _JMBG = getNizKaraktera(obj._JMBG);
    }

    Osoba& operator =(const Osoba& obj)
    {
        if (this != &obj)
        {
            delete[]_imePrezime;
            delete[]_JMBG;
            _imePrezime = getNizKaraktera(obj._imePrezime);
            _JMBG = getNizKaraktera(obj._JMBG);
        }
        return *this;
    }

   


    virtual ~Osoba()
    {
        cout << "Bazni destrukotr" << endl;
        delete[]_imePrezime;
        _imePrezime = nullptr;
        delete[]_JMBG;
        _JMBG = nullptr;

    }
    virtual void Test() {
        cout << "BAZNA POCETNA IMPLEMENTACIJA" << endl;
    }

    virtual void Info() = 0;//pure virt info

    void Ispis() {
        cout << _imePrezime << " " << _JMBG << endl;
    }

    friend ostream& operator << (ostream& COUT, Osoba& obj)
    {
        COUT << obj._imePrezime << " " << obj._JMBG << endl;
        return COUT;
    }
};

class Profesor :public Osoba {
public:
    char* _titula;
    Profesor(const char* titula = "prof", const char* imeprezime = "---", const char* jmb = "---") :Osoba(imeprezime,jmb)
    {
        _titula = getNizKaraktera(titula);
       
    }
    Profesor(const Profesor& obj) :Osoba(obj)
    {
        _titula = getNizKaraktera(obj._titula);
    }
    Profesor& operator =(const Profesor& obj)
    {

        if (this != &obj)
        {
            delete[]_titula;

            Osoba::operator=(obj);
            _titula = getNizKaraktera(obj._titula);
        }
        return *this;
    }

    void Test() override {
        cout << "IZVEDENA NAPREDNA IMPLEMENTACIJA" << endl;
    }
    void Info() override{
        cout << *this;
    }
    ~Profesor()
    {
        cout << "Izvedeni destrukotr" << endl;
        delete[]_titula;
        _titula = nullptr;
    }
    friend ostream& operator << (ostream& COUT, Profesor& obj)
    {
        COUT <<obj._titula<<" "<< obj._imePrezime << " " << obj._JMBG << endl;
        return COUT;
    }
};
class Predmet{
    char* _naziv;
    int* _ECTS;
    Profesor* _predmetniProfesor;
};
class Student {
public:
    char* _brojIndeksa;
    Predmet* _polozeno;
    int* _trenutno;
    int _max;
};



int main()
{
    /*Osoba osoba("Vedad Kesk", "324235");*/
Profesor profesor("dr.sc", "Harun Šator", "214312124");
//osoba.Test();
cout << profesor;
profesor.Info();

Osoba* profesorEdgeCase = new Profesor("dr.sc.", "ElmirBabovic", "213412414");
profesorEdgeCase->Info();
delete profesorEdgeCase;
    /*osoba.Ispis();
    cout << osoba;*/

    
    /*
    cout << profesor;
    Profesor profesorkopija = profesor;
    cout << profesorkopija;
    cin.get();*/

}


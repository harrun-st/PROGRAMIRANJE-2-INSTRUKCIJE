#include <iostream>
using namespace std;

//pokazivaci:
    //+alokacija(new)
class Predmet {
public:
    char* _naziv;
    int _ocjena;
    int* _ECTS;

    Predmet() {//default konstruktor
        _ocjena = 5; //kad je int samo = i nesto
        _ECTS = new int(0);
        const char* dftNaziv = "Nema predmeta";

        int vel = strlen(dftNaziv) + 1;
        _naziv = new char[vel];
        strcpy_s(_naziv, vel, dftNaziv);
    }

    void Ispis() {
        cout << "Naziv predmeta " <<_naziv<< endl;
        cout << "ocjena predmeta " << _ocjena<<endl;
        cout << "Ects predmeta " << *_ECTS<<endl;
    }
   
    Predmet(const char* naziv,int ocjena,int ects) { //user defined constructor
        _ocjena = ocjena;
        _ECTS = new int(ects);

        int vel = strlen(naziv) + 1;
        _naziv = new char[vel];
        strcpy_s(_naziv, vel, naziv);
    }
    Predmet(const Predmet& predmet)//copy konstruktor
    {
        _ocjena = predmet._ocjena;
        _ECTS = new int(*predmet._ECTS);
        int vel = strlen(predmet._naziv) + 1;
        _naziv = new char[vel];
        strcpy_s(_naziv, vel, predmet._naziv);
    }

    // predmetOperatorDodjela = predmet1;
    //predmet operator
    Predmet& operator=(const Predmet& predmet) {
        if (this != &predmet)//jel lijeva adresa predmeta jednaka desnoj adresi predmeta
        {
            /*ako nije copy paste sve iz kopy konstruktora*/ _ocjena = predmet._ocjena;
            _ECTS = new int(*predmet._ECTS);
            int vel = strlen(predmet._naziv) + 1;
            _naziv = new char[vel];
            strcpy_s(_naziv, vel, predmet._naziv);
        }
        

        return *this;
    }
    ~Predmet() {//Destruktor TILDA ~

        cout << "DESTRUKTOR SE POZVAO" << endl;
        delete _ECTS;
        _ECTS = nullptr;

        delete[]_naziv;
        _naziv = nullptr;
    }
};
void main()
{
    Predmet predmet0;//<-- sa 0 je dft constr;
    predmet0.Ispis();
    Predmet predmet1("Programiranje II", 9, 7);
    Predmet predmet2("Matematika II", 6, 6);
    Predmet predmet3("WRD", 6, 6);

    Predmet predmetkopija1 = predmet1;

    Predmet predmetOperatorDodjela;
    predmetOperatorDodjela = predmet1;
    predmet1.Ispis();
    predmetOperatorDodjela.Ispis();
   
    system("pause>0");
}



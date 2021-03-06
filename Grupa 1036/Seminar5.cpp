#include "stdafx.h"
#include<iostream>
using namespace std;

class Apartament {
private:
	char* proprietar;
	char adresa[50];
	unsigned int an_constructie;
	char confort;
	int numar_camere;
	double* suprafete;

	const int id;
	static unsigned int numar_apartamente;

public:
	Apartament():id(Apartament::numar_apartamente) {
		this->proprietar = new char[strlen("Anonim") + 1];
		strcpy(this->proprietar, "Anonim");
		strcpy(this->adresa, "necunoscuta");
		this->an_constructie = 2000;
		this->confort = '2';
		this->numar_camere = 0;
		this->suprafete = NULL;
		Apartament::numar_apartamente++;
	}

	void afisare();

	Apartament(char* v_proprietar, char v_adresa[50], unsigned int v_an_constructie,
		char v_confort, int v_nr_camere, double* v_suprafete)
	:id(Apartament::numar_apartamente++){
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->confort = v_confort;
		this->an_constructie = v_an_constructie;
		this->numar_camere = v_nr_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}

	}


	Apartament(char* v_proprietar, char v_adresa[50], char v_confort,
		unsigned int v_an_constructie = 2017)
		:an_constructie(v_an_constructie),
		id(Apartament::numar_apartamente++)
	{
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->confort = v_confort;
		this->numar_camere = 0;
		this->suprafete = NULL;

	}

	Apartament(const Apartament& sursa):
	id(Apartament::numar_apartamente++){
		this->proprietar = new char[strlen(sursa.proprietar) + 1];
		strcpy(this->proprietar, sursa.proprietar);
		strcpy(this->adresa, sursa.adresa);
		this->confort = sursa.confort;
		this->an_constructie = sursa.an_constructie;
		this->numar_camere = sursa.numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = sursa.suprafete[i];
		}
	}

	~Apartament() {
		cout << "In destructor..." << endl;
		if (this->proprietar != NULL) {
			delete[] this->proprietar;
		}
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		Apartament::numar_apartamente--;
	}

	//getteri si setteri
	char* getProprietar() {
		return this->proprietar;
	}
	void setProprietar(char* v_proprietar) {
		if (strlen(v_proprietar) < 5) {
			throw new exception("Nume prea scurt");
		}
		else {
			if (this->proprietar != NULL) {
				delete[] this->proprietar;
			}
			this->proprietar = new char[strlen(v_proprietar) + 1];
			strcpy(this->proprietar, v_proprietar);
		}
	}

	char* getAdresa() {
		return this->adresa;
	}

	int getNumarCamere() {
		return this->numar_camere;
	}

	double* getSuprafete() {
		return this->suprafete;
	}

	void setSuprafete(int v_nr_camere, double* v_suprafete) {
		this->numar_camere = v_nr_camere;
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}
	}

	//getter pt atr constant
	int getId() {
		return this->id;
	}

	//getter si setter pentru atr static
	static unsigned int getNumarApartamente() {
		return Apartament::numar_apartamente;
	}

	static void setNumarApartamente(unsigned int nr) {
		Apartament::numar_apartamente = nr;
	}

	Apartament& operator=(const Apartament& sursa) {
		if (this->proprietar != NULL) {
			delete[] this->proprietar;
		}
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		this->proprietar = new char[strlen(sursa.proprietar) + 1];
		strcpy(this->proprietar, sursa.proprietar);
		strcpy(this->adresa, sursa.adresa);
		this->confort = sursa.confort;
		this->an_constructie = sursa.an_constructie;
		this->numar_camere = sursa.numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = sursa.suprafete[i];
		}

		return *this;
	}

	//supraincarcare operator<<
	/*friend ostream& operator<<(ostream& out, Apartament& a) {
		out << "Id: " << a.id << endl;
		//restul 
		return out;
	}*/

};

ostream& operator<<(ostream& out, Apartament& a) {
	out << "Id: " << a.getId() << endl;

	return out;
}

unsigned int Apartament::numar_apartamente = 0;

void Apartament::afisare() {
	cout << "Id: " << this->id << endl;
	cout << "Proprietar: " << this->proprietar << endl;
	cout << "Adresa: " << this->adresa << endl;
	cout << "An constructie: " << this->an_constructie << endl;
	cout << "Confort: " << this->confort << endl;
	cout << "Numar camere: " << this->numar_camere << endl;
	for (int i = 0; i < this->numar_camere; i++) {
		cout << "Suprafata camerei " << i + 1 << " este: " << this->suprafete[i] << endl;
	}


}

void main()
{
	Apartament::setNumarApartamente(1000);
	Apartament a1;
	a1.afisare();

	Apartament* pa1;
	pa1 = &a1;
	pa1->afisare();

	Apartament* pa2 = new Apartament();
	pa2->afisare();
	delete pa2;

	double v[3] = { 10.5,16.3,12.5 };
	Apartament a2("Irina", "strada x, nr y", 2010, '1', 3, v);
	a2.afisare();

	Apartament* pa3 = new Apartament("Ion", "strada Mihail", 2015, '2', 3, v);
	pa3->afisare();

	Apartament a3("Ion", "strada x", '2');
	a3.afisare();

	Apartament* pa4 = new Apartament("Mihai", "strada y", '1', 2018);
	pa4->afisare();
	delete pa4;

	//setteri
	Apartament a4;
	a4.setProprietar("Abcde");
	double v2[2] = { 10,16 };
	a4.setSuprafete(2, v2);

	//getteri
	cout << "Proprietar: " << a4.getProprietar() << endl;
	cout << "Adresa: " << a4.getAdresa() << endl;
	cout << "Numar camere: " << a4.getNumarCamere() << endl;
	for (int i = 0; i < a4.getNumarCamere(); i++) {
		cout << a4.getSuprafete()[i] << endl;
	}

	Apartament a5 = a4; //apel constructor copiere cu sursa=a4
	a5.afisare();

	Apartament a6(a5); //apel constructor copiere cu sursa=a5
	a6.afisare();

	cout << "Numarul total de apartamente este: "
		<< Apartament::getNumarApartamente() << endl;

	Apartament a7;
	a7 = a6;
	a7.afisare();

	cout << a7;


}
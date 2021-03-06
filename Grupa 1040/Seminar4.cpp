// Seminar4.cpp : Defines the entry point for the console application.
//

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

public:
	Apartament() {
		this->proprietar = new char[strlen("Anonim") + 1];
		strcpy(this->proprietar, "Anonim");
		strcpy(this->adresa, "Necunoscuta");
		this->an_constructie = 2000;
		this->confort = '1';
		this->numar_camere = 0;
		this->suprafete = NULL;
	}
	Apartament(char* v_proprietar, char v_adresa[50],
		unsigned int v_an_constructie, char v_confort,
		int v_nr_camere, double* v_suprafete) {
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->an_constructie = v_an_constructie;
		this->confort = v_confort;
		this->numar_camere = v_nr_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}

	}

	//constructor cu valori implicite pentru an
	Apartament(char* v_proprietar, char v_adresa[50],
		char v_confort, unsigned int v_an_constructie = 2017)
		:an_constructie(v_an_constructie)
	{
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->confort = v_confort;
		this->numar_camere = 0;
		this->suprafete = NULL;
	}

	void afisare() {
		cout << "Proprietar: " << this->proprietar << endl;
		cout << "Adresa: " << this->adresa << endl;
		cout << "An constructie: " << this->an_constructie << endl;
		cout << "Confort: " << this->confort << endl;
		cout << "Numar camere: " << this->numar_camere << endl;
		for (int i = 0; i < this->numar_camere; i++) {
			cout << "Suprafata camerei " << i + 1 << " este:" << this->suprafete[i] << endl;
		}
	}

	//destructor
	~Apartament() {
		cout << "Destructor....." << endl;
		if (this->proprietar != NULL) {
			delete[] this->proprietar;
		}
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
	}


	//getteri si setteri
	char* getProprietar() {
		return this->proprietar;
	}

	void setProprietar(char* v_proprietar) {
		if (strlen(v_proprietar) < 5) {
			throw new exception("Nume prea scurt.");
		}
		else {
			//nu generez memory leak
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

	double* getSuprafete() {
		return this->suprafete;
	}

	int getNumarCamere() {
		return this->numar_camere;
	}

	void setSuprafete(int v_nr_camere, double* v_suprafete) {
		this->numar_camere = v_nr_camere;
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		this->suprafete = new double[v_nr_camere];
		for (int i = 0; i < v_nr_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}
	}

	//constructor de copiere
	Apartament(const Apartament& sursa) {
		this->proprietar = new char[strlen(sursa.proprietar) + 1];
		strcpy(this->proprietar,sursa.proprietar);
		strcpy(this->adresa, sursa.adresa);
		this->an_constructie = sursa.an_constructie;
		this->confort = sursa.confort;
		this->numar_camere = sursa.numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = sursa.suprafete[i];
		}
	}



};


void main()
{
	Apartament a1;
	a1.afisare();

	//un pointer la un obiect existent
	Apartament* pa1;
	pa1 = &a1;
	pa1->afisare();

	Apartament* pa2 = new Apartament();
	pa2->afisare();
	delete pa2;


	cout << "--------------------------------------" << endl;
	double v[2] = {15.6,20.4};
	Apartament a2("Enachescu Irina", "strada x", 2008, '2', 2, v);
	a2.afisare();

	Apartament* pa3 = new Apartament("Ion Popescu", "Bucuresti", 2010, '1', 2, v);
	pa3->afisare();

	Apartament a3("Ion Ion", "strada Apei", '2');
	a3.afisare();

	Apartament a4("Ion Ion Ion", "strada Apei 2", '1', 2001);
	a4.afisare();

	Apartament a5;

	//setteri
	a5.setProprietar("Irina");
	a5.setSuprafete(2, v);

	//getteri
	cout << "Proprietar: " << a5.getProprietar() << endl;
	cout << "Numar camere:" << a5.getNumarCamere() << endl;
	for (int i = 0; i < a5.getNumarCamere(); i++) {
		cout << a5.getSuprafete()[i] << endl;
	}

	Apartament a6 = a5;
	a6.afisare();
	

}


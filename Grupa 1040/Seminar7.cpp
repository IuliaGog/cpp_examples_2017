#include "stdafx.h"
#include<iostream>

using namespace std;
//tip special de data care permite ca o variabila sa aiba un set predefinit
//de constante
enum Combustibil {
	BENZINA,
	GPL,
	DIESEL
};
class Masina {
private:
	const int serie; //constant
	double pret;
	char producator[50]; //sir de caractere alocat static
	char* marca; //sir de caractere alocat dinamic
	int vechime;
	int* km_parcursi; //vector alocat dinamic
	Combustibil combustibil;

	static int nr_masini; //atribut static
public:

	//Constructor cu un parametru
	//atributele constante se initializeaza obligatoriu in lista de initializari a constructorului dupa :
	//daca sunt mai multe atribute constante atunci ele se vor separa prin virgula
	Masina(int v_serie) :serie(v_serie) {
		this->pret = 0;
		strcpy(this->producator, "Necunoscut");
		this->marca = new char[strlen("Necunoscuta") + 1];
		strcpy(this->marca, "Necunoscuta");
		this->vechime = 0;
		this->km_parcursi = NULL;
		this->combustibil = BENZINA;

		//incrementez variabila statica pentru ca s-a creat o masina noua
		Masina::nr_masini++;
	}

	//constructor cu toti parametrii
	Masina(int v_serie, char* v_producator, char* v_marca, double v_pret,
		int v_vechime, int* v_km_parcursi, Combustibil v_combustibil)
		:serie(v_serie) {
		this->pret = v_pret;
		//pentru sirurile de caractere alocate static nu se va aloca memorie in prealabil
		strcpy(this->producator, v_producator);
		//pentru sirurile de caractere alocate dinamic este obligatoriu sa se aloce memorie inainte de initializare
		this->marca = new char[strlen(v_marca) + 1];
		//initializarea sirurilor de caractere se face mereu cu strcpy. Nu se va folosi operatorul = !!!
		strcpy(this->marca, v_marca);
		this->vechime = v_vechime;

		//pentru vectorii alocati dinamic este obligatoriu sa se aloce memorie inainte de initializare
		this->km_parcursi = new int[v_vechime];
		//copierea valorilor de la un vector la altul se va face obligatoriu cu for si nu cu operatorul = !!!
		for (int i = 0; i < v_vechime; i++) {
			this->km_parcursi[i] = v_km_parcursi[i];
		}
		this->combustibil = v_combustibil;

		Masina::nr_masini++;
	}
	//destructor
	//obligatoriu daca avem cel putin un camp alocat dinamic in clasa
	~Masina() {
		if (this->marca != NULL) {
			delete[] this->marca;
		}
		if (this->km_parcursi != NULL) {
			delete[] this->km_parcursi;
		}
		//decrementez variabila statica pentru ca s-a distrus o masina
		Masina::nr_masini--;
	}

	//constructor de copiere
	//permite crearea unui obiect nou pe baza unui obiect existent
	//obligatoriu daca avem cel putin un atribut alocat dinamic in clasa
	Masina(const Masina& sursa):serie(sursa.serie) {
		this->pret = sursa.pret;
		//pentru sirurile de caractere alocate static nu se va aloca memorie in prealabil
		strcpy(this->producator, sursa.producator);
		//pentru sirurile de caractere alocate dinamic este obligatoriu sa se aloce memorie inainte de initializare
		this->marca = new char[strlen(sursa.marca) + 1];
		//initializarea sirurilor de caractere se face mereu cu strcpy. Nu se va folosi operatorul = !!!
		strcpy(this->marca, sursa.marca);
		this->vechime = sursa.vechime;

		//pentru vectorii alocati dinamic este obligatoriu sa se aloce memorie inainte de initializare
		this->km_parcursi = new int[sursa.vechime];
		//copierea valorilor de la un vector la altul se va face obligatoriu cu for si nu cu operatorul = !!!
		for (int i = 0; i < sursa.vechime; i++) {
			this->km_parcursi[i] = sursa.km_parcursi[i];
		}
		this->combustibil = sursa.combustibil;

		Masina::nr_masini++;
	}

	//supraincarcarea operatorului= 
	//obligatoriu daca avem cel putin un atribut alocat dinamic in clasa si dorim sa copiem valorile unui
	//obiect intr-altul
	Masina& operator=(const Masina& sursa) {
		/*pentru ca in obiectul curent atributele sunt deja initalizate se vor face verificari pentru
		a se dezaloca inainte memoria ocupata de atributele care sunt alocate dinamic.
		Se evita astfel crearea de memory leaks.
		*/
		if (this->marca != NULL) {
			delete[] this->marca;
		}
		if (this->km_parcursi != NULL) {
			delete[] this->km_parcursi;
		}
		this->pret = sursa.pret;
		strcpy(this->producator, sursa.producator);
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		this->vechime = sursa.vechime;

		this->km_parcursi = new int[sursa.vechime];
		for (int i = 0; i < sursa.vechime; i++) {
			this->km_parcursi[i] = sursa.km_parcursi[i];
		}
		this->combustibil = sursa.combustibil;
		//returnez mereu obiectul curent, cel in care am copiat valorile din sursa
		return *this;
	}

	//setter pentru marca
	void setMarca(char* v_marca) {
		//verificare ca s-a primit cel putin un caracter pentru marca
		if (strlen(v_marca) > 0) {
			/*pentru ca in obiectul curent marca este deja initalizata se face verificare pentru
			a se dezaloca inainte memoria ocupata de atributul alocat dinamic marca.
			Se evita astfel crearea de memory leaks.
			*/
			if (this->marca != NULL)
			{
				delete[] this->marca;
			}
			this->marca = new char[strlen(v_marca) + 1];
			strcpy(this->marca, v_marca);
		}
		else {
			throw new exception("Lungimea marcii trebuie sa fie de minim un caracter");
		}
	}

	//setter pentru combustibil
	void setCombustibil(Combustibil v_combustibil) {
		this->combustibil = v_combustibil;
	}

	//setter pentru km parcursi
	//Se vor trimite ca parametri atat vectorul cu valori cat si numarul de elemente
	void setKmParcursi(int v_vechime, int* v_km_parcursi) {
		this->vechime = v_vechime;
		//evit memory leaks
		if (this->km_parcursi != NULL) {
			delete[] this->km_parcursi;
		}
		this->km_parcursi = new int[v_vechime];
		for (int i = 0; i < v_vechime; i++) {
			this->km_parcursi[i] = v_km_parcursi[i];
		}
	}

	//getter pentru combustibil
	Combustibil getCombustibil() {
		return this->combustibil;
	}

	//supraincarcarea operatorului << pentru clasa Masina
	friend ostream& operator<<(ostream& out, Masina m) {
		out << "=======================================" << endl;
		out << "Serie: " << m.serie << endl;
		out << "Producator: " << m.producator << endl;
		out << "Marca: " << m.marca << endl;
		out << "Pret: " << m.pret << endl;
		out << "Vechime: " << m.vechime << endl;
		for (int i = 0; i < m.vechime; i++) {
			out << "\t Km parcursi in anul " << i + 1 << " :"
				<< m.km_parcursi[i] << endl;
		}
		out << "Combustibil: ";
		switch (m.combustibil)
		{
		case 0: 
			out << "Benzina" << endl;
			break;
		case 1:
			out << "GPL" << endl;
			break;
		case 2:
			out << "Diesel" << endl;
			break;
		} 
		out << "=======================================" << endl;
		return out;
	}

	//supraincarea operatorului ++ forma prefixata
	//Acesta va creste vechimea cu 1
	//km parcursi pentru ultimul an de vechime adaugat sunt implicit 0
	Masina& operator++() {
		//creez un vector nou de km_parcursi care sa aiba cu un an in plus
		int* v_km_parcursi = new int[this->vechime + 1];
		//copiez valorile existente
		for (int i = 0; i < this->vechime; i++)
		{
			v_km_parcursi[i] = this->km_parcursi[i];
		}
		//includ si km pentru anul recent adaugat
		v_km_parcursi[this->vechime] = 0;
		this->vechime++;
		if (this->km_parcursi != NULL)
		{
			delete[] this->km_parcursi;
		}
		this->km_parcursi = v_km_parcursi;

		return *this;
	}

	//supraincarea operatorului ++ forma postfixata
	//Acesta va creste vechimea cu 1
	//km parcursi pentru ultimul an de vechime adaugat sunt implicit 0
	Masina operator++(int) {
		Masina copie = *this;
		//creez un vector nou de km_parcursi care sa aiba cu un an in plus
		int* v_km_parcursi = new int[this->vechime + 1];
		//copiez valorile existente
		for (int i = 0; i < this->vechime; i++)
		{
			v_km_parcursi[i] = this->km_parcursi[i];
		}
		//includ si km pentru anul recent adaugat
		v_km_parcursi[this->vechime] = 0;
		this->vechime++;
		if (this->km_parcursi != NULL)
		{
			delete[] this->km_parcursi;
		}
		this->km_parcursi = v_km_parcursi;

		return copie;
	}

	//supraincarcarea operatorului +
	//va aduna un double la pretul masinii
	Masina operator+(double v_pret) {
		Masina copie = *this;
		copie.pret += v_pret;
		return copie;
	}

	//supraincarcarea operatorului +
	//primul parametru este pretul si al doilea masina
	friend Masina operator+(double v_pret, Masina& m) {
		Masina copie = m;
		copie.pret += v_pret;
		return copie;
	}

	//supraincarcarea operatorului ==
	//doua masini sunt egale daca au acelasi producator si aceeasi marca
	friend bool operator==(Masina& m1, Masina& m2) {
		return strcmp(m1.producator, m2.producator) == 0
			&& strcmp(m1.marca, m2.marca) == 0;
	}

	//supraincarcarea operatorului >
	//m1>m2 daca pretul lui m1 este mai mare decat pretul lui m2
	friend bool operator>(Masina& m1, Masina& m2) {
		return m1.pret > m2.pret;
	}

	//getter pentru serie
	//cum este constant nu are decat getter
	int getSerie() {
		return this->serie;
	}

	//supraincarcarea operatorului += care aduna un intreg la km parcursi in anul curent
	Masina& operator+=(int v_km) {
		if (this->km_parcursi != NULL && this->vechime > 0) {
			this->km_parcursi[vechime - 1] += v_km;
		}
		return *this;
	}

	//metoda statica prin care se obtine numarul total de masini din aplicatie
	static int getNumarMasini() {
		return Masina::nr_masini;
	}

	//metoda membra a clasei prin care se face o prelucrare a datelor
	//se calculeaza km medii parcursi pe an de o masina
	double nrKmMedii() {
		if (this->vechime > 0) {
			int suma = 0;
			for (int i = 0; i < this->vechime; i++) {
				suma += this->km_parcursi[i];
			}
			return suma / this->vechime;
		}
		else {
			return 0;
		}
	}

	//supraincarcarea operatorului>> pentru a citi de la tastatura o masina
	friend istream& operator>>(istream& in, Masina& m) {
		//nu cer si seria de la tastaura pentru ca eu primesc o masina m, care 
		//are seria setata. Cum e constanta, nu o mai pot schimba.
		cout << "Dati pret: ";
		in >> m.pret;
		cout << "Dati producator: ";
		in.ignore();
		in.getline(m.producator,50);
		char buffer[50];
		cout << "Dati marca: ";
		in.getline(buffer, 50);
		if (m.marca != NULL) {
			delete[] m.marca;
		}
		m.marca = new char[strlen(buffer) + 1];
		strcpy(m.marca, buffer);
		cout << "Dati vechimea: ";
		in >> m.vechime;
		if (m.km_parcursi != NULL) {
			delete[] m.km_parcursi;
		}
		m.km_parcursi = new int[m.vechime];
		for (int i = 0; i < m.vechime; i++) {
			cout << "Dati km parcursi in anul " << i + 1 << ": ";
			in >> m.km_parcursi[i];
		}
		cout << "Dati combustibilul 0-BENZINA, 1-GPL, 2-DIESEL: ";
		int c;
		in >> c;
		switch (c) {
		case 0: 
			m.combustibil = BENZINA;
			break;
		case 1:
			m.combustibil = GPL;
			break;
		case 2:
			m.combustibil = DIESEL;
			break;
		default:
			m.combustibil = BENZINA;
			break;
		}
		return in;
	}

	//supraincarcarea operatorului de cast la double
	operator double() {
		return this->pret;
	}

	//supraincarcarea operatorului index
	int& operator[](int index) {
		if (index < 0 || index >= this->vechime)
		{
			cout << "Index in afara limitelor!" << endl;
			throw new exception("Index in afara limitelor!");
		}
		else
		{
			return this->km_parcursi[index];
		}
	}

	//supraincarcarea operatorului functie
	int operator()(int index) {
		if (index < 0 || index >= this->vechime)
		{
			cout << "Index in afara limitelor!" << endl;
			throw new exception("Index in afara limitelor!");
		}
		else {
			int suma = 0;
			for (int i = 0; i < index; i++) {
				suma += this->km_parcursi[i];
			}
			return suma;
		}
	}
};
//initializarea variabilei statice care numara masinile create in aplicatie
int Masina::nr_masini = 0;
void main()
{
	//Masina m1; //nu trebuie sa poata fi scris
	Masina m2(123); //creeaza o masina cu seria 123
	int v[5] = { 15000,10000,0,1200,1500 };
	Masina* m3 = new Masina(124, "Audi", "A5", 10500, 5, v, BENZINA);
	Masina m4(125);
	m4 = *m3;

	m4.setMarca("A3");
	m4.setCombustibil(GPL);
	int v2[3] = { 18000,25000, 15600};
	m4.setKmParcursi(3, v2);

	cout << m2 << *m3 << m4;
	cout << m4.getCombustibil();

	cout << m4++; //creste vechimea masinii cu un an, pentru care adauga 0 km parcursi
	cout << ++m4; //creste vechimea masinii cu un an, pentru care adauga 0 km parcursi


	m2 = *m3 + 1000.6; //aduna 1000.6 la pretul masinii

	m4 = 1520.3 + m2; //aduna 1520.3 la pretul masinii

	cout << m2 << *m3 << m4;

	if (*m3 == m4) { //doua masini sunt egale daca au acelasi producator si aceeasi marca
		cout << "Masinile sunt la fel!" << endl;
	}
	else {
		cout << "Masinile sunt diferite!" << endl;
	}
	
	if (m2>*m3) {
		cout << "Masina " << m2.getSerie() << " este mai scumpa decat masina " <<
			m3->getSerie() << endl;
	}
	
	m4 += 120; //aduna 120 la km parcursi in anul curent

	cout << "In total in aplicatie sunt: " << Masina::getNumarMasini()
		<< " masini" << endl;

	cout << "Numarul mediu de km parcusi pe an de masina " <<
		m2.getSerie() << " este " << m2.nrKmMedii() << endl;

	cout << (double)m4 << endl; //afiseaza pretul masinii

	cin >> m4;
	cout << m4;

	cout << "Km parcursi in anul 2 " << m2[1] << endl;
	m2[1] = 15000; //modifica nr de km din anul 2 al masinii m2

	cout << m2;

	cout << "Numarul total de km parcursi pana in anul 3 este: "
		<< m2(3) << endl; //operatorul functie
}


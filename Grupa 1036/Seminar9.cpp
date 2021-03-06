#include "stdafx.h"
#include<iostream>

using namespace std;
class Student {
protected:
	char* nume;
	bool integralist;
public:
	Student() {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");
		this->integralist = false;
	}
	Student(char* v_nume, bool v_integralist) {
		this->nume = new char[strlen(v_nume) + 1];
		strcpy(this->nume, v_nume);
		this->integralist = v_integralist;
	}
	Student(const Student& sursa) {
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->integralist = sursa.integralist;
	}
	~Student() {
		cout << "Student destructor..." << endl;
		if (this->nume != NULL) {
			delete[] this->nume;
		}
	}
	Student& operator=(const Student& sursa) {
		if (this->nume != NULL) {
			delete[] this->nume;
		}
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->integralist = sursa.integralist;
		return *this;
	}

	friend ostream & operator<<(ostream & out, Student& s) {
		out << "Nume: " << s.nume << endl;
		out << "Integralist: " << s.integralist << endl;
		return out;
	}
};

class StudentBursier :public Student {
private:
	float bursa;
	int nr_materii;
	char** materii_preferate;
public:
	StudentBursier() :Student() {
		this->bursa = 0;
		this->nr_materii = 0;
		this->materii_preferate = NULL;
	}
	StudentBursier(char* v_nume, bool v_integralist, double v_bursa, int v_nr_materii,
		char** v_materii):Student(v_nume,v_integralist) {
		this->bursa = v_bursa;
		this->nr_materii = v_nr_materii;
		this->materii_preferate = new char*[this->nr_materii];
		for (int i = 0; i < this->nr_materii; i++) {
			this->materii_preferate[i] = new char[strlen(v_materii[i]) + 1];
			strcpy(this->materii_preferate[i], v_materii[i]);
		}
	}

	~StudentBursier() {
		cout << "Student Bursier destructor..." << endl;
		if (this->materii_preferate != NULL) {
			for (int i = 0; i < this->nr_materii; i++) {
				if (this->materii_preferate[i] != NULL) {
					delete[] this->materii_preferate[i];
				}
			}
			delete[] this->materii_preferate;
		}
	}

	friend ostream & operator<<(ostream & out, StudentBursier& sb) {
		out << (Student&)sb;
		out << "Bursa: " << sb.bursa << endl;
		out << "Nr materii preferate: " << sb.nr_materii << endl;
		out << "Materii preferate: " << endl;
		for (int i = 0; i < sb.nr_materii; i++) {
			out << "\t " << sb.materii_preferate[i] << endl;
		}
		return out;
	}

	StudentBursier(const StudentBursier& sursa) :Student(sursa) {
		this->bursa = sursa.bursa;
		this->nr_materii = sursa.nr_materii;
		this->materii_preferate = new char*[this->nr_materii];
		for (int i = 0; i < this->nr_materii; i++) {
			this->materii_preferate[i] = new char[strlen(sursa.materii_preferate[i]) + 1];
			strcpy(this->materii_preferate[i], sursa.materii_preferate[i]);
		}
	}

	StudentBursier& operator=(const StudentBursier& sursa) {
		Student::operator=(sursa);
		if (this->materii_preferate != NULL) {
			for (int i = 0; i < this->nr_materii; i++) {
				if (this->materii_preferate[i] != NULL) {
					delete[] this->materii_preferate[i];
				}
			}
			delete[] this->materii_preferate;
		}
		this->bursa = sursa.bursa;
		this->nr_materii = sursa.nr_materii;
		this->materii_preferate = new char*[this->nr_materii];
		for (int i = 0; i < this->nr_materii; i++) {
			this->materii_preferate[i] = new char[strlen(sursa.materii_preferate[i]) + 1];
			strcpy(this->materii_preferate[i], sursa.materii_preferate[i]);
		}
		return *this;

	}
};

void main()
{
	Student s1;
	Student s2("Popescu Ion", true);
	cout << s1 << s2;

	StudentBursier sb1;
	char* v[3] = {"chimie","biologie", "fizica"};
	StudentBursier sb2("Ionescu Mihai", false, 970.6, 3, v);
	cout << sb1 << sb2;

	StudentBursier sb3 = sb2;
	sb1 = sb3;
	cout << sb1 << sb2 << sb3;
    
}


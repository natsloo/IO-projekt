#include "DodatkowaUsluga.h"

DodatkowaUsluga::DodatkowaUsluga(std::string nazwa, double cena) {
	this->nazwa = nazwa;
	this->cena = cena;
}

std::string DodatkowaUsluga::linia() {
	std::string linia = nazwa + ',' + std::to_string(cena);
	return linia;
}
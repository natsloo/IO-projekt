#include "DodatkowaUsluga.h"

DodatkowaUsluga::DodatkowaUsluga(std::string nazwa, double cena) {
	this->nazwa = nazwa;
	this->cena = cena;
}

std::string DodatkowaUsluga::linia() {
	std::string linia = nazwa + ',' + std::to_string(cena);
	return linia;
}

std::string DodatkowaUsluga::opis() {
	std::string linia = std::to_string(cena) + "    " + nazwa;
	return linia;
}

double DodatkowaUsluga::get_cena() {
	return cena;
}

std::string DodatkowaUsluga::get_nazwa() {
	return nazwa;
}
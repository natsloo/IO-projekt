#include "Pokoj.h"

Pokoj::Pokoj(int numer, int maksymalna_liczba_osob, double cena_za_noc, std::string standard_pokoju) {
	this->numer = numer;
	this->maksymalna_liczba_osob = maksymalna_liczba_osob;
	this->cena_za_noc = cena_za_noc;
	this->standard_pokoju = standard_pokoju;
}

std::string Pokoj::linia() {
	std::string linia = std::to_string(numer) + ',' + std::to_string(maksymalna_liczba_osob) + ',' + std::to_string(cena_za_noc) + ',' + standard_pokoju;
	return linia;
}

std::string Pokoj::opis()
{
	return "Numer pokoju: "+ std::to_string(numer) + ", max liczba osob: " + std::to_string(maksymalna_liczba_osob) + ", cena/noc: " + std::to_string(cena_za_noc) + ", standard: " + standard_pokoju;
}
#include "Pokoj.h"
#include "Rezerwacja.h"

Pokoj::Pokoj(int numer, int maksymalna_liczba_osob, double cena_za_noc, std::string standard_pokoju, std::string status) {
	this->numer = numer;
	this->maksymalna_liczba_osob = maksymalna_liczba_osob;
	this->cena_za_noc = cena_za_noc;
	this->standard_pokoju = standard_pokoju;
	this->niedostepne_daty = Rezerwacja::odczytaj_niedostepne_daty_dla_pokoju(numer);
}

std::string Pokoj::linia() {
	std::string linia = std::to_string(numer) + ',' + std::to_string(maksymalna_liczba_osob) + ',' + std::to_string(cena_za_noc) + ',' + standard_pokoju + ',' + aktualny_status;
	return linia;
}

std::string Pokoj::opis()
{
	return "Numer pokoju: "+ std::to_string(numer) + ", max liczba osob: " + std::to_string(maksymalna_liczba_osob) + ", cena/noc: " + std::to_string(cena_za_noc) + ", standard: " + standard_pokoju;
}

int Pokoj::getNumer()
{
	return numer;
}

int Pokoj::getMaksymalnaLiczbaOsob()
{
	return maksymalna_liczba_osob;
}

double Pokoj::getCenaZaNoc()
{
	return cena_za_noc;
}

std::string Pokoj::getStandardPokoju()
{
	return standard_pokoju;
}

std::vector<Data> Pokoj::getNiedostepneDaty()
{
	return niedostepne_daty;
}

void Pokoj::set_niedostepne(Data d1, Data d2) {
	for (Data d = d1; d <= d2; d++) {
		niedostepne_daty.push_back(d);
	}
}

void Pokoj::przeladuj_pokoj() {
	this->niedostepne_daty = Rezerwacja::odczytaj_niedostepne_daty_dla_pokoju(numer);
}

std::string Pokoj::get_status()
{
	return aktualny_status;
}

void Pokoj::set_status(std::string s)
{
	aktualny_status = s;
}
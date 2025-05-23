//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Gosc.h
//  @ Date : 05.05.2025
//  @ Author : 
//
//


#if !defined(_GOSC_H)
#define _GOSC_H

#include <vector>
#include <memory>
#include <stdlib.h>
#include "Ekran.h"
#include "Uzytkownik.h"
#include "Rezerwacja.h"
#include "KatalogDlaGosci.h"

class Gosc : public Uzytkownik {
private:
	std::vector<Rezerwacja> historia_rezerwacji;
	void przegladaj_katalog();
	void przegladaj_historie_rezerwacji();
	std::shared_ptr<KatalogDlaGosci> katalog;
	void zarezerwuj(Data data_przyjazdu, Data data_wymeldowania, int pokoj);
	void dobierz_uslugi(std::vector<bool>& wybrane);
	std::vector<short> filtruj(std::shared_ptr<Data> data_przyjazdu, std::shared_ptr<Data> data_wymeldowania);
	std::vector<short> zastosuj_filtry(Data data_przyjazdu, Data data_wymeldowania, int min_cena_noc, int max_cena_noc, int min_liczba_osob, std::string standard);
public:
	Gosc();
	~Gosc() = default;
	void gui();
};

#endif  //_GOSC_H

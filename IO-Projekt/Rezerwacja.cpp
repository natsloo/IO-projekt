//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Rezerwacja.cpp
//  @ Date : 05.05.2025
//  @ Author : 
//
//


#include "Rezerwacja.h"
#include "Platnosc.h"
#include "Katalog.h"

Rezerwacja::Rezerwacja(std::string uzytkownik, Data data_przyjazdu, Data data_wymeldowania, std::shared_ptr<Pokoj> pokoj, std::vector<DodatkowaUsluga> dodatkowe_uslugi, std::string status_rezerwacji, double cena, bool nowa, int id)
{
	this->uzytkownik = uzytkownik;
	this->data_przyjazdu = data_przyjazdu;
	this->data_wymeldowania = data_wymeldowania;
	this->pokoj = pokoj;
	this->dodatkowe_uslugi = dodatkowe_uslugi;
	this->status_rezerwacji = status_rezerwacji;
	this->cena = cena;
 
	if (nowa) {
		int id_z_pliku = odczytaj_id_z_pliku();
		this->id = ++id_z_pliku;
		zapisz_id_do_pliku(this->id);
		dopisz_do_pliku();
	}
	else {
		this->id = id;
	}
}

int Rezerwacja::odczytaj_id_z_pliku() {
	std::ifstream p("dane/id.txt");
	std::string linia;
	std::getline(p, linia);
	p.close();
	return stoi(linia);
}

void Rezerwacja::zapisz_id_do_pliku(int id) {
	std::ofstream p("dane/id.txt", std::ios::trunc);
	std::string linia = std::to_string(id);
	p << linia;
	p.close();
}

void Rezerwacja::dopisz_do_pliku() {
	json dus = json::array();
	for (int i = 0; i < dodatkowe_uslugi.size(); i++) {
		dus.push_back({ dodatkowe_uslugi[i].get_nazwa(),dodatkowe_uslugi[i].get_cena() });
	}
	json j;
	j["nazwa uzytkownika"] = uzytkownik;
	j["data przyjazdu"] = Data::data_na_string(data_przyjazdu);
	j["data wymeldowania"] = Data::data_na_string(data_wymeldowania);
	j["pokoj"] = pokoj->getNumer();
	j["dodatkowe uslugi"] = dus;
	j["status"] = status_rezerwacji;
	j["cena"] = cena;
	j["id"] = id;

	json wszystkie_rezerwacje = json::array();
	std::ifstream plik_in("dane/rezerwacje.json");
	if (plik_in.is_open()) {
		plik_in >> wszystkie_rezerwacje;
		if (!wszystkie_rezerwacje.is_array()) {
			wszystkie_rezerwacje = json::array();
		}
		plik_in.close();
	}

	wszystkie_rezerwacje.push_back(j);

	std::ofstream plik_out("dane/rezerwacje.json");
	if (plik_out.is_open()) {
		plik_out << wszystkie_rezerwacje.dump(4);
		plik_out.close();
	}
}

std::vector<Rezerwacja> Rezerwacja::odczytaj_rezerwacje(std::string nazwa_uzytkownika) {
	json wszystkie_rezerwacje = json::array();
	std::ifstream plik_in("dane/rezerwacje.json");
	if (plik_in.is_open()) {
		plik_in >> wszystkie_rezerwacje;
		if (!wszystkie_rezerwacje.is_array()) {
			wszystkie_rezerwacje = json::array();
		}
		plik_in.close();
	}
	std::vector<Rezerwacja> uzytkownik_rez;
	for (auto& w : wszystkie_rezerwacje) {
		if (w["nazwa uzytkownika"] == nazwa_uzytkownika) {
			std::vector<DodatkowaUsluga> dus;  
			for (auto& a : w["dodatkowe uslugi"])
			{
				dus.emplace_back(a[0], a[1]);
			}
			Rezerwacja rez(w["nazwa uzytkownika"], Data(w["data przyjazdu"]), Data(w["data wymeldowania"]), Katalog::get_pokoj_(w["pokoj"]), dus, w["status"], w["cena"], false, w["id"]);  
			uzytkownik_rez.push_back(rez);
		}
	}
	return uzytkownik_rez;
}

std::vector<Rezerwacja> Rezerwacja::odczytaj_wszystkie_rezerwacje() {
	json wszystkie_rezerwacje = json::array();
	std::ifstream plik_in("dane/rezerwacje.json");
	if (plik_in.is_open()) {
		plik_in >> wszystkie_rezerwacje;
		if (!wszystkie_rezerwacje.is_array()) {
			wszystkie_rezerwacje = json::array();
		}
		plik_in.close();
	}
	std::vector<Rezerwacja> rez;
	for (auto& w : wszystkie_rezerwacje) {
		std::vector<DodatkowaUsluga> dus;
		for (auto& a : w["dodatkowe uslugi"])
		{
			dus.emplace_back(a[0], a[1]);
		}
		Rezerwacja r(w["nazwa uzytkownika"], Data(w["data przyjazdu"]), Data(w["data wymeldowania"]), Katalog::get_pokoj_(w["pokoj"]), dus, w["status"], w["cena"], false, w["id"]);
		rez.push_back(r);
	}
	return rez;
}

std::vector<Data> Rezerwacja::odczytaj_niedostepne_daty_dla_pokoju(int numer_pokoju) {
	json wszystkie_rezerwacje = json::array();
	std::ifstream plik_in("dane/rezerwacje.json");
	if (plik_in.is_open()) {
		plik_in >> wszystkie_rezerwacje;
		if (!wszystkie_rezerwacje.is_array()) {
			wszystkie_rezerwacje = json::array();
		}
		plik_in.close();
	}
	std::vector<Data> niedostepne_daty;
	for (auto& w : wszystkie_rezerwacje) {
		if (w["pokoj"] == numer_pokoju && w["status"] != "anulowana") {
			for (Data d = Data(w["data przyjazdu"]); d <= Data(w["data wymeldowania"]); d++) {
				niedostepne_daty.push_back(d);
			}
		}
	}
	return niedostepne_daty;
}

Platnosc Rezerwacja::zaplac() 
{
	this->status_rezerwacji = "oplacona";
	zmien_status_rezerwacji(this->status_rezerwacji);
	return Platnosc(cena, uzytkownik, Data::dzis_timestamp(), this->id);
}

void Rezerwacja::zmien_status_rezerwacji(std::string status_rezerwacji) {
	json wszystkie_rezerwacje = json::array();
	std::ifstream plik_in("dane/rezerwacje.json");
	if (plik_in.is_open()) {
		plik_in >> wszystkie_rezerwacje;
		if (!wszystkie_rezerwacje.is_array()) {
			wszystkie_rezerwacje = json::array();
		}
		plik_in.close();
	}

	for (auto& w : wszystkie_rezerwacje) {
		if (w["id"] == this->id) {
			w["status"] = status_rezerwacji;
			system("pause");
		}
	}

	std::ofstream plik_out("dane/rezerwacje.json");
	if (plik_out.is_open()) {
		plik_out << wszystkie_rezerwacje.dump(4);
		plik_out.close();
	}
}

void Rezerwacja::pokaz_szczegoly() 
{
	std::cout << "\nRezerwacja na termin: " << Data::data_na_string(data_przyjazdu) << " - " << Data::data_na_string(data_wymeldowania) << "\n";
	std::cout << "Pokoj nr: " << pokoj->getNumer() << "\n"; 
	std::cout << "Dodatkowe uslugi:" << "\n";
	std::cout << "Ilosc: " << dodatkowe_uslugi.size() << "\n";
	for (int i = 0; i < dodatkowe_uslugi.size(); i++) {
		std::cout << "\t" << i + 1 << ". " << dodatkowe_uslugi[i].opis() << "\n";
	}
	std::cout << "Cena: " << cena << "\n";
	std::cout << "Status rezerwacji: " << status_rezerwacji << "\n";
	std::cout << "ID: " << id << "\n";

}

void Rezerwacja::anuluj() 
{
	this->status_rezerwacji = "anulowana";
	zmien_status_rezerwacji(this->status_rezerwacji);
	Katalog::przeladuj_pokoje();
}

Data Rezerwacja::get_data_przyjazdu() {
	return data_przyjazdu;
}

Data Rezerwacja::get_data_wymeldowania() {
	return data_wymeldowania;
}

std::string Rezerwacja::getStatusRezerwacji() {
	return status_rezerwacji;
}

void Rezerwacja::setStatusRezerwacji(std::string status) {
	status_rezerwacji = status;
}

int Rezerwacja::get_id() {
	return id;
}

std::string Rezerwacja::get_gosc()
{
	return this->uzytkownik;
}

std::shared_ptr<Pokoj> Rezerwacja::get_pokoj()
{
	return pokoj;
}
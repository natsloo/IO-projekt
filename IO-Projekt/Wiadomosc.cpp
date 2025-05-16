#include "Wiadomosc.h"



Wiadomosc::Wiadomosc(std::string nadawca, std::string adresat, std::string temat, std::vector<std::string> tresc, Data data_wyslania, bool zapisz) {
	this->nadawca = nadawca;
	this->adresat = adresat;
	this->temat = temat;
	this->tresc = tresc;
	this->data_wyslania = data_wyslania;
	/*std::cout << this->nadawca << " " << this->adresat << " " << Data::data_na_string(data_wyslania) << "\n";
	for (auto& l : tresc) {
		std::cout << l << "\n";
	}*/
	if (zapisz) {
		dopisz_do_pliku();
	}
}

void Wiadomosc::dopisz_do_pliku() {
	json j;
	//json j_vec(tresc);
	j["nadawca"] = nadawca;
	j["adresat"] = adresat;
	j["temat"] = temat;
	j["data"] = Data::dzis_timestamp();
	j["tresc"] = tresc;

	json wszystkie_wiadomosci = json::array();
	std::ifstream plik_in("dane/wiadomosc.json");
	if (plik_in.is_open()) {
		plik_in >> wszystkie_wiadomosci;
		if (!wszystkie_wiadomosci.is_array()) {
			wszystkie_wiadomosci = json::array();			
		}
		plik_in.close();
	}

	wszystkie_wiadomosci.push_back(j);

	std::ofstream plik_out("dane/wiadomosc.json");
	if (plik_out.is_open()) {
		plik_out << wszystkie_wiadomosci.dump(4);
		plik_out.close();
	}
}

std::pair<std::vector<Wiadomosc>, std::vector<Wiadomosc>> Wiadomosc::odczytaj_wiadomosci(std::string nazwa_uzytkownika) {
	json wszystkie_wiadomosci = json::array();
	std::ifstream plik_in("dane/wiadomosc.json");
	if (plik_in.is_open()) {
		plik_in >> wszystkie_wiadomosci;
		if (!wszystkie_wiadomosci.is_array()) {
			wszystkie_wiadomosci = json::array();
		}
		plik_in.close();
	}
	std::vector<Wiadomosc> wyslane, odebrane;
	for (auto& w : wszystkie_wiadomosci) {
		//std::cout << "ODCZYTUJE Z PLIKU!!!" << w["adresat"] << " " << w["nadawca"] << "\n";
		if (w["adresat"] == nazwa_uzytkownika) {
			Wiadomosc wiad(w["nadawca"], w["adresat"], w["temat"], w["tresc"], Data(w["data"]));
			odebrane.push_back(wiad);
		}
		if (w["nadawca"] == nazwa_uzytkownika) {
			Wiadomosc wiad(w["nadawca"], w["adresat"], w["temat"], w["tresc"], Data(w["data"]));
			wyslane.push_back(wiad);
		}
	}
	return std::pair<std::vector<Wiadomosc>, std::vector<Wiadomosc>>(wyslane, odebrane);
}

std::string Wiadomosc::getAdresat() {
	return adresat;
}

std::string Wiadomosc::getNadawca() {
	return nadawca;
}

std::string Wiadomosc::getTemat() {
	return temat;
}

std::vector<std::string> Wiadomosc::getTresc() {
	return tresc;
}

Data Wiadomosc::getDataWyslania() {
	return data_wyslania;
}
#include "Wiadomosc.h"



Wiadomosc::Wiadomosc(std::string nadawca, std::string adresat, std::vector<std::string> tresc, Data data_wyslania) {
	this->nadawca = nadawca;
	this->adresat = adresat;
	this->tresc = tresc;
	this->data_wyslania = data_wyslania;
	/*std::cout << this->nadawca << " " << this->adresat << " " << Data::data_na_string(data_wyslania) << "\n";
	for (auto& l : tresc) {
		std::cout << l << "\n";
	}*/
	dopisz_do_pliku();
}

void Wiadomosc::dopisz_do_pliku() {
	json j;
	//json j_vec(tresc);
	j["nadwaca"] = nadawca;
	j["adresat"] = adresat;
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
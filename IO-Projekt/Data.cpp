#pragma warning(disable : 4996)
#include "Data.h"

Data::Data()
{

}

Data::Data(int d, int m, int r) {
    this->dzien = d;
    this->miesiac = m;
    this->rok = r;
}

Data::Data(int d, int m, int r, int g, int mi, int s) {
    this->dzien = d;
    this->miesiac = m;
    this->rok = r;
    this->godzina = g;
    this->minuta = mi;
    this->sekunda = s;
}

Data::Data(std::string data) {
    std::stringstream ss(data);
    std::string token;
    std::getline(ss, token, '.');
    int dzien = stoi(token);

    std::getline(ss, token, '.');
    int miesiac = stoi(token);

    std::getline(ss, token, '.');
    int rok = stoi(token);

    this->dzien = dzien;
    this->miesiac = miesiac;
    this->rok = rok;
}

std::string Data::dzis_string() {
    std::time_t current_time = std::time(nullptr);
    char buffer[20];  // 20 - wystarczaj¹cy rozmiar na "YYYY-MM-DD HH:MM:SS"
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", std::localtime(&current_time));
    std::string data = "";
    for (int i = 0; i < 10; i++) {
        data += buffer[i];
    }
    return data;
}

Data Data::dzis() {
    std::time_t current_time = std::time(nullptr);
    char buffer[20];  // 20 - wystarczaj¹cy rozmiar na "YYYY-MM-DD HH:MM:SS"
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", std::localtime(&current_time));
    std::string data = "";
    for (int i = 0; i < 10; i++) {
        data += buffer[i];
    }
    std::stringstream ss(data);
    std::string token;

    std::getline(ss, token, '.');
    int dzien = stoi(token);

    std::getline(ss, token, '.');
    int miesiac = stoi(token);

    std::getline(ss, token, '.');
    int rok = stoi(token);

    return Data(dzien, miesiac, rok);

}

std::string Data::data_na_string(Data d) { // mo¿na siê tu pobawiæ formatem, jeœli bêdzie trzeba - teraz wypisuje np. 03.05.2025 bez zer
    std::string data;
    data = (d.dzien < 10 ? std::to_string(0) : "") + std::to_string(d.dzien) + '.' + (d.miesiac < 10 ? std::to_string(0) : "") + std::to_string(d.miesiac) + '.' + std::to_string(d.rok);
    return data;
}

Data Data::operator+(int dni) const {
    std::tm tm_date = {};
    tm_date.tm_mday = this->dzien + dni;
    tm_date.tm_mon = this->miesiac - 1; // miesi¹ce w tm s¹ liczone od 0
    tm_date.tm_year = this->rok - 1900; // rok to liczba lat od 1900

    // poprawienie ewentualnych b³êdów, np. 32 stycznia -> 1 lutego
    std::mktime(&tm_date);

    return Data(tm_date.tm_mday, tm_date.tm_mon + 1, tm_date.tm_year + 1900);
}

Data Data::operator-(int dni) const {
    std::tm tm_date = {};
    tm_date.tm_mday = this->dzien - dni;
    tm_date.tm_mon = this->miesiac - 1; // miesi¹ce w tm s¹ liczone od 0
    tm_date.tm_year = this->rok - 1900; // rok to liczba lat od 1900

    // poprawienie ewentualnych b³êdów, np. 32 stycznia -> 1 lutego
    std::mktime(&tm_date);

    return Data(tm_date.tm_mday, tm_date.tm_mon + 1, tm_date.tm_year + 1900);
}
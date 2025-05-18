#pragma warning(disable : 4996)
#include "Data.h"

Data::Data()
{

}

Data::Data(int d, int m, int r) {
    if (czy_poprawna_data(d, m, r)) {
        this->dzien = d;
        this->miesiac = m;
        this->rok = r;
    }
}

Data::Data(int d, int m, int r, int g, int mi, int s) {
    if (czy_poprawny_timestamp(d, m, r, g, mi, s)) {
        this->dzien = d;
        this->miesiac = m;
        this->rok = r;
        this->godzina = g;
        this->minuta = mi;
        this->sekunda = s;
    }
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

    if (czy_poprawna_data(dzien, miesiac, rok)) {
        this->dzien = dzien;
        this->miesiac = miesiac;
        this->rok = rok;
    }
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
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y.%H.%M.%S", std::localtime(&current_time));
    std::string data = "";
    for (int i = 0; i < 20; i++) {
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

    std::getline(ss, token, '.');
    int godzina = stoi(token);

    std::getline(ss, token, '.');
    int minuta = stoi(token);

    std::getline(ss, token, '.');
    int sekunda = stoi(token);

    return Data(dzien, miesiac, rok, godzina, minuta, sekunda);

}

std::string Data::data_na_string(Data d) { 
    std::string data;
    data = (d.dzien < 10 ? std::to_string(0) : "") + std::to_string(d.dzien) + '.' + (d.miesiac < 10 ? std::to_string(0) : "") + std::to_string(d.miesiac) + '.' + std::to_string(d.rok);
    return data;
}

std::string Data::dzis_timestamp() {
    std::time_t current_time = std::time(nullptr);
    char buffer[20];  // 20 - wystarczaj¹cy rozmiar na "YYYY-MM-DD HH:MM:SS"
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", std::localtime(&current_time));
    return std::string(buffer);
}

std::string Data::string() { 
    std::string data;
    data = (dzien < 10 ? std::to_string(0) : "") + std::to_string(dzien) + '.' + (miesiac < 10 ? std::to_string(0) : "") + std::to_string(miesiac) + '.' + std::to_string(rok);
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

Data& Data::operator+=(int dni) {
    *this = *this + dni;
    return *this;
}

Data& Data::operator-=(int dni) {
    *this = *this - dni;
    return *this;
}

Data Data::operator++(int) {
    Data kopia = *this;
    *this += 1;
    return kopia;
}

Data Data::operator--(int) {
    Data kopia = *this;
    *this -= 1;
    return kopia;
}

bool Data::operator==(const Data& d) const {
    return dzien == d.dzien &&
        miesiac == d.miesiac &&
        rok == d.rok;
}

bool Data::operator<(const Data& d) const {
    if (rok != d.rok) {
        return rok < d.rok;
    }
    if (miesiac != d.miesiac) {
        return miesiac < d.miesiac;
    }
    return dzien < d.dzien;
}

bool Data::operator<=(const Data& d) const {
    return *this < d || *this == d;
}

bool Data::operator>(const Data& d) const {
    return !(*this <= d);
}

bool Data::operator>=(const Data& d) const {
    return !(*this < d);
}

bool Data::czy_poprawna_data(int d, int m, int r) {
    if (r < 0 || m < 1 || m > 12 || d < 1) {
        return false;
    }
    static const int dni_w_miesiacu[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int max_dni = dni_w_miesiacu[m - 1];

    if (m == 2 && ((r % 4 == 0 && r % 100 != 0) || (r % 400 == 0)))
        max_dni = 29;

    return d <= max_dni;
}

bool Data::czy_poprawny_timestamp(int d, int m, int r, int g, int mi, int s) {
    if (!czy_poprawna_data(d, m, r))
        return false;

    if (g < 0 || g > 23 || mi < 0 || mi > 59 || s < 0 || s > 59)
        return false;

    return true;
}